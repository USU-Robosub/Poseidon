#ifndef POWERMANAGER
#define POWERMANAGER

#include <iostream>
#include <fstream>

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
