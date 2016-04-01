#ifndef POWERMANAGER
#define POWERMANAGER

#include <IEscPower.h>
#include <IImuPower.h>

class PowerManager
{
private:
	bool escsOn;
    IEscPower& escPower_;
    IImuPower& imuPower_;

public:
	PowerManager(IEscPower& escPower, IImuPower& imuPower);
	void turnOnEscs();
	void turnOffEscs();
	void turnOnImuSensor();
	void turnOffImuSensor();
};

#endif
