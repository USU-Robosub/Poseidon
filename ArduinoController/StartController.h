#include "IController.h"

class StartController : public IController {
private:
  bool activated = false;
public:
  void execute() {
    SerialTools::writeByte(activated?0x1:0x0);
    activated = false;
  }
  void kill() {
    activated = true;
  }
};
