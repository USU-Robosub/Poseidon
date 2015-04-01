require Dir.pwd + "/DiveMaster"

#thrust = ThrustController.new

test = Sensors.new

def function(var)
	puts "Ready... Go!"
	sleep(20)
	var.setForwardThrust(0.1)
	sleep(60)
	var.setForwardThrust(0.95)
	sleep(60 * 3)
	var.setForwardThrust(0)
	puts "Finished"
end

#function thrust
