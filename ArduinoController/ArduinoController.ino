#include "ThrustController.h"
#include "EscController.h"
#include "LedController.h"
#include "LightController.h"
#include "PingController.h"
#include "KillSwitchController.h"
#include "VoltageController.h"
#include "StartController.h"
#include "PressureController.h"
#include "TemperatureController.h"

const uint32_t CONTROLLER_CNT = 15u;
class IController* controllers[CONTROLLER_CNT];

void setup() {
  delay(1);
  SerialTools::begin(USB,115200);
  SerialTools::begin(DEBUG,9600);
  DMSGN("Due Ready!");
  SerialTools::writeString("Ready!", 6);
  
  controllers[0]= new KillSwitchController(controllers, CONTROLLER_CNT);
  attachInterrupt(
    digitalPinToInterrupt(GpioPin::KILLSWITCH_PIN), 
    [](){((KillSwitchController*)controllers[0])->isr(GpioPin::KILLSWITCH_PIN);},
    CHANGE
  );
  controllers[1]  = new ThrustController(PwmPin::MOVE_PIN);
  controllers[2]  = new ThrustController(PwmPin::STRAFE_PIN);
  controllers[3]  = new ThrustController(PwmPin::DIVE_PIN);
  controllers[4]  = new ThrustController(PwmPin::YAW_PIN);
  controllers[5]  = new ThrustController(PwmPin::PITCH_PIN);
  controllers[6]  = new ThrustController(PwmPin::ROLL_PIN);
  controllers[7]  = new EscController();
  controllers[8]  = new LedController();
  controllers[9]  = new PingController();
  controllers[10] = new LightController();
  controllers[11] = new VoltageController();
  controllers[12] = new StartController();
  controllers[13] = new PressureController();
  controllers[14] = new TemperatureController();
  
  while((!Serial.available())||(Serial.read()==0));
}

void loop() {
  uint8_t controllerIndex = SerialTools::readByte();
  if(controllerIndex < CONTROLLER_CNT) {
    // only execute if a command exists
    DMSG("Controller: "); DMSGN(controllerIndex);
    controllers[controllerIndex]->execute();
  }
}
