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
    // sets default trim
    forwardTrim.first = 1;
    forwardTrim.second = 1;
    diveTrim.first = 1;
    diveTrim.second = 1;
}

void ThrustController::goDirection(float forward, float strafe, float dive) {
    std::stringstream ss;
    ss << "Thrusting... F: " << forward << " S: " << strafe << " D: " << dive;
    logger_->info(ss.str().c_str());
    auto strafeCorrection = getReciprocalValues(strafe * strafeRatio);
    auto leftForward = strafeCorrection.first + forward;
    auto rightForward = strafeCorrection.second + forward;
    float powerScale = getScaleToMaxPower(leftForward, rightForward);
    auto forwardPair = std::make_pair(leftForward*powerScale, rightForward*powerScale);
    auto strafePair = getReciprocalValues(strafe*powerScale);
    setThrust(forwardPair, strafePair, dive*powerScale);
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
    setThrust(yawPair, std::make_pair(0.0f, 0.0f), 0.0f);
}

void ThrustController::setForwardTrim(float left, float right) {
    std::stringstream ss;
    ss << "Setting forward trim: L " << left << " R " << right;
    logger_->info(ss.str().c_str());

    forwardTrim.first = left;
    forwardTrim.second = right;
}

void ThrustController::setDiveTrim(float front, float back) {
    std::stringstream ss;
    ss << "Setting dive trim: F " << front << " B " << back;
    logger_->info(ss.str().c_str());

    diveTrim.first = front;
    diveTrim.second = back;
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

void ThrustController::setThrust(FloatPair forwardPair, FloatPair strafePair, float dive) {
    leftForwardThruster_->Thrust(forwardPair.first * forwardTrim.first);
    rightForwardThruster_->Thrust(forwardPair.second * forwardTrim.second);

    leftStrafeThruster_->Thrust(strafePair.first);
    rightStrafeThruster_->Thrust(strafePair.second);

    forwardDiveThruster_->Thrust(dive * diveTrim.first);
    rearDiveThruster_->Thrust(dive * diveTrim.second);
}

ThrustController::~ThrustController()
{
    logger_->info("Stopping Thrusters...");
}
