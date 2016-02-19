#include "IController.h"

class LedController : public IController {
private:
  const uint8_t GREEN = 22;
  const uint8_t WHITE = 52;
public:
  LedController() {
    pinMode(WHITE, OUTPUT);
    digitalWrite(WHITE, LOW);
  }
  void execute() {
    for(int i = 0; i < 2; i++) {
      digitalWrite(WHITE, HIGH);
      delay(250);
      digitalWrite(WHITE, LOW);
      delay(250);
    }
  }
};
