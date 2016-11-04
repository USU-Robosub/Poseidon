#include "IController.h"

class LightController : public IController {
private:
  uint8_t lights_ = 45;
public:
  LightController(uint8_t lights) : lights_(lights) {
    pinMode(lights_, OUTPUT);
    digitalWrite(lights_, HIGH);
  }
  void execute() {
    while(!Serial.available());
    digitalWrite(lights_, !Serial.read());
  }
  void kill() {
    //digitalWrite(LIGHTS, HIGH);
  }
};
