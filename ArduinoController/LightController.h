#include "IController.h"

class LightController : public IController {
private:
  const uint8_t LIGHTS = 45;
public:
  LightController() {
    pinMode(LIGHTS, OUTPUT);
    kill();
  }
  void execute() {
    while(!Serial.available());
    digitalWrite(LIGHTS, !Serial.read());
  }
  void kill() {
    digitalWrite(LIGHTS, HIGH);
  }
};
