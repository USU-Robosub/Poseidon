//
// Created by Nathan Copier on 1/28/2016.
//

#include "SerialThruster.h"

SerialThruster::SerialThruster(Serial& serial, int thrusterIndex)
        : serial_(serial), thrusterIndex_(thrusterIndex) { }

void SerialThruster::Thrust(float powerLevel) {
    std::cout << "powerLevel" << powerLevel << std::endl;
    serial_.writeByte(thrusterIndex_);
    serial_.writeShort((powerLevel * 500) + 1500);
}
