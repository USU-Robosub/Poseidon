//
// Created by Kyler Jensen on 3/29/17.
//

#ifndef SLAM_TELEMETRYSERVICE_H
#define SLAM_TELEMETRYSERVICE_H

#include <unordered_set>
#include "TelemetryPacket.h"
#include "../camera_frame_stream/IFrameStream.h"
#include "../Observable.h"

namespace slam {

    class TelemetryService : public Observable<TelemetryPacket> {

    private:
        SmartPointer<IFrameStream> frameStream;
        SmartPointer<std::thread> runner;
        bool running = true;
        void run();

    public:
        TelemetryService();
        ~TelemetryService();

    };

}


#endif //SLAM_TELEMETRYSERVICE_H
