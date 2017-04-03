#include "DSOcollector.h"

slam::DSOcollector::DSOcollector()
{
  printf("OUT: Web output wrapper started\n");
}

slam::DSOcollector::~DSOcollector()
{
  printf("OUT: Web output wrapper closed\n");
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
