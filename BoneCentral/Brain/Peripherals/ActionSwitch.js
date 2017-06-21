var EventEmitter = require("events").EventEmitter;
var utilities = require("../Utilities");
var ActionSwitchFsm = require("./ActionSwitchFsm");

module.exports = (function () {

    function ActionSwitch(iStream) {
        EventEmitter.call(this);
        iStream.on("data", this._handleData.bind(this));
        this._initializeFsm();
    }

    utilities.inherits(ActionSwitch, EventEmitter);

    ActionSwitch.prototype._handleData = function (data) {
        try {
            var tokens = data.toString().split('\n');
            for(var i = 0; i < tokens.length; i++) {
                this._parse(tokens[i]);
            }
        }
        catch(e) { console.log("_handleData: " + e); }
    };

    ActionSwitch.prototype._parse = function(token) {
        var dataJson = JSON.parse(token+"\n");
        if (_isActionEvent(dataJson)) {
            this._updateStateFrom(dataJson.Value);
        }
        else {
            console.log("Could not resolve type (ActionSwitch) '" + dataJson.Type + "'");
        }
    };

    var _isActionEvent = function(json) {
        return json.Type === "ActionEvent";
    };

    ActionSwitch.prototype._updateStateFrom = function(switchState) {
        this._fsm.doTransition(switchState);
    };

    ActionSwitch.prototype._initializeFsm = function () {
        this._fsm = new ActionSwitchFsm();
        this._fsm.on("kill", this._emit("kill"));
        this._fsm.on("start", this._emit("start"));
    };

    ActionSwitch.prototype._emit = function (eventName) {
      return function () {this.emit(eventName);}.bind(this);
    };

    return ActionSwitch;

})();