var $           = require('../Utilities').Promises
var wait        = require('../Utilities').Wait;
var Poseidon    = require('../app.js');

var run         = $.Deferred();
var power       = Poseidon.HardwareFactory.createPowerManager();
var engine      = Poseidon.HardwareFactory.createThrustController();
const THRUST    = 0.3

power.connect("run", function() {
    console.log("- START -");
    run.resolve();
})

run
.then(function() {
    engine.move(THRUST);
})
.then(wait(200))
.then(function() {
    engine.move(0);
    engine.dive(THRUST);
})
.then(wait(200))
.then(function() {
    engine.dive(0);
    engine.secondaryDive(THRUST);
})
.then(wait(200))
.then(function() {
    engine.secondaryDive(0);
    engine.yaw(THRUST);
})
.then(wait(200))
.then(function() {
    engine.yaw(0);
    engine.pitch(THRUST);
})
.then(wait(200))
.then(function() {
    engine.pitch(0);
    engine.roll(THRUST);
})
.then(wait(200))
.then(function() {
    console.log("- FINISH -");
    engine.kill();
    power.exit("exit", process.exit);
});