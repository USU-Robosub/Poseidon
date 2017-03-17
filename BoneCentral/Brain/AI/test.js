var Poseidon = require('../app.js');

var power = Poseidon.HardwareFactory.createPowerManager();

setTimeout(function() {
    power.exit();
    process.exit();
}, 10000);