
# Generally reliable submarine control, containing pool-tested functionality

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
#power = PowerManagement.new
#power.turnOnESCs()

print "Creating ThrustController instance...\n"
thrustController = ThrustController.new

print "Pausing for a while...\n"
sleep(5)
