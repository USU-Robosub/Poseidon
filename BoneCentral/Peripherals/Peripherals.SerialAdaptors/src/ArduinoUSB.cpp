#include "ArduinoUSB.h"

void ArduinoUSB::update(IHub* hub){
  
}

void ArduinoUSB::process(IHub* hub, std::string connection, json message){
  if(message["target"] == nodeName){
    if(message["type"] == "READ_STRING") {
      hub->send(connection, generate_GOT(message["from"], json({
        {"string": serial.readString()}
      })));
    }else if(message["type"] == "READ_BYTE") {
      hub->send(connection, generate_GOT(message["from"], json({
        {"byte": serial.readByte()}
      })));
    }else if(message["type"] == "READ_FLOAT") {
      hub->send(connection, generate_GOT(message["from"], json({
        {"float": serial.readFloat()}
      })));
    }else if(message["type"] == "READ_DOUBLE") {
      hub->send(connection, generate_GOT(message["from"], json({
        {"double": serial.readDouble()}
      })));
    }else if(message["type"] == "READ_INT") {
      hub->send(connection, generate_GOT(message["from"], json({
        {"int": serial.readInt()}
      })));
    }else if(message["type"] == "READ_UINT") {
      hub->send(connection, generate_GOT(message["from"], json({
        {"uint": serial.readUInt()}
      })));
    }else if(message["type"] == "READ_SHORT") {
      hub->send(connection, generate_GOT(message["from"], json({
        {"short": serial.readShort()}
      })));
    }else if(message["type"] == "READ_USHORT") {
      hub->send(connection, generate_GOT(message["from"], json({
        {"ushort": serial.readUShort()}
      })));
    }else if(message["type"] == "READ_DATA") {
      char data[];
      serial.readData(data, message["data"]["size"]);
      hub->send(connection, generate_GOT(message["from"], json({
        {"data": data}
      })));
    }else if(message["type"] == "WRITE_FLOAT") {
      serial.writeFloat(message["data"]["float"]);
    }else if(message["type"] == "WRITE_DOUBLE") {
      serial.writeDouble(message["data"]["double"]);
    }else if(message["type"] == "WRITE_INT") {
      serial.writeInt(message["data"]["int"]);
    }else if(message["type"] == "WRITE_UINT") {
      serial.writeUInt(message["data"]["uint"]);
    }else if(message["type"] == "WRITE_SHORT") {
      serial.writeShort(message["data"]["short"]);
    }else if(message["type"] == "WRITE_USHORT") {
      serial.writeUShort(message["data"]["ushort"]);
    }else if(message["type"] == "WRITE_BYTE") {
      serial.writeByte(message["data"]["byte"]);
    }else if(message["type"] == "WRITE_DATA") {
      std::string dataString = message["data"]["data"];
      serial.writeData(dataString.c_str(), dataString.length());
    }
  }
}

std::string generate_GOT(std::string target, json value){
  return json({
    {"target", message["from"]},
    {"type", "GOT_STRING"},
    {"from", nodeName},
    {"data": value}
  }).dump();
}
