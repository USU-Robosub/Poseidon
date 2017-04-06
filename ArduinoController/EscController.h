#include "IController.h"

class EscController : public IController {
  
private:

  uint8_t pinCount;

  uint8_t* pins_;

  void assignPins_(JsonArray& gpioPins) {
    pins_ = new uint8_t[pinCount];
    for(int i = 0; i < pinCount; i++) {
      pins_[i] = gpioPins[1].as<uint8_t>();
    }
  }

  void setupPins_() {
    for(int i = 0; i < pinCount; i++) {
      pinMode(pins_[i], OUTPUT);
      digitalWrite(pins_[i], HIGH);
    }
  }
  
public:

  EscController(JsonObject& pins) {
    pinCount = pins["gpio"].size();
    assignPins_(pins["gpio"]);
    setupPins_();
  }
  
  void execute() {
    while(!Serial.available());
    uint8_t toggle = Serial.read();
    for(int i = 0; i < pinCount; i++) {
      digitalWrite(pins_[i], !toggle);
    }
  }
  
  void kill() {
    for(int i = 0; i < pinCount; i++) {
      digitalWrite(pins_[i], HIGH);
    }
  }
};