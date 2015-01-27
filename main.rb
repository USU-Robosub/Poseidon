
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
thrustController.achieveXRate(Thrust::FULL_REVERSE,  15);
thrustController.achieveXRate(Thrust::NEUTRAL,      5);

print "Exploring extremes of forward and backwards thrusters...\n"
thrustController.achieveYRate(Thrust::FULL_AHEAD,   10);
thrustController.achieveYRate(Thrust::FULL_REVERSE, 15);
thrustController.achieveYRate(Thrust::NEUTRAL,      5);

print "Exploring extremes of up and down thrusters...\n"
thrustController.achieveZRate(Thrust::FULL_AHEAD,   10);
thrustController.achieveZRate(Thrust::FULL_REVERSE, 15);
thrustController.achieveZRate(Thrust::NEUTRAL,      5);

print "Exploring extremes of yaw rates...\n"
thrustController.achieveYawRate(Thrust::FULL_AHEAD,     10);
thrustController.achieveYawRate(Thrust::FULL_REVERSE,   15);
thrustController.achieveYawRate(Thrust::NEUTRAL,        5);

print "Attempting to roll the sub over...\n"
thrustController.achieveRollRate(Thrust::FULL_AHEAD,    5);
thrustController.achieveRollRate(Thrust::FULL_REVERSE,  10);
thrustController.achieveRollRate(Thrust::NEUTRAL,       5);

print "Pausing for a while...\n"
sleep(5)

print "Firing all thrusters...\n"
thrustController.achieveXRate(Thrust::FULL_AHEAD,   3);
thrustController.achieveYRate(Thrust::FULL_AHEAD,   3);
thrustController.achieveZRate(Thrust::FULL_AHEAD,   3);

print "Pausing for a while...\n"
sleep(5)

print "Backing down...\n"
thrustController.achieveZRate(Thrust::NEUTRAL,  3);
thrustController.achieveYRate(Thrust::NEUTRAL,  3);
thrustController.achieveXRate(Thrust::NEUTRAL,  3);

print "Test complete!\n"
