/**
 * Created by TekuConcept on 8/3/2016.
 */
#ifndef SERIAL_TOOLS_H
#define SERIAL_TOOLS_H

#include "Debugger.h"
#define USB   0
#define DEBUG 1
#define EVENT 2
#define AUX   3

/**
 * Extend the functionality of the Serial object,
 * providing various useful type value streams.
 */
class SerialTools{
public:
  /* - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   *                    READ FUNCTIONS                   *
  \* - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /* reading strings is not yet implemented here */
  static uint8_t readByte(uint8_t channel = USB) {
    uint8_t result = 0;
    readData((char*)&result, sizeof(uint8_t), channel);
    return result;
  }
  
  static float readFloat(uint8_t channel = USB) {
    float result = 0;
    readData((char*)&result, sizeof(float), channel);
    return result;
  }

  static double readDouble(uint8_t channel = USB) {
    double result = 0;
    readData((char*)&result, sizeof(double), channel);
    return result;
  }

  static int32_t readInt(uint8_t channel = USB) {
    int result = 0;
    readData((char*)&result, sizeof(int32_t), channel);
    return result;
  }

  static uint32_t readUInt(uint8_t channel = USB) {
    uint32_t result = 0;
    readData((char*)&result, sizeof(uint32_t), channel);
    return result;
  }

  static int16_t readShort(uint8_t channel = USB) {
    int16_t result = 0;
    readData((char*)&result, sizeof(int16_t), channel);
    return result;
  }

  static uint16_t readUShort(uint8_t channel = USB) {
    uint16_t result = 0;
    readData((char*)&result, sizeof(uint16_t), channel);
    return result;
  }

  static void readData(char* ptr, int size, uint8_t channel = USB) {
    while(available(channel) < size);
    for(int i = 0; i < size; i++) {
      ptr[i] = read(channel);
      DHEX((uint8_t)ptr[i]);
    }
    DMSGN();
  }

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   *                   WRITE FUNCTIONS                   *
  \* - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /**
   * Writes a null-terminated string to the Serial's
   * out buffer.
   */
  static void writeString(const char* data, int size, uint8_t channel = USB) {
    for(int i = 0; i < size; i++) {
      print(data[i], channel);
    }
    print('\0');
  }

  static void writeByte(uint8_t out, uint8_t channel = USB) {
    writeData((char*)&out, sizeof(uint8_t), channel);
  }

  static void writeFloat(float out, uint8_t channel = USB) {
    writeData((char*)&out, sizeof(float), channel);
  }

  static void writeDouble(double out, uint8_t channel = USB) {
    writeData((char*)&out, sizeof(double), channel);
  }

  static void writeInt(int32_t out, uint8_t channel = USB) {
    writeData((char*)&out, sizeof(int32_t), channel);
  }

  static void writeUInt(uint32_t out, uint8_t channel = USB) {
    writeData((char*)&out, sizeof(uint32_t), channel);
  }

  static void writeShort(int16_t out, uint8_t channel = USB) {
    writeData((char*)&out, sizeof(int16_t), channel);
  }

  static void writeUShort(uint16_t out, uint8_t channel = USB) {
    writeData((char*)&out, sizeof(uint16_t), channel);
  }

  static void writeData(char* ptr, int size, uint8_t channel = USB) {
    for(int i = 0; i < size; i++){
        print(ptr[i], channel);
    }
  }

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   *                  SYSTEM FUNCTIONS                   *
  \* - - - - - - - - - - - - - - - - - - - - - - - - - - */

  static void begin(int channel, int baud) {
    switch(channel) {
      case 1: Serial1.begin(baud); break;
      case 2: Serial2.begin(baud); break;
      case 3: Serial3.begin(baud); break;
      default: Serial.begin(baud); break;
    }
  }
  
  static void end(int channel) {
    switch(channel) {
      case 1: Serial1.end(); break;
      case 2: Serial2.end(); break;
      case 3: Serial3.end(); break;
      default: Serial.end(); break;
    }
  }
  
  static char read(uint8_t channel = USB) {
    switch(channel) {
      case 1: return Serial1.read();
      case 2: return Serial2.read();
      case 3: return Serial3.read();
      default: return Serial.read();
    }
  }
  
  static void print(char value, uint8_t channel = USB) {
    switch(channel) {
      case 1: Serial1.print(value); break;
      case 2: Serial2.print(value); break;
      case 3: Serial3.print(value); break;
      default: Serial.print(value); break;
    }
  }
  
  static int available(uint8_t channel = USB) {
    switch(channel) {
      case 1: return Serial1.available();
      case 2: return Serial2.available();
      case 3: return Serial3.available();
      default: return Serial.available();
    }
  }

  static void printHex(uint8_t c, uint8_t channel = USB) {
    printHexChar((uint8_t)((c&0xF0) >> 4), channel);
    printHexChar((uint8_t)(c&0x0F), channel);
  }

private:
  SerialTools(){}
  static void printHexChar(uint8_t val, uint8_t channel) {
    if(val < 10)      print('0'+val, channel);
    else if(val < 16) print((char)(val-10+'A'), channel);
    else              print('-', channel);
  }
};

#endif
