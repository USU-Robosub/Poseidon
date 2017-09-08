//
// Created by Nathan Copier on 1/28/2016.
//

#include "SerialThruster.h"

SerialThruster::SerialThruster(Serial& serial, int thrusterIndex)
        : serial_(serial), thrusterIndex_(thrusterIndex) { }

void SerialThruster::Thrust(float powerLevel) {
    serial_.writeByte(thrusterIndex_);
    serial_.writeUShort((powerLevel * 500) + 1500);
}
