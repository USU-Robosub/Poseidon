#ifndef DIVING_MASTER
#define DIVING_MASTER

#include "ILogger.h"
#include "IThrusterFactory.h"
#include "IThruster.h"

#include <memory>
#include <chrono>
#include <cassert>
#include <cmath>
#include <thread>

class ThrustController
{
public:
    ThrustController(IThrusterFactory& thrusterFactory, std::shared_ptr<ILogger> logger);
    ~ThrustController();

private:
    std::shared_ptr<IThruster> leftForwardThruster_;
    std::shared_ptr<IThruster> rightForwardThruster_;
    std::shared_ptr<IThruster> leftStrafeThruster_;
    std::shared_ptr<IThruster> rightStrafeThruster_;
    std::shared_ptr<IThruster> forwardDiveThruster_;
    std::shared_ptr<IThruster> rearDiveThruster_;

    std::shared_ptr<ILogger> logger_;
};

#endif
