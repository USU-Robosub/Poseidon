/**
 * Created by Nathan Copier on 4/28/2016.
 */

var HeadLights = require("./Headlights");
var PowerManager = require("./PowerManager");
var ThrustController = require("./ThrustController");
var CppLogSource = require("./CppLogSource");
var ImuSensor = require("./ImuSensor");
var ActionSwitch = require("../Peripherals/ActionSwitch");
var Sockets = require('../Sockets');
var Ports = require('../Sockets/Ports.json');

module.exports = (function() {

    var logSocket = Sockets.createSocket(Ports.LoggerPort);
    var dispatcherSocket = Sockets.createSocket(Ports.DispatcherPort);

    function Factory() {}

    Factory.prototype.createCppLogSource = function (loggerOutput) {
        return new CppLogSource(logSocket.Output, loggerOutput)
    };

    Factory.prototype.createHeadlights = function () {
        return new HeadLights(dispatcherSocket.Input);
    };

    Factory.prototype.createImuSensor = function () {
        return new ImuSensor(dispatcherSocket.Output, dispatcherSocket.Input);
    };

    Factory.prototype.createPowerManager = function () {
        return new PowerManager(dispatcherSocket.Input, dispatcherSocket.Output);
    };

    Factory.prototype.createThrustController = function () {
        return new ThrustController(dispatcherSocket.Input);
    };

    Factory.prototype.createActionSwitch = function () {
        return new ActionSwitch(dispatcherSocket.Output);
    };

    return Factory;
    
})();