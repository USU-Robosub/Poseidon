/**
 * Created by Nathan Copier on 2/17/2016.
 */
var $ = require("jquery-deferred");

module.exports = (function(){

    function ImuSensor(iStream, oStream){
        this._iStream = iStream;
        this._oStream = oStream;
        _initializePromises.call(this);
        this._iStream.on("data", _handleData(this));
    }

    var _initializePromises = function () {
        this._accelRequest = $.Deferred().resolve();
        this._angularAccelRequest = $.Deferred().resolve();
        this._headingRequest = $.Deferred().resolve();
        this._inTempRequest = $.Deferred().resolve();
        this._inPressureRequest = $.Deferred().resolve();
        this._exTempRequest = $.Deferred().resolve();
        this._exPressureRequest = $.Deferred().resolve();
    };

    var _handleData = function(self){return function (data) {
        try {
            var dataJson = JSON.parse(data.toString());
            if (dataJson.Type === "Acceleration") self._accelRequest.resolve(dataJson);
            else if (dataJson.Type === "AngularAcceleration") self._angularAccelRequest.resolve(dataJson);
            else if (dataJson.Type === "Heading") self._headingRequest.resolve(dataJson);
            else if (dataJson.Type === "InternalTemperature") self._inTempRequest.resolve(dataJson);
            else if (dataJson.Type === "InternalPressure") self._inPressureRequest.resolve(dataJson);
            else if (dataJson.Type === "ExternalTemperature") self._exTempRequest.resolve(dataJson);
            else if (dataJson.Type === "ExternalPressure") self._exPressureRequest.resolve(dataJson);
        }
        catch(e) {}
    };};

    ImuSensor.prototype.getAcceleration = function () {
        if(this._accelRequest.state() !== "pending") {
            this._accelRequest = $.Deferred();
            this._oStream.write("getAcceleration\n");
        }
        return this._accelRequest.promise();
    };

    ImuSensor.prototype.getAngularAcceleration = function () {
        if(this._angularAccelRequest.state() !== "pending") {
            this._angularAccelRequest = $.Deferred();
            this._oStream.write("getAngularAcceleration\n");
        }
        return this._angularAccelRequest.promise();
    };

    ImuSensor.prototype.getHeading = function () {
        if(this._headingRequest.state() !== "pending") {
            this._headingRequest = $.Deferred();
            this._oStream.write("getHeading\n");
        }
        return this._headingRequest.promise();
    };

    ImuSensor.prototype.getInternalTemperature = function () {
        if(this._inTempRequest.state() !== "pending") {
            this._inTempRequest = $.Deferred();
            this._oStream.write("getInternalTemperature\n");
        }
        return this._inTempRequest.promise();
    };

    ImuSensor.prototype.getInternalPressure = function () {
        if(this._inPressureRequest.state() !== "pending") {
            this._inPressureRequest = $.Deferred();
            this._oStream.write("getInternalPressure\n");
        }
        return this._inPressureRequest.promise();
    };

    ImuSensor.prototype.getExternalTemperature = function () {
        if(this._exTempRequest.state() !== "pending") {
            this._exTempRequest = $.Deferred();
            this._oStream.write("getExternalTemperature\n");
        }
        return this._exTempRequest.promise();
    };

    ImuSensor.prototype.getExternalPressure = function () {
        if(this._exPressureRequest.state() !== "pending") {
            this._exPressureRequest = $.Deferred();
            this._oStream.write("getExternalPressure\n");
        }
        return this._exPressureRequest.promise();
    };

    return ImuSensor;

})();