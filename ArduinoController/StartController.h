#include "IController.h"

class StartController : public IController {
private:
  bool activated;
public:
  void execute() {
    if(activated) {
      Serial.println("1");
    }
    else {
      Serial.println("0");
    }
    activated = false;
  }
  void kill() {
    activated = true;
  }
};
