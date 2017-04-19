#include <catch.hpp>
#include "../../include/camera_frame_stream/CVFrameStream.h"

using namespace slam;

TEST_CASE("CVFrameStream works as expected") {

    auto frameStream = CVFrameStream(0);

    auto frame = frameStream.getFrame();

    REQUIRE(frame->getColorSpace() == RGB);

    REQUIRE(frame->getCols() > 0);

    REQUIRE(frame->getRows() > 0);

    REQUIRE(*frame->toMat().size.p > 0);

}
