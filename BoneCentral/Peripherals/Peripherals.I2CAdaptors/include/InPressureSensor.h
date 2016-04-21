#ifndef DRIVER_IN_PRESSURE_SENSOR
#define DRIVER_IN_PRESSURE_SENSOR

#include <BMP085.h>
#include <IPressureSensor.h>
#include <memory>

class InPressureSensor : public IPressureSensor {
public:
    InPressureSensor(std::shared_ptr<BMP085> pressure);
    int getPressure();
private:
	std::shared_ptr<BMP085> pressure_;
};

#endif
