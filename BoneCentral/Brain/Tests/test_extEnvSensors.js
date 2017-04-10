var $           = require('../Utilities').Promises
var Poseidon    = require('../app.js');

var power       = Poseidon.HardwareFactory.createPowerManager();
var sensors     = Poseidon.HardwareFactory.createImuSensor();

power.connect("run", function() {
    var waitTempr = $.Deferred();
    var waitPress  = $.Deferred();
    
    sensors.getExternalPressure().done(function(data) {
        waitPress.resolve(data);
    });
    sensors.getExternalTemperature().done(function(data){
        waitTempr.resolve(data);
    });
    
    $.WhenAll(waitPress, waitTempr)
    .done(function(tempr, press){
        console.log(tempr);
        console.log(press);
        power.exit("exit", process.exit);
    });
});