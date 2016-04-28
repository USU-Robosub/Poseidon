/**
 * Created by Nathan Copier on 4/28/2016.
 */

var HeadLights = require("./Headlights");
var PowerManager = require("./PowerManager");
var ThrustController = require("./ThrustController");
var CppLogSource = require("./CppLogSource");
var ImuSensor = require("./ImuSensor");
var Sockets = require('../Sockets');
var Ports = require('../Sockets/Ports.json');

module.exports = (function() {

    var logSocket = Sockets.createSocket(Ports.LoggerPort);
    var dispatcherSocket = Sockets.createSocket(Ports.ThrusterPort);
    var imuSocket = Sockets.createSocket(Ports.ImuPort);

    function Factory() {}

    Factory.prototype.createCppLogSource = function () {
        return new CppLogSource(logSocket, console)
    };

    Factory.prototype.createHeadlights = function () {
        return new HeadLights(dispatcherSocket);
    };

    Factory.prototype.createImuSensor = function () {
        return new ImuSensor(imuSocket, imuSocket);
    };

    Factory.prototype.createPowerManager = function () {
        return new PowerManager(dispatcherSocket);
    };

    Factory.prototype.createThrustController = function () {
        return new ThrustController(dispatcherSocket);
    };

    return Factory;
    
})();