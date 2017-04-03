#include "DSOcollector.h"

slam::DSOcollector::DSOcollector() : 
  framesBeingProcessed(std::unordered_map<unsigned int, std::shared_ptr<CameraFrame>>())
{
  
}

slam::DSOcollector::~DSOcollector()
{
  
}

void slam::DSOcollector::publishGraph(const std::map<uint64_t,Eigen::Vector2i> &connectivity)
{

}

void slam::DSOcollector::publishKeyframes( std::vector<dso::FrameHessian*> &frames, bool final, dso::CalibHessian* HCalib)
{

}

void slam::DSOcollector::publishCamPose(dso::FrameShell* frame, dso::CalibHessian* HCalib)
{

}

void slam::DSOcollector::pushLiveFrame(dso::FrameHessian* image)
{

}

void slam::DSOcollector::pushDepthImage(dso::MinimalImageB3* image)
{

}

bool slam::DSOcollector::needPushDepthImage()
{
  return false;
}

void slam::DSOcollector::pushDepthImageFloat(dso::MinimalImageF* image, dso::FrameHessian* KF )
{

}

slam::TelemetryPacket slam::DSOcollector::GetCurrentTelemetry()
{
  return currentTelemetry;
}

void slam::DSOcollector::frameWillBeProcessed(std::shared_ptr<CameraFrame> frame, unsigned int uniqueId)
{
  std::pair<unsigned int, std::shared_ptr<CameraFrame>> newFrame(uniqueId, frame);
  framesBeingProcessed.insert(newFrame);
}

unsigned int slam::DSOcollector::numberOfFramesBeingProcessed()
{
  return framesBeingProcessed.size();
}

