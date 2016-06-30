/**
 * Created by Nathan Copier on 5/26/2016.
 */

var Promises = require("../Utilities").Promises;

module.exports = (function () {

    function GateDetector(iStream, oStream, logger) {
        this._oStream = oStream;
        this._logger = logger;
        _initializePromises.call(this);
        iStream.on("data", _handleData(this));
    }

    var _initializePromises = function () {
        this._startRequest = Promises.Deferred().resolve();
        this._poleCoordRequest = Promises.Deferred().resolve();
        this._hsvRequest = Promises.Deferred().resolve();
        this._stopRequest = Promises.Deferred().resolve();
    };

    var _handleData = function (self) { return function (data) {
        try {
            var dataJson = JSON.parse(data.toString());
            if(dataJson.Type == null) dataJson.Type = "";
            if(dataJson.Type == "startedSearching") self._startRequest.resolve(dataJson);
            if(dataJson.Type == "PoleCoordinates") self._poleCoordRequest.resolve(dataJson);
            if(dataJson.Type == "HsvRefresh") self._hsvRequest.resolve(dataJson);
            if(dataJson.Type == "stoppedSearching") self._stopRequest.resolve(dataJson);
        }
        catch (e) {
            this._logger.warn("GateDetector failed to deserialize JSON!");
        }
    };};

    GateDetector.prototype.startSearching = function () {
        if(this._startRequest.state() !== "pending") {
            this._startRequest = Promises.Deferred();
            this._oStream.write("startSearchingForPoles\n");
        }
        return this._startRequest.promise();
    };

    GateDetector.prototype.GetPoleCoordinates = function () {
        if(this._poleCoordRequest.state() !== "pending") {
            this._poleCoordRequest = Promises.Deferred();
            this._oStream.write("getPoleCoordinates\n");
        }
        return this._poleCoordRequest.promise();
    };

    GateDetector.prototype.refreshHsv = function () {
        if(this._hsvRequest.state() !== "pending") {
            this._hsvRequest = Promises.Deferred();
            this._oStream.write("refreshHsv\n");
        }
        return this._hsvRequest.promise();
    };

    GateDetector.prototype.stopSearching = function () {
        if(this._stopRequest.state() !== "pending") {
            this._stopRequest = Promises.Deferred();
            this._oStream.write("stopSearchingForPoles\n");
        }
        return this._stopRequest.promise();
    };

    return GateDetector;

})();