//
// Created by Nathan Copier on 11/20/2015.
//

#include "PwmThrusterFactory.h"

std::shared_ptr<IThruster> PwmThrusterFactory::createForwardThruster() {
    return std::make_shared<PWM>(PWM_SUB0);
}

std::shared_ptr<IThruster> PwmThrusterFactory::createStrafeThruster() {
    return std::make_shared<PWM>(PWM_SUB1);
}

std::shared_ptr<IThruster> PwmThrusterFactory::createDiveThruster() {
    return std::make_shared<PWM>(PWM_SUB2);
}
