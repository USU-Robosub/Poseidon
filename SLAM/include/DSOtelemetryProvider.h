#pragma once

#include <string>
#include "DSOcollector.h"
#include "IFrameStream.h"

#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//#include <thread>
#include <iostream>
#include <sstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "util/settings.h"
#include "FullSystem/FullSystem.h"
#include "util/Undistort.h"

using namespace cv;
using namespace dso;

namespace slam
{
  class DSOtelemetryProvider{
  private:
    IFrameStream* frameStream;
    bool lockProcessingThread;
    DSOcollector* collector;
    FullSystem* fullSystem = 0;
    Undistort* undistorter = 0;
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