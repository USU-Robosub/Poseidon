#include "IController.h"

class TemperatureController : public IController {
public:
    TemperatureController() {
        // initialize one-wire interface
    }

    void execute() {
        // get data, convert to degrees C, and return
        SerialTools::writeDouble(0);
    }
    
    void kill() {}
};