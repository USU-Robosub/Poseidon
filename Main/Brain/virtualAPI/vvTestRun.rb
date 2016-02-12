#This is the test run file file for virtual vision 
require "./virtualVision"

virtualEye = VirtualVision.new
returnedBuoyPos = virtualEye.getBuoyPosition([230, 5, 50])
print "Buoy position: #{returnedBuoyPos}\n"
# virtualEye.resetBuoyPos
print "Gate position: #{virtualEye.getGatePosition}\n"
print "Track position: #{virtualEye.getTrackPosition([100, 266, 24])}\n"
print "Track angle compared to sub: #{virtualEye.getTrackAngle([23, 51, 56])}\n"