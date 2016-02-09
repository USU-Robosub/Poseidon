#include <thread>
#include <iostream>
#include "GateDetector.h"

void getPos(GateDetector g)
{
    /*
    while(true)
    {
        std::cout << g.getRightGatePosition() << std::endl;
    }
    */
}

int main( int argc, char** argv )
{
    GateDetector g;

    std::thread first(&GateDetector::startCapture, g);
    std::thread second(getPos, g);
    //first.join();
    std::cout << "Press enter to stop\n";
    std::cin.ignore();

    g.stopCapture();
    

    return 0;
}
