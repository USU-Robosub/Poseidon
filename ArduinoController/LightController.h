#include "IController.h"

class LightController : public IController {
public:
  LightController() {
    pinMode(LIGHTS_PIN, OUTPUT);
    digitalWrite(LIGHTS_PIN, HIGH);
  }
  void execute() {
    digitalWrite(LIGHTS_PIN, !SerialTools::readByte());
  }
  void kill() { }
};