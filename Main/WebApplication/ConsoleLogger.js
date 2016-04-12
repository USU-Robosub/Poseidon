module.exports = (function(){

    function ConsoleLogger(){}

    ConsoleLogger.prototype.log = function(log){
        // LogTypes: 'info', 'warn', 'error'
        console[log.LogType](log.Message);
    };

    return ConsoleLogger;

})()