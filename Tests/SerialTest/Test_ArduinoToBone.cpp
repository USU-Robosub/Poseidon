#include <iostream>
#include <string>
#include "Serial.h"

#define MSG(x)  std::cout << x
#define MSGN(x) std::cout << x << "\n"
#define ERR(x)  std::cerr << x << "\n"
#define m_assert(x,y) (x) != (y) ? MSGN("FAIL") : MSGN("PASS")

int main() {
    MSGN("-- BEGIN TEST --");
    
    MSG("\nCreating Serial Object... ");
    Serial serial("/dev/ttyACM0");
    MSGN("Done!\n");
    
    std::string res = serial.readString();
    MSG("Message: "); MSGN(res);
    serial.writeByte('R');
    
    MSGN("Receiving Static Values from Arduino...");
    
    int bytes = 0;
    MSG("> Receiving Bytes...\t\t");
    serial.readData((char*)&bytes, 4);
    m_assert(bytes, 0x0A0B0C0D);
    
    MSG("> Receiving Byte...\t\t");
    m_assert(serial.readByte(), 0xFF);
    
    MSG("> Receiving Float...\t\t");
    m_assert(serial.readFloat(), 0.1F);
    
    MSG("> Receiving Double...\t\t");
    m_assert(serial.readDouble(), 0.2);
    
    MSG("> Receiving Int...\t\t");
    m_assert(serial.readInt(), -3);
    
    MSG("> Receiving Unsigned Int...\t");
    m_assert(serial.readUInt(), 4);
    
    MSG("> Receiving Short...\t\t");
    m_assert(serial.readShort(), -5);
    
    MSG("> Receiving Unsigned Short...\t");
    m_assert(serial.readUShort(), 6);
    
    MSGN("\n--  END TEST  --");
    return 0;
}