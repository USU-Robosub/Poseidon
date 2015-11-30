//
// Created by Nathan Copier on 11/22/2015.
//

#include "MockThrusterFactory.h"

std::shared_ptr<IThruster> MockThrusterFactory::createForwardThruster() {
    return std::make_shared<MockThruster>();
}

std::shared_ptr<IThruster> MockThrusterFactory::createStrafeThruster() {
    return std::make_shared<MockThruster>();
}

std::shared_ptr<IThruster> MockThrusterFactory::createDiveThruster() {
    return std::make_shared<MockThruster>();
}
