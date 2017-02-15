#include "IController.h"

class LedController : public IController {
private:
public:
  LedController() {
    pinMode(LED_CTRL_PIN, OUTPUT);
    digitalWrite(LED_CTRL_PIN, LOW);
  }
  void execute() {
    for(int i = 0; i < 2; i++) {
      digitalWrite(LED_CTRL_PIN, HIGH);
      delay(250);
      digitalWrite(LED_CTRL_PIN, LOW);
      delay(250);
    }
  }
  void kill() {
    digitalWrite(LED_CTRL_PIN, LOW);
  }
};
