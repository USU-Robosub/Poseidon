#ifndef DIVING_MASTER
#define DIVING_MASTER

#include "ILogger.h"
#include "IThrusterFactory.h"
#include "IThruster.h"
#include "ImuSensor.h"
#include "PidController.h"

#include <memory>
#include <mutex>
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
    ~ThrustController();

private:
    std::shared_ptr<IThruster> moveThruster_;
    std::shared_ptr<IThruster> diveThruster_;
    std::shared_ptr<IThruster> yawThruster_;

    ImuSensor& imuSensor_;
    std::shared_ptr<ILogger> logger_;

    float yawSetPoint_;
    PidController yawController_;
    PidController::Configuration yawConfiguration_;

    const float MAX_THROTTLE = 1.0f;
    const float MIN_THROTTLE = -1.0f;
    const unsigned int timeDelta_ = 100; //ms

    bool isDead_;
    std::mutex setPointMutex_;
    std::thread* pidThread_;
    bool shouldDie_;

    void setNeutral();
    void runPidLoop();
    void updateMoveThruster();
    void updateYawThruster();
    void updateDiveThruster();

    void setShouldDie();
    void unsetShouldDie();
    bool shouldDie() const;
    void endPidThread();
};

#endif
