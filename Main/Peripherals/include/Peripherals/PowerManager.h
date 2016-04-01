#ifndef POWERMANAGER
#define POWERMANAGER

#include <EscPower>

class PowerManager
{
private:
	bool escsOn;
    EscPower& escPower_;
public:
	PowerManager(EscPower& escPower);
	void turnOnEscs();
	void turnOffEscs();
};

#endif
