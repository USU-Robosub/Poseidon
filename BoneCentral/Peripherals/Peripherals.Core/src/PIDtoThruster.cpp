#include "PIDtoThruster.h"

void PIDtoThruster::update(IHub*){

}

void PIDtoThruster::process(IHub* hub, std::string*, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("SET") && message->getData()["correctionValue"].is_number()){
      hub->send("LOCAL", Message(thrusterName, "SET_POWER", nodeName, json({
        {"power", message->getData()["correctionValue"]}
      })));
    }if(message->matchesType("STOP")){
      hub->send("LOCAL", Message(thrusterName, "SET_POWER", nodeName, json({
        {"power", 0}
      })));
    }
  }
}
