var Event   = require("../Utilities/EventHandler.js");

module.exports = (function(){

    function PowerManager(cmdOut, cmdIn, events) {
        this._cmdOut = cmdOut;
        this._cmdIn  = cmdIn;
        this._events = events;
        
        this.onAction = new Event();
        this._cmdIn.on("data", _handleData(this));
    }
    
    var _handleData = function(self){return function (data) {
        try {
            var tokens = data.toString().split('\n');
            for(i = 0; i < tokens.length-1; i++) {
                var dataJson = JSON.parse(tokens[i]+"\n");
                if (dataJson.Type === "ActionEvent") {
                    self.onAction.call();
                }
                else { console.log("Could not resolved type (PowerManager) '"+dataJson.Type+"'"); }
            }
        }
        catch(e) { console.log("_handleData: "+e); }
    };};

    PowerManager.prototype.turnOnEscs = function(){
        this._cmdOut.write("turnOnEscs\n");
    };

    PowerManager.prototype.turnOffEscs = function(){
        this._cmdOut.write("turnOffEscs\n");
    };

    PowerManager.prototype.turnOnImu = function () {
        this._cmdOut.write("turnOnImu\n");
    };

    PowerManager.prototype.turnOffImu = function () {
        this._cmdOut.write("turnOffImu\n");
    };
    
    PowerManager.prototype.connect = function(name,callback) {
        this._events.OnConnect.addEventListener(name,callback);
    };

    PowerManager.prototype.exit = function (name,callback) {
        this._cmdOut.write("exit\n");
        this._events.OnExit.addEventListener(name,callback);
    };
    
    PowerManager.prototype.action = function(name, callback) {
        this.onAction.addEventListener(name,callback);
    }

    return PowerManager;

})();
