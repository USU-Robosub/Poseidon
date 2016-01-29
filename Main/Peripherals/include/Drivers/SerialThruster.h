//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_SERIAL_THRUSTER_H
#define PERIPHERALS_SERIAL_THRUSTER_H

#include <IThruster.h>
#include "Serial.h"

enum ThrusterIndex {
    LEFT_FORWARD = 0,
    RIGHT_FORWARD,
    LEFT_STRAFE,
    RIGHT_STRAFE,
    FRONT_DIVE,
    BACK_DIVE
};

class SerialThruster : public IThruster {
private:
    Serial& serial_;
    ThrusterIndex thrusterIndex_;
public:
    SerialThruster(Serial serial, ThrusterIndex thrusterIndex);
    void Thrust(float powerLevel);

};


#endif //PERIPHERALS_SERIAL_THRUSTER_H
