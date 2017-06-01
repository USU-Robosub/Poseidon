#pragma once
#include "IOWrapper/Output3DWrapper.h"
#include "util/FrameShell.h"
#include "TelemetryPacket.h"
#include <unordered_map>

namespace slam
{
  class DSOcollector : public dso::IOWrap::Output3DWrapper
  {
  public:
    DSOcollector();
    virtual ~DSOcollector();
    virtual void publishGraph(const std::map<uint64_t,Eigen::Vector2i> &connectivity);
    virtual void publishKeyframes( std::vector<dso::FrameHessian*> &frames, bool final, dso::CalibHessian* HCalib);
    virtual void publishCamPose(dso::FrameShell* frame, dso::CalibHessian* HCalib);
    virtual void pushLiveFrame(dso::FrameHessian* image);
    virtual void pushDepthImage(dso::MinimalImageB3* image);
    virtual bool needPushDepthImage();
    virtual void pushDepthImageFloat(dso::MinimalImageF* image, dso::FrameHessian* KF );
    TelemetryPacket GetCurrentTelemetry();
    void frameWillBeProcessed(std::shared_ptr<ICameraFrame> frame, unsigned int uniqueId);
    unsigned int numberOfFramesBeingProcessed();
  private:
    std::unordered_map<unsigned int, std::shared_ptr<ICameraFrame>> framesBeingProcessed; // if some frames are skipped then this buffer my expand forever
    std::unordered_map<unsigned int, TelemetryPacket> underConstructionTelemetryPackets; // if some frames are skipped then this buffer my expand forever
    TelemetryPacket currentTelemetry;
  };
}
