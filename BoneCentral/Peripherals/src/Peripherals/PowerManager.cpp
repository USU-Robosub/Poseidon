#include "PowerManager.h"

PowerManager::PowerManager(IEscPower& escPower, IImuPower& imuPower) : escPower_(escPower),
	imuPower_(imuPower)
{
}

void PowerManager::turnOnEscs()
{
	escPower_.turnOnEscs();
}

void PowerManager::turnOffEscs()
{
	escPower_.turnOffEscs();
}

void PowerManager::turnOnImuSensor() 
{
	imuPower_.wake();
}

void PowerManager::turnOffImuSensor()
{
	imuPower_.sleep();
}