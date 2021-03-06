#include "IController.h"

class LightController : public IController {
public:
  LightController() {
    pinMode(GpioPin::LIGHTS_PIN, OUTPUT);
    digitalWrite(GpioPin::LIGHTS_PIN, HIGH);
  }
  void execute() {
    digitalWrite(GpioPin::LIGHTS_PIN, !SerialTools::readByte());
  }
  void kill() { }
};