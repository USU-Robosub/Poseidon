class DiveMaster
	def initialize
		@NEUTRAL = 0
		@FULL_AHEAD = 0.99
		@FULL_REVERSE = -0.99
	end
	def setForwardThrust(velocity)
		print "setForwardThrust #{velocity}"
	end
	def setDiveThrust(velocity)
		print "setDiveThrust #{velocity}"
	end
	def setStrafeThrust(velocity)
		print "setStrafeThrust #{velocity}"
	end
	def setYawThrust(velocity)
		print "setYawThrust #{velocity}"
	end
end