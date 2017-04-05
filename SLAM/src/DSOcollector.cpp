#include "DSOcollector.h"

slam::DSOcollector::DSOcollector() : 
  underConstructionTelemetryPackets(std::unordered_map<unsigned int, TelemetryPacket>())
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
  const double* rawProjectionMatrix = frame->camToWorld.matrix3x4().data();
  std::shared_ptr<slam::Pose> poseFromMatrix = std::make_shared<slam::Pose>(slam::Pose(rawProjectionMatrix)); 
  delete[] rawProjectionMatrix;
  underConstructionTelemetryPackets[frame->incoming_id].pose = poseFromMatrix;
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
  std::pair<unsigned int, TelemetryPacket> newTelemetryPacket(uniqueId, TelemetryPacket());
  newTelemetryPacket.second.cameraFrame = frame;
  underConstructionTelemetryPackets.insert(newTelemetryPacket);
}

unsigned int slam::DSOcollector::numberOfFramesBeingProcessed()
{
  return underConstructionTelemetryPackets.size();
}

