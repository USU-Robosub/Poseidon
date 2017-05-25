#ifndef IIMU_POWER_H
#define IIMU_POWER_H

class IImuPower
{
public:
	virtual void sleep() = 0;
	virtual void wake() = 0;
};

#endif