//
// Created by Nathan Copier on 11/21/2015.
//

#ifndef PERIPHERALS_I_COMPASS_H
#define PERIPHERALS_I_COMPASS_H

class ICompass {
public:
    virtual uint16_t X() = 0;
    virtual uint16_t Y() = 0;
    virtual uint16_t Z() = 0;
};

#endif //PERIPHERALS_I_COMPASS_H
