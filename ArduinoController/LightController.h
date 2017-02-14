#include "IController.h"

class LightController : public IController {
private:
  const uint8_t LIGHTS = 45;
public:
  LightController() {
    pinMode(LIGHTS, OUTPUT);
    digitalWrite(LIGHTS, HIGH);
  }
  void execute() {
    digitalWrite(LIGHTS, !SerialTools::readByte());
  }
  void kill() {
    //digitalWrite(LIGHTS, HIGH);
  }
};
