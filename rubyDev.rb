
# for testing new sub controls and maneuvers

require Dir.pwd + "/kernel/DiveMaster"

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

# enable ESCs otherwise they won't run
power = PowerManagement.new
power.turnOnESCs()

print "Creating ThrustController instance...\n"
thrustController = ThrustController.new

print "Pausing for a while...\n"
sleep(5)

print "Exploring extremes of forward and backwards thrusters...\n"
thrustController.accelerateForward(Thrust::FULL_AHEAD,   10)
thrustController.accelerateForward(Thrust::FULL_REVERSE, 15)
thrustController.accelerateForward(Thrust::NEUTRAL,      5)

print "Pausing for a while...\n"
sleep(3)

print "Exploring extremes of left and right thrusters...\n"
thrustController.accelerateDrift(Thrust::FULL_AHEAD,   10)
thrustController.accelerateDrift(Thrust::FULL_REVERSE, 15)
thrustController.accelerateDrift(Thrust::NEUTRAL,      5)

print "Pausing for a while...\n"
sleep(3)

print "Exploring extremes of up and down thrusters...\n"
thrustController.accelerateDive(Thrust::FULL_AHEAD,   10)
thrustController.accelerateDive(Thrust::FULL_REVERSE, 15)
thrustController.accelerateDive(Thrust::NEUTRAL,      5)

print "Pausing for a while...\n"
sleep(3)

print "Exploring extremes of yaw rates...\n"
thrustController.accelerateYaw(Thrust::FULL_AHEAD,     10)
thrustController.accelerateYaw(Thrust::FULL_REVERSE,   15)
thrustController.accelerateYaw(Thrust::NEUTRAL,        5)

print "Pausing for a while...\n"
sleep(3)

print "Pausing for a while...\n"
sleep(5)

print "Firing all thrusters...\n"
thrustController.accelerateForward(Thrust::FULL_AHEAD, 4)
thrustController.accelerateDrift(Thrust::FULL_AHEAD,   4)
thrustController.accelerateDive(Thrust::FULL_AHEAD,    4)

print "Pausing for a while...\n"
sleep(5)

print "Backing down...\n"
thrustController.accelerateForward(Thrust::NEUTRAL, 4)
thrustController.accelerateDrift(Thrust::NEUTRAL,   4)
thrustController.accelerateDive(Thrust::NEUTRAL,    4)

print "Test complete!\n"
