#include <Arduino.h>
#include "SerialTools.h"

#define B115200 115200
#define GARBAGE 0
#define m_assert(T,V) if(T != V) { result = (result<<1)|1; } else { result <<= 1; }

typedef struct Data {
    float a;
    double b;
    int32_t c;
    uint32_t d;
    int16_t e;
    uint16_t f;
} Data;

void setup() {
    Serial.begin(B115200);
    SerialTools::writeString("Ready!", 6);
    while((!Serial.available())||(Serial.read()==GARBAGE));
    
    uint16_t result = 0;
    
    Data data;
    data.a = 0.1F;
    data.b = 0.2;
    data.c = -3;
    data.d = 4;
    data.e = -5;
    data.f = 6;
    
    SerialTools::writeData((char*)&data, sizeof(Data));
    
    Data dmod;
    SerialTools::readData((char*)&dmod, sizeof(Data));
    
    m_assert(dmod.a, data.a*2)
    m_assert(dmod.b, data.b*2)
    m_assert(dmod.c, data.c*2)
    m_assert(dmod.d, data.d*2)
    m_assert(dmod.e, data.e*2)
    m_assert(dmod.f, data.f*2)
    
    SerialTools::writeShort(result);
}

void loop() { }