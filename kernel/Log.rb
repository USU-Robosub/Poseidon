require Dir.pwd + "/DiveMaster"

# This function will create a new instance of Sensors
# and start lagging sensor data to individual files
# resepective to the sensor for later analysis.
def start_logging file
	aidx = 1;
	gidx = 1;
	pidx = 1;
	tidx = 1;

	# create Log directory
	if !Dir.exists?(file)
		puts "Building file: #{file}"
		Dir.mkdir(file)
	end

	# check log files exist
	while (File.exists?(File.join(file, "/accel_#{aidx}.log")))
		puts File.join(file, "/accel_#{aidx}.log")
		aidx += 1
	end
	while (File.exists?(File.join(file, "/gyro_#{gidx}.log")))
		puts File.join(file, "/gyro_#{gidx}.log")
		gidx += 1
	end
	while (File.exists?(File.join(file, "/press_#{pidx}.log")))
		puts File.join(file, "/press_#{pidx}.log")
		pidx += 1
	end
	while (File.exists?(File.join(file, "/temp_#{tidx}.log")))
		puts File.join(file, "/temp_#{tidx}.log")
		tidx += 1
	end

	accl = File.new(File.join(file, "/accel_#{aidx}.log"), "w")
	gyro = File.new(File.join(file, "/gyro_#{gidx}.log"), "w")
	pres = File.new(File.join(file, "/press_#{pidx}.log"), "w")
	temp = File.new(File.join(file, "/temp_#{tidx}.log"), "w")
	sensors = Sensors.new
	sensors.turnOnIMU

	stop = false
	while !stop
		sleep(1.0/24.0) # 24 samples a second (24Hz)

		time_ms = (Time.now.to_f * 1000).to_i
		puts "#{time_ms}"
		accl.puts("#{time_ms} #{sensors.acceleration}")
		gyro.puts("#{time_ms} #{sensors.gyroscope}")
		pres.puts("#{time_ms} #{sensors.pressure}")
		temp.puts("#{time_ms} #{(sensors.temperatureA + sensors.temperatureB) / 2}")
	end

	accl.close
	gyro.close
	pres.close
	temp.close
	puts "End of log"
end

<<<<<<< HEAD
start_logging "/home/debian/Desktop/Log"
=======
start_logging "/home/debian/Desktop/Log"
>>>>>>> origin/remote-control
