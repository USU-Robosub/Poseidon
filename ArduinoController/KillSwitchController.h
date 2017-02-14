#include "IController.h"

class KillSwitchController : public IController {
private:
  volatile int active;
  IController ** list;
  int count, self;
  const int STAT_LED = 22;
  
public:
  KillSwitchController(IController ** _list_, int _count_, int _self_) {
    list = _list_;
    count = _count_;
    self = _self_;
    pinMode(STAT_LED, OUTPUT);
  }

  void execute() {
    SerialTools::writeByte(active?0x1:0x0);
  }

  void kill() {
    for(int i = 0; i<count; i++) {
      if(i != self)
        list[i]->kill();
    }
  }

  void isr(int interrupt) {
    noInterrupts();
    // when not active, interrupt pin read a '1'
    // when active, interrupt pin read a '0'
    active = !digitalRead(interrupt);
    if(active)
      kill();
    digitalWrite(STAT_LED, active);
    interrupts();
  }
};
