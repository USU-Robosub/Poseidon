//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_SERIAL_THRUSTER_H
#define PERIPHERALS_SERIAL_THRUSTER_H

#include <IThruster.h>
#include "Serial.h"
#include "ArduinoConfig.h"

class SerialThruster : public IThruster {
private:
    Serial& serial_;
    int thrusterIndex_;
public:
    SerialThruster(Serial& serial, int thrusterIndex);
    void Thrust(float powerLevel);

};


#endif //PERIPHERALS_SERIAL_THRUSTER_H
