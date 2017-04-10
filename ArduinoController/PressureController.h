#include "IController.h"

class PressureController : public IController {
public:
    PressureController() {
        // initialize analog pin
    }

    void execute() {
        // read analog value, convert to meters, return
        SerialTools::writeDouble(0);
    }
    
    void kill() {}
};