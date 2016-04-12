/**
 * Created by Nathan Copier on 2/17/2016.
 */

module.exports = (function() {

    function CppLogSource(streamIn, outputLogger) {
        _readStream(streamIn, outputLogger);
        streamIn.on("readable", function(){
            _readStream(streamIn, outputLogger);
        });
    }

    function _readStream(streamIn, outputLogger) {
        var input = streamIn.read();
        outputLogger.log("Received Data!: " + input);
        while(input) {
            var logString = input.toString().replace('\n', '');
            outputLogger.log("Data received: " + logString);
            _translateLog(outputLogger, logString);
            input = streamIn.read();
        }
    }

    function _translateLog(outputLogger, logString) {
        var sliceIndex = logString.indexOf(' ');
        var logType = logString.slice(0, sliceIndex);
        var message = logString.slice(sliceIndex+1);
        outputLogger[logType](message);
    }

    return CppLogSource;

})();
