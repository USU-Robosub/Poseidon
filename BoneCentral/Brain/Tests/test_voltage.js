var Poseidon    = require('../app.js');

var power       = Poseidon.HardwareFactory.createPowerManager();
var sensors     = Poseidon.HardwareFactory.createImuSensor();

power.connect("run", function() {
    sensors.getVoltage().done(function(data){
        console.log(data);
        power.exit("exit", process.exit);
    });
});