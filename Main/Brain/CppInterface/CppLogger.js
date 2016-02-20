/**
 * Created by Nathan Copier on 2/17/2016.
 */

module.exports = (function() {
    function CppLogger(streamIn, outputLogger) {
        streamIn.on("data", function(log){
            _translateLog(outputLogger, log);
        });
    }

    var _translateLog = function(outputLogger, log) {
        var sliceIndex = log.indexOf(' ');
        outputLogger.log({
            LogType: log.slice(0, sliceIndex),
            Message: log.slice(sliceIndex+1)
        });
    };

    return CppLogger;

})();
