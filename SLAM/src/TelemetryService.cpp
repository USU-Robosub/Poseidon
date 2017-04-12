//
// Created by Kyler Jensen on 3/29/17.
//

#include "../include/telemetry/TelemetryService.h"
#include "../include/camera_frame_stream/CVFrameStream.h"

using namespace slam;

TelemetryService::TelemetryService() {
    frameStream = make_smart<CVFrameStream>(0);
    runner = make_smart<std::thread>([this](){ run(); }); // spawn new thread that calls run()
}

TelemetryService::~TelemetryService() {
    running = false;
    runner->join();
}

void TelemetryService::run() {
    while(running) {
        auto frame = frameStream->getFrame();
        auto map = DepthMap();
        auto pose = Pose();
        TelemetryPacket packet = { frame, map, pose };
        publish(packet);
        std::this_thread::sleep_for(std::chrono::milliseconds(33)); // pause execution (~30fps)
    }
}
