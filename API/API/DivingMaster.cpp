
#include "DivingMaster.h"
#include <stdexcept>
#include <cmath>
#include <iostream>


DivingMaster* DivingMaster::singleton_ = 0;
DivingMaster& DivingMaster::getInstance()
{
    if (!singleton_)
        singleton_ = new DivingMaster();
    return *singleton_;
}



DivingMaster::DivingMaster()
{
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



DivingMaster::~DivingMaster()
{
    //stop all thrusters
    setXThrust(NEUTRAL);
    setYThrust(NEUTRAL);
    setZThrust(NEUTRAL);

    //stop all thrusters
    pwmX_->stop();
    pwmY_->stop();
    pwmZ_->stop();
}



void DivingMaster::achieveXSpeed(float goal, int by)
{
    std::cout << goal << std::endl;
    std::cout.flush();
}



void DivingMaster::achieveYSpeed(float goal, int by)
{

}



void DivingMaster::achieveZSpeed(float goal, int by)
{

}



void DivingMaster::achievePitchRate(float goal, int by)
{

}



void DivingMaster::achieveYawRate(float goal, int by)
{

}



void DivingMaster::achieveRollRate(float goal, int by)
{

}



// **************************** PRIVATE METHODS *****************************



void DivingMaster::setXThrust(float rate)
{
    setLeftXThrust(rate);
    setRightXThrust(rate);
}



void DivingMaster::setYThrust(float rate)
{
    setLeftYThrust(rate);
    setRightYThrust(rate);
}



void DivingMaster::setZThrust(float rate)
{
    setLeftZThrust(rate);
    setRightZThrust(rate);
}



void DivingMaster::setYawRate(float rate)
{
    setLeftXThrust(rate);
    setRightXThrust(-rate);
}



void DivingMaster::setRollRate(float rate)
{
    setLeftZThrust(rate);
    setRightZThrust(-rate);
}



void DivingMaster::setLeftXThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for left X thrust rate!");

    if (pwmX_->setDutyA(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set left PWM_X's duty!");
}



void DivingMaster::setRightXThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for right X thrust rate!");

    if (pwmX_->setDutyB(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set right PWM_X's duty!");
}



void DivingMaster::setLeftYThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for left Y thrust rate!");

    if (pwmY_->setDutyA(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set left PWM_Y's duty!");
}



void DivingMaster::setRightYThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for right Y thrust rate!");

    if (pwmY_->setDutyB(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set right PWM_Y's duty!");
}



void DivingMaster::setLeftZThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for left Z thrust rate!");

    if (pwmZ_->setDutyA(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set left PWM_Z's duty!");
}



void DivingMaster::setRightZThrust(float rate)
{
    if (rate < FULL_REVERSE || rate > FULL_AHEAD)
        throw std::invalid_argument("Invalid value for right Z thrust rate!");

    if (pwmZ_->setDutyB(rateToDuty(rate)) != 0)
        throw std::runtime_error("Failure to set right PWM_Z's duty!");
}



uint DivingMaster::rateToDuty(float rate)
{
    if (rate < 0)
        return static_cast<uint>(ceil(PWM_NEUTRAL + rate * (PWM_MIN - PWM_NEUTRAL)));
    else
        return static_cast<uint>(floor(PWM_NEUTRAL + rate * (PWM_MAX - PWM_NEUTRAL)));
}



float DivingMaster::logisticFn(float x, float k, float x0)
{
    static const float E = 2.7182818284f;
    return static_cast<float>(1 / (1 + pow(E, -k * (x - x0))));
}
