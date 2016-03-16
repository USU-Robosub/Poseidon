#include "IController.h"

class KillSwitchController : public IController {
private:
  volatile bool active;
  IController ** list;
  int count;
  
public:
  KillSwitchController(IController ** _list_, int _count_) {
    list = _list_;
    count = _count_;
  }
    
  void execute() {
    Serial.println(active?'1':'0');
  }
    
  void kill() {
    for(int i = 0; i<count; i++) {
      list[i]->kill();
    }
  }
    
  void isr(int interrupt) {
    noInterrupts();
    active = digitalRead(interrupt) == 1;
    if(active)
      kill();
    interrupts();
  }
};
