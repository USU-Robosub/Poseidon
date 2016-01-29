//
// Created by Nathan Copier on 1/28/2016.
//

#include "Serial.h"

Serial::Serial() {
    std::system("stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
    input_ = std::make_shared<std::ifstream>("/dev/ttyUSB0");
    output_ = std::make_shared<std::ofstream>("/dev/ttyUSB0");
}

void Serial::writeByte(unsigned short byteValue) {
    *output_ << char((byteValue << 8) >> 8) << std::flush;
}

void Serial::writeShort(unsigned short shortValue) {
    *output_ << char(shortValue >> 8) << char((shortValue << 8) >> 8) << std::flush;
}

Serial::~Serial() {
    input_->close();
    output_->close();
}