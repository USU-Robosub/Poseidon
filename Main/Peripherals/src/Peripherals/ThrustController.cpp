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

void ThrustController::goDirection(float forward, float strafe, float dive) {
    logger_->info("Thrusting...");
    float powerScale;
    auto strafeCorrection = getReciprocalValues(strafe * strafeRatio);
    auto leftForward = strafeCorrection.first + forward;
    auto rightForward = strafeCorrection.second + forward;
    powerScale = getScaleToMaxPower(leftForward, rightForward);
    auto forwardPair = std::make_pair(leftForward*powerScale, rightForward*powerScale);
    auto strafePair = getReciprocalValues(strafe*powerScale);
    setThrust(forwardPair, strafePair, dive*powerScale);
}

void ThrustController::setThrust(FloatPair forwardPair, FloatPair strafePair, float dive) {
    leftForwardThruster_->Thrust(forwardPair.first);
    rightForwardThruster_->Thrust(forwardPair.second);
    leftStrafeThruster_->Thrust(strafePair.first);
    rightStrafeThruster_->Thrust(strafePair.second);
    forwardDiveThruster_->Thrust(dive);
    rearDiveThruster_->Thrust(dive);
}

float ThrustController::getScaleToMaxPower(float left, float right) {
    auto power = getMaxMag(left, right);
    return power > maxPower ? maxPower / power : 1;
}

float ThrustController::getMaxMag(float left, float right) {
    if(left < 0) left *= -1;
    if(right < 0) left *= -1;
    return right > left ? right : left;
}

void ThrustController::faceDirection(float yaw) {
    logger_->info("Yawing...");
    auto yawPair = getReciprocalValues(yaw);
    leftForwardThruster_->Thrust(yawPair.first);
    rightForwardThruster_->Thrust(yawPair.second);
}

std::pair<float,float> ThrustController::getReciprocalValues(float value) {
    float left, right;
    if(value < 0.0f) {
        left = value;
        right = -1 * value * reverseRatio;
    }
    else {
        left = value * reverseRatio;
        right = -1 * value;
    }
    return std::make_pair(left, right);
}

ThrustController::~ThrustController()
{
    logger_->info("Stopping Thrusters...");
}
