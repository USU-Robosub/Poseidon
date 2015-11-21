//
// Created by Nathan Copier on 11/21/2015.
//

#ifndef PERIPHERALS_I_POWER_MODULE_H
#define PERIPHERALS_I_POWER_MODULE_H

class IPowerModule {
public:
    virtual void burstToggleESC(uint8_t esc) = 0;
};

#endif //PERIPHERALS_I_POWER_MODULE_H
