// Headlights.js - Javascript interface for controlling the headlights of Poseidon
//
// Created by Kevin Burgon on 02/01/2016

module.exports = (function(){

    function Headlights(cmdOut) {
        this._cmdOut = cmdOut;
    }

    Headlights.prototype.toggleLights = function() {
        this._cmdOut.write("switchLights\n");
    };

    return Headlights;

})();
