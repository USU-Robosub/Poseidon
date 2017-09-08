#ifndef TANK_CONTROLLER_H
#define TANK_CONTROLLER_H

#include "IController.h"
#include <Arduino.h>

#define ENA 5
#define ENB 6
#define MOTOR_INPUT1 8
#define MOTOR_INPUT2 7
#define MOTOR_INPUT3 12
#define MOTOR_INPUT4 13
#define MOTOR_STOP    {\
    digitalWrite(MOTOR_INPUT1,LOW ); digitalWrite(MOTOR_INPUT2,LOW );\
    digitalWrite(MOTOR_INPUT3,LOW ); digitalWrite(MOTOR_INPUT4,LOW );\
}

class TankController {
public:
  TankController() : yawPower(0), movePower(0) {
    pinMode(ENA,OUTPUT); // power level pin for left side
    pinMode(ENB,OUTPUT); // power level pin for the right side
    pinMode(MOTOR_INPUT1,OUTPUT); // direction control for right side
    pinMode(MOTOR_INPUT2,OUTPUT); // <-/
    pinMode(MOTOR_INPUT3,OUTPUT); // direction control for left side
    pinMode(MOTOR_INPUT4,OUTPUT); // <-/
  }
  void updateYaw(float power) {
    yawPower = power;
    update();
  }
  void updateMove(float power) {
    movePower = power;
    update();
  }
  void update(){
    float s = 1;
    float m = (movePower > 0) ? movePower : -movePower;
    float y = (yawPower > 0) ? yawPower : -yawPower;
    if(m == 0 || y == 0)  s = 1;
    else if(m == 1)       s = 1 + y;
    else if(y == 1)       s = 1 + m;
    else                  s = 1 + (m + y) / 2.0F;
    float left = (movePower - yawPower) / s;
    float right = (movePower + yawPower) / s;
    const int SCALE = 165;
    const float DELTA = 0.05F;
    int lstate, rstate;

    // get direction of left motor, and kill motor when close to center
    if (inRange(left, DELTA))   lstate = 0;
    else if (left > 0)          lstate = 1;
    else                        lstate = -1;
    // get direction of right motor, and kill motor when close to center
    if (inRange(right, DELTA))  rstate = 0;
    else if (right > 0)         rstate = 1;
    else                        rstate = -1;

    int lres, rres;
    // make power level positive, scaled, then centered at 90
    lres = (lstate *  left) * SCALE + 90;
    rres = (rstate * right) * SCALE + 90;

    MOTOR_STOP;
    analogWrite(ENB,lres); // PWM to ENB pin
    analogWrite(ENA,rres); // PWM to ENA pin
    // set direction of left motor by turning pins MOTOR_INPUT3 and MOTOR_INPUT4 on/off
    if(lstate > 0)      { digitalWrite(MOTOR_INPUT3,LOW ); digitalWrite(MOTOR_INPUT4,HIGH); }
    else if(lstate < 0) { digitalWrite(MOTOR_INPUT3,HIGH); digitalWrite(MOTOR_INPUT4,LOW ); }
    else                { digitalWrite(MOTOR_INPUT3,LOW ); digitalWrite(MOTOR_INPUT4,LOW ); }
    // set direction of right motor by turning pins MOTOR_INPUT3 and MOTOR_INPUT4 on/off
    if(rstate > 0)      { digitalWrite(MOTOR_INPUT1,LOW ); digitalWrite(MOTOR_INPUT2,HIGH); }
    else if(rstate < 0) { digitalWrite(MOTOR_INPUT1,HIGH); digitalWrite(MOTOR_INPUT2,LOW ); }
    else                { digitalWrite(MOTOR_INPUT1,LOW ); digitalWrite(MOTOR_INPUT2,LOW ); }
  }
  void kill() {
    MOTOR_STOP
  }
  bool inRange(float value, float delta) {
    return (value <= delta) && (value >= -delta);
  }
private:
  float yawPower = 0;
  float movePower = 0;
};

class TankYawController : public IController {
public:
  TankYawController(TankController* tankController) : tankController(tankController) {}
  void execute() {
    uint16_t val = SerialTools::readUShort();
    float power = (static_cast<int16_t>(val) - 1500) / 500.0F;
    tankController->updateYaw(power);
  }
  void kill() {
    tankController->kill();
  }
private:
  TankController* tankController;
};

class TankMoveController : public IController {
public:
  TankMoveController(TankController* tankController) : tankController(tankController) {}
  void execute() {
    uint16_t val = SerialTools::readUShort();
    float power = (static_cast<int16_t>(val) - 1500) / 500.0F;
    tankController->updateMove(power);
  }
  void kill() {
    tankController->kill();
  }
private:
  TankController* tankController;
};

#endif
