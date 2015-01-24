
#include "ThrustController.h"
#include <stdexcept>
#include <cmath>
#include <thread>
#include <iostream>


//list static members so I can reference them
constexpr std::chrono::milliseconds ThrustController::UPDATE_DELAY;


ThrustController* ThrustController::singleton_ = 0;
ThrustController& ThrustController::getInstance()
{
    if (!singleton_)
        singleton_ = new ThrustController();
    return *singleton_;
}



ThrustController::ThrustController():
    thrustState_(ThrustVector(0)), yawState_(0), rollState_(0)
{
    std::cout << "Initializing ThrusterController..." << std::endl;

    //create and initialize all PWM thruster modules
    pwmX_ = std::make_shared<PWM>(PWM_SUB0);
    pwmY_ = std::make_shared<PWM>(PWM_SUB1);
    pwmZ_ = std::make_shared<PWM>(PWM_SUB2);

    //set all thrusters to neutral
    pwmX_->setPeriod(PWM_PERIOD);
    pwmY_->setPeriod(PWM_PERIOD);
    pwmZ_->setPeriod(PWM_PERIOD);

    //enable all thrusters
    pwmX_->start();
    pwmY_->start();
    pwmZ_->start();
}



ThrustController::~ThrustController()
{
    std::cout << "Tearing down ThrusterController..." << std::endl;

    //stop all thrusters
    setXThrust(NEUTRAL);
    setYThrust(NEUTRAL);
    setZThrust(NEUTRAL);

    //stop all thrusters
    pwmX_->stop();
    pwmY_->stop();
    pwmZ_->stop();
}



void ThrustController::achieveXSpeed(float goal, uint by)
{
    if (by == 0)
        throw std::invalid_argument("Impossible X acceleration!");

    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    auto oldThrust = thrustState_.x_;
    for (uint n = 1; n <= updateCount; n++)
    {
        setXThrust(oldThrust + n * (goal - oldThrust) / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }

    thrustState_.x_ = goal;
}



void ThrustController::achieveYSpeed(float goal, uint by)
{
    if (by == 0)
        throw std::invalid_argument("Impossible Y acceleration!");

    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    auto oldThrust = thrustState_.y_;
    for (uint n = 1; n <= updateCount; n++)
    {
        setYThrust(oldThrust + n * (goal - oldThrust) / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }

    thrustState_.y_ = goal;
}



void ThrustController::achieveZSpeed(float goal, uint by)
{
    if (by == 0)
        throw std::invalid_argument("Impossible Z acceleration!");

    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    auto oldThrust = thrustState_.z_;
    for (uint n = 1; n <= updateCount; n++)
    {
        setZThrust(oldThrust + n * (goal - oldThrust) / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }

    thrustState_.z_ = goal;
}



void ThrustController::achieveYawRate(float goal, uint by)
{
    if (by == 0)
        throw std::invalid_argument("Impossible yaw acceleration!");

    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    auto oldThrust = yawState_;
    for (uint n = 0; n <= updateCount; n++)
    {
        setYawRate(oldThrust + n * (goal - oldThrust) / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }

    yawState_ = goal;
}



void ThrustController::achieveRollRate(float goal, uint by)
{
    if (by == 0)
        throw std::invalid_argument("Impossible roll acceleration!");

    //linearly accelerate to target by the desired number of seconds
    auto updateCount = by * 1000 / UPDATE_DELAY_MS;
    auto oldThrust = yawState_;
    for (uint n = 0; n <= updateCount; n++)
    {
        setRollRate(oldThrust + n * (goal - oldThrust) / updateCount);
        std::this_thread::sleep_for(UPDATE_DELAY);
    }

    rollState_ = goal;
}



// **************************** PRIVATE METHODS *****************************



void ThrustController::setXThrust(float rate)
{
    setLeftXThrust(rate);
    setRightXThrust(rate);
}



void ThrustController::setYThrust(float rate)
{
    setLeftYThrust(rate);
    setRightYThrust(rate);
}



void ThrustController::setZThrust(float rate)
{
    setLeftZThrust(rate);
    setRightZThrust(rate);
}



void ThrustController::setYawRate(float rate)
{
    setLeftXThrust(rate);
    setRightXThrust(-rate);
}



void ThrustController::setRollRate(float rate)
{
    setLeftZThrust(rate);
    setRightZThrust(-rate);
}



void ThrustController::setLeftXThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for left X thrust rate!");

    std::cout << "left X:  " << rate << std::endl;

    if (pwmX_->setDutyA(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set left PWM_X's duty!");
}



void ThrustController::setRightXThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for right X thrust rate!");

    std::cout << "right X: " << rate << std::endl;

    if (pwmX_->setDutyB(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set right PWM_X's duty!");
}



void ThrustController::setLeftYThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for left Y thrust rate!");

    std::cout << "left Y:  " << rate << std::endl;

    if (pwmY_->setDutyA(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set left PWM_Y's duty!");
}



void ThrustController::setRightYThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for right Y thrust rate!");

    std::cout << "right Y: " << rate << std::endl;

    if (pwmY_->setDutyB(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set right PWM_Y's duty!");
}



void ThrustController::setLeftZThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for left Z thrust rate!");

    std::cout << "left Z:  " << rate << std::endl;

    if (pwmZ_->setDutyA(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set left PWM_Z's duty!");
}



void ThrustController::setRightZThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for right Z thrust rate!");

    std::cout << "right Z: " << rate << std::endl;

    if (pwmZ_->setDutyB(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set right PWM_Z's duty!");
}



uint ThrustController::rateToDuty(float rate)
{
    if (rate < 0)
        return static_cast<uint>(ceil(PWM_NEUTRAL + rate * (PWM_MIN - PWM_NEUTRAL)));
    else
        return static_cast<uint>(floor(PWM_NEUTRAL + rate * (PWM_MAX - PWM_NEUTRAL)));
}



float ThrustController::logisticFn(float x, float k, float x0)
{
    static const float E = 2.7182818284f;
    return static_cast<float>(1 / (1 + pow(E, -k * (x - x0))));
}
