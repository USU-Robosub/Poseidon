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
	void turnOnEscs();
	void turnOffEscs();
};

#endif
