
#include "API/ThrustController.h"
#include <iostream>


int main(int argc, char** argv)
{
    ThrustController dm = ThrustController::getInstance();
    dm.achieveXSpeed(1, 2);
    dm.achieveXSpeed(0.75, 1);
    dm.achieveXSpeed(0, 1);

    return EXIT_SUCCESS;
}

//void setRelativeDepth(float depth);
//void setRelativePosition(float x, float y);
