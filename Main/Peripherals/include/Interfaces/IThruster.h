//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_THRUSTER_H
#define PERIPHERALS_I_THRUSTER_H

class IThruster {
public:
    virtual int setPeriod(uint ns) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual int setDutyA(uint ns) = 0;
    virtual int setDutyB(uint ns) = 0;
};

#endif //PERIPHERALS_I_THRUSTER_H
