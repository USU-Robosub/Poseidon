var Poseidon = require('../app.js');
var power = Poseidon.HardwareFactory.createPowerManager();

var counter = 0;

power.action("action", function() {
    console.log("Event Fired " + counter);
    counter++;
    if(counter === 2)
        power.exit("exit", process.exit);
});