#include <Servo.h>
enum Servos {
  FRONT_LEFT = 3,
  FRONT_RIGHT = 5,
  BACK_LEFT = 10,
  BACK_RIGHT = 6
};

uint16_t readShort() {
  while(Serial.available() < 2) {}
  return Serial.read() << 8 | Serial.read();
}

class Controller {
 public:
  virtual void execute() = 0;
};

class ThrustController : public Controller {
 private:
   Servo servo_;
 public:
  ThrustController(Servos servoValue) {
    servo_.attach(servoValue);
  }
  void execute() {
    servo_.writeMicroseconds(readShort());
  }
};

Controller* controllers[4];

void setup() {
  controllers[0] = new ThrustController(FRONT_LEFT);
  controllers[1] = new ThrustController(FRONT_RIGHT);
  controllers[2] = new ThrustController(BACK_LEFT);
  controllers[3] = new ThrustController(BACK_RIGHT);
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    uint8_t controllerNumber = Serial.read();
    controllers[controllerNumber]->execute();
  }
}
