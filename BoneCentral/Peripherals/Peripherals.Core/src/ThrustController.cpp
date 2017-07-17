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
        isDead_(true),
        pidThread_(nullptr),
        logger_(logger) { }

void ThrustController::start() {
    if (pidThread_ != nullptr) return;
    setNeutral();
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
    while (!shouldDie()) {
        updateMoveThruster();
        updateYawThruster();
        updateDiveThruster();
        usleep( timeDelta_ );
    }
}

void ThrustController::updateMoveThruster() {}

void ThrustController::updateYawThruster() {
    std::lock_guard<std::mutex> lock(setPointMutex_);
    float azimuth = imuSensor_.getHeading().angles().azimuth;
    auto throttle = yawController_.calculateAdjustmentFor(0, yawSetPoint_ - azimuth);
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
    yawController_ = PidController()
            .withBounds(MIN_THROTTLE, MAX_THROTTLE)
            .withTimeDelta(timeDelta_)
            .withConstants(yawConfiguration_);
    yawSetPoint_ = angle;
}

void ThrustController::kill() {
    endPidThread();
    setNeutral();
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
