/**
 * Created by Nathan Copier on 2/17/2016.
 */
var $ = require("jquery-deferred");

module.exports = (function(){

    function ImuReader(iStream, oStream){
        this._iStream = iStream;
        this._oStream = oStream;
        _initializePromises.call(this);
        this._iStream.on("data", _handleData(this));
    }

    var _initializePromises = function () {
        this._accelRequest = $.Deferred().resolve();
    };

    var _handleData = function(self){return function (data) {
        try {
            var dataJson = JSON.parse(data.toString());
            if (dataJson.Type === "Acceleration") self._accelRequest.resolve(dataJson);
        }
        catch(e) {}
    };};

    ImuReader.prototype.getAcceleration = function () {
        if(this._accelRequest.state() !== "pending") {
            this._accelRequest = $.Deferred();
            this._oStream.write("getAcceleration\n");
        }
        return this._accelRequest.promise();
    };

    return ImuReader;

})();