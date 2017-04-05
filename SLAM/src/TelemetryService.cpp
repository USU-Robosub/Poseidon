//
// Created by Kyler Jensen on 3/29/17.
//

#include "../include/telemetry/TelemetryService.h"

using namespace slam;

TelemetryPacket TelemetryService::getCurrentTelemetry() {
    //TODO Implement this
    throw std::runtime_error("Not implemented.");
}

void TelemetryService::subscribe(TelemetryListener listener) {
    listeners.push_back(listener);
}

void TelemetryService::unsubscribe(TelemetryListener listener) {
    listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

int TelemetryService::subscribers() const {
    return (int) listeners.size();
}
