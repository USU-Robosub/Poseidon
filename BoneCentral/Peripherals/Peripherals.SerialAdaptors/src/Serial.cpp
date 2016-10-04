//
// Created by Nathan Copier on 1/28/2016.
//

#include "Serial.h"

Serial::Serial() {
    std::system("stty -F /dev/ttyACM0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
    input_ = std::make_shared<std::ifstream>("/dev/ttyACM0");
    output_ = std::make_shared<std::ofstream>("/dev/ttyACM0");
    arduinoInitialized_ = false;
    initializeArduino();
}

void Serial::writeByte(unsigned short byteValue) {
    if (arduinoInitialized_)
    {
        std::lock_guard<std::mutex> guard(serialLock_);
        *output_ << char(byteValue & 0xFF) << std::flush;
    }
}

void Serial::writeShort(unsigned short shortValue) {
    if (arduinoInitialized_)
    {
        std::lock_guard<std::mutex> guard(serialLock_);
        *output_ << char(shortValue >> 8) << char(shortValue & 0xFF) << std::flush;
    }
}

json Serial::readJson() {
    if (arduinoInitialized_)
    {
        std::lock_guard<std::mutex> guard(serialLock_);
        json arduinoData;
        *input >> arduinoData;
        return arduinoData;
    }
    return {};
}

char Serial::readChar() {
    if (arduinoInitialized_)
    {
        std::lock_guard<std::mutex> guard(serialLock_);
        char arduinoReading;
        *input >> arduinoReading;
        return arduinoReading;
    }
    return '';
}

void initializeArduino() {
    // TODO: create initialization code
    arduinoInitialized_ = true;
}

Serial::~Serial() {
    input_->close();
    output_->close();
}

std::mutex Serial::serialLock_;
