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
        this._angularAccelRequest = $.Deferred().resolve();
        this._headingRequest = $.Deferred().resolve();
    };

    var _handleData = function(self){return function (data) {
        try {
            var dataJson = JSON.parse(data.toString());
            if (dataJson.Type == "Acceleration") self._accelRequest.resolve(dataJson);
            else if (dataJson.Type == "AngularAcceleration") self._angularAccelRequest.resolve(dataJson);
            else if (dataJson.Type == "Heading") self._headingRequest.resolve(dataJson);
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

    ImuReader.prototype.getAngularAcceleration = function () {
        if(this._angularAccelRequest.state() !== "pending") {
            this._angularAccelRequest = $.Deferred();
            this._oStream.write("getAngularAcceleration\n");
        }
        return this._angularAccelRequest.promise();
    };

    ImuReader.prototype.getHeading = function () {
        if(this._headingRequest.state() !== "pending") {
            this._headingRequest = $.Deferred();
            this._oStream.write("getHeading\n");
        }
        return this._headingRequest.promise();
    };

    return ImuReader;

})();