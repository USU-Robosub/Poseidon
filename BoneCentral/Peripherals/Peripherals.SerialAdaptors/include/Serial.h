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

using json = nlohmann::json;

class Serial {
private:
    std::shared_ptr<std::ifstream> input_;
    std::shared_ptr<std::ofstream> output_;
    static std::mutex serialLock_;
public:
    Serial();
    void writeByte(unsigned short byteValue);
    void writeShort(unsigned short shortValue);
    json readJson();
    ~Serial();
};


#endif //PERIPHERALS_SERIAL_H
