#ifndef ESCPOWER
#define ESCPOWER

#include <IEscPower.h>
#include "Serial.h"

class EscPower : public IEscPower
{
private:
    Serial& serial_;
    
public:
	EscPower(Serial& serial);
	void turnOnEscs();
	void turnOffEscs();
};

#endif
