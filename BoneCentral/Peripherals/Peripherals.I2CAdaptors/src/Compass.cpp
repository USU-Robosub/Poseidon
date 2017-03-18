#include "Compass.h"

Compass::Compass(std::shared_ptr<HMC5883L> compass) : 
	compass_(compass) {
	compass_->setOutputRate(HMC5883L::Rate::Hz75);
}



FloatTuple Compass::getHeading()
{
	return std::make_tuple(compass_->X(), compass_->Y(), compass_->Z());;
}