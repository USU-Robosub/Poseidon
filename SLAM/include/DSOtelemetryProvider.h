#pragma once

#include <string>
#include "util/settings.h"
#include "FullSystem/FullSystem.h"
#include "util/Undistort.h"
#include "DSOcollector.h"
#include "IFrameStream.h"

namespace slam
{
  class DSOtelemetryProvider{
  private:
    IFrameStream* frameStream;
    bool lockProcessingThread;
    DSOcollector* collector;
    dso::FullSystem* fullSystem = 0;
    dso::Undistort* undistorter = 0;
    unsigned int frameCount;
  public:
    DSOtelemetryProvider(IFrameStream* frameStream, std::string cameraCalibrationFile);
    ~DSOtelemetryProvider();
    void useThreadToProcessData(); // this will stop further execution on the called thread
    void releaseProcessingThread();
    bool isEnabled();
    //bool isTracking();
    //bool isStarting();
    TelemetryPacket GetCurrentTelemetry();
    unsigned int getFrameCount();
  };
}