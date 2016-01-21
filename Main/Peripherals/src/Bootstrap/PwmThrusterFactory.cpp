//
// Created by Nathan Copier on 11/20/2015.
//

#include "PwmThrusterFactory.h"

std::shared_ptr<IThruster> PwmThrusterFactory::createLeftForwardThruster() {
    return std::make_shared<PWM>(PWM_SUB0, 0);
}

std::shared_ptr<IThruster> PwmThrusterFactory::createRightForwardThruster() {
    return std::make_shared<PWM>(PWM_SUB0, 1);
}

std::shared_ptr<IThruster> PwmThrusterFactory::createLeftStrafeThruster() {
    return std::make_shared<PWM>(PWM_SUB1, 0);
}

std::shared_ptr<IThruster> PwmThrusterFactory::createRightStrafeThruster() {
    return std::make_shared<PWM>(PWM_SUB1, 1);
}

std::shared_ptr<IThruster> PwmThrusterFactory::createForwardDiveThruster() {
    return std::make_shared<PWM>(PWM_SUB2, 0);
}

std::shared_ptr<IThruster> PwmThrusterFactory::createRearDiveThruster() {
    return std::make_shared<PWM>(PWM_SUB2, 1);
}
