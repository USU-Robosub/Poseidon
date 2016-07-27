/**
 * Created by floris on 7/14/16.
 */

const States = {
    INITIAL_DIVE: 0,
    THRUST_FORWARD: 1,
    DIVE: 2,
    SEARCH_LEFT: 3,
    SEARCH_RIGHT: 4,
    THRUST_TOWARDS_GATE: 5,
    PASSING_GATE: 6,
    FAIL: -1
};

module.exports = (function () {

    var utilities = require("../Utilities/index");
    var wait = utilities.Wait;

    function StateMachine(logger) {
        this._state = States.INITIAL_DIVE;
        this._logger = logger
    }

    StateMachine.prototype.doTransition = function(gate) {
        if (this._state === States.INITIAL_DIVE) _transitionFromInitialDive.call(this, gate);
        else if (this._state === States.THRUST_FORWARD) _transitionFromThrustForward.call(this, gate);
        else  if (this._state === States.DIVE) _transitionFromDive.call(this, gate);
        else if (this._state === States.SEARCH_LEFT) _transitionFromSearchLeft.call(this, gate);
        else if (this._state === States.SEARCH_RIGHT) _transitionFromSearchRight.call(this, gate);
        else if (this._state === States.THRUST_TOWARDS_GATE) _transitionFromThrustTowardsGate.call(this, gate);
    };

    var _transitionFromInitialDive = function (gate) {
        console.log("Transitioning from Initial Dive");
        var poleCount = gate.getPoleCount();
        this._state = States.DIVE;
    };

    var _transitionFromThrustForward = function(gate) {
        console.log("Transitioning from Thrust Forward");
        var poleCount = gate.getPoleCount();
        if (this._forwardWait) return;
        this._forwardWait = wait(2000);
    };

    var _transitionFromDive = function (gate) {
        console.log("Transitioning from Dive");
        var poleCount = gate.getPoleCount();
        var gateCenter = gate.getGateCenter();
        this._state = States.THRUST_TOWARDS_GATE;
    };

    var _hasReachedDepth = function (target) {
        return target.Y > 0; // this._targetBox.BOTTOM;
    };

    var _transitionFromSearchLeft = function (gate) {
        console.log("Transitioning from Search Left");
        var poleCount = gate.getPoleCount();
        States.THRUST_TOWARDS_GATE;
    };

    var _transitionFromSearchRight = function (gate) {
        console.log("Transitioning from Search Right");
        var poleCount = gate.getPoleCount();
        States.THRUST_TOWARDS_GATE;
    };

    var _transitionFromThrustTowardsGate = function (gate) {
        console.log("Transitioning from Thrust Towards Gate");
    };

    StateMachine.prototype.getState = function () {
        return this._state;
    };

    StateMachine.States = States;

    return StateMachine;

})();
