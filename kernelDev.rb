
# for testing of very new and Rice-exposed API or driver methods

require Dir.pwd + "/kernel/DiveMaster"

print "Creating IMUSensor instance...\n"
imuSensor = IMUSensor.new

puts imuSensor.readTemperature()
puts imuSensor.readPressure()
puts imuSensor.readSealevel()
puts imuSensor.readAltitude()
#puts imuSensor.readCompass()
#puts imuSensor.readAcceleration()
#puts imuSensor.readGyro()
puts imuSensor.readTemp()

print "Sensor test complete!\n"
