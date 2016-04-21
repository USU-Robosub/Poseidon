//
// Created by Nathan Copier on 1/28/2016.
//

#include "../include/Serial.h"

Serial::Serial() {
    std::system("stty -F /dev/ttyACM0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
    input_ = std::make_shared<std::ifstream>("/dev/ttyACM0");
    output_ = std::make_shared<std::ofstream>("/dev/ttyACM0");
}

void Serial::writeByte(unsigned short byteValue) {
    *output_ << char(byteValue & 0xFF) << std::flush;
}

void Serial::writeShort(unsigned short shortValue) {
    *output_ << char(shortValue >> 8) << char(shortValue & 0xFF) << std::flush;
}

Serial::~Serial() {
    input_->close();
    output_->close();
}