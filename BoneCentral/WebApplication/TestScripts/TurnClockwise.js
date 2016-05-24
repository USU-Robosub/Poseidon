/**
 * Created by Nathan Copier on 5/23/2016.
 */

var Utilities = require("../../Brain/Utilities");
var timeDelay = 1000;

module.exports = (function () {
    return {
        execute: function (thrustController, imuSensor, logger) {
            logger.info("Turning for " + timeDelay + " milliseconds.");
            thrustController.faceDirection(0.2, 0);
            var promise = Utilities.Wait(timeDelay);
            promise.then(function () {
                thrustController.faceDirection(0, 0);
            });
        }
    }
})();