#include "ThrustController.h"

// TODO: Global Memory is bad!! This should be moved.
constexpr std::chrono::milliseconds ThrustController::UPDATE_DELAY;


ThrustController::ThrustController(IThrusterFactory& thrusterFactory, std::shared_ptr<ILogger> logger) :
        forwardThruster_(thrusterFactory.createForwardThruster()),
        strafeThruster_(thrusterFactory.createStrafeThruster()),
        diveThruster_(thrusterFactory.createDiveThruster()),
        logger_(logger)
{

    logger_->info("Initializing Thrusters...");

    //set all thrusters to neutral
    forwardThruster_->setPeriod(PWM_PERIOD);
    strafeThruster_ ->setPeriod(PWM_PERIOD);
    diveThruster_   ->setPeriod(PWM_PERIOD);

    //enable all thrusters
    forwardThruster_->start();
    strafeThruster_ ->start();
    diveThruster_   ->start();
}



ThrustController::~ThrustController()
{
    logger_->info("Stopping Thrusters...");

    //stop all thrusters
    setForwardThrust(NEUTRAL);
    setStrafeThrust(NEUTRAL);
    setYawThrust(NEUTRAL);

    //disable all PWM thruster modules
    forwardThruster_->stop();
    strafeThruster_ ->stop();
    diveThruster_   ->stop();
}



void ThrustController::setForwardThrust(float goal)
{
    setLeftForwardThrust(goal);
    setRightForwardThrust(goal);
}



void ThrustController::setStrafeThrust(float goal)
{
    setLeftStrafeThrust(goal);
    setRightStrafeThrust(goal);
}



void ThrustController::setDiveThrust(float goal)
{
    setLeftDiveThrust(goal);
    setRightDiveThrust(goal);
}



void ThrustController::setYawThrust(float left)
{
    setLeftForwardThrust(left);
    setRightForwardThrust(-left);
}



void ThrustController::setPitchThrust(float left, float right)
{
    setLeftForwardThrust(left);
    setRightForwardThrust(right);
}



void ThrustController::accelerateForward(float goal, uint by)
{
    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    for (uint n = 1; n < updateCount + 1; n++)
    {
        setForwardThrust(n * goal / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }
}



void ThrustController::accelerateStrafe(float goal, uint by)
{
    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    for (uint n = 1; n < updateCount + 1; n++)
    {
        setStrafeThrust(n * goal / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }
}



void ThrustController::accelerateDive(float goal, uint by)
{
    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    for (uint n = 1; n < updateCount + 1; n++)
    {
        setDiveThrust(n * goal / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }
}



void ThrustController::accelerateYaw(float goal, uint by)
{
    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    for (uint n = 1; n < updateCount + 1; n++)
    {
        setYawThrust(n * goal / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }
}



// **************************** PRIVATE METHODS *****************************



void ThrustController::setAllThrust(float rate)
{
    setForwardThrust(rate);
    setStrafeThrust(rate);
    setDiveThrust(rate);
}



void ThrustController::setLeftForwardThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD) {
        auto message = "Invalid value for LeftForward thrust rate!";
        logger_->error(message);
        throw std::invalid_argument(message);
    }

    int r = 0;

    if (leftForward_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += forwardThruster_->setDutyA(rateToDuty(CANCEL_BRAKE_MIN, false));
	    std::this_thread::sleep_for(UPDATE_DELAY);
        r += forwardThruster_->setDutyA(rateToDuty(0, false));
	    std::this_thread::sleep_for(UPDATE_DELAY);
    }

    r += forwardThruster_->setDutyA(rateToDuty(rate, false));
    leftForward_ = rate;

    if (r > 0) {
        auto message = "Failure to set pwmForward_ A's duty!";
        logger_->error(message);
        throw std::runtime_error(message);
    }
}



void ThrustController::setRightForwardThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for RightForward thrust rate!");

    int r = 0;

    if (rightForward_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += forwardThruster_->setDutyB(rateToDuty(CANCEL_BRAKE_MIN, false));
	    std::this_thread::sleep_for(UPDATE_DELAY);
        r += forwardThruster_->setDutyB(rateToDuty(0, false));
	    std::this_thread::sleep_for(UPDATE_DELAY);
    }

    r += forwardThruster_->setDutyB(rateToDuty(rate, false));
    rightForward_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmForward_ B's duty!");
}



void ThrustController::setLeftStrafeThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for LeftDrift thrust rate!");

    //std::cout << "LeftDrift goal:  " << rate << std::endl;

    int r = 0;

    if (leftDrift_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += strafeThruster_->setDutyA(rateToDuty(CANCEL_BRAKE_MIN, true));
        std::this_thread::sleep_for(UPDATE_DELAY);
	    r += strafeThruster_->setDutyA(rateToDuty(0, true));
	    std::this_thread::sleep_for(UPDATE_DELAY);
    }

    r += strafeThruster_->setDutyA(rateToDuty(rate, true));
    leftDrift_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmDrift_ A's duty!");
}



void ThrustController::setRightStrafeThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for RightDrift thrust rate!");

    int r = 0;

    if (rightDrift_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += strafeThruster_->setDutyB(rateToDuty(CANCEL_BRAKE_MIN, true));
	    std::this_thread::sleep_for(UPDATE_DELAY);
        r += strafeThruster_->setDutyB(rateToDuty(0, true));
	    std::this_thread::sleep_for(UPDATE_DELAY);
    }

    r += strafeThruster_->setDutyB(rateToDuty(rate, true));
    rightDrift_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmDrift_ B's duty!");
}



void ThrustController::setLeftDiveThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for LeftDive thrust rate!");

    int r = 0;

    if (leftDive_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += diveThruster_->setDutyA(rateToDuty(CANCEL_BRAKE_MIN, true));
	    std::this_thread::sleep_for(UPDATE_DELAY);
        r += diveThruster_->setDutyA(rateToDuty(0, true));
	    std::this_thread::sleep_for(UPDATE_DELAY);
    }

    r += diveThruster_->setDutyA(rateToDuty(rate, true));
    leftDive_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmDive_ A's duty!");
}



void ThrustController::setRightDiveThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for RightDive thrust rate!");

    int r = 0;

    if (rightDive_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += diveThruster_->setDutyB(rateToDuty(CANCEL_BRAKE_MIN, true));
	std::this_thread::sleep_for(UPDATE_DELAY);
        r += diveThruster_->setDutyB(rateToDuty(0, true));
	std::this_thread::sleep_for(UPDATE_DELAY);
    }

    r += diveThruster_->setDutyB(rateToDuty(rate, true));
    rightDive_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmDive_ B's duty!");
}



uint ThrustController::rateToDuty(float rate, bool isSebotix) const
{
    if (isSebotix && rate >= -MIN_SEAB_POWER && rate <= MIN_SEAB_POWER)
        rate = 0; //no need to provide power if the motors can't turn

    if (rate < 0)
        return static_cast<uint>(ceil(PWM_NEUTRAL + rate * (PWM_NEUTRAL - PWM_MIN)));
    else
        return static_cast<uint>(floor(PWM_NEUTRAL + rate * (PWM_MAX - PWM_NEUTRAL)));
}



float ThrustController::logisticFn(float x, float k, float x0) const
{
    static const float E = 2.7182818284f;
    return static_cast<float>(1 / (1 + pow(E, -k * (x - x0))));
}
