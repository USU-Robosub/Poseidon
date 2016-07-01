/**
 * Created by floris on 6/29/16.
 */

var utilities = require("../Brain/Utilities/index");
var wait = utilities.Wait;

const MAINTAIN_DIVE = 0.29;
const SINK = 0.5;
const TICK = 100; // in ms
const MINIMUM_THRUST = 0.15;

module.exports = (function(){

    function GoThroughGate(gateDetector, thrustController) {
        this._gateDetector = gateDetector;
        this._thrustController = thrustController;
    }

    GoThroughGate.prototype.execute = function () {
        _setDefaults.call(this);
        this._shouldQuit = false;
        this._thrustController.dive(this._diveThrust, this._diveThrust);
        _runTick.call(this);
    };

    var _setDefaults = function() {
        this._leftThrust = 0.0;
        this._rightThrust = 0.0;
        this._diveThrust = SINK;
    };

    var _runTick = function() {
        if (this._shouldQuit) {
            this._thrustController.thrustForward(0,0);
            this._thrustController.dive(0,0);
            return;
        }
        wait(TICK).done(function () {
            this._gateDetector.getPoleCoordinates().done(function (poles) {
                _trackGate.call(this, poles);
                _runTick.call(this);
            }.bind(this));
        }.bind(this));
    };

    var _trackGate = function(poles) {
        if (poles.length === 2) {
            var gateCenter = _getGateCenter(poles);
            _alignX.call(this, gateCenter);
            _alignY.call(this, gateCenter);
        }
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
        if (_hasReachedDepth(target) && _isStillDiving.call(this)) {
            _thrustForward.call(this);
        }
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
        return target.X < -25;
    };

    var _listLeft = function () {
        _incrementLeftThrust.call(this, -0.002);
        _incrementRightThrust.call(this, 0.002);
    };

    var _hasDriftedLeft = function (target) {
        return target.X > 25;
    };

    var _listRight = function () {
        _incrementLeftThrust.call(this, 0.002);
        _incrementRightThrust.call(this, -0.002);
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
        return target.Y > -50;
    };

    var _isStillDiving = function () {
        return this._diveThrust === SINK;
    };

    var _maintainDepth = function () {
        this._diveThrust = MAINTAIN_DIVE;
    };

    var _hasDriftedDown = function (target) {
        return target.Y > 25;
    };

    var _reduceDive = function () {
        _incrementDiveThrust.call(this, -0.002);
    };

    var _hasDriftedUp = function (target) {
        return target.Y < -25;
    };

    var _increaseDive = function () {
        _incrementDiveThrust.call(this, 0.002);
    };

    var _incrementDiveThrust = function(diff) {
        var thrust = this._diveThrust;
        this._diveThrust = thrust + diff;
    };

    function normalizeThrust(thrust) {
        if (_belowForwardMinThrust(thrust)) {
            thrust = MINIMUM_THRUST;
        }
        else if (_belowReverseMinThrust(thrust)) {
            thrust = -MINIMUM_THRUST;
        }
        return _roundToFourSigFigs(thrust);
    }

    var _belowForwardMinThrust = function (thrust) {
        return thrust < MINIMUM_THRUST && thrust > 0;
    };

    var _belowReverseMinThrust = function (thrust) {
        return thrust > -MINIMUM_THRUST && thrust < 0;
    };

    var _roundToFourSigFigs = function (num) {
        return Math.floor(num * 1000) / 1000;
    };

    GoThroughGate.prototype.terminate = function () {
        this._shouldQuit = true;
    };

    return GoThroughGate;

})();