#include "IController.h"

#define GPIO_CNT 6u

class EscController : public IController {
  
private:
  uint8_t GPIO_PINS[GPIO_CNT] = {
    ESC_S1_PIN,
    ESC_S2_PIN,
    ESC_S3_PIN,
    ESC_S4_PIN,
    ESC_S5_PIN,
    ESC_S6_PIN
  };
public:
  EscController() {
    for(uint32_t i = 0; i < GPIO_CNT; i++) {
      pinMode(GPIO_PINS[i], OUTPUT);
      digitalWrite(GPIO_PINS[i], HIGH);
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
    uint8_t toggle = SerialTools::readByte();
    for(uint32_t i = 0; i < GPIO_CNT; i++) {
      digitalWrite(GPIO_PINS[i], !toggle);
    }
  }
  
  void kill() {
    for(uint32_t i = 0; i < GPIO_CNT; i++) {
      digitalWrite(GPIO_PINS[i], HIGH);
    }
  }
};

#undef GPIO_CNT