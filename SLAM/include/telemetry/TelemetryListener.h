//
// Created by Kyler Jensen on 4/5/17.
//

#ifndef SLAM_TELEMETRYLISTENER_H
#define SLAM_TELEMETRYLISTENER_H

#include "TelemetryPacket.h"
#include <functional>

namespace slam {

    typedef void (*TelemetryListener)(TelemetryPacket);

}


#endif //SLAM_TELEMETRYLISTENER_H
