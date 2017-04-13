#include "IController.h"

class StartController : public IController {
private:
  bool pending = false;
  uint8_t value = 0;
  const int ACTIVE   = 0x1;
  const int INACTIVE = 0x0;
  
public:
  bool isPending() {
    return pending;
  }
  void execute() {
    SerialTools::writeByte(value, EVENT);
    pending = false;
  }
  void kill() {
    value = digitalRead(GpioPin::KILLSWITCH_PIN);
    pending = true;
  }
};
