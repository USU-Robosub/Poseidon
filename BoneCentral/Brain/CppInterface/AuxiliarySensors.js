//
// Created by TekuConcept 4/9/2017
//

var $ = require("jquery-deferred");

module.exports = (function(){

    function AuxiliarySensors(iStream, oStream) {
        this._iStream = iStream;
        this._oStream = oStream;
        _initializePromises.call(this);
        this._iStream.on("data", _handleData(this));
    }
    
    var _initializePromises = function () {
        this._voltRequest = $.Deferred().resolve();
    }

    var _handleData = function(self){return function (data) {
        try {
            var tokens = data.toString().split('\n');
            for(i = 0; i < tokens.length-1; i++) {
                var dataJson = JSON.parse(tokens[i]+"\n");
                if (dataJson.Type === "Voltage") self._voltRequest.resolve(dataJson);
                else { console.log("Could not resolved type '"+dataJson.Type+"'"); }
            }
        }
        catch(e) { console.log("_handleData: "+e); }
    };};

    AuxiliarySensors.prototype.getVoltage = function () {
        if(this._voltRequest.state() !== "pending") {
            this._voltRequest = $.Deferred();
            this._oStream.write("measureVoltage\n");
        }
        return this._voltRequest.promise();
    };

    return AuxiliarySensors;

})();