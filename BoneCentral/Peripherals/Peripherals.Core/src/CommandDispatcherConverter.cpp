#include "CommandDispatcherConverter.h"

void CommandDispatcherConverter::update(IHub* hub){
  std::queue<std::string> messages = tcpConnection.read();
  while(!messages.empty()){
    std::stringstream command(messages.front());
    dispatchCommand(hub, command);
    messages.pop();
  }
}

void CommandDispatcherConverter::process(IHub*, std::string*, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("GOT")){
      if(message->isFrom(accelerometerName)){
        tcpConnection.send(json({
          {"Type", "Acceleration"},
          {"X", message->getData()["x"]},
          {"Y", message->getData()["y"]},
          {"Z", message->getData()["z"]}
        }).dump());
      }else if(message->isFrom(gyroscopeName)){
        tcpConnection.send(json({
          {"Type", "AngularAcceleration"},
          {"X", message->getData()["x"]},
          {"Y", message->getData()["y"]},
          {"Z", message->getData()["z"]}
        }).dump());
      }else if(message->isFrom(compassName)){
        tcpConnection.send(json({
          {"Type", "Heading"},
          {"x", message->getData()["x"]},
          {"y", message->getData()["y"]},
          {"z", message->getData()["z"]},
          {"azimuth", message->getData()["azimuth"]},
          {"inclination", message->getData()["inclination"]}
        }).dump());
      }else if(message->isFrom(internalTemperatureName)){
        tcpConnection.send(json({
          {"Type", "InternalPressure"},
          {"Value", message->getData()["value"]}
        }).dump());
      }else if(message->isFrom(internalPressureName)){
        tcpConnection.send(json({
          {"Type", "InternalPressure"},
          {"Value", message->getData()["value"]}
        }).dump());
      }else if(message->isFrom(externalTemperatureName)){
        tcpConnection.send(json({
          {"Type", "ExternalTemperature"},
          {"Value", message->getData()["value"]}
        }).dump());
      }else if(message->isFrom(externalPressureName)){
        tcpConnection.send(json({
          {"Type", "ExternalPressure"},
          {"Value", message->getData()["value"]}
        }).dump());
      }
    }
  }
}

void CommandDispatcherConverter::dispatchCommand(IHub* hub, std::stringstream& command){
  std::string cmd;
  command >> cmd;
  // starts pid |
  if (cmd == "startThrusters")                start(hub);
  // set power move motor |
  else if(cmd == "move")                      move(hub, command);
  // set yaw pid target |
  else if(cmd == "yaw")                       yaw(hub, command);
  // set power dive motor |
  else if(cmd == "dive")                      dive(hub, command);
  // end pid and set power 0 all motors |
  else if(cmd == "killThrusters")             kill(hub);
  // set pid config |
  else if(cmd == "configureYaw")              configureYaw(hub, command);
  // set pid time delta |
  else if(cmd == "configureTimeDelta")        configureTimeDelta(hub, command);
  // send arduino turnOnEscs command |
  else if(cmd == "turnOnEscs")                turnOnEscs(hub);
  // send arduino turnOffEscs command |
  else if(cmd == "turnOffEscs")               turnOffEscs(hub);
  // send arduino switchLights command |
  else if(cmd == "switchLights")              switchLights(hub);
  // awake sensors |
  else if(cmd == "turnOnImu")                 turnOnImuSensor(hub);
  // sleep sensors |
  else if(cmd == "turnOffImu")                turnOffImuSensor(hub);
  // read accel then send back |
  else if(cmd == "getAcceleration")           getAcceleration(hub);
  // read gyro then send back |
  else if(cmd == "getAngularAcceleration")    getAngularAcceleration(hub);
  // read compass then send back |
  else if(cmd == "getHeading")                getHeading(hub);
  // read internal temp then send back |
  else if(cmd == "getInternalTemperature")    getInternalTemperature(hub);
  // read internal press then send back |
  else if(cmd == "getInternalPressure")       getInternalPressure(hub);
  // read external temp then send back |
  else if(cmd == "getExternalTemperature")    getExternalTemperature(hub);
  // read external press then send back |
  else if(cmd == "getExternalPressure")       getExternalPressure(hub);
  // closes app |
  else if(cmd == "exit")                      hub->exit();
  // logs a warning |
  else                                        logWarning(hub, "Invalid command");
}

void CommandDispatcherConverter::start(IHub* hub){
  hub->send("LOCAL", Message(yawPIDname, "ENABLE", nodeName));
}

void CommandDispatcherConverter::move(IHub* hub, std::stringstream& command){
  float throttle;
  command >> throttle;
  hub->send("LOCAL", Message(moveThrusterName, "SET_POWER", nodeName, json({
    {"power", throttle}
  })));
}

