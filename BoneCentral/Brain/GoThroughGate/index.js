/**
 * Created by floris on 6/29/16.
 */

var StateMachine = require("./StateMachine");
var Gate = require("./Gate");
var utilities = require("../Utilities/index");

module.exports = {init: function(){

    function GoThroughGate(thrustController, logger) {
        this._thrustController = thrustController;
        this._logger = logger;
    }

    GoThroughGate.prototype.execute = function () {
        this._deferred = utilities.Promises.Deferred();
        this._thrustController.dive(0.8);
        utilities.Wait(3000).then(function () {
            this._thrustController.move(0.15);
            return utilities.Wait(3000);
        }.bind(this)).then(function () {
            this._deferred.resolve();
        }.bind(this));
        return this._deferred.promise();
    };

    GoThroughGate.prototype.kill = function () {
        this._deferred.reject();
    };

    return GoThroughGate;

}};
