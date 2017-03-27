#include <Arduino.h>
#include "SerialTools.h"

#define m_assert(T,V) if(T != V) { result = (result<<1)|1; } else { result <<= 1; }
#define B115200 115200
#define GARBAGE 0

void setup() {
    Serial.begin(B115200);
    SerialTools::writeString("Ready!", 6);
    while((!Serial.available())||(Serial.read()==GARBAGE));
    
    uint16_t result = 0;
    int test = 0;
    
    SerialTools::readData((char*)&test, sizeof(int));
    m_assert(test, 0x0A0B0C0D)
    m_assert(SerialTools::readByte(), 0xFF)
    m_assert(SerialTools::readFloat(), 0.1F)
    m_assert(SerialTools::readDouble(), 0.2)
    m_assert(SerialTools::readInt(), -3)
    m_assert(SerialTools::readUInt(), 4)
    m_assert(SerialTools::readShort(), -5)
    m_assert(SerialTools::readUShort(), 6)
    
    SerialTools::writeInt(result);
}

void loop() { }