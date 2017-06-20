var EventEmitter = require("events").EventEmitter;
var utilities = require("../Utilities");

const States = {
    INITIAL: 0,
    INACTIVE: 1,
    WAITING: 2,
    ACTIVE: 3
};

const SwitchStates = {
    OFF: 0,
    ON: 1
};

const initialTime = 5000; //milliseconds
const activationTime = 3000; //milliseconds

module.exports = (function () {

    function ActionSwitchFsm() {
        EventEmitter.call(this);
        this._transitionToInitial()
    }

    utilities.inherits(ActionSwitchFsm, EventEmitter);

    ActionSwitchFsm.prototype.doTransition = function (switchState) {
        this._switchState = switchState;
        if (this._state === States.INACTIVE) this._transitionFromInactive();
        else if (this._state === States.ACTIVE) this._transitionFromActive();
    };

    ActionSwitchFsm.prototype._transitionFromInitial = function () {
        if (this._switchIsOn()) {
            this._transitionToInitial();
        }
        else {
            this._state = States.INACTIVE;
        }
    };

    ActionSwitchFsm.prototype._transitionFromInactive = function () {
        if (!this._switchIsOn()) return;
        this._state = States.WAITING;
        utilities.Wait(activationTime).then(this._transitionFromWaiting.bind(this));
    };

    ActionSwitchFsm.prototype._transitionFromWaiting = function () {
        if (this._switchIsOn()) {
            this._state = States.ACTIVE;
            this.emit("start");
        }
        else  {
            this._transitionToInitial()
        }
    };

    ActionSwitchFsm.prototype._transitionFromActive = function () {
        if (this._switchIsOn()) return;
        this._transitionToInitial();
        this.emit("kill");
    };

    ActionSwitchFsm.prototype._transitionToInitial = function() {
        this._state = States.INITIAL;
        utilities.Wait(initialTime).then(this._transitionFromInitial.bind(this));
    };

    ActionSwitchFsm.prototype._switchIsOn = function () {
        return this._switchState === SwitchStates.ON;
    };

    return ActionSwitchFsm;

})();