#ifndef DIVING_MASTER
#define DIVING_MASTER

#include "ILogger.h"
#include "IThrusterFactory.h"
#include "IThruster.h"

#include <memory>
#include <utility>
#include <cmath>
#include <sstream>

typedef std::pair<float, float> FloatPair;

class ThrustController
{
public:
    ThrustController(IThrusterFactory& thrusterFactory, std::shared_ptr<ILogger> logger);
    void goDirection(float forward, float strafe, float dive);
    void faceDirection(float yaw, float dive);
    void setForwardTrim(float left, float right);
    void setStrafeTrim(float left, float right);
    void setDiveTrim(float front, float back);
    void setDiveOffset(float front, float back);
    void killAllThruster();
    ~ThrustController();

private:
    std::shared_ptr<IThruster> leftForwardThruster_;
    std::shared_ptr<IThruster> rightForwardThruster_;
    std::shared_ptr<IThruster> leftStrafeThruster_;
    std::shared_ptr<IThruster> rightStrafeThruster_;
    std::shared_ptr<IThruster> forwardDiveThruster_;
    std::shared_ptr<IThruster> rearDiveThruster_;

    std::shared_ptr<ILogger> logger_;

    const float maxPower = 1.0f;
    const float minPower = 0.0f;
    const float reverseRatio = 0.84507f;
    const float strafeRatio = 0.7f;

    FloatPair forwardTrim;
    FloatPair diveTrim;
    FloatPair diveOffset;
    FloatPair strafeTrim;

    FloatPair getReciprocalValues(float value);
    float getSafeOffset(float a, float b);
    float getScaleToMaxPower(float left, float right);
    float getMaxMag(float left, float right);
    void setThrust(FloatPair forwardPair, FloatPair strafePair, FloatPair divePair);
};

#endif
