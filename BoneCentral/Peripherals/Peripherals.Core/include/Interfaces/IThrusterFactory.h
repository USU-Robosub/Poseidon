//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_THRUSTER_FACTORY_H
#define PERIPHERALS_I_THRUSTER_FACTORY_H

#include "IThruster.h"
#include <memory>

class IThrusterFactory {
public:
    virtual std::shared_ptr<IThruster> createMoveThruster() = 0;
    virtual std::shared_ptr<IThruster> createStrafeThruster() = 0;
    virtual std::shared_ptr<IThruster> createDiveThruster() = 0;
    virtual std::shared_ptr<IThruster> createYawThruster() = 0;
    virtual std::shared_ptr<IThruster> createPitchThruster() = 0;
    virtual std::shared_ptr<IThruster> createRollThruster() = 0;
};

#endif //PERIPHERALS_I_THRUSTER_FACTORY_H
