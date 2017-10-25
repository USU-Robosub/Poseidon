#include "IController.h"

class LedController : public IController {
private:
public:
  LedController() {
    pinMode(GpioPin::LED_CTRL_PIN, OUTPUT);
    digitalWrite(GpioPin::LED_CTRL_PIN, LOW);
  }
  void execute() {
    for(int i = 0; i < 2; i++) {
      digitalWrite(GpioPin::LED_CTRL_PIN, HIGH);
      delay(250);
      digitalWrite(GpioPin::LED_CTRL_PIN, LOW);
      delay(250);
    }
  }
  void kill() {
    digitalWrite(GpioPin::LED_CTRL_PIN, LOW);
  }
};