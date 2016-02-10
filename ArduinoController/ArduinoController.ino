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

typedef union _data {
  float f;
  char  s[4];
} floatData;

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
  const uint8_t GPIO_PINS[6] = {35, 39, 41, 47, 49, 53};
public:
  EscController() {
    for(int i = 0; i < 6; i++) {
      pinMode(GPIO_PINS[i], OUTPUT);
      digitalWrite(GPIO_PINS[i], HIGH);
    }
  }
  void execute() {
    while(!Serial.available());
    uint8_t toggle = Serial.read();
    for(int i = 0; i < 6; i++) {
      digitalWrite(GPIO_PINS[i], !toggle);
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
    while(!Serial.available());
    digitalWrite(WHITE, Serial.read());
  }
};

class LightController : public Controller {
private:
  const uint8_t LIGHTS = 45;
public:
  LightController() {
    pinMode(LIGHTS, OUTPUT);
    digitalWrite(LIGHTS, LOW);
  }
  void execute() {
    while(!Serial.available());
    digitalWrite(LIGHTS, !Serial.read());
  }
};

class PingController : public Controller {
public:
  void execute() {
    if(Serial.available())
    {
      Serial.print(Serial.read());
      Serial.print(" ");
    }
    Serial.println("I'm Here!");
  }
};

const uint32_t CONTROLLER_CNT = 10u;
class Controller* controllers[CONTROLLER_CNT];

void setup() {
  Serial.begin(115200);
  
  controllers[0] = new ThrustController(LEFT_FORWARD);
  controllers[1] = new ThrustController(RIGHT_FORWARD);
  controllers[2] = new ThrustController(LEFT_STRAFE);
  controllers[3] = new ThrustController(RIGHT_STRAFE);
  controllers[4] = new ThrustController(FRONT_DIVE);
  controllers[5] = new ThrustController(BACK_DIVE);
  controllers[6] = new EscController();
  controllers[7] = new LedController();
  controllers[8] = new PingController();
  controllers[9] = new LightController();
}

void loop() {
  if(Serial.available()) {
    uint8_t controllerNumber = Serial.read();
    if(controllerNumber < CONTROLLER_CNT)
      // only execute if a command exists
      controllers[controllerNumber]->execute();
  }
}
