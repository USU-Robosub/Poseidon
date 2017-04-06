//
//  structDepthMap.cpp
//  StructureForDepthMap
//
//  Created by Aubrey Parker on 2/8/17.


#include "../include/DepthMap.h"
#include "catch.hpp"

using namespace slam;

TEST_CASE("Struct for depth Map test"){
    auto test1 = DepthMap(2, 4);
    
    SECTION ("Construter Test"){
        REQUIRE(test1.getDepth(0, 0) == UNKNOWN_DEPTH);
        REQUIRE(test1.getDepth(0, 3) == UNKNOWN_DEPTH);
        REQUIRE(test1.getDepth(1, 0) == UNKNOWN_DEPTH);
        REQUIRE(test1.getDepth(1, 3) == UNKNOWN_DEPTH);
    }
    
    SECTION("Test GetDepth and SetDepth"){
        test1.setDepth(0, 3, 2);
        REQUIRE(test1.getDepth(0, 3) == 2);
        
    }
}

