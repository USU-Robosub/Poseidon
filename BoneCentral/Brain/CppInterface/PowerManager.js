module.exports = (function(){

    function PowerManager(cmdOut) {
        this._cmdOut = cmdOut;
    }

    PowerManager.prototype.turnOnEscs = function(){
        this._cmdOut.write("turnOnEscs\n");
    };

    PowerManager.prototype.turnOffEscs = function(){
        this._cmdOut.write("turnOffEscs\n");
    };

    return PowerManager;

})();
