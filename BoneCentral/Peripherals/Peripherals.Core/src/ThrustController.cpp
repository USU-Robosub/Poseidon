#include "ThrustController.h"

ThrustController::ThrustController(IThrusterFactory& thrusterFactory, std::shared_ptr<ILogger> logger) :
        moveThruster_(thrusterFactory.createMoveThruster()),
        strafeThruster_(thrusterFactory.createStrafeThruster()),
        diveThruster_(thrusterFactory.createDiveThruster()),
        yawThruster_(thrusterFactory.createYawThruster()),
        pitchThruster_(thrusterFactory.createPitchThruster()),
        rollThruster_(thrusterFactory.createRollThruster()),
        logger_(logger) { }

void ThrustController::goDirection(float _move_, float _strafe_, float _dive_) {
    move(_move_);
    strafe(_strafe_);
    dive(_dive_);
}

void ThrustController::move(float throttle) {
    moveThruster_->Thrust(getSafeThrottle(throttle));
}

void ThrustController::strafe(float throttle) {
    strafeThruster_->Thrust(getSafeThrottle(throttle));
}

void ThrustController::dive(float throttle) {
    diveThruster_->Thrust(getSafeThrottle(throttle));
}

void ThrustController::rotate(float _yaw_, float _pitch_, float _roll_) {
    yaw(_yaw_);
    pitch(_pitch_);
    roll(_roll_);
}

void ThrustController::yaw(float throttle) {
    yawThruster_->Thrust(getSafeThrottle(throttle));
}

void ThrustController::pitch(float throttle) {
    pitchThruster_->Thrust(getSafeThrottle(throttle));
}

void ThrustController::roll(float throttle) {
    rollThruster_->Thrust(getSafeThrottle(throttle));
}

void ThrustController::killAllThrusters() {
    move(0);
    strafe(0);
    dive(0);
    yaw(0);
    pitch(0);
    roll(0);
}

float ThrustController::getSafeThrottle(float throttle) {
    if(throttle > MAX_THROTTLE || throttle < MIN_THROTTLE)
        return 0;
    return throttle;
}

ThrustController::~ThrustController() {
    logger_->info("Stopping Thrusters...");
}
