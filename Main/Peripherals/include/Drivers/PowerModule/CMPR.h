/**
  * \class PowerModule
  *
  *  Created on: Feb 6, 2015
  *      Author: TekuConcept
  *
  * \brief The purpose of this class is to provide a wrapper between hardware and software for power-based applications.
  */

#ifndef CMPR_H_
#define CMPR_H_

#include "Drivers/I2C/I2C.h"
#include "CMPR_Const.h"
#include "stdint.h"

class PowerModule {
public:
	/** \brief Initializes a new power module for basic power management.
      * \param bus The address of the I2C bus the power module listens on.
      */
	PowerModule(uint _bus_);
	virtual ~PowerModule();

	/** \brief Enables one of the Electronic Speed Controllers.
      * \param esc An unsigned byte representing the index of the ESC.
      */
	void enableESC(uint8_t esc);

	/** \brief Disables one of the Electronic Speed Controllers.
      * \param esc An unsigned byte representing the index of the ESC.
      */
	void disableESC(uint8_t esc);

	/** \brief Enables or disables a collection of Electronic Speed Controllers in one call.
      * \param esc An unsigned byte holding bit-based booling flags identifying the ESCs to enable and disable respectively.
      *            Example: esc = 0xE7; (0b11100111) - the first and last three ESCs will be enabled and the middle two disabled.
      */
	void burstEnableESC(uint8_t esc);

	/** \brief Returns the analog reading of ADC 1
      */
	uint16_t getAmperageA();

	/** \brief Returns the analog reading of ADC 2
      */
	uint16_t getAmperageB();

	/** \brief Returns the analog reading of ADC 3
      */
	uint16_t getAmperageC();

	/** \brief Returns the analog reading of ADC 4
      */
	uint16_t getAmperageD();

private:
	I2C bus;
};

#endif /* CMPR_H_ */
