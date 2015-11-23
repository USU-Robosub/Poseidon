//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_PWM_THRUSTER_FACTORY_H
#define PERIPHERALS_PWM_THRUSTER_FACTORY_H

#include <IThrusterFactory.h>
#include <PWM/PWM.h>


class PwmThrusterFactory : public IThrusterFactory {

public:
    std::shared_ptr<IThruster> createForwardThruster();
    std::shared_ptr<IThruster> createStrafeThruster();
    std::shared_ptr<IThruster> createDiveThruster();

};


#endif //PERIPHERALS_PWM_THRUSTER_FACTORY_H
