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
        pidThread_(nullptr),
        logger_(logger) { }

void ThrustController::start() {
    if (pidThread_ != nullptr) return;
<<<<<<< HEAD
=======
    //setNeutral();
>>>>>>> 304e928db9a792113303893a07fdcd3e0ae3fad3
    unsetShouldDie();
    pidThread_ = new std::thread([&](){
        runPidLoop();
    });
}

void ThrustController::unsetShouldDie() {
    std::lock_guard<std::mutex> lock(setPointMutex_);
    shouldDie_ = false;
}

void ThrustController::runPidLoop() {
    yawController_ = PidController()
            .withBounds(MIN_THROTTLE, MAX_THROTTLE)
            .withTimeDelta(timeDelta_)
            .withConstants(yawConfiguration_);
    while (!shouldDie()) {
        updateMoveThruster();
        updateYawThruster();
        updateDiveThruster();
        auto deltaInMicroseconds = timeDelta_ * 1000;
        usleep( deltaInMicroseconds );
    }
}

void ThrustController::createYawController() {
    if (yawController_) delete yawController_;
    yawController_ = PidController()
            .withBounds(MIN_THROTTLE, MAX_THROTTLE)
            .withTimeDelta(timeDelta_)
            .withConstants(yawConfiguration_);
}

void ThrustController::updateMoveThruster() {}

float ThrustController::modmod(float dividend, float divisor){
    return dividend - floor(dividend / divisor) * divisor;
}

float ThrustController::angleDelta(float base, float target){
    auto dif = target - base;
    return modmod(dif + M_PI, M_PI * 2) - M_PI;
}

void ThrustController::updateYawThruster() {
    std::lock_guard<std::mutex> lock(setPointMutex_);
    float azimuth = imuSensor_.getHeading().angles().azimuth;
    auto throttle = yawController_.calculateAdjustmentFor(0, angleDelta(yawSetPoint_, azimuth));
    yawThruster_->Thrust( throttle );
}

void ThrustController::updateDiveThruster() {}

bool ThrustController::shouldDie() {
    std::lock_guard<std::mutex> lock(setPointMutex_);
    return shouldDie_;
}

void ThrustController::move(float throttle) {
    std::lock_guard<std::mutex> lock(setPointMutex_);
    moveThruster_->Thrust( throttle );
}

void ThrustController::dive(float throttle) {
    std::lock_guard<std::mutex> lock(setPointMutex_);
    diveThruster_->Thrust( throttle );
}

void ThrustController::yaw(float angle) {
    std::lock_guard<std::mutex> lock(setPointMutex_);
    yawSetPoint_ = angle;
}

void ThrustController::kill() {
    endPidThread();
    moveThruster_->Thrust(0);
    yawThruster_->Thrust(0);
    diveThruster_->Thrust(0);
}

void ThrustController::endPidThread() {
    setShouldDie();
    pidThread_->join();
    delete pidThread_;
    pidThread_ = nullptr;
}

void ThrustController::setShouldDie() {
    std::lock_guard<std::mutex> lock(setPointMutex_);
    shouldDie_ = true;
}

void ThrustController::setNeutral() {
    move(0);
    yaw(0);
    dive(0);
}

void ThrustController::configureYaw(PidController::Configuration configuration) {
    setPointMutex_.lock();
    yawConfiguration_ = configuration;
    auto angle = yawSetPoint_;
    setPointMutex_.unlock();
    yaw( angle );
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
