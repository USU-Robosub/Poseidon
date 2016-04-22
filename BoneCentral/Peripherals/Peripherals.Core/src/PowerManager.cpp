#include "PowerManager.h"

PowerManager::PowerManager(IPowerFactory& powerFactory) :
		escPower_(powerFactory.createEscPower()),
		imuPower_(powerFactory.createImuPower()) { }

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