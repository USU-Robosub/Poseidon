/**
 * Created by Nathan Copier on 2/17/2016.
 */

module.exports = (function() {

    function CppLogger(streamIn, outputLogger) {
        streamIn.on("readable", function(){
            var input = outputLogger.log(streamIn.read());
            while(input) {
                var logString = input.toString().replace('\n', '');
                _translateLog(outputLogger, logString);
                input = outputLogger.log(streamIn.read());
            }
        });
    }

    var _translateLog = function(outputLogger, logString) {
        var sliceIndex = logString.indexOf(' ');
        var logType = logString.slice(0, sliceIndex);
        var message = logString.slice(sliceIndex+1);
        outputLogger[logType](message);
    };

    return CppLogger;

})();
