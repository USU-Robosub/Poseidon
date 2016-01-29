//
// Created by Nathan Copier on 1/28/2016.
//

#include "Serial.h"

Serial::Serial() {
    std::system("stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
    input_ = std::ifstream("/dev/ttyUSB0");
    output_ = std::ofstream("/dev/ttyUSB0");
}

void Serial::writeByte(short byteValue) {
    output_ << char((byteValue << 8) >> 8) << std::flush;
}

void Serial::writeShort(short shortValue) {
    output_ << char(byteValue >> 8) << char((byteValue << 8) >> 8) << std::flush;
}

Serial::~Serial() {
    input_.close();
    output_.close();
}