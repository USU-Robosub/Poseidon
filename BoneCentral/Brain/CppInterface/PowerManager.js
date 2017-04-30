module.exports = (function(){

    function PowerManager(cmdOut, events) {
        this._cmdOut = cmdOut;
        this._events = events;
    }

    PowerManager.prototype.turnOnEscs = function(){
        this._cmdOut.write("turnOnEscs\n");
    };

    PowerManager.prototype.turnOffEscs = function(){
        this._cmdOut.write("turnOffEscs\n");
    };

    PowerManager.prototype.turnOnImu = function () {
        this._cmdOut.write("turnOnImuSensor\n");
    };

    PowerManager.prototype.turnOffImu = function () {
        this._cmdOut.write("turnOffImuSensor\n");
    };
    
    PowerManager.prototype.connect = function() {
        return this._events.OnConnect;
    }

    PowerManager.prototype.exit = function () {
        this._cmdOut.write("exit\n");
        return this._events.OnExit;
    };

    return PowerManager;

})();
