#include "IController.h"

class PingController : public IController {
public:
  void execute() {
    SerialTools::writeString("I'm Here!", 9);
  }
  void kill() { }
};
