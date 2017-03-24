#include "IController.h"

class LightController : public IController {
public:
  LightController() {
    pinMode(GPIO::LIGHTS_PIN, OUTPUT);
    digitalWrite(GPIO::LIGHTS_PIN, HIGH);
  }
  void execute() {
    digitalWrite(GPIO::LIGHTS_PIN, !SerialTools::readByte());
  }
  void kill() { }
};