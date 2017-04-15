var DynamicEngine       = require('./DynamicEngine.js');

module.exports = (function() {
    function ModuleFactory(hardwareFactory) {
        this.hardware = hardwareFactory;
    }
    
    ModuleFactory.prototype.createDynamicEngine = function() {
        return new DynamicEngine(this.hardware);
    };
    
    return ModuleFactory;
})();