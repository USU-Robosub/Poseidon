//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_THRUSTER_H
#define PERIPHERALS_MOCK_THRUSTER_H

#include <IThruster.h>

class MockThruster : public IThruster {
public:
    void Thrust(float powerLevel);
};


#endif //PERIPHERALS_MOCK_THRUSTER_H
