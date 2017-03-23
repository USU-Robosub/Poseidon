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

    return PowerManager;

})();
