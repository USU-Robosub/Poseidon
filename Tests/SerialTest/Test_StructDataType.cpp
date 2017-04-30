#include <iostream>
#include <string>
#include "Serial.h"

#define MSG(x)  std::cout << x
#define MSGN(x) std::cout << x << "\n"
#define ERR(x)  std::cerr << x << "\n"
#define m_assert(x,y) (x) != (y) ? MSGN("FAIL") : MSGN("PASS")

typedef struct Data {
    float a;
    double b;
    int c;
    unsigned d;
    short e;
    unsigned short f;
} Data;



int main() {
    MSGN("-- BEGIN TEST --");
    
    MSG("\nCreating Serial Object... ");
    Serial serial("/dev/ttyACM0");
    MSGN("Done!\n");
    
    std::string res = serial.readString();
    MSG("Message: "); MSGN(res);
    serial.writeByte('R');
    
    Data data;
    data.a = 0.0F;
    data.b = 0.0;
    data.c = 0;
    data.d = 0;
    data.e = 0;
    data.f = 0;
    
    MSGN("Receiving Static Values from Arduino...");
    serial.readData((char*)&data, sizeof(Data));
    // MSG("> "); MSGN(data.a);
    // MSG("> "); MSGN(data.b);
    // MSG("> "); MSGN(data.c);
    // MSG("> "); MSGN(data.d);
    // MSG("> "); MSGN(data.e);
    // MSG("> "); MSGN(data.f);
    MSG("> Float:\t");  m_assert(data.a, 0.1F);
    MSG("> Double:\t"); m_assert(data.b, 0.2);
    MSG("> Int:\t\t");  m_assert(data.c, -3);
    MSG("> UInt:\t\t"); m_assert(data.d, 4);
    MSG("> Short:\t");  m_assert(data.e, -5);
    MSG("> UShort:\t"); m_assert(data.f, 6);
    
    data.a *= 2;
    data.b *= 2;
    data.c *= 2;
    data.d *= 2;
    data.e *= 2;
    data.f *= 2;
    
    MSGN("Sending Modified Static Values to Arduino...");
    serial.writeData((char*)&data, sizeof(Data));
    short err = serial.readShort();
    MSG("Result: "); MSGN(err);
    
    MSG("> Float:\t");  m_assert((err>>5)&1, 0);
    MSG("> Double:\t"); m_assert((err>>4)&1, 0);
    MSG("> Int:\t\t");  m_assert((err>>3)&1, 0);
    MSG("> UInt:\t\t"); m_assert((err>>2)&1, 0);
    MSG("> Short:\t");  m_assert((err>>1)&1, 0);
    MSG("> UShort:\t"); m_assert((err>>0)&1, 0);
    
    MSGN("\n--  END TEST  --");
    return 0;
}