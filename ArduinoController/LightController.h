#include "IController.h"

class LightController : public IController {
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
