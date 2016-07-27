#include "ThrustController.h"
#include "EscController.h"
#include "LedController.h"
#include "LightController.h"
#include "PingController.h"
#include "KillSwitchController.h"
#include "VoltageController.h"
#include "StartController.h"

const uint8_t KILLPIN = 50;
const uint8_t KILL_ADDR = 10;
const uint32_t CONTROLLER_CNT = 13u;
class IController* controllers[CONTROLLER_CNT];

void setup() {
  Serial.begin(115200);
  
  controllers[0] = new ThrustController(LEFT_FORWARD, 50);
  controllers[1] = new ThrustController(RIGHT_FORWARD, 50);
  controllers[2] = new ThrustController(LEFT_STRAFE, 50);
  controllers[3] = new ThrustController(RIGHT_STRAFE, 50);
  controllers[4] = new ThrustController(FRONT_DIVE);
  controllers[5] = new ThrustController(BACK_DIVE);
  controllers[6] = new EscController();
  controllers[7] = new LedController();
  controllers[8] = new PingController();
  controllers[9] = new LightController();
  controllers[11]= new VoltageController();
  controllers[12]= new StartController();
  controllers[KILL_ADDR]= new KillSwitchController(controllers, CONTROLLER_CNT, KILL_ADDR);
  attachInterrupt(
    digitalPinToInterrupt(KILLPIN), 
    [](){((KillSwitchController*)controllers[KILL_ADDR])->isr(KILLPIN);},
    CHANGE
  );
}

void loop() {
  if(Serial.available()) {
    uint8_t controllerNumber = Serial.read();
    if(controllerNumber < CONTROLLER_CNT)
      // only execute if a command exists
      controllers[controllerNumber]->execute();
  }
}
