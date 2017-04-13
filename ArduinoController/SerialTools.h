/**
 * Created by TekuConcept on 8/3/2016.
 */
#ifndef SERIAL_TOOLS_H
#define SERIAL_TOOLS_H

#include "Debugger.h"
#define USB 0
#define DEBUG 1
#define EVENT 2

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
  static uint8_t readByte() {
    uint8_t result = 0;
    readData((char*)&result, sizeof(uint8_t));
    return result;
  }
  
  static float readFloat() {
    float result = 0;
    readData((char*)&result, sizeof(float));
    return result;
  }

  static double readDouble() {
    double result = 0;
    readData((char*)&result, sizeof(double));
    return result;
  }

  static int32_t readInt() {
    int result = 0;
    readData((char*)&result, sizeof(int32_t));
    return result;
  }

  static uint32_t readUInt() {
    uint32_t result = 0;
    readData((char*)&result, sizeof(uint32_t));
    return result;
  }

  static int16_t readShort() {
    int16_t result = 0;
    readData((char*)&result, sizeof(int16_t));
    return result;
  }

  static uint16_t readUShort() {
    uint16_t result = 0;
    readData((char*)&result, sizeof(uint16_t));
    return result;
  }

  static void readData(char* ptr, int size) {
    locked = true;
    while(available() < size);
    for(int i = 0; i < size; i++) {
      ptr[i] = read();
      DHEX((uint8_t)ptr[i]);
    }
    DMSGN();
    locked = false;
  }

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   *                   WRITE FUNCTIONS                   *
  \* - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /**
   * Writes a null-terminated string to the Serial's
   * out buffer.
   */
  static void writeString(const char* data, int size) {
    locked = true;
    for(int i = 0; i < size; i++) {
      print(data[i]);
    }
    print('\0');
    locked = false;
  }

  static void writeByte(uint8_t out) {
    writeData((char*)&out, sizeof(uint8_t));
  }

  static void writeFloat(float out) {
    writeData((char*)&out, sizeof(float));
  }

  static void writeDouble(double out) {
    writeData((char*)&out, sizeof(double));
  }

  static void writeInt(int32_t out) {
    writeData((char*)&out, sizeof(int32_t));
  }

  static void writeUInt(uint32_t out) {
    writeData((char*)&out, sizeof(uint32_t));
  }

  static void writeShort(int16_t out) {
    writeData((char*)&out, sizeof(int16_t));
  }

  static void writeUShort(uint16_t out) {
    writeData((char*)&out, sizeof(uint16_t));
  }

  static void writeData(char* ptr, int size) {
    locked = true;
    for(int i = 0; i < size; i++){
        print(ptr[i]);
    }
    locked = false;
  }

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   *                  SYSTEM FUNCTIONS                   *
  \* - - - - - - - - - - - - - - - - - - - - - - - - - - */

  static void printHex(uint8_t c) {
    printHexChar((uint8_t)((c&0xF0) >> 4));
    printHexChar((uint8_t)(c&0x0F));
  }

  static void selectChannel(uint8_t c) {
    if(!locked)
      channel = c;
  }

  static uint8_t getChannel() {
    return channel;
  }

  static void begin(int channelID, int baud) {
    switch(channelID) {
      case 1: Serial1.begin(baud); break;
      case 2: Serial2.begin(baud); break;
      default: Serial.begin(baud); break;
    }
  }
  
  static void end(int channelID) {
    switch(channelID) {
      case 1: Serial1.end(); break;
      case 2: Serial2.end(); break;
      default: Serial.end(); break;
    }
  }
  
  static char read() {
    switch(channel) {
      case 1: return Serial1.read();
      case 2: return Serial2.read();
      default: return Serial.read();
    }
  }
  
  static void print(char value) {
    switch(channel) {
      case 1: Serial1.print(value); break;
      case 2: Serial2.print(value); break;
      default: Serial.print(value); break;
    }
  }
  
  static int available() {
    switch(channel) {
      case 1: return Serial1.available();
      case 2: return Serial2.available();
      default: return Serial.available();
    }
  }

private:
  SerialTools(){}
  static void printHexChar(uint8_t val) {
    char res = '0';
    if(val < 10)      print(val);
    else if(val < 16) print((char)(val-10+'A'));
    else              print('-');
  }
  static uint8_t channel;
  static bool locked;
};

bool SerialTools::locked = false;
uint8_t SerialTools::channel = 0;

#endif
