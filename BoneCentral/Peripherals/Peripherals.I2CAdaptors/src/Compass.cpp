#include "Compass.h"

Compass::Compass(std::shared_ptr<HMC5883L> compass) : 
	compass_(compass) {}



Vector Compass::getHeading()
{
	/*return Vector(
            compass_->X(),
            compass_->Y(),
            compass_->Z()
	);*/
	return Vector(0, 0, 0);
}