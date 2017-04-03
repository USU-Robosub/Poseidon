#pragma once
//#include "boost/thread.hpp"
#include "util/MinimalImage.h"
#include "IOWrapper/Output3DWrapper.h"
#include <iostream>

#include "FullSystem/HessianBlocks.h"
#include "util/FrameShell.h"

namespace slam
{
  class DSOcollector : public dso::IOWrap::Output3DWrapper
  {
  public:

          inline DSOcollector()
          {
              printf("OUT: Web output wrapper started\n");
          }

          virtual ~DSOcollector()
          {
              printf("OUT: Web output wrapper closed\n");
          }
/*
          virtual void publishGraph(const std::map<uint64_t,Eigen::Vector2i> &connectivity)
          {

          }

          virtual void publishKeyframes( std::vector<FrameHessian*> &frames, bool final, CalibHessian* HCalib)
          {

          }

          virtual void publishCamPose(FrameShell* frame, CalibHessian* HCalib)
          {

          }

          virtual void pushLiveFrame(FrameHessian* image)
          {

          }

          virtual void pushDepthImage(MinimalImageB3* image)
          {

          }
          virtual bool needPushDepthImage()
          {
              return false;
          }

          virtual void pushDepthImageFloat(MinimalImageF* image, FrameHessian* KF )
          {

          }
          */
  };
}
