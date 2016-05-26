/**
 * Created by Nathan Copier on 5/26/2016.
 */

var Promises = require("../Utilities").Promises;

module.exports = (function () {

    function GateDetector(iStream, oStream, logger) {
        this._oStream = oStream;
        this._logger = logger;
        _initializePromises.call(this);
        iStream.on("data",  _handleData(this));
    }

    var _initializePromises = function () {
        this._poleCoordRequest = Promises.Deferred().resolve();
    };

    var _handleData = function (self) { return function (data) {
        try {
            var dataJson = JSON.parse(data.toString());
            if(dataJson.Type == "PoleCoordinates") self._poleCoordRequest.resolve(dataJson);
        }
        catch (e) {
            this._logger.warn("GateDetector failed to deserialize JSON!");
        }
    };};

    GateDetector.prototype.GetPoleCoordinates = function () {
        if(this._poleCoordRequest.state() !== "pending") {
            this._poleCoordRequest = Promises.Deferred();
            this._oStream.write("GATE_allX\n");
        }
        return this._poleCoordRequest.promise();
    };

    return GateDetector;

})();