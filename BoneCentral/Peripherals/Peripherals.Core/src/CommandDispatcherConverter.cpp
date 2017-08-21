#include "CommandDispatcherConverter.h"

void CommandDispatcherConverter::update(IHub*){
  /*while(inStream.hasLine()){
    std::string commandString = inStream.readLine();
    std::stringstream command(commandString);
    dispatchCommand(hub, command);
  }*/
}

void CommandDispatcherConverter::process(IHub*, std::string*, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("GOT")){
      if(message->isFrom(accelerometerName)){
        outStream << json({
          {"Type", "Acceleration"},
          {"X", message->getData()["x"]},
          {"Y", message->getData()["y"]},
          {"Z", message->getData()["z"]}
        });
      }else if(message->isFrom(gyroscopeName)){
        outStream << json({
          {"Type", "AngularAcceleration"},
          {"X", message->getData()["x"]},
          {"Y", message->getData()["y"]},
          {"Z", message->getData()["z"]}
        });
      }else if(message->isFrom(compassName)){
        outStream << json({
          {"Type", "Heading"},
          {"x", message->getData()["x"]},
          {"y", message->getData()["y"]},
          {"z", message->getData()["z"]},
          {"azimuth", message->getData()["azimuth"]},
          {"inclination", message->getData()["inclination"]}
        });
      }else if(message->isFrom(internalTemperatureName)){
        outStream << json({
          {"Type", "InternalPressure"},
          {"Value", message->getData()["value"]}
        });
      }else if(message->isFrom(internalPressureName)){
        outStream << json({
          {"Type", "InternalPressure"},
          {"Value", message->getData()["value"]}
        });
      }else if(message->isFrom(externalTemperatureName)){
        outStream << json({
          {"Type", "ExternalTemperature"},
          {"Value", message->getData()["value"]}
        });
      }else if(message->isFrom(externalPressureName)){
        outStream << json({
          {"Type", "ExternalPressure"},
          {"Value", message->getData()["value"]}
        });
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
  hub->send("LOCAL", json({
    {"target", yawPIDname},
    {"type", "ENABLE"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::move(IHub* hub, std::stringstream& command){
  float throttle;
  command >> throttle;
  hub->send("LOCAL", json({
    {"target", moveThrusterName},
    {"type", "SET_POWER"},
    {"from", nodeName},
    {"data", {
      {"power", throttle}
    }}
  }).dump());
}

void CommandDispatcherConverter::yaw(IHub* hub, std::stringstream& command){
  float angle;
  command >> angle;
  hub->send("LOCAL", json({
    {"target", yawPIDname},
    {"type", "SET_TARGET"},
    {"from", nodeName},
    {"data", {
      {"target", angle}
    }}
  }).dump());
}

void CommandDispatcherConverter::dive(IHub* hub, std::stringstream& command){
  float throttle;
  command >> throttle;
  hub->send("LOCAL", json({
    {"target", diveThrusterName},
    {"type", "SET_POWER"},
    {"from", nodeName},
    {"data", {
      {"power", throttle}
    }}
  }).dump());
}

void CommandDispatcherConverter::kill(IHub* hub){
  hub->send("LOCAL", json({
    {"target", yawPIDname},
    {"type", "DISABLE"},
    {"from", nodeName}
  }).dump());
  hub->send("LOCAL", json({
    {"target", moveThrusterName},
    {"type", "SET_POWER"},
    {"from", nodeName},
    {"data", {
      {"power", 0}
    }}
  }).dump());
  hub->send("LOCAL", json({
    {"target", diveThrusterName},
    {"type", "SET_POWER"},
    {"from", nodeName},
    {"data", {
      {"power", 0}
    }}
  }).dump());
}

void CommandDispatcherConverter::configureYaw(IHub* hub, std::stringstream& command){
  float P, I, D;
  command >> P >> I >> D;
  hub->send("LOCAL", json({
    {"target", yawPIDname},
    {"type", "SET_CONFIG"},
    {"from", nodeName},
    {"data", {
      {"P", P},
      {"I", I},
      {"D", D}
    }}
  }).dump());
}

void CommandDispatcherConverter::configureTimeDelta(IHub* hub, std::stringstream& command){
  unsigned int timeDelta;
  command >> timeDelta;
  hub->send("LOCAL", json({
    {"target", yawPIDname},
    {"type", "SET_DELTA_TIME"},
    {"from", nodeName},
    {"data", {
      {"deltaTime", timeDelta}
    }}
  }).dump());
}

void CommandDispatcherConverter::turnOnEscs(IHub* hub){
  hub->send("LOCAL", json({
    {"target", escSwitchName},
    {"type", "TURN_ON"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::turnOffEscs(IHub* hub){
  hub->send("LOCAL", json({
    {"target", escSwitchName},
    {"type", "TURN_OFF"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::switchLights(IHub* hub){
  hub->send("LOCAL", json({
    {"target", lightSwitchName},
    {"type", "SWITCH"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::turnOnImuSensor(IHub* hub){
  hub->send("LOCAL", json({{"target", accelerometerName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", gyroscopeName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", compassName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", internalTemperatureName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", internalPressureName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", externalTemperatureName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", externalPressureName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
}

void CommandDispatcherConverter::turnOffImuSensor(IHub* hub){
  hub->send("LOCAL", json({{"target", accelerometerName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", gyroscopeName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", compassName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", internalTemperatureName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", internalPressureName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", externalTemperatureName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", externalPressureName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
}

void CommandDispatcherConverter::getAcceleration(IHub* hub){
  hub->send("LOCAL", json({
    {"target", accelerometerName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::getAngularAcceleration(IHub* hub){
  hub->send("LOCAL", json({
    {"target", gyroscopeName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::getHeading(IHub* hub){
  hub->send("LOCAL", json({
    {"target", compassName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::getInternalTemperature(IHub* hub){
  hub->send("LOCAL", json({
    {"target", internalTemperatureName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::getInternalPressure(IHub* hub){
  hub->send("LOCAL", json({
    {"target", internalPressureName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::getExternalTemperature(IHub* hub){
  hub->send("LOCAL", json({
    {"target", externalTemperatureName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::getExternalPressure(IHub* hub){
  hub->send("LOCAL", json({
    {"target", externalPressureName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void CommandDispatcherConverter::logWarning(IHub* hub, std::string warning){
  hub->send("LOCAL", json({
    {"target", "LOGGER"},
    {"type", "WARNING"},
    {"from", nodeName},
    {"data", warning}
  }).dump());
}
