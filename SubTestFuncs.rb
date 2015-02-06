require Dir.pwd + "/API/DiveMaster"

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

class SubTestFuncs
	attr_accessor :thrustController
	def initialize
		print "Initializing test functions...\n"
		print "Creating ThrustController instance...\n"
		@thrustController = ThrustController.new

		print "Pausing for a while...\n"
		sleep(5)
	end
	def figureEight
		while true do
			print("Heading NorthWest...\n");
			thrustController.achieveYRate(Thrust::FULL_AHEAD, 10);
			thrustController.achieveXRate(Thrust::FULL_REVERSE, 10);
			thrustController.achieveZRate(Thrust::TWO_THIRDS_AHEAD, 6);
			print("Achieved full speed!\n");
			sleep(20);
			print("Stopping...\n");
			thrustController.achieveXRate(Thrust::NEUTRAL, 5);
			thrustController.achieveYRate(Thrust::NEUTRAL, 5);
			thrustController.achieveZRate(Thrust::NEUTRAL, 3);

			print("Heading East\n");
			thrustController.achieveXRate(Thrust::FULL_AHEAD, 10);
			print("Achieved full speed!\n");
			sleep(15);
			print("Stopping...\n");
			thrustController.achieveXRate(Thrust::NEUTRAL, 5);

			print("Heading SouthWest\n");
			thrustController.achieveYRate(Thrust::FULL_REVERSE, 10);
			thrustController.achieveXRate(Thrust::FULL_AHEAD, 10);
			thrustController.achieveZRate(Thrust::TWO_THIRDS_REVERSE, 6);
			print("Achieved full speed!\n");
			sleep(20);
			print("Stopping...\n");
			thrustController.achieveXRate(Thrust::NEUTRAL, 5);
			thrustController.achieveYRate(Thrust::NEUTRAL, 5);
			thrustController.achieveZRate(Thrust::NEUTRAL, 3);

			print("Heading West\n");
			thrustController.achieveXRate(Thrust::FULL_REVERSE, 10);
			print("Achieved full speed!\n");
			sleep(15);
			print("Stopping...\n");
			thrustController.achieveXRate(Thrust::NEUTRAL, 5);
			print("We're back where we started!  Starting again...\n");
		end
	end
end