//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_SERIAL_FACTORY_H
#define PERIPHERALS_SERIAL_FACTORY_H

#include <IThrusterFactory.h>
#include "SerialThruster.h"
#include "EscPower.h"
#include "Headlights.h"
#include "ExTemperatureSensor.h"
#include "ExPressureSensor.h"
#include "Serial.h"


class SerialFactory : public IThrusterFactory {
private:
    Serial serial_;
public:
    std::shared_ptr<IThruster> createLeftForwardThruster();
    std::shared_ptr<IThruster> createRightForwardThruster();
    std::shared_ptr<IThruster> createLeftStrafeThruster();
    std::shared_ptr<IThruster> createRightStrafeThruster();
    std::shared_ptr<IThruster> createForwardDiveThruster();
    std::shared_ptr<IThruster> createRearDiveThruster();
    std::shared_ptr<ITemperatureSensor> createExternalTemperatureSensor();
    std::shared_ptr<IPressureSensor> createExternalPressureSensor();
    std::shared_ptr<IEscPower> createEscPower();
    std::shared_ptr<IHeadlights> createHeadlights();
};


#endif //PERIPHERALS_SERIAL_FACTORY_H
