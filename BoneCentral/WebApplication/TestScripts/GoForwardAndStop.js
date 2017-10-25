/**
 * Created by Nathan Copier on 5/24/2016.
 */


var Utilities = require("../../Brain/Utilities");
var Wait = Utilities.Wait;
var Promises = Utilities.Promises;

module.exports = (function () {
    return {
        execute: function (thrustController, imuSensor, logger) {
            _thrustForward(3000, thrustController, logger);
        }
    }})();

var _thrustForward = function (timeDelay, thrustController, logger) {
    var promise = Promises.Deferred();
    logger.info("Thrusting forward for " + timeDelay + " milliseconds.");
    thrustController.goDirection(0.2, 0, 0);
    Wait(timeDelay).then(function () {
        logger.info("Stopping...");
        thrustController.goDirection(0, 0, 0);
        promise.resolve();
    });
    return promise;
};