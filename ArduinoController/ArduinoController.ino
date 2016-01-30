#include <Servo.h>

enum ServoPin {
  // TODO: Assign pins
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

class Controller {
 public:
  virtual void execute() = 0;
};

class ThrustController : public Controller {
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

class EscController : public Controller {
private:
  const uint8_t GPIO_PINS[6] = {39, 41, 43, 49, 51, 53};
public:
  EscController() {
    for(int i = 0; i < 6; i++) {
      pinMode(GPIO_PINS[i], OUTPUT);
      digitalWrite(GPIO_PINS[i], LOW);
    }
  }
  void execute() {
    while(!Serial.available());
    uint8_t toggle = Serial.read();
    for(int i = 0; i < 6; i++) {
      digitalWrite(GPIO_PINS[i], toggle);
    }
  }
};

class LedController : public Controller {
private:
  const uint8_t GREEN = 22;
  const uint8_t WHITE = 52;
public:
  LedController() {
    pinMode(WHITE, OUTPUT);
    digitalWrite(WHITE, LOW);
  }
  void execute() {
    for(int i = 0; i < 2; i++) {
      digitalWrite(WHITE, HIGH);
      delay(250);
      digitalWrite(WHITE, LOW);
      delay(250);
    }
  }
};

Controller* controllers[8];

void setup() {
  controllers[0] = new ThrustController(LEFT_FORWARD);
  controllers[1] = new ThrustController(RIGHT_FORWARD);
  controllers[2] = new ThrustController(LEFT_STRAFE);
  controllers[3] = new ThrustController(RIGHT_STRAFE);
  controllers[4] = new ThrustController(FRONT_DIVE);
  controllers[5] = new ThrustController(BACK_DIVE);
  controllers[6] = new EscController();
  controllers[7] = new LedController();
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    uint8_t controllerNumber = Serial.read();
    controllers[controllerNumber]->execute();
  }
}