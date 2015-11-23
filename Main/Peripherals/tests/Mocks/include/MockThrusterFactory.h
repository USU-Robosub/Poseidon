//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_THRUSTER_FACTORY_H
#define PERIPHERALS_MOCK_THRUSTER_FACTORY_H

#include <IThrusterFactory.h>
#include "MockThruster.h"

class MockThrusterFactory : public IThrusterFactory {
public:
    std::shared_ptr<IThruster> createForwardThruster();
    std::shared_ptr<IThruster> createStrafeThruster();
    std::shared_ptr<IThruster> createDiveThruster();
};


#endif //PERIPHERALS_MOCK_THRUSTER_FACTORY_H
