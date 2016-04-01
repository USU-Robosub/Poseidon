#ifndef ESCPOWER
#define ESCPOWER

#include <iostream>
#include <fstream>
#include "Serial.h"

class EscPower
{
private:
	bool escsOn;
    Serial& serial_;
public:
	EscPower(Serial& serial);
	void turnOnEscs();
	void turnOffEscs();
};

#endif
