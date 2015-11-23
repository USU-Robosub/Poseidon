//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_POWER_MODULE_H
#define PERIPHERALS_MOCK_POWER_MODULE_H

#include <IPowerModule.h>

class MockPowerModule : public IPowerModule {
public:
    void burstToggleESC(uint8_t esc){}
};


#endif //PERIPHERALS_MOCK_POWER_MODULE_H
