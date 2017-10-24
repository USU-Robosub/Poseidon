/**
  * \class IDriver
  *
  *  Created on: Mar 24, 2016
  * Last Edited: Mar 24, 2016
  *
  * \brief This is a driver wrapper for testing connectivity
  *			and continuity.
  */

#ifndef I_DRIVER_H
#define I_DRIVER_H

class IDriver {
public:
	/** \brief Takes an ID reading from the sensor.
	*	\return Returns the ID associated with the specific driver.
	*/
    virtual int WhoAmI() = 0;
};

#endif
