//
// Created by Nathan Copier on 1/28/2016.
// Refactored by TekuConcept on 8/3/2016.
//

#ifndef PERIPHERALS_SERIAL_H
#define PERIPHERALS_SERIAL_H

#define DUE

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <memory>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#define LOG(x) std::cerr << x

class Serial {
public:
    enum Speed {
        HIGH = B115200,
        NORMAL = B9600
    };
    
    Serial(std::string device, bool shouldAcknowledge=true, Speed speed=Speed::HIGH);
    ~Serial();
    
    std::string     readString();
    unsigned char   readByte();
    float           readFloat();
    double          readDouble();
    int             readInt();
    unsigned int    readUInt();
    short           readShort();
    unsigned short  readUShort();
    void            readData(char* ptr, size_t size);
    
    void writeFloat(float value);
    void writeDouble(double value);
    void writeInt(int value);
    void writeUInt(unsigned int value);
    void writeShort(short value);
    void writeUShort(unsigned short value);
    void writeByte(unsigned char value);
    void writeData(char* ptr, size_t size);

private:
    static std::mutex serialLock_;
    int fd;
    
    void configure(Speed speed);
    void acknowledge();
};


#endif //PERIPHERALS_SERIAL_H