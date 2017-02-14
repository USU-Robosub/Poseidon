#include "IController.h"

class EscController : public IController {
private:
  const uint8_t GPIO_PINS[6] = {36, 39, 41, 47, 49, 53};
public:
  EscController() {
    for(int i = 0; i < 6; i++) {
      pinMode(GPIO_PINS[i], OUTPUT);
      digitalWrite(GPIO_PINS[i], HIGH);
    }
  }
  void execute() {
    uint8_t toggle = SerialTools::readByte();
    for(int i = 0; i < 6; i++) {
      digitalWrite(GPIO_PINS[i], !toggle);
    }
  }
  void kill() {
    for(int i = 0; i < 6; i++) {
      digitalWrite(GPIO_PINS[i], HIGH);
    }
  }
};