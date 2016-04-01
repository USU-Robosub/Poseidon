#ifndef ESCPOWER
#define ESCPOWER

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
