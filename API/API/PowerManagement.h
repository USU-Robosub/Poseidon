
#ifndef POWER_MANAGEMENT
#define POWER_MANAGEMENT

#include "../drivers/I2C/I2C.h"

class PowerManagement
{
    public:
        PowerManagement();
        ~PowerManagement();

        void turnOnESCs();
        void turnOffESCs();

    private:
        static int instanceCount_;

        I2C bus_;
};

#endif
