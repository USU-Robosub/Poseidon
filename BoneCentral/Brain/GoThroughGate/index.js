/**
 * Created by floris on 6/29/16.
 */

module.exports = (function(){

    var utilities = require("../Utilities/index");
    var wait = utilities.Wait;

    const MAINTAIN_DIVE = 0.29;
    const SINK = 0.5;
    const TICK = 30; // in ms
    const MINIMUM_THRUST = 0.15;
    const THRUST_INCREMENT = 0.0005;
    const NEUTRAL = 0.0;
    const TargetBox = {
        LEFT: -25,
        RIGHT: 25,
        TOP: 25,
        BOTTOM: -25
    };
    const States = {
        INITIAL_DIVE: 0,
        DIVE: 1,
        CONTINUE: 2,
        BEGIN_SEARCH: 3,
        SEARCH_LEFT: 4,
        SEARCH_RIGHT: 5
    };

    function GoThroughGate(visionFactory, peripheralsFactory) {
        this._gateDetector = visionFactory.createGateDetector(console);
        this._thrustController = peripheralsFactory.createThrustController();
        this._state = States.DIVE;
    }

    GoThroughGate.prototype.execute = function () {
        _setDefaults.call(this);
        this._shouldQuit = false;
        this._thrustController.dive(this._diveThrust, this._diveThrust);
        wait(500).done(function () {
            this._state = States.DIVE;
        }.bind(this));
        _runTick.call(this);
    };

    var _setDefaults = function() {
        this._leftThrust = NEUTRAL;
        this._rightThrust = NEUTRAL;
        this._diveThrust = SINK;
    };

    var _runTick = function() {
        if (this._shouldQuit) {
            _killThrusters.call(this);
            return;
        }
        wait(TICK).done(function () {
            this._gateDetector.getPoleCoordinates().done(function (poles) {
                if ( this._state !== States.INITIAL_DIVE) _trackGate.call(this, poles);
                _runTick.call(this);
            }.bind(this));
        }.bind(this));
    };

    var _killThrusters = function () {
        this._thrustController.thrustForward(0, 0);
        this._thrustController.dive(0, 0);
    };

    var _trackGate = function(poles) {
        if (poles.length === 2 && this._state !== States.DIVE) this._state = States.CONTINUE;
        if (poles.length == 1 && this._state !== States.DIVE) this._state = States.BEGIN_SEARCH;
        if (poles.length == 0) {
            this._shouldQuit = true;
            return;
        }
        if (this._state === States.BEGIN_SEARCH) _beginSearch.call(this, poles);
        if (this._state === States.CONTINUE) _travelToGate.call(this, poles);
        if (this._state === States.DIVE) _continueDive.call(this, poles);
    };

    var _continueDive = function (target) {
        if (_hasReachedDepth(target)) {
            _thrustForward.call(this);
            this._state = States.CONTINUE;
        }
    };

    var _travelToGate = function (poles) {
        var gateCenter = _getGateCenter(poles);
        _alignX.call(this, gateCenter);
        _alignY.call(this, gateCenter);
    };

    var _getGateCenter = function(poles) {
        var leftCenter = _getPoleCenter(poles[0]);
        var rightCenter = _getPoleCenter(poles[0]);
        var x = (leftCenter.X + rightCenter.X)/2;
        var y = (leftCenter.Y + rightCenter.Y)/2;
        return {X: x, Y: y};
    };

    var _getPoleCenter = function (pole) {
        var xTotal = 0, yTotal = 0;
        for (var i = 0; i < 4; i++) {
            xTotal += (+pole[i].X);
            yTotal += (+pole[i].Y);
        }
        return {X: xTotal/4, Y: yTotal/4};
    };

    var _alignX = function(target) {
        if (_hasDriftedRight(target)) {
            _listLeft.call(this);
        }
        else if (_hasDriftedLeft(target)) {
            _listRight.call(this);
        }
        this._thrustController.thrustForward(this._leftThrust, this._rightThrust);
    };

    var _thrustForward = function () {
        _incrementLeftThrust.call(this, 0.2);
        _incrementRightThrust.call(this, 0.2);
    };

    var _hasDriftedRight = function (target) {
        return target.X < TargetBox.LEFT;
    };

    var _listLeft = function () {
        _incrementLeftThrust.call(this, -THRUST_INCREMENT);
        _incrementRightThrust.call(this, THRUST_INCREMENT);
    };

    var _hasDriftedLeft = function (target) {
        return target.X > TargetBox.RIGHT;
    };

    var _listRight = function () {
        _incrementLeftThrust.call(this, THRUST_INCREMENT);
        _incrementRightThrust.call(this, -THRUST_INCREMENT);
    };

    var _incrementLeftThrust = function(diff) {
        this._leftThrust = normalizeThrust(this._leftThrust + diff);
    };

    var _incrementRightThrust = function(diff) {
        this._rightThrust = normalizeThrust(this._rightThrust + diff);
    };

    var _alignY = function(target) {
        if (_hasReachedDepth(target) && _isStillDiving.call(this)) _maintainDepth.call(this);
        else if (_hasDriftedDown(target)) _reduceDive.call(this);
        else if (_hasDriftedUp(target) && !_isStillDiving.call(this)) _increaseDive.call(this);
        this._thrustController.dive(this._diveThrust, this._diveThrust);
    };

    var _hasReachedDepth = function (target) {
        return target.Y > TargetBox.BOTTOM;
    };

    var _maintainDepth = function () {
        this._diveThrust = MAINTAIN_DIVE;
    };

    var _hasDriftedDown = function (target) {
        return target.Y > TargetBox.TOP;
    };

    var _reduceDive = function () {
        _incrementDiveThrust.call(this, -THRUST_INCREMENT);
    };

    var _hasDriftedUp = function (target) {
        return target.Y < TargetBox.BOTTOM;
    };

    var _increaseDive = function () {
        _incrementDiveThrust.call(this, THRUST_INCREMENT);
    };

    var _incrementDiveThrust = function(diff) {
        var thrust = this._diveThrust;
        this._diveThrust = thrust + diff;
    };

    var normalizeThrust = function(thrust) {
        if (_belowForwardMinThrust(thrust)) {
            thrust = MINIMUM_THRUST;
        }
        else if (_belowReverseMinThrust(thrust)) {
            thrust = -MINIMUM_THRUST;
        }
        return _roundToFourSigFigs(thrust);
    };

    var _belowForwardMinThrust = function (thrust) {
        return NEUTRAL < thrust && thrust < MINIMUM_THRUST;
    };

    var _belowReverseMinThrust = function (thrust) {
        return -MINIMUM_THRUST < thrust && thrust < NEUTRAL;
    };

    var _roundToFourSigFigs = function (num) {
        return Math.floor(num * 1000) / 1000;
    };

    return GoThroughGate;

})();