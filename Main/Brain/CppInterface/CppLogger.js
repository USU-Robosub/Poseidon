/**
 * Created by Nathan Copier on 2/17/2016.
 */

module.exports = (function() {

    function CppLogger(streamIn, outputLogger) {
        streamIn.on("readable", function(){
            outputLogger.log(streamIn.read());
            var logString = streamIn.read().toString().replace('\n', '');
            _translateLog(outputLogger, logString);
        });
    }

    var _translateLog = function(outputLogger, logString) {
        var sliceIndex = logString.indexOf(' ');
        outputLogger.log({
            LogType: logString.slice(0, sliceIndex),
            Message: logString.slice(sliceIndex+1)
        });
    };

    return CppLogger;

})();
