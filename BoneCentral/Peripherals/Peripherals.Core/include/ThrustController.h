#ifndef DIVING_MASTER
#define DIVING_MASTER

#include "ILogger.h"
#include "IThrusterFactory.h"
#include "IThruster.h"
#include "ImuSensor.h"
#include "PidController.h"

#include <memory>
#include <mutex>
#define _USE_MATH_DEFINES
#include <math.h>
#include <thread>
#include <unistd.h>

class ThrustController
{
public:
    ThrustController(IThrusterFactory& thrusterFactory, ImuSensor& imuSensor, std::shared_ptr<ILogger> logger);
    void start();
    void move(float throttle);
    void dive(float throttle);
    void yaw(float angle);
    void kill();
    void configureYaw(PidController::Configuration configuration);
    void configureTimeDelta(unsigned int timeDelta);
    ~ThrustController();

private:
    std::shared_ptr<IThruster> moveThruster_;
    std::shared_ptr<IThruster> diveThruster_;
    std::shared_ptr<IThruster> yawThruster_;
    ImuSensor& imuSensor_;

    float yawSetPoint_;
    PidController yawController_;
    PidController::Configuration yawConfiguration_;

    const float MAX_THROTTLE = 1.0f;
    const float MIN_THROTTLE = -1.0f;
    unsigned int timeDelta_ = 100; //ms

    std::mutex setPointMutex_;
    std::thread* pidThread_;
    bool shouldDie_;

    std::shared_ptr<ILogger> logger_;

    void setNeutral();
    void runPidLoop();
    void createYawController();
    void updateMoveThruster();
    void updateYawThruster();
    void updateDiveThruster();

    void setShouldDie();
    void unsetShouldDie();
    bool shouldDie();
    void endPidThread();
    
    float modmod(float dividend, float divisor);
    float angleDelta(float base, float target);
};

#endif
