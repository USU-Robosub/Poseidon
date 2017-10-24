#include "ThrustController.h"

ThrustController::ThrustController(
        IThrusterFactory& thrusterFactory,
        ImuSensor& imuSensor,
        std::shared_ptr<ILogger> logger
) :
        moveThruster_(thrusterFactory.createMoveThruster()),
        diveThruster_(thrusterFactory.createDiveThruster()),
        yawThruster_(thrusterFactory.createYawThruster()),
        imuSensor_(imuSensor),
        logger_(logger) { }


void ThrustController::createYawController() {
    yawController_ = PidController()
            .withBounds(MIN_THROTTLE, MAX_THROTTLE)
            .withTimeDelta(timeDelta_)
            .withConstants(yawConfiguration_);

}

void ThrustController::updateMoveThruster() {}

void ThrustController::updateYawThruster() {}

void ThrustController::updateDiveThruster() {}

void ThrustController::move(float throttle) {
    moveThruster_->Thrust( throttle );
}

void ThrustController::dive(float throttle) {
    diveThruster_->Thrust( throttle );
}

void ThrustController::yaw(float angle) {
    yawController_->updateSetPoint(angle);
}

void ThrustController::kill() {
	yawController_->stop();
    moveThruster_->Thrust(0);
    diveThruster_->Thrust(0);
}

void ThrustController::setNeutral() {
	yawController_->stop();
    move(0);
    dive(0);
}

void ThrustController::configureYaw(PidController::Configuration configuration) {
	yawController_->withConstants(configuration);
}

void ThrustController::configureTimeDelta(unsigned int timeDelta) {
    setPointMutex_.lock();
    timeDelta_ = timeDelta;
    auto angle = yawSetPoint_;
    setPointMutex_.unlock();
    yaw( angle );
}

ThrustController::~ThrustController() {
    logger_->info("Stopping Thrusters...");
}
