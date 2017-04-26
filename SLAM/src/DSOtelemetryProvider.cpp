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
    dso::MinimalImageB minImg(frame->getCols(), frame->getRows(), frame->getData());
  	dso::ImageAndExposure* undistImg = undistorter->undistort<unsigned char>(&minImg, 1,0, 1.0f);
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
  dso::multiThreading = false;
  dso::disableAllDisplay = true;
  dso::setting_logStuff = false;
  dso::setting_debugout_runquiet = true;
  dso::setting_render_displayVideo = false;
  dso::setting_desiredImmatureDensity = 1000;
  dso::setting_desiredPointDensity = 1200;
  dso::setting_minFrames = 5;
  dso::setting_maxFrames = 7;
  dso::setting_maxOptIterations=4;
  dso::setting_minOptIterations=1;
  dso::setting_kfGlobalWeight = 1.3;
  dso::setting_photometricCalibration = 0;
  dso::setting_affineOptModeA = 0;
  dso::setting_affineOptModeB = 0;
  //====
  
  this->frameStream = frameStream;
  lockProcessingThread = false;
  frameCount = 0;

  undistorter = dso::Undistort::getUndistorterForFile(cameraCalibrationFile, "", "");
  dso::setGlobalCalib(
            (int)undistorter->getSize()[0],
            (int)undistorter->getSize()[1],
            undistorter->getK().cast<float>());
            
  fullSystem = new dso::FullSystem();
  fullSystem->linearizeOperation=false;

  collector = new DSOcollector();
  fullSystem->outputWrapper.push_back(collector);

  if(undistorter->photometricUndist != 0)
  	fullSystem->setGammaFunction(undistorter->photometricUndist->getG());
}