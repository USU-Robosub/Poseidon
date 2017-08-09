#include "Thruster.h"

void update(IHub* hub){

}

void process(IHub* hub, std::string connection, json message){
  if(message["target"] == nodeName){
    if(message["type"] == "SET_POWER"){
      float power = message["data"]["power"];
      hub->send(connection, json({
        {"target", arduinoName},
        {"type", "WRITE_BYTE"},
        {"from", nodeName},
        {"data", {
          {"byte", arduinoIndex}
        }}
      }).dump());
      hub->send(connection, json({
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
