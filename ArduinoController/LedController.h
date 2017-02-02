#include "IController.h"

class LedController : public IController {
private:
  uint8_t green_;
  uint8_t white_;
public:
  LedController(JsonObject& pins) : green_(pins["green"]), white_(pins["white"]) {
    pinMode(white_, OUTPUT);
    digitalWrite(white_, LOW);
  }
  void execute() {
    for(int i = 0; i < 2; i++) {
      digitalWrite(white_, HIGH);
      delay(250);
      digitalWrite(white_, LOW);
      delay(250);
    }
  }
  void kill() {
    digitalWrite(green_, LOW);
    digitalWrite(white_, LOW);
  }
};
