/**
 * Created by floris on 7/12/16.
 */

module.exports = (function () {

    const SINK = 0.5;
    const MINIMUM_THRUST = 0.15;
    const NORMAL_THRUST = 0.2;
    const THRUST_INCREMENT = 0.0005;
    const NEUTRAL = 0.0;

    const MAINTAIN_DIVE = 0.29;

    const PULSE_INTERVAL_RATE = 50;
    const PULSE_DELAY = PULSE_INTERVAL_RATE/2;

    var pulseInterval;

    function ThrustManager(factory){
        this._thrustController = factory.createThrustController();
        this._leftThrust = NEUTRAL;
        this._rightThrust = NEUTRAL;
        this._diveThrust = NEUTRAL;
    }

    ThrustManager.prototype.setTargetBox = function (targetBox) {
        this._targetBox = targetBox;
    };

    ThrustManager.prototype.thrustForward = function () {
        this._leftThrust = NORMAL_THRUST;
        this._rightThrust = NORMAL_THRUST;
        _executeForwardThrust.call(this);
    };

    ThrustManager.prototype.alignX = function(target) {
        if (_hasDriftedRight.call(this, target)) {
            console.log("Sub has drifted right.\t\tThe target is at X: " + target.X + " Y: " + target.Y);
            _listLeft.call(this);
        }
        else if (_hasDriftedLeft.call(this, target)) {
            console.log("Sub has drifted left. \t\tThe target is at X: " + target.X + " Y: " + target.Y);
            _listRight.call(this);
        }
        _executeForwardThrust.call(this);
    };

    var _hasDriftedRight = function (target) {
        return target.X < this._targetBox.LEFT;
    };

    var _listLeft = function () {
        _incrementLeftThrust.call(this, -THRUST_INCREMENT);
        _incrementRightThrust.call(this, THRUST_INCREMENT);
    };

    var _hasDriftedLeft = function (target) {
        return target.X > this._targetBox.RIGHT;
    };

    var _listRight = function () {
        _incrementLeftThrust.call(this, THRUST_INCREMENT);
        _incrementRightThrust.call(this, -THRUST_INCREMENT);
    };

    var _incrementLeftThrust = function(diff) {
        this._leftThrust = _roundToSevenSigFigs(this._leftThrust + diff);
    };

    var _incrementRightThrust = function(diff) {
        this._rightThrust = _roundToSevenSigFigs(this._rightThrust + diff);
    };

    ThrustManager.prototype.alignY = function(target) {
        if (_hasDriftedDown.call(this, target)) _reduceDive.call(this);
        else if (_hasDriftedUp.call(this, target)) _increaseDive.call(this);
        _executeDiveThrust.call(this);
    };

    ThrustManager.prototype.maintainDepth = function () {
        this._diveThrust = MAINTAIN_DIVE;
    };

    var _hasDriftedDown = function (target) {
        return target.Y > this._targetBox.TOP;
    };

    var _reduceDive = function () {
        _incrementDiveThrust.call(this, -THRUST_INCREMENT);
    };

    var _hasDriftedUp = function (target) {
        return target.Y < this._targetBox.BOTTOM;
    };

    var _increaseDive = function () {
        _incrementDiveThrust.call(this, THRUST_INCREMENT);
    };

    var _incrementDiveThrust = function(diff) {
        var thrust = this._diveThrust;
        this._diveThrust = thrust + diff;
    };

    var normalizeThrust = function(thrust) {
        if (_belowForwardMinThrust(thrust) || _belowReverseMinThrust(thrust)) {
            thrust = NEUTRAL;
        }
        return _roundToSevenSigFigs(thrust);
    };

    var _belowForwardMinThrust = function (thrust) {
        return NEUTRAL < thrust && thrust < MINIMUM_THRUST;
    };

    var _belowReverseMinThrust = function (thrust) {
        return -MINIMUM_THRUST < thrust && thrust < NEUTRAL;
    };

    var _roundToSevenSigFigs = function (num) {
        return Math.floor(num * 1000000) / 1000000;
    };

    ThrustManager.prototype.yawLeft = function (yawMagnitude) {
        if (yawMagnitude >= MINIMUM_THRUST) {
            this._leftThrust = -MINIMUM_THRUST;
            this._rightThrust = MINIMUM_THRUST;
            _executeForwardThrust.call(this);
        }
        _pulseYawLeft.call(this);
    };

    var _pulseYawLeft = function() {
        pulseInterval = setInterval(function() {
            this._rightThrust = MINIMUM_THRUST;
            this._leftThrust = -MINIMUM_THRUST;
            _executeForwardThrustWithPulse.call(this);
            setTimeout(function() {
                this._rightThrust = NEUTRAL;
                _executeForwardThrustWithPulse.call(this);
            }, PULSE_DELAY);
        }, PULSE_INTERVAL_RATE);
    };

    ThrustManager.prototype.yawRight = function (yawMagnitude) {
        if (yawMagnitude >= MINIMUM_THRUST) {
            this._leftThrust = MINIMUM_THRUST;
            this._rightThrust = -MINIMUM_THRUST;
            _executeForwardThrust.call(this);
        }
        else {
            _pulseYawRight.call(this);
        }
    };

    var _pulseYawRight = function() {
        pulseInterval = setInterval(function() {
            this._leftThrust = MINIMUM_THRUST;
            this._rightThrust = -MINIMUM_THRUST;
            _executeForwardThrustWithPulse.call(this);
            setTimeout(function() {
                this._leftThrust = NEUTRAL;
                _executeForwardThrustWithPulse.call(this);
            }, PULSE_DELAY);
        }, PULSE_INTERVAL_RATE);
    };

    ThrustManager.prototype.dive = function () {
        this._leftThrust = NEUTRAL;
        this._rightThrust = NEUTRAL;
        _executeForwardThrust.call(this);
        this._thrustController.dive(SINK, SINK);
    };

    ThrustManager.prototype.killThrusters = function () {
        this._leftThrust = this._rightThrust = this._diveThrust = NEUTRAL;
        _executeForwardThrust.call(this);
        _executeDiveThrust.call(this);
    };

    var _executeForwardThrust = function() {
        clearInterval(pulseInterval);
        var left = normalizeThrust(this._leftThrust);
        var right = normalizeThrust(this._rightThrust);
        this._thrustController.thrustForward(left, right);
    };

    var _executeForwardThrustWithPulse = function() {
        var left = normalizeThrust(this._leftThrust);
        var right = normalizeThrust(this._rightThrust);
        this._thrustController.thrustForward(left, right);
    }

    var _executeDiveThrust = function () {
        var diveThrust = normalizeThrust(this._diveThrust);
        this._thrustController.dive(diveThrust, diveThrust)
    };

    return ThrustManager;

})();
