/*
 * PowerModule.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: TekuConcept
 */

#include "CMPR.h"

PowerModule::PowerModule(uint _bus_):
	bus(_bus_)
{
}
PowerModule::~PowerModule() {
	// TODO Auto-generated destructor stub
}




void PowerModule::enableESC(uint8_t esc) {
	uint8_t dat = bus.read(CMPR_ADDR, CMPR_THST);

	dat |= 1 << esc;

	bus.write(CMPR_ADDR, CMPR_THST, dat);
}
void PowerModule::disableESC(uint8_t esc) {
	uint8_t dat = bus.read(CMPR_ADDR, CMPR_THST);

	dat &= ~(1 << esc);

	bus.write(CMPR_ADDR, CMPR_THST, dat);
}




void PowerModule::burstEnableESC(uint8_t esc) {
	bus.write(CMPR_ADDR, CMPR_THST, esc);
}




uint16_t PowerModule::getAmperageA() {
	uint16_t v = 0;
	bus.write(CMPR_ADDR, CMPR_READ, CMPR_A_HI);
	v |= bus.read(CMPR_ADDR, CMPR_A_HI) << 8;
	bus.write(CMPR_ADDR, CMPR_READ, CMPR_A_LO);
	v |= bus.read(CMPR_ADDR, CMPR_A_LO);
	return v;
}
uint16_t PowerModule::getAmperageB() {
	uint16_t v = 0;
	bus.write(CMPR_ADDR, CMPR_READ, CMPR_B_HI);
	v |= bus.read(CMPR_ADDR, CMPR_B_HI) << 8;
	bus.write(CMPR_ADDR, CMPR_READ, CMPR_B_LO);
	v |= bus.read(CMPR_ADDR, CMPR_B_LO);
	return v;
}
uint16_t PowerModule::getAmperageC() {
	uint16_t v = 0;
	bus.write(CMPR_ADDR, CMPR_READ, CMPR_C_HI);
	v |= bus.read(CMPR_ADDR, CMPR_C_HI) << 8;
	bus.write(CMPR_ADDR, CMPR_READ, CMPR_C_LO);
	v |= bus.read(CMPR_ADDR, CMPR_C_LO);
	return v;
}
uint16_t PowerModule::getAmperageD() {
	uint16_t v = 0;
	bus.write(CMPR_ADDR, CMPR_READ, CMPR_D_HI);
	v |= bus.read(CMPR_ADDR, CMPR_D_HI) << 8;
	bus.write(CMPR_ADDR, CMPR_READ, CMPR_D_LO);
	v |= bus.read(CMPR_ADDR, CMPR_D_LO);
	return v;
}
