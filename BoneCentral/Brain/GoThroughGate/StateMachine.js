/**
 * Created by floris on 7/14/16.
 */

const States = {
    INITIAL_DIVE: 0,
    DIVE: 1,
    SEARCH_LEFT: 2,
    SEARCH_RIGHT: 3,
    CONTINUE: 4,
    DRIFTED_LEFT: 5,
    DRIFTED_RIGHT: 6,
    NEAR_GATE: 7,
    PASSING_GATE: 8,
    FAIL: -1
};

module.exports = (function () {

    function StateMachine() {
        this._state = States.INITIAL_DIVE;
    }

    StateMachine.prototype.doTransition = function(poleCount, gateCenter) {
        if (this._state === States.INITIAL_DIVE) _transitionFromInitialDive.call(this);
        else  if (this._state === States.DIVE) _transitionFromDive.call(this, poleCount, gateCenter);
        else if (this._state === States.SEARCH_LEFT) _transitionFromSearchLeft.call(this, poleCount);
        else if (this._state === States.DRIFTED_RIGHT) _transitionFromSearchRight.call(this, poleCount);
        else if (this._state === States.CONTINUE) _transitionFromContinue.call(this, poleCount, gateCenter);
        else if (this._state === States.NEAR_GATE) _transitionFromNearGate.call(this, poleCount);
    };

    var _transitionFromInitialDive = function () {
        this._state = States.DIVE;
    };

    var _transitionFromDive = function (poleCount, gateCenter) {
        if (poleCount < 1) this._state = States.FAIL;
        else if (_hasReachedDepth.call(this, gateCenter) && poleCount === 1) this._state = States.SEARCH_LEFT;
        else if (_hasReachedDepth.call(this, gateCenter) && poleCount > 1) this._state = States.CONTINUE;
    };

    var _hasReachedDepth = function (target) {
        return target.Y > 0; // this._targetBox.BOTTOM;
    };

    var _transitionFromSearchLeft = function (poleCount) {
        if (poleCount < 1) this._state = States.SEARCH_RIGHT;
        else if(poleCount > 1) this._state = States.CONTINUE;
    };

    var _transitionFromSearchRight = function (poleCount) {
        if (poleCount <= 1) this._state = States.FAIL;
        else if (poleCount > 1) this._state = States.CONTINUE;
    };

    var _transitionFromContinue = function (poleCount) {
        if (someUnknownCondition) this._state = States.NEAR_GATE;
        else if (poleCount < 1) this._state = States.FAIL;
    };

    var _transitionFromNearGate = function (poleCount) {
        if (poleCount < 1) this._state = States.PASSING_GATE;
    };

    StateMachine.prototype.getState = function () {
        return this._state;
    };

    StateMachine.States = States;

    return StateMachine;

})();