//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_COMPASS_H
#define PERIPHERALS_MOCK_COMPASS_H

#include <ICompass.h>

class MockCompass : public ICompass {
public:
    float X(){ return 0; }
    float Y(){ return 0; }
    float Z(){ return 0; }
};


#endif //PERIPHERALS_MOCK_COMPASS_H
