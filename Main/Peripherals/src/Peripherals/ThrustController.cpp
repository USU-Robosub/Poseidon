#include "ThrustController.h"

ThrustController::ThrustController(IThrusterFactory& thrusterFactory, std::shared_ptr<ILogger> logger) :
        leftForwardThruster_(thrusterFactory.createLeftForwardThruster()),
        rightForwardThruster_(thrusterFactory.createRightForwardThruster()),
        leftStrafeThruster_(thrusterFactory.createLeftStrafeThruster()),
        rightStrafeThruster_(thrusterFactory.createRightStrafeThruster()),
        forwardDiveThruster_(thrusterFactory.createForwardDiveThruster()),
        rearDiveThruster_(thrusterFactory.createRearDiveThruster()),
        logger_(logger)
{

    logger_->info("Initializing Thrusters...");
}

ThrustController::~ThrustController()
{
    logger_->info("Stopping Thrusters...");
}
