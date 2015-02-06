/*
 * PowerModule.h
 *
 *  Created on: Feb 6, 2015
 *      Author: TekuConcept
 */

#ifndef CMPR_H_
#define CMPR_H_

#include "../I2C/I2C.h"
#include "CMPR_Const.h"
#include "stdint.h"

class PowerModule {
public:
	PowerModule(uint _bus_);
	virtual ~PowerModule();

	// control power to a single ESC
	void enableESC(uint8_t esc);
	void disableESC(uint8_t esc);

	// control power to all ESCs
	void burstEnableESC();
	void burstDisableESC();

	// values returned range from 0 to 1024
	uint16_t getAmperageA();
	uint16_t getAmperageB();
	uint16_t getAmperageC();
	uint16_t getAmperageD();

private:
	I2C bus;
};

#endif /* CMPR_H_ */
