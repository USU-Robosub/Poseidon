#ifndef PERIPHERALS_ASSEMBLER_START_H
#define PERIPHERALS_ASSEMBLER_H

#include <string>
#include <iostream>
#include "Node.hpp"

class CommandDispatcherConverter : public Node{
public:

  CommandDispatcherConverter(
    std::istream& inStream,
    std::ostream& outStream,
    std::string moveThrusterName,
    std::string yawPIDname,
    std::string diveThrusterName,
    std::string escSwitchName,
    std::string lightSwitchName,
    std::string accelerometerName,
    std::string gyroscopeName,
    std::string compassName,
    std::string internalTemperatureName,
    std::string internalPressureName,
    std::string externalTemperatureName,
    std::string externalPressureName
  ) :
    inStream(inStream),
    outStream(outStream),
    moveThrusterName(moveThrusterName),
    yawPIDname(yawPIDname),
    diveThrusterName(diveThrusterName),
    escSwitchName(escSwitchName),
    lightSwitchName(lightSwitchName),
    accelerometerName(accelerometerName),
    gyroscopeName(gyroscopeName),
    compassName(compassName),
    internalTemperatureName(internalTemperatureName),
    internalPressureName(internalPressureName),
    externalTemperatureName(externalTemperatureName),
    externalPressureName(externalPressureName) {}

  void update(IHub* hub);
  void process(IHub* hub, std::string* connection, Message* message);
private:
  std::istream& inStream;
  std::ostream& outStream;
  std::string moveThrusterName;
  std::string yawPIDname;
  std::string diveThrusterName;
  std::string escSwitchName;
  std::string lightSwitchName;
  std::string accelerometerName;
  std::string gyroscopeName;
  std::string compassName;
  std::string internalTemperatureName;
  std::string internalPressureName;
  std::string externalTemperatureName;
  std::string externalPressureName;
  void dispatchCommand(IHub* hub, std::stringstream& command);
  void move(IHub* hub, std::stringstream& command);
  void yaw(IHub* hub, std::stringstream& command);
  void dive(IHub* hub, std::stringstream& command);
  void start(IHub* hub);
  void kill(IHub* hub);
  void configureYaw(IHub* hub, std::stringstream& command);
  void configureTimeDelta(IHub* hub, std::stringstream& command);
  void turnOnEscs(IHub* hub);
  void turnOffEscs(IHub* hub);
  void switchLights(IHub* hub);
  void turnOnImuSensor(IHub* hub);
  void turnOffImuSensor(IHub* hub);
  void getAcceleration(IHub* hub);
  void getAngularAcceleration(IHub* hub);
  void getHeading(IHub* hub);
  void getInternalTemperature(IHub* hub);
  void getInternalPressure(IHub* hub);
  void getExternalTemperature(IHub* hub);
  void getExternalPressure(IHub* hub);
  void logWarning(IHub* hub, std::string);
};

#endif
