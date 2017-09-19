#ifndef ESC_POWER
#define ESC_POWER

#include <IEscPower.h>
#include "Serial.h"
#include "ArduinoConfig.h"

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
