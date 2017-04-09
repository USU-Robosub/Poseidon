// In this test, both JS and C++ apps should start.
// Then after 10 seconds, both should stop.

var Poseidon = require('../app.js');
var power = Poseidon.HardwareFactory.createPowerManager();

power.connect("start", function() {
    setTimeout(function() {
        power.exit("exit", process.exit);
    }, 10000);
}