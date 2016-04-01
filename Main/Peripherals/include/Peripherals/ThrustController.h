#ifndef DIVING_MASTER
#define DIVING_MASTER

#include "ILogger.h"
#include "IThrusterFactory.h"
#include "IThruster.h"

#include <memory>
#include <utility>

typedef std::pair<float, float> FloatPair;

class ThrustController
{
public:
    ThrustController(IThrusterFactory& thrusterFactory, std::shared_ptr<ILogger> logger);
    void goDirection(float forward, float strafe, float dive);
    void faceDirection(float yaw);
    void setForwardTrim(float left, float right);
    void setDiveTrim(float front, float back);
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

    FloatPair getReciprocalValues(float value);
    float getScaleToMaxPower(float left, float right);
    float getMaxMag(float left, float right);
    void setThrust(FloatPair forwardPair, FloatPair strafePair, float dive);
};

#endif
