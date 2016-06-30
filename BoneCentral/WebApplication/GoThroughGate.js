/**
 * Created by floris on 6/29/16.
 */

var utilities = require("../Brain/Utilities/index");
var wait = utilities.Wait;

const MAINTAIN_DIVE = 0.29;
const SINK = 0.5;
const TICK = 100; // in ms

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
            _alignVertically.call(this, gateCenter);
            _alignHorizontally.call(this, gateCenter);
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

    var _alignVertically = function(target) {
        if (target.Y > -50 && this._diveThrust === SINK) {
            _updateLeftThrust.call(this, 0.2);
            _updateRightThrust.call(this, 0.2);
        }
        if (target.X < -25) {
            _updateLeftThrust.call(this, -0.002);
            _updateRightThrust.call(this, 0.002);
        }
        else if (target.X > 25) {
            _updateLeftThrust.call(this, 0.002);
            _updateRightThrust.call(this, -0.002);
        }
        this._thrustController.thrustForward(this._leftThrust, this._rightThrust);
    };

    var _alignHorizontally = function(target) {
        if (target.Y > -50 && this._diveThrust === SINK) this._diveThrust = MAINTAIN_DIVE;
        else if (target.Y > 25)  _updateDiveThrust.call(this, -0.002);
        else if (target.Y < -25 && this._diveThrust !== SINK) _updateDiveThrust.call(this, 0.002);
        this._thrustController.dive(this._diveThrust, this._diveThrust);
    };

    var _updateLeftThrust = function(diff) {
        var thrust = this._leftThrust + diff;
        this._leftThrust = Math.floor(thrust*1000)/1000;
    };

    var _updateRightThrust = function(diff) {
        var thrust = this._rightThrust + diff;
        this._rightThrust = Math.floor(thrust*1000)/1000;
    };

    var _updateDiveThrust = function(diff) {
        this._diveThrust = normalizeThrust(this._diveThrust + diff);
    };

    GoThroughGate.prototype.terminate = function () {
        this._shouldQuit = true;
    };

    function normalizeThrust(thrust) {
        if (thrust < 0.15 && thrust > 0) {
            thrust = 0.15;
        }
        else if (thrust > -0.15 && thrust < 0) {
            thrust = -0.15;
        }
        return Math.floor(thrust * 1000) / 1000;
    }

    return GoThroughGate;

})();