#include "IController.h"

class StartController : public IController {
private:
  bool activated = false;
public:
  void execute() {
    if(activated) {
      Serial.println("{\"R\":\"1\"}");
    }
    else {
      Serial.println("{\"R\":\"0\"}");
    }
    activated = false;
  }
  void kill() {
    activated = true;
  }
};
