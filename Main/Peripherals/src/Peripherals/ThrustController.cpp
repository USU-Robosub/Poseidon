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

    float scaledDive = dive * powerScale;
    FloatPair divePair;
    divePair.first = getSafeOffset(scaledDive, diveOffset.first);
    divePair.second = getSafeOffset(scaledDive, diveOffset.second);
    setThrust(forwardPair, strafePair, divePair);
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

void ThrustController::faceDirection(float yaw, float dive) {
    logger_->info("Yawing...");
    auto yawPair = getReciprocalValues(yaw);

    float scaledDive = dive;
    FloatPair divePair;
    divePair.first = getSafeOffset(scaledDive, diveOffset.first);
    divePair.second = getSafeOffset(scaledDive, diveOffset.second);
    setThrust(yawPair, std::make_pair(0.0f, 0.0f), divePair);
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

void ThrustController::setDiveOffset(float front, float back) {
    std::stringstream ss;
    ss << "Setting dive Offset: F " << front << " B " << back;
    logger_->info(ss.str().c_str());

    diveOffset.first = front;
    diveOffset.second = back;
}

float ThrustController::getSafeOffset(float a, float b) {
    float safe = a + b;
    if(safe > 1)
        safe = 1;
    else if(safe < -1)
        safe = -1;
    return safe;
}

void ThrustController::killAllThruster() {
    setThrust(std::make_pair(0.0f, 0.0f), std::make_pair(0.0f, 0.0f), std::make_pair(0.0f, 0.0f));
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

void ThrustController::setThrust(FloatPair forwardPair, FloatPair strafePair, FloatPair divePair) {
    leftForwardThruster_->Thrust(forwardPair.first * forwardTrim.first);
    rightForwardThruster_->Thrust(forwardPair.second * forwardTrim.second);

    leftStrafeThruster_->Thrust(strafePair.first);
    rightStrafeThruster_->Thrust(strafePair.second);

    forwardDiveThruster_->Thrust(divePair.first * diveTrim.first);
    rearDiveThruster_->Thrust(divePair.second * diveTrim.second);
}

ThrustController::~ThrustController()
{
    logger_->info("Stopping Thrusters...");
}
