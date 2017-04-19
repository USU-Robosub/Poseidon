#include "IController.h"

class VoltageController : public IController {
  private:
    const double R1 = 30000.0;
    const double R2 =  7500.0;
  public:
    VoltageController() {
      pinMode(GpioPin::VOLT_PIN, INPUT);
    }
    
    void execute() {
      int value = analogRead(GpioPin::VOLT_PIN);
      /*
       * Measured Values for Calibration
       * P1 = (11.32, 700); P2 = (8.38, 517)
       *
       * Solve for the linear function: x = (y-b)/m
       * voltage = (2.94 * value + 13.56) / 183
       */
      SerialTools::writeDouble((2.94 * value + 13.56) / 183);
    }
    
    void kill() { }
};