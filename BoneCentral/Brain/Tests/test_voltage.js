var Poseidon    = require('../app.js');

var power       = Poseidon.HardwareFactory.createPowerManager();
var voltmeter   = Poseidon.HardwareFactory.createVoltageSensor();

power.connect("run", function() {
    voltmeter.getVoltage().done(function(data){
        console.log(data);
        power.exit("exit", process.exit);
    });
});