//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_THRUSTER_H
#define PERIPHERALS_MOCK_THRUSTER_H

#include <IThruster.h>

class MockThruster : public IThruster {
public:
    int setPeriod(uint ns){ return 0; }
    void start(){}
    void stop(){}
    int setDutyA(uint ns){ return 0; }
    int setDutyB(uint ns){ return 0; }
};


#endif //PERIPHERALS_MOCK_THRUSTER_H
