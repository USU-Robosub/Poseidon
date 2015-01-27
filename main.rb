
require Dir.pwd + "/API/DiveMaster"

#wasn't able to import these from C++, so redefined them here
module Thrust
    FULL_AHEAD = 1
    TWO_THIRDS_AHEAD = 2 / 3
    HALF_AHEAD = 1 / 2
    ONE_THIRD_AHEAD = 1 / 3
    NEUTRAL = 0
    ONE_THIRD_REVERSE = -1 / 3
    HALF_REVERSE = -1 / 2
    TWO_THIRDS_REVERSE = -2 / 3
    FULL_REVERSE = -1
end

print "Creating ThrustController instance...\n"
thrustController = ThrustController.new

print "Pausing for a while...\n"
sleep(5)

print "Exploring extremes of left and right thrusters...\n"
thrustController.achieveXRate(Thrust::FULL_AHEAD,   10);
thrustController.achieveXRate(Thrust.FULL_REVERSE,  15);
thrustController.achieveXRate(Thrust::NEUTRAL,      5);

print "Exploring extremes of forward and backwards thrusters...\n"
thrustController.achieveYRate(ThrustController::FULL_AHEAD,   10);
thrustController.achieveYRate(ThrustController::FULL_REVERSE, 15);
thrustController.achieveYRate(ThrustController::NEUTRAL,      5);

print "Exploring extremes of up and down thrusters...\n"
thrustController.achieveZRate(ThrustController::FULL_AHEAD,   10);
thrustController.achieveZRate(ThrustController::FULL_REVERSE, 15);
thrustController.achieveZRate(ThrustController::NEUTRAL,      5);

print "Exploring extremes of yaw rates...\n"
thrustController.achieveYawRate(ThrustController::FULL_AHEAD,     10);
thrustController.achieveYawRate(ThrustController::FULL_REVERSE,   15);
thrustController.achieveYawRate(ThrustController::NEUTRAL,        5);

print "Attempting to roll the sub over...\n"
thrustController.achieveRollRate(ThrustController::FULL_AHEAD,    5);
thrustController.achieveRollRate(ThrustController::FULL_REVERSE,  10);
thrustController.achieveRollRate(ThrustController::NEUTRAL,       5);

print "Pausing for a while...\n"
sleep(5)

print "Firing all thrusters...\n"
thrustController.achieveXRate(ThrustController::FULL_AHEAD,   3);
thrustController.achieveYRate(ThrustController::FULL_AHEAD,   3);
thrustController.achieveZRate(ThrustController::FULL_AHEAD,   3);

print "Pausing for a while...\n"
sleep(5)

print "Backing down...\n"
thrustController.achieveZRate(ThrustController::NEUTRAL,      3);
thrustController.achieveYRate(ThrustController::NEUTRAL,      3);
thrustController.achieveXRate(ThrustController::NEUTRAL,      3);

print "Test complete!\n"
