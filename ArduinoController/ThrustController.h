#include <Servo.h>
#include "IController.h"

class ThrustController : public IController {
 private:
   const uint16_t IDLE    = 1500;
   const uint16_t FORWARD = 2000;
   const uint16_t REVERSE = 1000;
   Servo servo_;
 public:
  ThrustController(uint8_t servoPin) {
    servo_.attach(servoPin);
    servo_.writeMicroseconds(IDLE);
  }
  
  void execute() {
    uint16_t val = SerialTools::readUShort();
    servo_.writeMicroseconds(getBoundedThrottle(val));
  }
  
  void kill() {
    servo_.writeMicroseconds(IDLE);
  }
  
  uint16_t getBoundedThrottle(uint16_t value) {
    if(value > FORWARD) return FORWARD;
    else if(value < REVERSE) return REVERSE;
    else return value;
  }
};