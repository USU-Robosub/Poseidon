function DiveMaster() {
	this.NEUTRAL = 0;
	this.FULL_AHEAD = 0.99;
	this.FULL_REVERSE = -0.99;

	this.setForwardThrust = function(velocity) {
		console.log("setForwardThrust " + velocity);
	};
	this.setDiveThrust = function(velocity) {
		console.log("setDiveThrust " + velocity);
	};
	this.setStrafeThrust = function(velocity) {
		console.log("setStrafeThrust " + velocity);
	};
	this.setYawThrust = function(velocity) {
		console.log("setYawThrust " + velocity);
	};
}

module.exports = DiveMaster;
