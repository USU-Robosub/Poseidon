#ifndef POWER_MANAGEMENT
#define POWER_MANAGEMENT

#include "../drivers/PowerModule/CMPR.h"

class PowerManagement
{
    public:
        PowerManagement();
        ~PowerManagement();

        void turnOnESCs();
        void turnOffESCs();

    private:
        static int instanceCount_;

        PowerModule module;
};

#endif
