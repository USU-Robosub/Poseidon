//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_THRUSTER_H
#define PERIPHERALS_I_THRUSTER_H

class IThruster {
public:
    virtual void Thrust(float powerLevel) = 0;
};

#endif //PERIPHERALS_I_THRUSTER_H
