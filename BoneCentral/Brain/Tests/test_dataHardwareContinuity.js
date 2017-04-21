var $           = require('../Utilities').Promises
var wait        = require('../Utilities').Wait;
var Poseidon    = require('../app.js');

var power       = Poseidon.HardwareFactory.createPowerManager();
var engine      = Poseidon.HardwareFactory.createThrustController();
var run         = $.Deferred();
const THRUST    = 0.3;

power.connect("begin", function(){
    console.log("- BEGIN TEST -");
    power.turnOnEscs();
    run.resolve();
});

run
.then(function(){engine.move(          THRUST);console.log("move");}).then(wait(1000))
.then(function(){engine.move(               0);console.log("move");}).then(wait(1000))
// .then(function(){engine.move(         -THRUST);}).then(wait(1000))
// .then(function(){engine.move(               0);}).then(wait(1000))
.then(function(){engine.secondaryDive( THRUST);console.log("strafe");}).then(wait(1000))
.then(function(){engine.secondaryDive(      0);console.log("strafe");}).then(wait(1000))
// .then(function(){engine.secondaryDive(-THRUST);}).then(wait(1000))
// .then(function(){engine.secondaryDive(      0);}).then(wait(1000))
.then(function(){engine.dive(          THRUST);console.log("dive");}).then(wait(1000))
.then(function(){engine.dive(               0);console.log("dive");}).then(wait(1000))
// .then(function(){engine.dive(         -THRUST);}).then(wait(1000))
// .then(function(){engine.dive(               0);}).then(wait(1000))
.then(function(){engine.yaw(           THRUST);console.log("yaw");}).then(wait(1000))
.then(function(){engine.yaw(                0);console.log("yaw");}).then(wait(1000))
// .then(function(){engine.yaw(          -THRUST);}).then(wait(1000))
// .then(function(){engine.yaw(                0);}).then(wait(1000))
.then(function(){engine.pitch(         THRUST);console.log("pitch");}).then(wait(1000))
.then(function(){engine.pitch(              0);console.log("pitch");}).then(wait(1000))
// .then(function(){engine.pitch(        -THRUST);}).then(wait(1000))
// .then(function(){engine.pitch(              0);}).then(wait(1000))
.then(function(){engine.roll(          THRUST);console.log("roll");}).then(wait(1000))
.then(function(){engine.roll(               0);console.log("roll");}).then(wait(1000))
// .then(function(){engine.roll(         -THRUST);}).then(wait(1000))
// .then(function(){engine.roll(               0);}).then(wait(1000))
.then(wait(1000))
.done(function(){
    console.log("- END TEST -");
    engine.kill();
    power.turnOffEscs();
    power.exit("end", process.exit);
});