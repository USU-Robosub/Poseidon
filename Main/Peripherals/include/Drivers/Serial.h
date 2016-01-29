//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_SERIAL_H
#define PERIPHERALS_SERIAL_H

#include <iostream>


class Serial {
private:
    std::ifstream& input_;
    std::ofstream& out_;
public:
    Serial();
    void writeByte(unsigned short byteValue);
    void writeShort(unsigned short shortValue);
    ~Serial();
};


#endif //PERIPHERALS_SERIAL_H
