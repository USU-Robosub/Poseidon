
# for testing of very new and Rice-exposed API or driver methods

require Dir.pwd + "/kernel/DiveMaster"

print "Creating IMUSensor instance...\n"
imuSensor = IMUSensor.new

print imuSensor.readTemperature()
print imuSensor.readPressure()
print imuSensor.readSealevel()
print imuSensor.readAltitude()
puts  imuSensor.readCompass()
puts  imuSensor.readAcceleration()
puts  imuSensor.readGyro()
print imuSensor.readTemperature()

print "Sensor test complete!\n"
