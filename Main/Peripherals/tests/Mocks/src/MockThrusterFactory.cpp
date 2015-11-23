//
// Created by Nathan Copier on 11/22/2015.
//

#include "MockThrusterFactory.h"

std::shared_ptr<IThruster> MockThrusterFactory::createForwardThruster() {
    std::make_shared<MockThruster>();
}

std::shared_ptr<IThruster> MockThrusterFactory::createStrafeThruster() {
    std::make_shared<MockThruster>();
}

std::shared_ptr<IThruster> MockThrusterFactory::createDiveThruster() {
    std::make_shared<MockThruster>();
}
