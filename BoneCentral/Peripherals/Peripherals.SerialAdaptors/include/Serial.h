//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_SERIAL_H
#define PERIPHERALS_SERIAL_H

#include <fstream>
#include <memory>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <json.h>
#include <ScriptLogger.h>


class Serial {
private:
    std::shared_ptr<std::ifstream> input_;
    std::shared_ptr<std::ofstream> output_;
    std::shared_ptr<std::ScriptLogger> logger_;
    static std::mutex serialLock_;
    bool arduinoInitialized_;
public:
    Serial();
    void writeByte(unsigned short byteValue);
    void writeShort(unsigned short shortValue);
    json readJson();
    char readChar();
    void initializeArduino();
    bool getArduinoInitialized();
    ~Serial();
};


#endif //PERIPHERALS_SERIAL_H
