//
// Created by Kyler Jensen on 3/29/17.
//

#ifndef SLAM_TELEMETRYPROVIDER_H
#define SLAM_TELEMETRYPROVIDER_H

#include "TelemetryPacket.h"
#include "../camera_frame_stream/IFrameStream.h"

namespace slam {

    class TelemetryProvider {

    public:
        TelemetryPacket getCurrentTelemetry();

    };

}


#endif //SLAM_TELEMETRYPROVIDER_H
