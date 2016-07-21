/**
 * Created by floris on 7/14/16.
 */

const States = {
    INITIAL_DIVE: 0,
    DIVE: 1,
    SEARCH_LEFT: 2,
    SEARCH_RIGHT: 3,
    CONTINUE: 4,
    PASSING_GATE: 5,
    FAIL: -1
};

module.exports = (function () {

    function StateMachine(logger) {
        this._state = States.INITIAL_DIVE;
        this._logger = logger
    }

    StateMachine.prototype.doTransition = function(gate) {
        if (this._state === States.INITIAL_DIVE) _transitionFromInitialDive.call(this);
        else  if (this._state === States.DIVE) _transitionFromDive.call(this, gate);
        else if (this._state === States.SEARCH_LEFT) _transitionFromSearchLeft.call(this, gate);
        else if (this._state === States.SEARCH_RIGHT) _transitionFromSearchRight.call(this, gate);
        else if (this._state === States.CONTINUE) _transitionFromContinue.call(this, gate);
    };

    var _transitionFromInitialDive = function () {
        console.log("Transitioning from Initial Dive");
        this._state = States.DIVE;
    };

    var _transitionFromDive = function (gate) {
        console.log("Transitioning from Dive");
        var poleCount = gate.getPoleCount();
        var gateCenter = gate.getGateCenter();
        if (poleCount < 1) this._state = States.FAIL;
        else if (_hasReachedDepth.call(this, gateCenter) && poleCount === 1) this._state = States.SEARCH_LEFT;
        else if (_hasReachedDepth.call(this, gateCenter) && poleCount > 1) this._state = States.CONTINUE;
    };

    var _hasReachedDepth = function (target) {
        return target.Y > 0; // this._targetBox.BOTTOM;
    };

    var _transitionFromSearchLeft = function (gate) {
        console.log("Transitioning from Search Left");
        var poleCount = gate.getPoleCount();
        if (poleCount < 1) this._state = States.SEARCH_RIGHT;
        else if(poleCount > 1) this._state = States.CONTINUE;
    };

    var _transitionFromSearchRight = function (gate) {
        console.log("Transitioning from Search Right");
        var poleCount = gate.getPoleCount();
        if (poleCount <= 1) this._state = States.FAIL;
        else if (poleCount > 1) this._state = States.CONTINUE;
    };

    var _transitionFromContinue = function (gate) {
        console.log("Transitioning from Continue");
        var poleCount = gate.getPoleCount();
        if (poleCount < 1) this._state = States.PASSING_GATE;
    };

    StateMachine.prototype.getState = function () {
        return this._state;
    };

    StateMachine.States = States;

    return StateMachine;

})();
