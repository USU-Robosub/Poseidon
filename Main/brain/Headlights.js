function Headlights() {
	
	this.areOn = false;

	this.toggleLights = function() {
		if (areOn) {
			areOn = true;
		}
		else {
			areOn = false;
		}
		console.log("switchLights" + areOn);
	}
}

module.exports = Headlights;
