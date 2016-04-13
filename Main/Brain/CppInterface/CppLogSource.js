/**
 * Created by Nathan Copier on 2/17/2016.
 */

module.exports = (function() {

    function CppLogSource(streamIn, outputLogger) {
        streamIn.on("data", function(data){
            var logString = data.toString().replace('\n', '');
            _translateLog(outputLogger, logString);
        });
    }

    function _translateLog(outputLogger, logString) {
        var sliceIndex = logString.indexOf(' ');
        var logType = logString.slice(0, sliceIndex);
        var message = logString.slice(sliceIndex+1);
        outputLogger[logType](message);
    }

    return CppLogSource;
})();
