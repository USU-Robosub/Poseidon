#include "IController.h"
#include <OneWire.h> 
#include <DallasTemperature.h>

class TemperatureController : public IController {
private:
    OneWire oneWire;
    DallasTemperature sensors;
public:
    TemperatureController()
      : oneWire(GpioPin::TEMPERATURE_PIN), sensors(&oneWire) {
        sensors.begin();
    }

    void execute() {
        sensors.requestTemperatures();
        double res = sensors.getTempCByIndex(0);
        DMSG("Temperature: ");
        DMSGN(res);
        SerialTools::writeDouble(res);
    }
    
    void kill() {}
};
