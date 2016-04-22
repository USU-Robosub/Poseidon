#include "IController.h"

class PingController : public IController {
public:
  void execute() {
    if(Serial.available())
    {
      Serial.print(Serial.read());
      Serial.print(" ");
    }
    Serial.println("I'm Here!");
  }
  void kill() { }
};
