#include "CommandDispatcherConverter.h"

void CommandDispatcherConverter::update(IHub* hub){
  while(inStream.hasLine()){
    std::string commandString = inStream.readLine();
    std::stringstream command(commandString);
    dispatchCommand(hub, command);
  }
}

void CommandDispatcherConverter::process(IHub* hub, std::string connection, json message){
  if(message["target"] == nodeName){
    if(message["type"] == "GOT"){
      if(message["from"] == accelerometerName){
        outStream << json({
          {"Type", "Acceleration"},
          {"X", message["data"]["x"]},
          {"Y", message["data"]["y"]},
          {"Z", message["data"]["z"]}
        });
      }else if(message["from"] == gyroscopeName){
        outStream << json({
          {"Type", "AngularAcceleration"},
          {"X", message["data"]["x"]},
          {"Y", message["data"]["y"]},
          {"Z", message["data"]["z"]}
        });
      }else if(message["from"] == compassName){
        outStream << json({
          {"Type", "Heading"},
          {"x", message["data"]["x"]},
          {"y", message["data"]["y"]},
          {"z", message["data"]["z"]},
          {"azimuth", message["data"]["azimuth"]},
          {"inclination", message["data"]["inclination"]}
        });
      }else if(message["from"] == internalTemperatureName){
        outStream << json({
          {"Type", "InternalPressure"},
          {"Value", message["data"]["value"]}
        });
      }else if(message["from"] == internalPressureName){
        outStream << json({
          {"Type", "InternalPressure"},
          {"Value", message["data"]["value"]}
        });
      }else if(message["from"] == externalTemperatureName){
        outStream << json({
          {"Type", "ExternalTemperature"},
          {"Value", message["data"]["value"]}
        });
      }else if(message["from"] == externalPressureName){
        outStream << json({
          {"Type", "ExternalPressure"},
          {"Value", message["data"]["value"]}
        });
      }
    }
  }
}

void CommandDispatcherConverter::dispatchCommand(IHub* hub, std::stringstream& command){
  std::string cmd;
  command >> cmd;
  // starts pid |
  if (cmd == "startThrusters")                start();
  // set power move motor |
  else if(cmd == "move")                      move(hub, command);
  // set yaw pid target |
  else if(cmd == "yaw")                       yaw(hub, command);
  // set power dive motor |
  else if(cmd == "dive")                      dive(hub, command);
  // end pid and set power 0 all motors |
  else if(cmd == "killThrusters")             kill();
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
  else if(cmd == "getAngularAcceleration")    getAngularAcceleration();
  // read compass then send back |
  else if(cmd == "getHeading")                getHeading();
  // read internal temp then send back |
  else if(cmd == "getInternalTemperature")    getInternalTemperature();
  // read internal press then send back |
  else if(cmd == "getInternalPressure")       getInternalPressure();
  // read external temp then send back |
  else if(cmd == "getExternalTemperature")    getExternalTemperature();
  // read external press then send back |
  else if(cmd == "getExternalPressure")       getExternalPressure();
  // closes app |
  else if(cmd == "exit")                      hub->exit();
  // logs a warning |
  else                                        logWarning("Invalid command");
}

void start(IHub* hub){
  hub->send("LOCAL", json({
    {"target", yawPIDname},
    {"type", "ENABLE"},
    {"from", nodeName}
  }).dump());
}

void move(IHub* hub, std::stringstream& command){
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

void yaw(IHub* hub, std::stringstream& command){
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

void dive(IHub* hub, std::stringstream& command){
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

void kill(IHub* hub){
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

void configureYaw(IHub* hub, std::stringstream& command){
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

void configureTimeDelta(IHub* hub, std::stringstream& command){
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

void turnOnEscs(IHub* hub){
  hub->send("LOCAL", json({
    {"target", escSwitchName},
    {"type", "TURN_ON"},
    {"from", nodeName}
  }).dump());
}

void turnOffEscs(IHub* hub){
  hub->send("LOCAL", json({
    {"target", escSwitchName},
    {"type", "TURN_OFF"},
    {"from", nodeName}
  }).dump());
}

void switchLights(IHub* hub){
  hub->send("LOCAL", json({
    {"target", lightSwitchName},
    {"type", "SWITCH"},
    {"from", nodeName}
  }).dump());
}

void turnOnImuSensor(IHub* hub){
  hub->send("LOCAL", json({{"target", accelerometerName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", gyroscopeName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", compassName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", internalTemperatureName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", internalPressureName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", externalTemperatureName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", externalPressureName}, {"type", "AWAKE"}, {"from", nodeName}}).dump());
}

void turnOffImuSensor(IHub* hub){
  hub->send("LOCAL", json({{"target", accelerometerName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", gyroscopeName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", compassName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", internalTemperatureName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", internalPressureName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", externalTemperatureName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
  hub->send("LOCAL", json({{"target", externalPressureName}, {"type", "SLEEP"}, {"from", nodeName}}).dump());
}

void getAcceleration(IHub* hub){
  hub->send("LOCAL", json({
    {"target", accelerometerName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void getAngularAcceleration(IHub* hub){
  hub->send("LOCAL", json({
    {"target", gyroscopeName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void getHeading(IHub* hub){
  hub->send("LOCAL", json({
    {"target", compassName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void getInternalTemperature(IHub* hub){
  hub->send("LOCAL", json({
    {"target", internalTemperatureName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void getInternalPressure(IHub* hub){
  hub->send("LOCAL", json({
    {"target", internalPressureName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void getExternalTemperature(IHub* hub){
  hub->send("LOCAL", json({
    {"target", externalTemperatureName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void getExternalPressure(IHub* hub){
  hub->send("LOCAL", json({
    {"target", externalPressureName},
    {"type", "GET"},
    {"from", nodeName}
  }).dump());
}

void logWarning(IHub* hub, std::string warning){
  hub->send("LOCAL", json({
    {"target", "LOGGER"},
    {"type", "WARNING"},
    {"from", nodeName},
    {"data", warning}
  }).dump());
}
