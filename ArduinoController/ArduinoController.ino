#include <Servo.h>
enum ServoPin {
  // TODO: Assign pins
  LEFT_FORWARD = -1,
  RIGHT_FORWARD = -1,
  LEFT_STRAFE = -1,
  RIGHT_STRAFE = -1,
  FRONT_DIVE = -1,
  BACK_DIVE = -1
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
  ThrustController(ServoPin servoPin) {
    servo_.attach(servoPin);
  }
  void execute() {
    servo_.writeMicroseconds(readShort());
  }
};

class EscController : public Controller {
public:
  void execute() {
    while(!Serial.available());
    uint8_t toggle = Serial.read();
    int gpioPins[] = {39, 41, 43, 49, 51, 53};
    for(int i = 0; i < 6; i++) {
      digitalWrite(gpioPins[i], toggle);
    }
  }
};

Controller* controllers[6];

void setup() {
  controllers[0] = new ThrustController(LEFT_FORWARD);
  controllers[1] = new ThrustController(RIGHT_FORWARD);
  controllers[2] = new ThrustController(LEFT_STRAFE);
  controllers[3] = new ThrustController(RIGHT_STRAFE);
  controllers[4] = new ThrustController(FRONT_DIVE);
  controllers[5] = new ThrustController(BACK_DIVE);
  controllers[6] = new EscController();
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    uint8_t controllerNumber = Serial.read();
    controllers[controllerNumber]->execute();
  }
}
