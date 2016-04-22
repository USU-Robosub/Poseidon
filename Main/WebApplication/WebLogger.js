module.exports = (function(){

    var stored = '';
    var parent;

    function WebLogger(callUp){
        parent = callUp;
    }

    WebLogger.prototype.info = function(log){
        stored += 'info ' + log + '\n';
        if (parent && parent.info) {
            parent.info(log);
        }
    };

    WebLogger.prototype.warn = function(log){
        stored += 'warn ' + log + '\n';
        if (parent && parent.warn) {
            parent.warn(log);
        }
    };

    WebLogger.prototype.error = function(log){
        stored += 'error ' + log + '\n';
        if (parent && parent.error) {
            parent.error(log);
        }
    };

    WebLogger.prototype.pull = function() {
        to_return = stored;
        stored = '';
        return to_return;
    }

    return WebLogger;

})();