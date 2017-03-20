// In this test, both JS and C++ apps should start.
// Then after 10 seconds, both should stop.

var Poseidon = require('../app.js');
var power = Poseidon.HardwareFactory.createPowerManager();

setTimeout(function() {
    power.exit();
    process.exit();
}, 10000);