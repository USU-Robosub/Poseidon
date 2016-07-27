#include <Servo.h>
#include "IController.h"

enum ServoPin {
  LEFT_FORWARD = 12,
  RIGHT_FORWARD = 11,
  LEFT_STRAFE = 9,
  RIGHT_STRAFE = 8,
  FRONT_DIVE = 7,
  BACK_DIVE = 6
};

class ThrustController : public IController {
 private:
   const uint16_t IDLE = 1500;
   const uint16_t FORWARD = 2000;
   const uint16_t REVERSE = 1000;
   int16_t tunningOffset;
   Servo servo_;
 public:
  ThrustController(ServoPin servoPin) {
    init(servoPin, 0);
  }
  
  ThrustController(ServoPin servoPin, int16_t offset) {
    init(servoPin, offset);
  }

  void init(ServoPin servoPin, int16_t offset) {
    tunningOffset = offset;
    servo_.attach(servoPin);
    servo_.writeMicroseconds(IDLE);
  }
  
  void execute() {
    uint16_t val = readShort();
    servo_.writeMicroseconds(getBoundedThrottle(val));
  }
  
  void kill() {
    servo_.writeMicroseconds(getBoundedThrottle(IDLE));
  }
  
  uint16_t getBoundedThrottle(uint16_t value) {
    uint16_t fVal = value + tunningOffset;
    if(fVal > FORWARD)
      return FORWARD;
    else if(fVal < REVERSE)
      return REVERSE;
    else
      return fVal;
  }
};
