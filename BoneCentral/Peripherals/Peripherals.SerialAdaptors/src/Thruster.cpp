#include "Thruster.h"

void Thruster::update(IHub*){

}

void Thruster::process(IHub* hub, std::string*, Message* message){
  if(message->isAddressedTo(nodeName) &&
  message->matchesType("SET_POWER") &&
  message->getData()["power"].is_number()){
    hub->send("LOCAL", Message(arduinoName, "WRITE_BYTE", nodeName, json({
      {"byte", arduinoIndex}
    })));
    float power = message->getData()["power"];
    hub->send("LOCAL", Message(arduinoName, "WRITE_SHORT", nodeName, json({
      {"short", (power * 500) + 1500}
    })));
  }
}