void CommandDispatcherConverter::yaw(IHub* hub, std::stringstream& command){
  float angle;
  command >> angle;
  hub->send("LOCAL", Message(yawPIDname, "SET_TARGET", nodeName, json({
    {"target", angle}
  })));
}

void CommandDispatcherConverter::dive(IHub* hub, std::stringstream& command){
  float throttle;
  command >> throttle;
  hub->send("LOCAL", Message(diveThrusterName, "SET_POWER", nodeName, json({
    {"power", throttle}
  })));
}

void CommandDispatcherConverter::kill(IHub* hub){
  hub->send("LOCAL", Message(yawPIDname, "DISABLE", nodeName));
  hub->send("LOCAL", Message(moveThrusterName, "SET_POWER", nodeName, json({
    {"power", 0}
  })));
  hub->send("LOCAL", Message(diveThrusterName, "SET_POWER", nodeName, json({
    {"power", 0}
  })));
}

void CommandDispatcherConverter::configureYaw(IHub* hub, std::stringstream& command){
  float P, I, D;
  command >> P >> I >> D;
  hub->send("LOCAL", Message(yawPIDname, "SET_CONFIG", nodeName, json({
    {"P", P},
    {"I", I},
    {"D", D}
  })));
}

void CommandDispatcherConverter::configureTimeDelta(IHub* hub, std::stringstream& command){
  unsigned int timeDelta;
  command >> timeDelta;
  hub->send("LOCAL", Message(yawPIDname, "SET_DELTA_TIME", nodeName, json({
    {"deltaTime", timeDelta}
  })));
}

void CommandDispatcherConverter::turnOnEscs(IHub* hub){
  hub->send("LOCAL", Message(escSwitchName, "TURN_ON", nodeName));
}

void CommandDispatcherConverter::turnOffEscs(IHub* hub){
  hub->send("LOCAL", Message(escSwitchName, "TURN_OFF", nodeName));
}

void CommandDispatcherConverter::switchLights(IHub* hub){
  hub->send("LOCAL", Message(lightSwitchName, "SWITCH", nodeName));
}

void CommandDispatcherConverter::turnOnImuSensor(IHub* hub){
  hub->send("LOCAL", Message(accelerometerName,         "AWAKE", nodeName));
  hub->send("LOCAL", Message(gyroscopeName,             "AWAKE", nodeName));
  hub->send("LOCAL", Message(compassName,               "AWAKE", nodeName));
  hub->send("LOCAL", Message(internalTemperatureName,   "AWAKE", nodeName));
  hub->send("LOCAL", Message(internalPressureName,      "AWAKE", nodeName));
  hub->send("LOCAL", Message(externalTemperatureName,   "AWAKE", nodeName));
  hub->send("LOCAL", Message(externalPressureName,      "AWAKE", nodeName));
}

void CommandDispatcherConverter::turnOffImuSensor(IHub* hub){
  hub->send("LOCAL", Message(accelerometerName,         "SLEEP", nodeName));
  hub->send("LOCAL", Message(gyroscopeName,             "SLEEP", nodeName));
  hub->send("LOCAL", Message(compassName,               "SLEEP", nodeName));
  hub->send("LOCAL", Message(internalTemperatureName,   "SLEEP", nodeName));
  hub->send("LOCAL", Message(internalPressureName,      "SLEEP", nodeName));
  hub->send("LOCAL", Message(externalTemperatureName,   "SLEEP", nodeName));
  hub->send("LOCAL", Message(externalPressureName,      "SLEEP", nodeName));
}

void CommandDispatcherConverter::getAcceleration(IHub* hub){
  hub->send("LOCAL", Message(accelerometerName, "GET", nodeName));
}

void CommandDispatcherConverter::getAngularAcceleration(IHub* hub){
  hub->send("LOCAL", Message(gyroscopeName, "GET", nodeName));
}

void CommandDispatcherConverter::getHeading(IHub* hub){
  hub->send("LOCAL", Message(compassName, "GET", nodeName));
}

void CommandDispatcherConverter::getInternalTemperature(IHub* hub){
  hub->send("LOCAL", Message(internalTemperatureName, "GET", nodeName));
}

void CommandDispatcherConverter::getInternalPressure(IHub* hub){
  hub->send("LOCAL", Message(internalPressureName, "GET", nodeName));
}

void CommandDispatcherConverter::getExternalTemperature(IHub* hub){
  hub->send("LOCAL", Message(externalTemperatureName, "GET", nodeName));
}

void CommandDispatcherConverter::getExternalPressure(IHub* hub){
  hub->send("LOCAL", Message(externalPressureName, "GET", nodeName));
}

void CommandDispatcherConverter::logWarning(IHub* hub, std::string warning){
  hub->send("LOCAL", Message("LOGGER", "WARNING", nodeName, json(warning)));
}
