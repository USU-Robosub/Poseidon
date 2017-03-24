#include "IController.h"

class KillSwitchController : public IController {
private:
  volatile int active;
  IController ** list;
  const int ACTIVE   = 0x1;
  const int INACTIVE = 0x0;
  int count;
  
public:
  KillSwitchController(IController ** _list_, int _count_) {
    list = _list_;
    count = _count_;
    pinMode(GPIO::LED_STAT_PIN, OUTPUT);
  }

  void execute() {
    SerialTools::writeByte(active ? ACTIVE : INACTIVE);
  }

  void kill() {
    for(int i = 1; i < count; i++)
      list[i]->kill();
  }

  void isr(int interrupt) {
    noInterrupts();
    // when not active, interrupt pin read a '1'
    // when active, interrupt pin read a '0'
    active = !digitalRead(interrupt);
    if(active)
      kill();
    digitalWrite(GPIO::LED_STAT_PIN, active);
    interrupts();
  }
};
