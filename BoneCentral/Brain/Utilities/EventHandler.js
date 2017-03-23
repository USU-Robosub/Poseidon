module.exports = (function() {
    function EventHandler() {
        this.events = {};
    }
    
    EventHandler.prototype.addEventListener = function(name, callback) {
        if(typeof callback === 'function' && typeof name === 'string') {
            this.events[name] = callback;
        }
    };
    
    EventHandler.prototype.removeEventListener = function(name) {
        if(typeof name === 'string' && name in this.events){
            delete this.events[name];
        }
    };
    
    EventHandler.prototype.call = function(args) {
        for(key in this.events) {
            this.events[key]();
        }
    };
    
    return EventHandler;
})();