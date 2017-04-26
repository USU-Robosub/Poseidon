#include "DSOtelemetryProvider.h"

using namespace slam;

unsigned int DSOtelemetryProvider::getFrameCount() {
  return frameCount;
}

TelemetryPacket DSOtelemetryProvider::GetCurrentTelemetry(){
  return collector->GetCurrentTelemetry();
}

bool DSOtelemetryProvider::isEnabled(){
  return lockProcessingThread;
}

void DSOtelemetryProvider::releaseProcessingThread(){
  lockProcessingThread = false;
}

void DSOtelemetryProvider::useThreadToProcessData(){
  lockProcessingThread = true;
  while(lockProcessingThread){
    std::shared_ptr<ICameraFrame> frame = frameStream->getFrame();
    collector->frameWillBeProcessed(frame, frameCount);
    //convert frame to gray scale for DSO
    MinimalImageB minImg(frame->getCols(), frame->getRows(), frame->getData());
  	ImageAndExposure* undistImg = undistorter->undistort<unsigned char>(&minImg, 1,0, 1.0f);
  	fullSystem->addActiveFrame(undistImg, frameCount);
  	frameCount++;
  	delete undistImg;
  }
}

DSOtelemetryProvider::~DSOtelemetryProvider(){
  collector->join();
  delete collector;
  delete undistorter;
  delete fullSystem;
}

DSOtelemetryProvider::DSOtelemetryProvider(IFrameStream* frameStream, std::string cameraCalibrationFile){
  //DSO settings
  multiThreading = false;
  disableAllDisplay = true;
  setting_logStuff = false;
  setting_debugout_runquiet = true;
  setting_render_displayVideo = false;
  setting_desiredImmatureDensity = 1000;
  setting_desiredPointDensity = 1200;
  setting_minFrames = 5;
  setting_maxFrames = 7;
  setting_maxOptIterations=4;
  setting_minOptIterations=1;
  setting_kfGlobalWeight = 1.3;
  setting_photometricCalibration = 0;
  setting_affineOptModeA = 0;
  setting_affineOptModeB = 0;
  //====
  
  this->frameStream = frameStream;
  lockProcessingThread = false;
  frameCount = 0;

  undistorter = Undistort::getUndistorterForFile(cameraCalibrationFile, "", "");
  setGlobalCalib(
            (int)undistorter->getSize()[0],
            (int)undistorter->getSize()[1],
            undistorter->getK().cast<float>());
            
  fullSystem = new FullSystem();
  fullSystem->linearizeOperation=false;

  collector = new DSOcollector();
  fullSystem->outputWrapper.push_back(collector);

  if(undistorter->photometricUndist != 0)
  	fullSystem->setGammaFunction(undistorter->photometricUndist->getG());
}