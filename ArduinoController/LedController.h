#include "IController.h"

class LedController : public IController {
private:
public:
  LedController() {
    pinMode(GPIO::LED_CTRL_PIN, OUTPUT);
    digitalWrite(GPIO::LED_CTRL_PIN, LOW);
  }
  void execute() {
    for(int i = 0; i < 2; i++) {
      digitalWrite(GPIO::LED_CTRL_PIN, HIGH);
      delay(250);
      digitalWrite(GPIO::LED_CTRL_PIN, LOW);
      delay(250);
    }
  }
  void kill() {
    digitalWrite(GPIO::LED_CTRL_PIN, LOW);
  }
};