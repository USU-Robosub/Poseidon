#include <iostream>
#include <string>
#include "Serial.h"

#define MSG(x)  std::cout << x
#define MSGN(x) std::cout << x << "\n"
#define ERR(x)  std::cerr << x << "\n"
#define m_assert(x) (x)&0x01 == 1 ? MSGN("FAIL") : MSGN("PASS")

int main() {
    MSGN("-- BEGIN TEST --");
    
    MSG("\nCreating Serial Object... ");
    Serial serial("/dev/ttyACM0");
    MSGN("Done!\n");
    
    std::string res = serial.readString();
    MSG("Message: "); MSGN(res);
    serial.writeByte('R');
    
    MSGN("Sending Static Values to Arduino...");
    int bytes = 0x0A0B0C0D;
    
    serial.writeData((char*)&bytes, 4);
    serial.writeByte(0xFF);
    serial.writeFloat(0.1F);
    serial.writeDouble(0.2);
    serial.writeInt(-3);
    serial.writeUInt(4);
    serial.writeShort(-5);
    serial.writeUShort(6);
    
    MSG("Results: ");
    int ires = serial.readInt();
    
    MSGN(ires);
    MSG("> Sending Bytes\t\t\t");         m_assert(ires>>7);
    MSG("> Sending Byte\t\t\t");          m_assert(ires>>6);
    MSG("> Sending Float\t\t\t");         m_assert(ires>>5);
    MSG("> Sending Double\t\t");          m_assert(ires>>4);
    MSG("> Sending Int\t\t\t");           m_assert(ires>>3);
    MSG("> Sending Unsigned Int\t\t");    m_assert(ires>>2);
    MSG("> Sending Short\t\t\t");         m_assert(ires>>1);
    MSG("> Sending Unsigned Short\t");    m_assert(ires>>0);
    
    MSGN("\n--  END TEST  --");
    return 0;
}