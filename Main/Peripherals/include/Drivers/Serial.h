//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_SERIAL_H
#define PERIPHERALS_SERIAL_H

#include <fstream>
#include <memory>
#include <cstdlib>


class Serial {
private:
    std::shared_ptr<std::ifstream> input_;
    std::shared_ptr<std::ofstream> output_;
public:
    Serial();
    void writeByte(unsigned short byteValue);
    void writeShort(unsigned short shortValue);
    ~Serial();
};


#endif //PERIPHERALS_SERIAL_H
