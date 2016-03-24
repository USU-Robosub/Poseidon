//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_COMPASS_H
#define PERIPHERALS_MOCK_COMPASS_H

#include <ICompass.h>
#include <tuple>

class MockCompass : public ICompass {
public:
    std::tuple<float, float, float> getHeading()
    {
        return std::make_tuple(0, 0, 0);
    }
};


#endif //PERIPHERALS_MOCK_COMPASS_H
