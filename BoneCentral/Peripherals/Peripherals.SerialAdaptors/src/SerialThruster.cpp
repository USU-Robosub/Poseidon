//
// Created by Nathan Copier on 1/28/2016.
//

#include "../include/SerialThruster.h"

SerialThruster::SerialThruster(Serial& serial, ThrusterIndex thrusterIndex)
        : serial_(serial), thrusterIndex_(thrusterIndex) { }

void SerialThruster::Thrust(float powerLevel) {
    serial_.writeByte(thrusterIndex_);
    serial_.writeShort((powerLevel * 500) + 1500);
}
