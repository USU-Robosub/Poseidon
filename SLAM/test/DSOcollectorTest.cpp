#include "catch.hpp"
#include "DSOcollector.h"
#include "RGBCameraFrame.h"
#include <iostream>
#include <execinfo.h>

using namespace slam;

TEST_CASE("DSOcollector works as expected", "[DSOcollector]") {
  
  auto collector = DSOcollector();
  
  SECTION("All of DSOcollector's members were initialized") {

    REQUIRE(!collector.needPushDepthImage());
    
  }
  
  SECTION("All of DSOcollector's functions exist") {
    
    auto frame = std::make_shared<RGBCameraFrame>(640, 480, std::chrono::steady_clock::now());
    
    REQUIRE_NOTHROW(collector.GetCurrentTelemetry());
    
    REQUIRE(collector.numberOfFramesBeingProcessed() == 0);
    
    REQUIRE_NOTHROW(collector.frameWillBeProcessed(frame, 0));
    
    REQUIRE(collector.numberOfFramesBeingProcessed() == 1);
  }
}