#include "ThrustController.h"
#include "EscController.h"
#include "LedController.h"
#include "LightController.h"
#include "PingController.h"

const uint32_t CONTROLLER_CNT = 10u;
class IController* controllers[CONTROLLER_CNT];

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
