# This is a mock API for the vision part of DiveMaster.
# require Dir.pwd + "/../kernel/DiveMaster"

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

class VirtualVision
	def initialize
		randX = Random.new
		randY = Random.new
		@buoyPos = [randX.rand(100.0), randY.rand(100.0)]
		@gatePos = [randX.rand(100.0), randY.rand(100.0)]
		@trackPos = [randX.rand(100.0), randY.rand(100.0)]
		@trackAngle = 0
	end
	def getBallPosition(buoyColor)
		return @buoyPos
	end
	def getGatePosition
		return @gatePos
	end
	def getTrackPosition(trackColor)
		return @trackPos
	end
	def resetBallPos
		@buoyPos = [randX.rand(100.0), randY.rand(100.0)]
	end
	def resetGatePos
		@gatePos = [randX.rand(100.0), randY.rand(100.0)]
	end
	def resetTrackPos
		@trackPos = [randX.rand(100.0), randY.rand(100.0)]
	end
	def getTrackAngle(trackColor)
		randNum = Random.new
		randAngle = randNum.rand(180.0) - 90
		return randAngle
	end

end

