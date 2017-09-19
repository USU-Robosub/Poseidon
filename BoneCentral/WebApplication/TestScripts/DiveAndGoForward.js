/**
 * Created by Nathan Copier on 5/24/2016.
 */

var Utilities = require("../../Brain/Utilities");
var Wait = Utilities.Wait;
var Promises = Utilities.Promises;

var diveThrust = 0.2;

module.exports = (function () {
    return {
        execute: function (thrustController, imuSensor, logger) {
            Promises.WhenAll(
                _dive(3000, thrustController, logger)
            ).then(function () {
                return _thrustForward(3000, thrustController, logger);
            }).then(function () {
                return _allStop(thrustController, logger);
            });
        }
    }})();

var _dive = function (timeDelay, thrustController, logger) {
    var promise = Promises.Deferred();
    logger.info("Diving for " + +timeDelay + " milliseconds.");
    thrustController.goDirection(0, 0, 0.3);
    Wait(timeDelay).then(function () {
        thrustController.goDirection(0, 0, diveThrust);
        promise.resolve();
    });
    return promise;
};

var _thrustForward = function (timeDelay, thrustController, logger) {
    var promise = Promises.Deferred();
    logger.info("Thrusting forward for " + timeDelay + " milliseconds.");
    thrustController.goDirection(0.2, 0, diveThrust);
    Wait(timeDelay).then(function () {
        thrustController.goDirection(0, 0, diveThrust);
        promise.resolve();
    });
    return promise;
};

var _allStop = function (thrustController, logger) {
    var promise = Promises.Deferred();
    logger.info("Stopping...");
    thrustController.goDirection(0, 0, 0);
    return promise;
};