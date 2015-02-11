
# for testing of very new and Rice-exposed API or driver methods

require Dir.pwd + "/kernel/DiveMaster"

print "Creating IMUSensor instance...\n"
imuSensor = IMUSensor.new

print imuSensor.readInteriorTemperature()
print imuSensor.readPressure()
print imuSensor.readSealevelPressure()
print imuSensor.readAltitude()
puts  imuSensor.readCompass()
puts  imuSensor.readAcceleration()
puts  imuSensor.readGyro()
print imuSensor.readTemperature()

print "Sensor test complete!\n"
