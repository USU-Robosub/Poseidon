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
    void goDirection(float _move_, float _strafe_, float _dive_);
    void rotate(float _yaw_, float _pitch_, float _roll_);
    void move(float throttle);
    void strafe(float throttle);
    void dive(float throttle);
    void yaw(float throttle);
    void pitch(float throttle);
    void roll(float throttle);
    void killAllThrusters();
    ~ThrustController();

private:
    std::shared_ptr<IThruster> moveThruster_;
    std::shared_ptr<IThruster> strafeThruster_;
    std::shared_ptr<IThruster> diveThruster_;
    std::shared_ptr<IThruster> yawThruster_;
    std::shared_ptr<IThruster> pitchThruster_;
    std::shared_ptr<IThruster> rollThruster_;

    std::shared_ptr<ILogger> logger_;

    const float MAX_THROTTLE = 1.0f;
    const float MIN_THROTTLE = -1.0f;
    // const float reverseRatio = 0.84507f;
    // const float strafeRatio = 0.7f;
    
    float getSafeThrottle(float throttle);
};

#endif
