var $           = require('../Utilities').Promises;
var wait        = require('../Utilities').Wait;
var Poseidon    = require("../app.js");

var power         = Poseidon.HardwareFactory.createPowerManager();
var engine        = Poseidon.HardwareFactory.createThrustController();
var dynamicEngine = Poseidon.ModuleFactory.createDynamicEngine();
var run           = $.Deferred();

power.connect("start", function() {
    console.log("- BEGIN -");
    power.turnOnImu();
    run.resolve();
});

run
.then(function() {
    dynamicEngine.start("yaw");
})
.then(wait(200))
.then(function() {
    dynamicEngine.yaw(0);
})
.then(wait(5000))
.then(function() {
    dynamicEngine.stop("yaw");
})
.then(wait(1000))
.then(function() {
    dynamicEngine.start("yaw");
    dynamicEngine.yaw(90);
})
.then(wait(5000))
.done(function() {
    dynamicEngine.stop();
    power.turnOffImu();
    console.log("- FINISH -");
    power.exit("end", process.exit);
});