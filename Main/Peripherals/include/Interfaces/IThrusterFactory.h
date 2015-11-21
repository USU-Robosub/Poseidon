//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_THRUSTER_FACTORY_H
#define PERIPHERALS_I_THRUSTER_FACTORY_H

#include <memory>
#include "IThruster.h"

class IThrusterFactory {
public:
    virtual std::shared_ptr<IThruster> createForwardThruster() = 0;
    virtual std::shared_ptr<IThruster> createStrafeThruster() = 0;
    virtual std::shared_ptr<IThruster> createDiveThruster() = 0;
};

#endif //PERIPHERALS_I_THRUSTER_FACTORY_H
