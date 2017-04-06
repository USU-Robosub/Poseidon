//
//  structDepthMap.cpp
//  StructureForDepthMap
//
//  Created by Aubrey Parker on 2/8/17.


#include "../include/telemetry/DepthMap.h"
#include "catch.hpp"

using namespace slam;

TEST_CASE("DepthMap works as expected") {
    auto test1 = DepthMap(2, 4);
    
    SECTION("The DepthMap constructor works as expected") {
        REQUIRE(test1.getDepth(0, 0) == UNKNOWN_DEPTH);
        REQUIRE(test1.getDepth(0, 3) == UNKNOWN_DEPTH);
        REQUIRE(test1.getDepth(1, 0) == UNKNOWN_DEPTH);
        REQUIRE(test1.getDepth(1, 3) == UNKNOWN_DEPTH);
    }
    
    SECTION("getDepth() and setDepth() work as expected") {
        test1.setDepth(0, 3, 2);
        REQUIRE(test1.getDepth(0, 3) == 2);
        
    }
}

