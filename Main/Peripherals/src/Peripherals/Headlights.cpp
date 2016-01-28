#include "Headlights.h"

Headlights::Headlights()
{
	std::system("stty -F /dev/ttyACM0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
}

void Headlights::switchLights(bool areOn)
{
	std::ofstream serialOut("/dev/ttyACM0");
	std::ifstream serialIn("/dev/ttyACM0");
	if (areOn)
	{
		serialOut << 0x36 << std::flush;
		serialOut << 0x1 << std::flush;
	}
	else
	{
		serialOut << 0x36 << 0x1 << std::flush;
	}
	serialOut.close();
	std::string response;
	getline(serialIn, response);
	std::cout << response << std::endl;
}
