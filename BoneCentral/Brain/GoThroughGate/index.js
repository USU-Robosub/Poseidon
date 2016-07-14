/**
 * Created by floris on 6/29/16.
 */

module.exports = (function(){

    var utilities = require("../Utilities/index");
    var wait = utilities.Wait;
    var $ = utilities.Promises;

    const COAST_TIME = 1000; // in ms
    const TICK = 30; // in ms

    const States = {
        INITIAL_DIVE: 0,
        DIVE: 1,
        CONTINUE: 2,
        BEGIN_SEARCH: 3,
        SEARCH_LEFT: 4,
        SEARCH_RIGHT: 5,
        PASSING_GATE: 6
    };

    const TargetBox = {
        LEFT: -25,
        RIGHT: 25,
        TOP: 25,
        BOTTOM: -25
    };

    function GoThroughGate(visionFactory, thrustManager, logger) {
        this._gateDetector = visionFactory.createGateDetector(logger);
        this._thrustManager = thrustManager;
        this._thrustManager.setTargetBox(TargetBox);
        this._state = States.INITIAL_DIVE;
        this._logger = logger;
    }

    GoThroughGate.prototype.execute = function () {
        this._deferred = $.Deferred();
        this._shouldQuit = false;
        this._thrustManager.dive();
        wait(500).done(function () {
            this._state = States.DIVE;
        }.bind(this));
        _runTick.call(this);
        return this._deferred.promise();
    };

    var _runTick = function() {
        if (this._state === States.PASSING_GATE) return;
        if (this._shouldQuit) {
            this._thrustManager.killThrusters();
            this._deferred.fail();
            return;
        }
        wait(TICK).done(function () {
            this._gateDetector.getPoleCoordinates().done(function (poles) {
                if ( this._state !== States.INITIAL_DIVE) _trackGate.call(this, poles);
                _runTick.call(this);
            }.bind(this));
        }.bind(this));
    };

    var _trackGate = function(poles) {
        if (poles.length === 2 && !_isDiving.call(this)) _travelToGate.call(this, poles);
        if (poles.length === 1 && !_isDiving.call(this) && !_isSearching.call(this)) _beginSearch.call(this, poles);
        if (poles.length === 1 && _isSearching.call(this) && !this._hasFoundPole) this._hasFoundPole = true;
        if (poles.length === 0 && !_isSearching.call(this) && !this._isNearGate) {
            this._logger.info("Can no longer detect gate. Stopping...");
            this._shouldQuit = true;
            return;
        }
        if (poles.length === 0 && this._isNearGate) {
            this._thrustManager.thrustForward();
            this._state = States.PASSING_GATE;
            wait(COAST_TIME).done(function () {
                this._deferred.resolve();
            }.bind(this));
        }
        if (this._state === States.SEARCH_LEFT) _searchLeft.call(this, poles);
        if (this._state === States.SEARCH_RIGHT) _searchRight.call(this, poles);
        if (this._state === States.DIVE) _continueDive.call(this, poles);
    };

    var _isDiving = function () {
        return this._state === States.DIVE;
    };

    var _isSearching = function () {
        return this._state === States.SEARCH_LEFT || this._state === States.SEARCH_RIGHT;
    };

    var _beginSearch = function (poles) {
        this._hasFoundPole = true;
        var poleCenter = _getPoleCenter(poles[0]);
        if (poleCenter.X < 0) this._state = States.SEARCH_RIGHT;
        else this._state = States.SEARCH_LEFT;
    };

    var _searchLeft = function (poles) {
        if (poles.length === 0 && this._hasFoundPole) {
            this._state = States.SEARCH_RIGHT;
            this._hasFoundPole = false;
            return;
        }
        this._thrustManager.yawLeft();
        if (poles.length !== 0) this._thrustManager.alignY(_getGateCenter(poles));
    };

    var _searchRight = function (poles) {
        if (poles.length === 0 && this._hasFoundPole) {
            this._state = States.SEARCH_LEFT;
            this._hasFoundPole = false;
            return;
        }
        this._thrustManager.yawRight();
        if (poles.length !== 0) this._thrustManager.alignY(_getGateCenter(poles));
    };

    var _travelToGate = function (poles) {
        if (this._state !== States.CONTINUE) {
            this._thrustManager.thrustForward();
            this._state = States.CONTINUE;
        }
        var poleLeft = _getPoleCenter(poles[0]);
        var poleRight = _getPoleCenter(poles[1]);
        if (poleLeft.X < -200 && poleRight.X > 200) this._isNearGate = true;
        var gateCenter = _getGateCenter(poles);
        this._thrustManager.alignX(gateCenter);
        this._thrustManager.alignY(gateCenter);
    };

    var _continueDive = function (poles) {
        var gateCenter = _getGateCenter(poles);
        if (_hasReachedDepth(gateCenter)) _stopDiving.call(this);
    };

    var _hasReachedDepth = function (target) {
        return target.Y > TargetBox.BOTTOM;
    };

    var _stopDiving = function () {
        this._thrustManager.maintainDepth();
        this._state = States.CONTINUE;
    };

    var _getGateCenter = function(poles) {
        var xTotal = 0, yTotal = 0;
        for (var i = 0; i < poles.length; i++) {
            var poleCenter = _getPoleCenter(poles[i]);
            xTotal += (poleCenter.X);
            yTotal += (poleCenter.Y);
        }
        return {X: xTotal/poles.length, Y: yTotal/poles.length};
    };

    var _getPoleCenter = function (pole) {
        var xTotal = 0, yTotal = 0;
        for (var i = 0; i < 4; i++) {
            xTotal += (+pole[i].X);
            yTotal += (+pole[i].Y);
        }
        return {X: xTotal/4, Y: yTotal/4};
    };

    return GoThroughGate;

})();