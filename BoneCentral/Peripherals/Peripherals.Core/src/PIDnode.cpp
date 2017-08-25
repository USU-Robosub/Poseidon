#include "PIDnode.h"

void PIDnode::update(IHub* hub){
  if(isRunning){
    hub->send("LOCAL", Message(sensorName, "GET", nodeName));
    float error = lastSensorReading - target;
    integral += error;
    derivative = error - previousError;
    previousError = error;
    float correctionValue = error * P + integral * I + derivative * D;
    hub->send("LOCAL", Message(actuatorName, "SET", nodeName, json({
      {"correctionValue", correctionValue}
    })));
  }
}

void PIDnode::process(IHub* hub, std::string*, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("SET_TARGET") && message->getData()["target"].is_number()){
      target = message->getData()["target"];
    }else if(message->matchesType("GOT") && message->getData()["value"].is_number()){
      lastSensorReading = message->getData()["value"];
    }else if(message->matchesType("SET_CONFIG") &&
    message->getData()["P"].is_number() &&
    message->getData()["I"].is_number() &&
    message->getData()["D"].is_number()){
      P = message->getData()["P"];
      I = message->getData()["I"];
      D = message->getData()["D"];
    }else if(message->matchesType("ENABLE")){
      isRunning = true;
    }else if(message->matchesType("DISABLE")){
      isRunning = false;
      hub->send("LOCAL", Message(actuatorName, "STOP", nodeName));
    }
  }
}

float PIDnode::getLastSensorReading(){
  return lastSensorReading;
}

float PIDnode::getTarget(){
  return target;
}

float PIDnode::getP(){
  return P;
}

float PIDnode::getI(){
  return I;
}

float PIDnode::getD(){
  return D;
}

bool PIDnode::isEnabled(){
  return isRunning;
}

void PIDnode::enable(){
  isRunning = true;
}

void PIDnode::setSensorValue(float sensorValue){
  lastSensorReading = sensorValue;
}
