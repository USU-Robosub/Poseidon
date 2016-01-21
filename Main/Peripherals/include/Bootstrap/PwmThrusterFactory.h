//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_PWM_THRUSTER_FACTORY_H
#define PERIPHERALS_PWM_THRUSTER_FACTORY_H

#include <IThrusterFactory.h>
#include <PWM/PWM.h>


class PwmThrusterFactory : public IThrusterFactory {

public:
    virtual std::shared_ptr<IThruster> createLeftForwardThruster();
    virtual std::shared_ptr<IThruster> createRightForwardThruster();
    virtual std::shared_ptr<IThruster> createLeftStrafeThruster();
    virtual std::shared_ptr<IThruster> createRightStrafeThruster();
    virtual std::shared_ptr<IThruster> createForwardDiveThruster();
    virtual std::shared_ptr<IThruster> createRearDiveThruster();

};


#endif //PERIPHERALS_PWM_THRUSTER_FACTORY_H
