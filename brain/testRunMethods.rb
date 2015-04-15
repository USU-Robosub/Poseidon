# This is a class of test code for the sub, for pooltime test runs.

# require Dir.pwd + "/kernel/DiveMaster"
# require Dir.pwd + "/virtualAPI/virtualVision"

class TestRunMethods
	def initialize(newPowerController, newThrustController)
		@power = newPowerController
		@thrustController = newThrustController
	end
	def prepareSystem
		@power = PowerController.new
		@power.turnOnESCs()

		print "Creating ThrustController instance...\n"
		@thrustController = ThrustController.new
	end
	def basicRun
		print "Pausing for a while...\n"
		sleep(5)

		print "Exploring extremes of forward and backwards thrusters...\n"
		@thrustController.accelerateForward(Thrust::FULL_AHEAD,   10)
		@thrustController.accelerateForward(Thrust::FULL_REVERSE, 15)
		@thrustController.accelerateForward(Thrust::NEUTRAL,      5)

		print "Pausing for a while...\n"
		sleep(3)

		print "Exploring extremes of left and right thrusters...\n"
		@thrustController.accelerateStrafe(Thrust::FULL_AHEAD,   10)
		@thrustController.accelerateStrafe(Thrust::FULL_REVERSE, 15)
		@thrustController.accelerateStrafe(Thrust::NEUTRAL,      5)

		print "Pausing for a while...\n"
		sleep(3)

		print "Exploring extremes of up and down thrusters...\n"
		@thrustController.accelerateDive(Thrust::FULL_AHEAD,   10)
		@thrustController.accelerateDive(Thrust::FULL_REVERSE, 15)
		@thrustController.accelerateDive(Thrust::NEUTRAL,      5)

		print "Pausing for a while...\n"
		sleep(3)

		print "Exploring extremes of yaw rates...\n"
		@thrustController.accelerateYaw(Thrust::FULL_AHEAD,     10)
		@thrustController.accelerateYaw(Thrust::FULL_REVERSE,   15)
		@thrustController.accelerateYaw(Thrust::NEUTRAL,        5)

		print "Pausing for a while...\n"
		sleep(3)

		print "Pausing for a while...\n"
		sleep(5)

		print "Firing all thrusters...\n"
		@thrustController.accelerateForward(Thrust::FULL_AHEAD, 4)
		@thrustController.accelerateStrafe(Thrust::FULL_AHEAD,   4)
		@thrustController.accelerateDive(Thrust::FULL_AHEAD,    4)

		print "Pausing for a while...\n"
		sleep(5)

		print "Backing down...\n"
		@thrustController.accelerateForward(Thrust::NEUTRAL, 4)
		@thrustController.accelerateStrafe(Thrust::NEUTRAL,   4)
		@thrustController.accelerateDive(Thrust::NEUTRAL,    4)

		print "Test complete!\n"
	end
	def zigZag
		# print "To be completed...\n"
		print "Heading 45 degrees to the left...\n"
		@thrustController.accelerateYaw(0.5, 2)
		@thrustController.accelerateYaw(0, 2)
		@thrustController.accelerateForward(0.5, 4)
		print "Achieved angle!  Now moving forward...\n"
		sleep(5)
		print "Changing Angle...\n"
		@thrustController.accelerateForward(0, 2)
		@thrustController.accelerateYaw(-0.5, 4)
		@thrustController.accelerateYaw(0, 2)
		print "Achieved angle!  Now moving forward...\n"
		@thrustController.accelerateForward(0.5, 4)
		sleep(5)
		print "Now diving...\n"
		@thrustController.accelerateDive(0.9, 2)
		sleep(5)
		@thrustController.accelerateDive(0, 2)
		print "Slowing Down and turning around...\n"
		@thrustController.accelerateYaw(0.5, 2)
		@thrustController.accelerateYaw(0, 2)
		@thrustController.accelerateForward(0.5, 4)
		print "Achieved angle!  Now moving backward...\n"
		sleep(5)
		print "Changing Angle...\n"
		@thrustController.accelerateForward(0, 2)
		@thrustController.accelerateYaw(-0.5, 4)
		@thrustController.accelerateYaw(0, 2)
		print "Achieved angle!  Now moving backward...\n"
		@thrustController.accelerateForward(0.5, 4)
		sleep(5)
		@thrustController.accelerateForward(0, 2)
		print "Done!  Now surfacing...\n"
		@thrustController.accelerateDive(-0.9, 2)
		sleep(5)	
		@thrustController.accelerateDive(0, 2)
		print "Reached the surface.  End acheived!\n"
	end
	def dryTest
		print "Starting dry test of thrusters.\nTesting forward/backward Thrust...\n"
		@thrustController.setForwardThrust(0.1)
		sleep(5)
		@thrustController.setForwardThrust(0)
		sleep(3)
		@thrustController.setForwardThrust(-0.1)
		sleep(5)
		@thrustController.setForwardThrust(0)
		print "Now testing Yaw...\n"
		@thrustController.setYawThrust(0.1)
		sleep(5)
		@thrustController.setYawThrust(0)
		sleep(3)
		@thrustController.setYawThrust(-0.1)
		sleep(5)
		@thrustController.setYawThrust(0)
		print "Now testing Dive Thrusters...\n"
		@thrustController.setDiveThrust(0.1)
		sleep(5)
		@thrustController.setDiveThrust(0)
		sleep(3)
		@thrustController.setDiveThrust(-0.1)
		sleep(5)
		@thrustController.setDiveThrust(0)
		print "Now testing Strafe Thrusters...\n"
		@thrustController.setStrafeThrust(0.1)
		sleep(5)
		@thrustController.setStrafeThrust(0)
		sleep(3)
		@thrustController.setStrafeThrust(-0.1)
		sleep(5)
		@thrustController.setStrafeThrust(0)
		print "Dry test done!"
	end
	def testForwardThrust
		print "Test forward thrusters at half power under water:  starting...\n"
		print "Diving...\n"
		@thrustController.setDiveThrust(0.7)
		sleep(5)
		@thrustController.setDiveThrust(0)
		print "Waiting 3 seconds to test buoyancy...\n"
		sleep(3)
		print "Setting forward thrust to 50% for 5 seconds...\n"
		@thrustController.setForwardThrust(0.5)
		sleep(5)
		print "Stopping forward thrusters and resurfacing...\n"
		@thrustController.setForwardThrust(0)
		@thrustController.setDiveThrust(-0.7)
		sleep(5)
		print "Done!\n"
	end
end
