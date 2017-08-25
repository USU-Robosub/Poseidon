#ifndef PID_NODE_H
#define PID_NODE_H

#include "Node.hpp"

class PIDnode : public Node{
public:
  PIDnode(std::string sensorName, std::string actuatorName, float P, float I, float D, float target) :
    sensorName(sensorName),
    actuatorName(actuatorName),
    P(P), I(I), D(D),
    target(target),
    integral(0),
    derivative(0),
    previousError(0),
    lastSensorReading(0),
    isRunning(false) {}

  void update(IHub* hub);
  void process(IHub* hub, std::string* connectionName, Message* message);
  float getLastSensorReading();
  float getTarget();
  float getP();
  float getI();
  float getD();
  bool isEnabled();
  void enable();
  void setSensorValue(float sensorValue);
private:
  std::string sensorName;
  std::string actuatorName;
  float P, I, D;
  float target;
  float integral;
  float derivative;
  float previousError;
  float lastSensorReading;
  bool isRunning;
};

#endif
