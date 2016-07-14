/**
 * Created by floris on 6/29/16.
 */

var StateMachine = require("./StateMachine");
var Gate = require("./Gate");

module.exports = (function(){

    var utilities = require("../Utilities/index");
    var wait = utilities.Wait;
    var $ = utilities.Promises;

    const COAST_TIME = 1000; // in ms
    const TICK = 30; // in ms
    const States = StateMachine.States;

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
        this._logger = logger;
    }

    GoThroughGate.prototype.execute = function () {
        this._stateMachine = new StateMachine();
        this._deferred = $.Deferred();
        this._shouldQuit = false;
        this._thrustManager.dive();
        wait(500).done(function () {
            this._stateMachine.doTransition();
        }.bind(this));
        _runTick.call(this);
        return this._deferred.promise();
    };

    var _runTick = function() {
        if (this._shouldQuit) {
            this._thrustManager.killThrusters();
            this._deferred.fail();
            return;
        }
        wait(TICK).done(function () {
            this._gateDetector.getPoleCoordinates().done(function (poles) {
                var gate = new Gate(poles);
                this._stateMachine.doTransition(gate);
                _performActionFromState.call(this, gate);
                _runTick.call(this);
            }.bind(this));
        }.bind(this));
    };

    var _performActionFromState = function(gate) {
        var state = this._stateMachine.getState();
        if (state === States.FAIL) {
            this._logger.info("Can no longer detect gate. Stopping...");
            this._shouldQuit = true;
            return;
        }
        if (state === States.DIVE) _continueDive.call(this, gate);
        if (state === States.SEARCH_LEFT) _searchLeft.call(this, gate);
        if (state === States.SEARCH_RIGHT) _searchRight.call(this, gate);
        if (state === States.CONTINUE) _travelToGate.call(this, gate);
        if (state === States.PASSING_GATE) _coastThroughGate.call(this);
    };

    var _travelToGate = function (gate) {
        var gateCenter = null;
        var poleCount = gate.getPoleCount();
        if (poleCount === 2) {
            this._lastGate = gate;
            gateCenter = gate.getGateCenter();
        }
        else if (poleCount === 1) {
            var offset = gate.getOffsetFrom(this._lastGate);
            gateCenter = this._lastGate.getGateCenter();
            gateCenter.X += offset;
        }
        this._thrustManager.alignX(gateCenter);
        this._thrustManager.alignY(gateCenter);
    };

    var _coastThroughGate = function () {
        this._thrustManager.thrustForward();
        wait(COAST_TIME).done(function () {
            this._deferred.resolve();
        }.bind(this));
    };

    var _searchLeft = function (gate) {
        this._thrustManager.yawLeft();
        if (gate.getPoleCount() !== 0) this._thrustManager.alignY(gate.getGateCenter());
    };

    var _searchRight = function (gate) {
        this._thrustManager.yawRight();
        if (gate.getPoleCount !== 0) this._thrustManager.alignY(gate.getGateCenter());
    };

    var _continueDive = function (gateCenter) {
    };

    return GoThroughGate;

})();