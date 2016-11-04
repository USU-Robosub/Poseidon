#include "IController.h"

#define R1 30000.0
#define R2  7500.0

class VoltageController : public IController {
  private:
    uint8_t volt_;
  
  public:
    VoltageController(uint8_t volt) : volt_(volt) {
      pinMode(volt_, INPUT);
    }
    
    void execute() {
      int value = analogRead(volt_);
      /*
       * Measured Values for Calibration
       * P1 = (11.32, 700); P2 = (8.38, 517)
       *
       * Solve for the linear function: x = (y-b)/m
       * voltage = (2.94 * value + 13.56) / 183
       */      
      Serial.println((2.94 * value + 13.56) / 183);
    }
    
    void kill() {
      
    }
};

