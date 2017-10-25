/**
 * Created by Nathan Copier on 2/17/2016.
 */

module.exports = (function() {

    function CppLogSource(streamIn, loggerOut) {
        streamIn.on("data", function(log){
            var logString = log.toString().replace('\n', '');
            _translateLog(loggerOut, logString);
        });
    }

    function _translateLog(loggerOut, logString) {
        var sliceIndex = logString.indexOf(' ');
        var logType = logString.slice(0, sliceIndex);
        var message = logString.slice(sliceIndex+1);
        loggerOut[logType](message);
    }

    return CppLogSource;

})();
