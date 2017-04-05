//
// Created by Kyler Jensen on 3/29/17.
//

#ifndef SLAM_TELEMETRYSERVICE_H
#define SLAM_TELEMETRYSERVICE_H

#include <unordered_set>
#include "TelemetryPacket.h"
#include "../camera_frame_stream/IFrameStream.h"
#include "TelemetryListener.h"

namespace slam {

    class TelemetryService {

    private:
        std::unordered_set<TelemetryListener> listeners = std::unordered_set<TelemetryListener>();

    public:
        TelemetryPacket getCurrentTelemetry();
        void subscribe(TelemetryListener listener);
        void unsubscribe(TelemetryListener listener);
        int subscribers() const;

    };

}


#endif //SLAM_TELEMETRYSERVICE_H
