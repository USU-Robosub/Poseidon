
#include "API/ThrustController.h"
#include <thread>
#include <chrono>
#include <iostream>


int main(int argc, char** argv)
{
    std::cout << "Creating ThrustController instance..." << std::endl;
    ThrustController dm = ThrustController::getInstance();

    std::cout << "Pausing for a while..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Exploring extremes of left and right thrusters..." << std::endl;
    dm.achieveXRate(ThrustController::FULL_AHEAD,   10);
    dm.achieveXRate(ThrustController::FULL_REVERSE, 15);
    dm.achieveXRate(ThrustController::NEUTRAL,      5);

    std::cout << "Exploring extremes of forward and backwards thrusters..." << std::endl;
    dm.achieveYRate(ThrustController::FULL_AHEAD,   10);
    dm.achieveYRate(ThrustController::FULL_REVERSE, 15);
    dm.achieveYRate(ThrustController::NEUTRAL,      5);

    std::cout << "Exploring extremes of up and down thrusters..." << std::endl;
    dm.achieveZRate(ThrustController::FULL_AHEAD,   10);
    dm.achieveZRate(ThrustController::FULL_REVERSE, 15);
    dm.achieveZRate(ThrustController::NEUTRAL,      5);

    std::cout << "Exploring extremes of yaw rates..." << std::endl;
    dm.achieveYawRate(ThrustController::FULL_AHEAD,     10);
    dm.achieveYawRate(ThrustController::FULL_REVERSE,   15);
    dm.achieveYawRate(ThrustController::NEUTRAL,        5);

    std::cout << "Attempting to roll the sub over..." << std::endl;
    dm.achieveRollRate(ThrustController::FULL_AHEAD,    5);
    dm.achieveRollRate(ThrustController::FULL_REVERSE,  10);
    dm.achieveRollRate(ThrustController::NEUTRAL,       5);

    std::cout << "Pausing for a while..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Firing all thrusters..." << std::endl;
    dm.achieveXRate(ThrustController::FULL_AHEAD,   3);
    dm.achieveYRate(ThrustController::FULL_AHEAD,   3);
    dm.achieveZRate(ThrustController::FULL_AHEAD,   3);

    std::cout << "Pausing for a while..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Backing down..." << std::endl;
    dm.achieveZRate(ThrustController::NEUTRAL,      3);
    dm.achieveYRate(ThrustController::NEUTRAL,      3);
    dm.achieveXRate(ThrustController::NEUTRAL,      3);

    std::cout << "Test complete!" << std::endl;

    return EXIT_SUCCESS;
}

//void setRelativeDepth(float depth);
//void setRelativePosition(float x, float y);
