/**
 * Created by Nathan Copier on 4/28/2016.
 */

var HeadLights          = require("./Headlights");
var PowerManager        = require("./PowerManager");
var ThrustController    = require("./ThrustController");
var ImuSensor           = require("./ImuSensor");
var CppLogSource        = require("./CppLogSource");
var AuxiliarySensors    = require("./AuxiliarySensors");

module.exports = (function() {
    function Factory(dispatcherSocket) {
        this.dispatcherSocket   = dispatcherSocket;
    }

    Factory.prototype.createHeadlights = function () {
        return new HeadLights(this.dispatcherSocket.Input);
    };

    Factory.prototype.createAuxiliarySensors = function () {
        return new AuxiliarySensors(this.dispatcherSocket.Output, this.dispatcherSocket.Input);
    };

    Factory.prototype.createImuSensor = function () {
        return new ImuSensor(this.dispatcherSocket.Output, this.dispatcherSocket.Input);
    };

    Factory.prototype.createPowerManager = function () {
        return new PowerManager(this.dispatcherSocket.Input, this.dispatcherSocket.Events);
    };

    Factory.prototype.createThrustController = function () {
        return new ThrustController(this.dispatcherSocket.Input);
    };

    return Factory;
})();