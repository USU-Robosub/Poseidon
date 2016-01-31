#include "ThrustController.h"
#include "EscController.h"
#include "LedController.h"

IController* controllers[8];

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
