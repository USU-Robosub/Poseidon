//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_COMPASS_H
#define PERIPHERALS_MOCK_COMPASS_H

#include <ICompass.h>

class MockCompass : public ICompass {
public:
    uint16_t X(){}
    uint16_t Y(){}
    uint16_t Z(){}
};


#endif //PERIPHERALS_MOCK_COMPASS_H
