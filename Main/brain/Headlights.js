// Headlights.js - Javascript interface for controlling the headlights of Poseidon
//
// Created by Kevin Burgon on 02/01/2016

function Headlights(cmdOut) {

	this.toggleLights = function() {
		child.stdin.write("switchLights");
	}
}

module.exports = Headlights;
