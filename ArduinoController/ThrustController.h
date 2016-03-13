#include <Servo.h>
#include "IController.h"

enum ServoPin {
  LEFT_FORWARD = 11,
  RIGHT_FORWARD = 10,
  LEFT_STRAFE = 9,
  RIGHT_STRAFE = 8,
  FRONT_DIVE = 7,
  BACK_DIVE = 6
};

uint16_t readShort() {
  while(Serial.available() < 2) {}
  return Serial.read() << 8 | Serial.read();
}

class ThrustController : public IController {
 private:
   const uint16_t IDLE = 1500;
   Servo servo_;
 public:
  ThrustController(ServoPin servoPin) {
    servo_.attach(servoPin);
    servo_.writeMicroseconds(IDLE);
  }
  void execute() {
    uint16_t val = readShort();
    servo_.writeMicroseconds(val);
  }
};
