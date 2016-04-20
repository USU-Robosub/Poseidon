#include "PowerManager.h"

PowerManager::PowerManager(IImuFactory& imuFactory) : escPower_(imuFactory.createEscPower()),
	imuPower_(imuFactory.createImuPower())
{
}

void PowerManager::turnOnEscs()
{
	escPower_->turnOnEscs();
}

void PowerManager::turnOffEscs()
{
	escPower_->turnOffEscs();
}

void PowerManager::turnOnImuSensor() 
{
	imuPower_->wake();
}

void PowerManager::turnOffImuSensor()
{
	imuPower_->sleep();
}