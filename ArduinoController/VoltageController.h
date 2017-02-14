#include "IController.h"

#define R1 30000.0
#define R2  7500.0

class VoltageController : public IController {
  private:
    const int VOLT = 10;
  
  public:
    VoltageController() {
      pinMode(VOLT, INPUT);
    }
    
    void execute() {
      int value = analogRead(VOLT);
      /*
       * Measured Values for Calibration
       * P1 = (11.32, 700); P2 = (8.38, 517)
       *
       * Solve for the linear function: x = (y-b)/m
       * voltage = (2.94 * value + 13.56) / 183
       */
      SerialTools::writeDouble((2.94 * value + 13.56) / 183);
    }
    
    void kill() {
      
    }
};

