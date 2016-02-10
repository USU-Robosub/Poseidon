#include "ThrustController.h"
#include "EscController.h"
#include "LedController.h"

typedef union _data {
  float f;
  char  s[4];
} floatData;

class Controller {
 public:
  virtual void execute() = 0;
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
