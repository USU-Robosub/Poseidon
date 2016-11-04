#include <ArduinoJson.h>

#include "ThrustController.h"
#include "EscController.h"
#include "LedController.h"
#include "LightController.h"
#include "PingController.h"
#include "KillSwitchController.h"
#include "VoltageController.h"
#include "StartController.h"
#include "PinJSON.h"

const uint8_t KILLPIN = 50; // Needs to remain global (therefore outside of JSON) for lambda interrupt
const uint8_t KILL_ADDR = 10;
const uint32_t CONTROLLER_CNT = 13u;
class IController* controllers[CONTROLLER_CNT];

void setup() {
  Serial.begin(115200);
  DynamicJsonBuffer buffer;
  auto json = buffer.parse(PinJSON::json);
  
  controllers[0] = new ThrustController(json["thrust"]["left_forward"].as<uint8_t>(), 50);
  controllers[1] = new ThrustController(json["thrust"]["right_forward"].as<uint8_t>(), 50);
  controllers[2] = new ThrustController(json["thrust"]["left_strafe"].as<uint8_t>(), 50);
  controllers[3] = new ThrustController(json["thrust"]["right_strafe"].as<uint8_t>(), 50);
  controllers[4] = new ThrustController(json["thrust"]["front_dive"].as<uint8_t>());
  controllers[5] = new ThrustController(json["thrust"]["back_dive"].as<uint8_t>());
  controllers[6] = new EscController(json["esc"].asObject());
  controllers[7] = new LedController(json["led"].asObject());
  controllers[8] = new PingController();
  controllers[9] = new LightController(json["light"]["lights"].as<uint8_t>());
  controllers[11]= new VoltageController(json["voltage"]["volt"].as<uint8_t>());
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
