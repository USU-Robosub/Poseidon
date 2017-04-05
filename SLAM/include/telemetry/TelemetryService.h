//
// Created by Kyler Jensen on 3/29/17.
//

#ifndef SLAM_TELEMETRYSERVICE_H
#define SLAM_TELEMETRYSERVICE_H

#include "TelemetryPacket.h"
#include "../camera_frame_stream/IFrameStream.h"
#include "TelemetryListener.h"

namespace slam {

    class TelemetryService {

    private:
        std::vector<TelemetryListener> listeners = std::vector<TelemetryListener>();

    public:
        TelemetryPacket getCurrentTelemetry();
        void subscribe(TelemetryListener listener);
        void unsubscribe(TelemetryListener listener);
        int subscribers() const;

    };

}


#endif //SLAM_TELEMETRYSERVICE_H
