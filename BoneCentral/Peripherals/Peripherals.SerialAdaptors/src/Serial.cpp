//
// Created by Nathan Copier on 1/28/2016.
// Refactored by TekuConcept on 2/13/2017.
//

#include "Serial.h"

#ifdef DEBUG
#define IFDEBUG if(true)
#else
#define IFDEBUG if(false)
#endif

std::mutex Serial::serialLock_;

Serial::Serial(std::string device) {
    IFDEBUG {
        LOG("\nReceived Device Name: " << device);
        LOG("\nEntering Serial Debug Mode\n");
        fd = 0;
    } else {
        if((fd = open(device.c_str(), O_RDWR)) < 0) {
            LOG("Device failed to open... entering dummy mode.\n");
            fd = 0;
            return;
        }
        
        configure();
    }
    acknowledge();
}

Serial::~Serial() {
    if(fd != 0) close(fd);
}

void Serial::configure() {
    struct termios topts;
    if(tcgetattr(fd, &topts)) {
        LOG("Failed to get terminal ios options from file descriptor.\n");
        throw 1;
    }
    if(cfsetispeed(&topts, B115200)) {
        LOG("Failed to set input baud rate.\n");
        throw 1;
    }
    if(cfsetospeed(&topts, B115200)) {
        LOG("Failed to set output baud rate.\n");
        throw 1;
    }
    topts.c_cflag &= ~(PARENB|CSTOPB|CSIZE|CRTSCTS);
    topts.c_cflag |= CS8|CREAD|CLOCAL;
    topts.c_iflag &= ~(IXON | IXOFF | IXANY);
    topts.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    topts.c_oflag &= ~OPOST;
    topts.c_cc[VMIN] = 1;
    topts.c_cc[VTIME] = 0;
    if(tcsetattr(fd, TCSANOW, &topts)) {
        LOG("Failed to set terminal ios options for file descriptor.\n");
        throw 1;
    }
    if(tcflush(fd, TCIFLUSH)) {
        LOG("Failed to flush file descriptor.\n");
        throw 1;
    }
}

void Serial::acknowledge() {
    std::string response = readString();
    IFDEBUG {
        LOG("Arduino Message: " << response << "\n");
    }
    writeByte('R');
}




std::string Serial::readString() {
    IFDEBUG {
        std::string res("Dummy String");
        return res;
    }
    
    if(fd==0) return "";
    std::stringstream ss;
    char c[1];
    
    do{
        read(fd, c, 1);
        ss << c[0];
    }while(c[0] != '\0');
    return ss.str();
}

unsigned char Serial::readByte() {
    unsigned char result = 0;
    readData((char*)&result, 1);
    return result;
}

float Serial::readFloat() {
    float result = 0;
    readData((char*)&result, 4);
    return result;
}

double Serial::readDouble() {
    double result = 0;
    readData((char*)&result, 8);
    return result;
}

int Serial::readInt() {
    int result = 0;
    readData((char*)&result, 4);
    return result;
}

unsigned int Serial::readUInt() {
    unsigned int result = 0;
    readData((char*)&result, 4);
    return result;
}

short Serial::readShort() {
    short result = 0;
    readData((char*)&result, 2);
    return result;
}

unsigned short Serial::readUShort() {
    unsigned short result = 0;
    readData((char*)&result, 2);
    return result;
}

void Serial::readData(char* ptr, size_t size) {
    std::lock_guard<std::mutex> guard(serialLock_);
    if(fd!=0) read(fd, ptr, size);
    else for(unsigned int i = 0; i < size; i++) ptr[i] = 0;
}




void Serial::writeFloat(float value) {
    writeData((char*)&value, 4);
}

void Serial::writeDouble(double value) {
    writeData((char*)&value, 8);
}

void Serial::writeInt(int value) {
    writeData((char*)&value, 4);
}

void Serial::writeUInt(unsigned int value) {
    writeData((char*)&value, 4);
}

void Serial::writeShort(short value) {
    writeData((char*)&value, 2);
}

void Serial::writeUShort(unsigned short value) {
    writeData((char*)&value, 2);
}

void Serial::writeByte(unsigned char value) {
    writeData((char*)&value, 1);
}

void Serial::writeData(char* ptr, size_t size) {
    IFDEBUG {
        LOG("Serial Write: " << std::hex << std::setw(2));
        for(size_t i = 0; i < size; i++) {
            LOG((unsigned short)ptr[i]);
        }
        LOG(std::dec << std::endl);
        return;
    }
    std::lock_guard<std::mutex> guard(serialLock_);
    if(fd == 0) return;
    write(fd, ptr, size);
}

#ifdef IFDEBUG
#undef IFDEBUG
#endif