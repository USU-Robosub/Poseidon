module.exports = (function(){

    var stored = '';
    var parent;

    function WebLogger(callUp){
        parent = callUp;
    }

    WebLogger.prototype.info = function(log){
        stored += 'info ' + log;
        if (callUp && callUp.info) {
            callUp.info(log);
        }
    };

    WebLogger.prototype.warn = function(log){
        stored += 'warn ' + log;
        if (callUp && callUp.warn) {
            callUp.warn(log);
        }
    };

    WebLogger.prototype.error = function(log){
        stored += 'error ' + log;
        if (callUp && callUp.error) {
            callUp.error(log);
        }
    };

    WebLogger.prototype.pull = function() {
        to_return = stored;
        stored = '';
        return to_return;
    }

    return WebLogger;

})();