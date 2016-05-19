/**
 * Created by Nathan Copier on 5/17/2016.
 */

var fileSystem = require("fs");

module.exports = (function () {

    function FileLogger(path) {
        this._fileStream = fileSystem.createWriteStream(path);
    }

    FileLogger.prototype.info = function (message) {
        _writeLog.call(this, "info", message);
    };

    FileLogger.prototype.warn = function (message) {
        _writeLog.call(this, "warn", message);
    };

    FileLogger.prototype.error = function (message) {
        _writeLog.call(this, "error", message);
    };

    var _writeLog = function (type, message) {
        this._fileStream.write(type + " " + message + "\n")
    };

    return FileLogger;

})();