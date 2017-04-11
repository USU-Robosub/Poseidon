#include "IController.h"

#define GRAVITY 9.86
#define WATER_DENSITY 1 /* at 4°C */

class PressureController : public IController {
private:
    double scale;
public:
    PressureController() {
        scale = (3.3/4096)*(2.9E6/2.64);
        pinMode(AdcPin::PRESSURE_PIN,INPUT);
    }

    void execute() {
        int raw = analogRead(AdcPin::PRESSURE_PIN);
        double pressure = raw*scale; // in pascals
        double depth = pressure / (GRAVITY * WATER_DENSITY); // in meters
        DMSG("Pressure: ");
        DMSG(pressure);
        DMSG(", Depth: ");
        DMSGN(depth);
        SerialTools::writeDouble(depth);
    }
    
    void kill() {}
};
