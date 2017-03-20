#include <Arduino.h>
#include "SerialTools.h"

#define B115200 115200
#define GARBAGE 0

void setup() {
    Serial.begin(B115200);
    SerialTools::writeString("Ready!", 6);
    while((!Serial.available())||(Serial.read()==GARBAGE));
    
    int test = 0x0A0B0C0D;
    SerialTools::writeData((char*)&test, 4);
    SerialTools::writeByte(0xFF);
    SerialTools::writeFloat(0.1F);
    SerialTools::writeDouble(0.2);
    SerialTools::writeInt(-3);
    SerialTools::writeUInt(4);
    SerialTools::writeShort(-5);
    SerialTools::writeUShort(6);
}

void loop() { }