#ifndef POWERMANAGER
#define POWERMANAGER

#include <iostream>
#include <fstream>

class PowerManager
{
private:
	bool escsOn;
public:
	PowerManager();
	void turnEscsOn();
	void turnEscsOff();
};

#endif
