#include "IController.h"

class StartController : public IController {
private:
  bool activated = false;
  const int ACTIVE   = 0x1;
  const int INACTIVE = 0x0;
  
public:
  void execute() {
    SerialTools::writeByte(activated?ACTIVE:INACTIVE);
    activated = false;
  }
  void kill() {
    activated = true;
  }
};
