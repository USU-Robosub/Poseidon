//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_SERIAL_THRUSTER_FACTORY_H
#define PERIPHERALS_SERIAL_THRUSTER_FACTORY_H

#include <IThrusterFactory.h>
#include <SerialThruster.h>
#include "Serial.h"


class SerialThrusterFactory : public IThrusterFactory {
private:
    Serial& serial_;
public:
    SerialThrusterFactory(Serial serial);
    std::shared_ptr<IThruster> createLeftForwardThruster();
    std::shared_ptr<IThruster> createRightForwardThruster();
    std::shared_ptr<IThruster> createLeftStrafeThruster();
    std::shared_ptr<IThruster> createRightStrafeThruster();
    std::shared_ptr<IThruster> createForwardDiveThruster();
    std::shared_ptr<IThruster> createRearDiveThruster();
};


#endif //PERIPHERALS_SERIAL_THRUSTER_FACTORY_H
