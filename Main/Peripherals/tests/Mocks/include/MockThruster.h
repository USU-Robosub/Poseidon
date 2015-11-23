//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_THRUSTER_H
#define PERIPHERALS_MOCK_THRUSTER_H

#include <IThruster.h>

class MockThruster : public IThruster {
public:
    int setPeriod(uint ns){}
    void start(){}
    void stop(){}
    int setDutyA(uint ns){}
    int setDutyB(uint ns){}
};


#endif //PERIPHERALS_MOCK_THRUSTER_H
