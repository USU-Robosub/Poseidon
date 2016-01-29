//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_THRUSTER_FACTORY_H
#define PERIPHERALS_I_THRUSTER_FACTORY_H

#include "IThruster.h"
#include <memory>

class IThrusterFactory {
public:
    virtual std::shared_ptr<IThruster> createLeftForwardThruster() = 0;
    virtual std::shared_ptr<IThruster> createRightForwardThruster() = 0;
    virtual std::shared_ptr<IThruster> createLeftStrafeThruster() = 0;
    virtual std::shared_ptr<IThruster> createRightStrafeThruster() = 0;
    virtual std::shared_ptr<IThruster> createForwardDiveThruster() = 0;
    virtual std::shared_ptr<IThruster> createRearDiveThruster() = 0;
};

#endif //PERIPHERALS_I_THRUSTER_FACTORY_H
