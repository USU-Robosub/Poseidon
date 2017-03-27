/**
 * Created by TekuConcept on 8/3/2016.
 */
#ifndef SERIAL_TOOLS_H
#define SERIAL_TOOLS_H

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
    while(Serial.available() < size);
    for(int i = 0; i < size; i++) {
      ptr[i] = Serial.read();
    }
  }

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   *                   WRITE FUNCTIONS                   *
  \* - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /**
   * Writes a null-terminated string to the Serial's
   * out buffer.
   */
  static void writeString(const char* data, int size) {
    for(int i = 0; i < size; i++) {
      Serial.print(data[i]);
    }
    Serial.print('\0');
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
    for(int i = 0; i < size; i++){
      // #ifdef DEBUG
      //   printHex((uint8_t)ptr[i]);
      // #else
        Serial.print(ptr[i]);
      // #endif
    }
  }

  static void printHex(uint8_t c) {
    printHexChar((uint8_t)((c&0xF0) >> 4));
    printHexChar((uint8_t)(c&0x0F));
  }

private:
  SerialTools(){}
  static void printHexChar(uint8_t val) {
    char res = '0';
    if(val < 10)
      Serial.print(val);
    else
      switch(val-10) {
        case 0: res = 'A'; break;
        case 1: res = 'B'; break;
        case 2: res = 'C'; break;
        case 3: res = 'D'; break;
        case 4: res = 'E'; break;
        case 5: res = 'F'; break;
      }
      Serial.print(res);
  }
};

#endif