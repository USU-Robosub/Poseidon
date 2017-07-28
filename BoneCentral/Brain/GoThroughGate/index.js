/**
 * Created by floris on 6/29/16.
 */

var StateMachine = require("./StateMachine");
var Gate = require("./Gate");
var utilities = require("../Utilities/index");

const States = {
    INITIAL: 0,
    DIVING: 1,
    MOVING: 2,
    FINAL: 3
};

const DIVE_TIME = 1000; //milliseconds
const MOVE_TIME = 60000; //milliseconds

const DIVE_POWER = 0.8;
const MAINTAIN_DIVE = 0.31;
const MOVE_POWER = 0.15;
const heading = -1.65;

module.exports = {init: function(){

    function GoThroughGate(thrustController, logger) {
        this._thrustController = thrustController;
        this._logger = logger;
        this._state = States.INITIAL;
    }

    GoThroughGate.prototype.execute = function () {
        this._deferred = utilities.Promises.Deferred();
        this._ticker = setInterval(this._doTick.bind(this), 10);
        return this._deferred.promise();
    };

    GoThroughGate.prototype._doTick = function () {
        if (this._state === States.INITIAL) this._transitionFromInitial();
        if (this._state === States.DIVING) this._transitionFromDiving();
        else if (this._state === States.MOVING) this._transitionFromMoving();
    };

    GoThroughGate.prototype._transitionFromInitial = function () {
        this._startTime = new Date();
        this._state = States.DIVING;
        this._thrustController.dive( -DIVE_POWER );
        this._thrustController.yaw( heading );
    };

    GoThroughGate.prototype._transitionFromDiving = function () {
        if (this._shouldContinueDiving()) return;
        this._startTime = new Date();
        this._state = States.MOVING;
        this._thrustController.dive( -MAINTAIN_DIVE )
        this._thrustController.move( MOVE_POWER );
    };

    GoThroughGate.prototype._shouldContinueDiving = function () {
        return new Date()-this._startTime < DIVE_TIME;
    };

    GoThroughGate.prototype._transitionFromMoving = function () {
        if (this._shouldContinueMoving()) return;
        this._state = States.FINAL;
        clearInterval(this._ticker);
        this._deferred.resolve();
    };

    GoThroughGate.prototype._shouldContinueMoving = function () {
        return new Date()-this._startTime < MOVE_TIME;
    };

    GoThroughGate.prototype.kill = function () {
        console.log("Gate Task Interrupted.");
        clearInterval(this._ticker);
        this._deferred.reject();
    };

    return GoThroughGate;

}};
