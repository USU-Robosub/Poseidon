#include "IController.h"

class KillSwitchController : public IController {
private:
  const uint8_t KILLPIN = 50;
  volatile bool active;
  auto f;
public:
  KillSwitchController(void (*iExec)()) {
    f = iExec;
    //attachInterrupt(digitalPinToInterrupt(KILLPIN), ISR0, CHANGE);
  }
  void execute() {
    Serial.println(active?'1':'0');
  }
  void ISR0() {
    noInterrupts();
    active = digitalRead(KILLPIN) == 1;
    if(active)
      (*f)();
    interrupts();
  }
};
