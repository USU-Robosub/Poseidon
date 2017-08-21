#include "Thruster.h"

void Thruster::update(IHub*){

}

void Thruster::process(IHub* hub, std::string* connection, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("SET_POWER")){
      float power = message->getData()["power"];
      hub->send(*connection, json({
        {"target", arduinoName},
        {"type", "WRITE_BYTE"},
        {"from", nodeName},
        {"data", {
          {"byte", arduinoIndex}
        }}
      }).dump());
      hub->send(*connection, json({
        {"target", arduinoName},
        {"type", "WRITE_SHORT"},
        {"from", nodeName},
        {"data", {
          {"short", (power * 500) + 1500}
        }}
      }).dump());
    }
  }
}
