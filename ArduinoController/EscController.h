#include "IController.h"

class EscController : public IController {
private:
  const uint8_t GPIO_PINS[6] = {35, 39, 41, 47, 49, 53};
public:
  EscController() {
    for(int i = 0; i < 6; i++) {
      pinMode(GPIO_PINS[i], OUTPUT);
      digitalWrite(GPIO_PINS[i], HIGH);
    }
  }
  void execute() {
    while(!Serial.available());
    uint8_t toggle = Serial.read();
    for(int i = 0; i < 6; i++) {
      digitalWrite(GPIO_PINS[i], !toggle);
    }
  }
};