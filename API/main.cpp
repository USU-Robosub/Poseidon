
#include "API/DivingMaster.h"
#include <iostream>


int main(int argc, char** argv)
{
    DivingMaster dm = DivingMaster::getInstance();
    dm.achieveXSpeed(1);

    return EXIT_SUCCESS;
}

//void setRelativeDepth(float depth);
//void setRelativePosition(float x, float y);
