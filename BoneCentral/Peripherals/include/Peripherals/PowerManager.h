#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <IImuFactory.h>

class PowerManager
{
private:
    std::shared_ptr<IEscPower> escPower_;
	std::shared_ptr<IImuPower> imuPower_;

public:
	PowerManager(IImuFactory& imuFactory);
	void turnOnEscs();
	void turnOffEscs();
	void turnOnImuSensor();
	void turnOffImuSensor();
};

#endif
