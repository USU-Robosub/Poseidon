//
// Created by TekuConcept on 12/22/2016.
//
#include "Serial.h"

Serial::Serial(std::string device) {
    // std::stringstream ss;
    // ss<<"stty -F "<<device<<" cs8 115200 ignbrk \
    //     -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon \
    //     -iexten -echo -echoe -echok -echoctl -echoke noflsh \
    //     -ixon -crtscts";
    // std::system(ss.str().c_str());
    // input_ = std::make_shared<std::ifstream>(device.c_str());
    // output_ = std::make_shared<std::ofstream>(device.c_str());
    
    // *output_ << "R" << std::flush;
    
    if((fd = open(device.c_str(), O_RDWR)) < 0) {
        LOG("Device failed to open... entering dummy mode.\n");
        fd = 0;
        return;
    }
    // check isatty(fd) == 1?
    
    // configure device
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

Serial::~Serial() {
    // input_->close();
    // output_->close();
    if(fd != 0) close(fd);
}

std::string Serial::readString() {
    if(fd==0) return "";
    // std::lock_guard<std::mutex> guard(serialLock_);
    std::stringstream ss;
    char c[1];
    
    // int i = 0;
    // std::cerr << std::hex;
    do{
        // NOTE: if the program halts here
        // it is because the arduino didn't
        // write anything to the stream.
        // c = input_->get();
        read(fd, c, 1);
        // if(i < 10) {
        //     std::cerr << (int)c[0] << " ";
        //     i++;
        // }
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
#ifdef DUE
    readData((char*)&result, 8);
#else
    float data = 0;
    readData((char*)&data, 4);
    result = (double)data;
#endif
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
    // std::lock_guard<std::mutex> guard(serialLock_);
    // input_->read(ptr, size);
    
    // for(size_t i = 0; i < size; i++) {
    //     *input_ >> ptr[i];
    // }
    
    if(fd!=0) read(fd, ptr, size);
    else for(unsigned int i = 0; i < size; i++)
            ptr[i] = 0;
}




void Serial::writeFloat(float value) {
    writeData((char*)&value, 4);
}

void Serial::writeDouble(double value) {
#ifdef DUE
    writeData((char*)&value, 8);
#else
    float val2 = (float)value;
    writeData((char*)&val2, 4);
#endif
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
    if(fd == 0) return;
    // std::lock_guard<std::mutex> guard(serialLock_);
    // for(size_t i = 0; i < size; i++) {
    //     *output_ << ptr[i];
    // }
    // *output_ << std::flush;
    // output_->write(ptr, size);
    // output_->flush();
    write(fd, ptr, size);
}