//
// Created by Kyler Jensen on 4/5/17.
//

#ifndef SLAM_TELEMETRYLISTENER_H
#define SLAM_TELEMETRYLISTENER_H

#include "TelemetryPacket.h"

namespace slam {

    typedef void (*TelemetryListener)(slam::TelemetryPacket);

}

#endif //SLAM_TELEMETRYLISTENER_H
