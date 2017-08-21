#include "ArduinoUSB.h"

void ArduinoUSB::update(IHub*){

}

void ArduinoUSB::process(IHub* hub, std::string* connection, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("READ_STRING")) {
      hub->send(*connection, Message(message->getSender(), "GOT_STRING", nodeName, json({
        {"string", serial.readString()}
      })));
    }else if(message->matchesType("READ_BYTE")) {
      hub->send(*connection, Message(message->getSender(), "GOT_BYTE", nodeName, json({
        {"byte", serial.readByte()}
      })));
    }else if(message->matchesType("READ_FLOAT")) {
      hub->send(*connection, Message(message->getSender(), "GOT_FLOAT", nodeName, json({
        {"float", serial.readFloat()}
      })));
    }else if(message->matchesType("READ_DOUBLE")) {
      hub->send(*connection, Message(message->getSender(), "GOT_DOUBLE", nodeName, json({
        {"double", serial.readDouble()}
      })));
    }else if(message->matchesType("READ_INT")) {
      hub->send(*connection, Message(message->getSender(), "GOT_INT", nodeName, json({
        {"int", serial.readInt()}
      })));
    }else if(message->matchesType("READ_UINT")) {
      hub->send(*connection, Message(message->getSender(), "GOT_UINT", nodeName, json({
        {"uint", serial.readUInt()}
      })));
    }else if(message->matchesType("READ_SHORT")) {
      hub->send(*connection, Message(message->getSender(), "GOT_SHORT", nodeName, json({
        {"short", serial.readShort()}
      })));
    }else if(message->matchesType("READ_USHORT")) {
      hub->send(*connection, Message(message->getSender(), "GOT_USHORT", nodeName, json({
        {"ushort", serial.readUShort()}
      })));
    }else if(message->matchesType("READ_DATA")) {
      char* data = new char[message->getData()["size"].get<unsigned int>()];
      serial.readData(data, message->getData()["size"]);
      hub->send(*connection, Message(message->getSender(), "GOT_DATA", nodeName, json({
        {"data", data}
      })));
      delete data;
    }else if(message->matchesType("WRITE_FLOAT")) {
      serial.writeFloat(message->getData()["float"]);
    }else if(message->matchesType("WRITE_DOUBLE")) {
      serial.writeDouble(message->getData()["double"]);
    }else if(message->matchesType("WRITE_INT")) {
      serial.writeInt(message->getData()["int"]);
    }else if(message->matchesType("WRITE_UINT")) {
      serial.writeUInt(message->getData()["uint"]);
    }else if(message->matchesType("WRITE_SHORT")) {
      serial.writeShort(message->getData()["short"]);
    }else if(message->matchesType("WRITE_USHORT")) {
      serial.writeUShort(message->getData()["ushort"]);
    }else if(message->matchesType("WRITE_BYTE")) {
      serial.writeByte(message->getData()["byte"]);
    }else if(message->matchesType("WRITE_DATA")) {
      std::string dataString = message->getData()["data"];
      serial.writeData(const_cast<char*>(dataString.c_str()), dataString.length());
    }
  }
}
