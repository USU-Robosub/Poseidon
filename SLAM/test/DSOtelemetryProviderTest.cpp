#include "catch.hpp"
#include "DSOtelemetryProvider.h"
#include <iostream>
#include <execinfo.h>
#include "_config.h"
#include "GrayscaleCameraFrame.h"

using namespace slam;

class testFrameStream : public IFrameStream {
public:
    virtual const std::shared_ptr<ICameraFrame> getFrame(){
      std::vector<std::vector<uchar>> data = {
              {255, 254},
              {253, 252}
      };
      return std::make_shared<GrayscaleCameraFrame>(data, std::chrono::steady_clock::now());
    }
};
  
TEST_CASE("DSOtelemetryProvider works as expected", "[DSOtelemetryProvider]") {
  
  std::cout << "\\/ Following is output from DSO \\/" << std::endl;
  
  auto dsoTelemetry = DSOtelemetryProvider(new testFrameStream(), TestConfig::testResourcesDirectory() + "/testCameraCalib.txt");
  
  SECTION("DSOtelemetryProvider can be created") {
    
    REQUIRE(!dsoTelemetry.isEnabled());
    
  }
  
  SECTION("DSOtelemetryProvider can be used to process images") {
  
    REQUIRE_NOTHROW(dsoTelemetry.GetCurrentTelemetry());
    
    REQUIRE(dsoTelemetry.getFrameCount() == 0);
  
    std::thread frameThread ([&dsoTelemetry](){dsoTelemetry.useThreadToProcessData();});
    
    while(dsoTelemetry.getFrameCount() < 5) {}
    
    dsoTelemetry.releaseProcessingThread();
    
    frameThread.join();
    
    REQUIRE(dsoTelemetry.getFrameCount() >= 5);
  }
}