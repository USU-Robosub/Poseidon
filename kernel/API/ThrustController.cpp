
#include "ThrustController.h"
#include <stdexcept>
#include <cmath>
#include <thread>
#include <iostream>


//list static members so I can reference them
constexpr std::chrono::milliseconds ThrustController::UPDATE_DELAY;
int ThrustController::instanceCount_;


ThrustController::ThrustController()
{
    if (instanceCount_ >= 1)
        throw new std::runtime_error("Cannot have more than one ThrustController!");

    std::cout << "Initializing ThrusterController..." << std::endl;

    //create and initialize all PWM thruster modules
    pwmForward_ = std::make_shared<PWM>(PWM_SUB0);
    pwmDrift_   = std::make_shared<PWM>(PWM_SUB1);
    pwmDive_    = std::make_shared<PWM>(PWM_SUB2);

    //set all thrusters to neutral
    pwmForward_->setPeriod(PWM_PERIOD);
    pwmDrift_  ->setPeriod(PWM_PERIOD);
    pwmDive_   ->setPeriod(PWM_PERIOD);

    //enable all thrusters
    pwmForward_->start();
    pwmDrift_  ->start();
    pwmDive_   ->start();

    instanceCount_++;
}



ThrustController::~ThrustController()
{
    std::cout << "Tearing down ThrusterController..." << std::endl;

    //stop all thrusters
    setForwardThrust(NEUTRAL);
    setDriftThrust(NEUTRAL);
    setYawThrust(NEUTRAL);

    //disable all PWM thruster modules
    pwmForward_->stop();
    pwmDrift_  ->stop();
    pwmDive_   ->stop();

    instanceCount_--;
}



void ThrustController::setForwardThrust(float goal)
{
    setLeftForwardThrust(goal);
    setRightForwardThrust(goal);
}



void ThrustController::setDriftThrust(float goal)
{
    setLeftDriftThrust(goal);
    setRightDriftThrust(goal);
}



void ThrustController::setDiveThrust(float goal)
{
    setLeftDiveThrust(goal);
    setRightDiveThrust(goal);
}



void ThrustController::setYawThrust(float goal)
{
    setLeftDriftThrust(goal);
    setRightDriftThrust(-goal);
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



void ThrustController::accelerateDrift(float goal, uint by)
{
    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    for (uint n = 1; n < updateCount + 1; n++)
    {
        setDriftThrust(n * goal / updateCount);
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
    setDriftThrust(rate);
    setDiveThrust(rate);
}



void ThrustController::setLeftForwardThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for LeftForward thrust rate!");

    //std::cout << "LeftForward goal:  " << rate << std::endl;

    int r = 0;

    if (leftForward_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += pwmForward_->setDutyA(rateToDuty(CANCEL_BRAKE_MIN, false));
        r += pwmForward_->setDutyA(rateToDuty(0, false));
    }

    r += pwmForward_->setDutyA(rateToDuty(rate, false));
    leftForward_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmForward_ A's duty!");
}



void ThrustController::setRightForwardThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for RightForward thrust rate!");

    //std::cout << "RightForward goal: " << rate << std::endl;

    int r = 0;

    if (rightForward_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += pwmForward_->setDutyB(rateToDuty(CANCEL_BRAKE_MIN, false));
        r += pwmForward_->setDutyB(rateToDuty(0, false));
    }

    r += pwmForward_->setDutyB(rateToDuty(rate, false));
    rightForward_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmForward_ B's duty!");
}



void ThrustController::setLeftDriftThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for LeftDrift thrust rate!");

    //std::cout << "LeftDrift goal:  " << rate << std::endl;

    int r = 0;

    if (leftDrift_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += pwmDrift_->setDutyA(rateToDuty(CANCEL_BRAKE_MIN, true));
        r += pwmDrift_->setDutyA(rateToDuty(0, true));
    }

    r += pwmDrift_->setDutyA(rateToDuty(rate, true));
    leftDrift_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmDrift_ A's duty!");
}



void ThrustController::setRightDriftThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for RightDrift thrust rate!");

    //std::cout << "RightDrift goal:  " << rate << std::endl;

    int r = 0;

    if (rightDrift_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += pwmDrift_->setDutyB(rateToDuty(CANCEL_BRAKE_MIN, true));
        r += pwmDrift_->setDutyB(rateToDuty(0, true));
    }

    r += pwmDrift_->setDutyB(rateToDuty(rate, true));
    rightDrift_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmDrift_ B's duty!");
}



void ThrustController::setLeftDiveThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for LeftDive thrust rate!");

    //std::cout << "LeftDive goal:  " << rate << std::endl;

    int r = 0;

    if (leftDive_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += pwmDive_->setDutyA(rateToDuty(CANCEL_BRAKE_MIN, true));
        r += pwmDive_->setDutyA(rateToDuty(0, true));
    }

    r += pwmDive_->setDutyA(rateToDuty(rate, true));
    leftDive_ = rate;

    if (r > 0)
        throw std::runtime_error("Failure to set pwmDive_ A's duty!");
}



void ThrustController::setRightDiveThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for RightDive thrust rate!");

    //std::cout << "RightDive goal:  " << rate << std::endl;

    int r = 0;

    if (rightDive_ > 0 && rate <= 0)
    { //switching to reverse, undo ESC braking
        r += pwmDive_->setDutyB(rateToDuty(CANCEL_BRAKE_MIN, true));
        r += pwmDive_->setDutyB(rateToDuty(0, true));
    }

    r += pwmDive_->setDutyB(rateToDuty(rate, true));
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