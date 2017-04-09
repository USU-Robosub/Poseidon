var $           = require('../Utilities').Promises
var wait        = require('../Utilities').Wait;
var Poseidon    = require('../app.js');

var power       = Poseidon.HardwareFactory.createPowerManager();
var imu         = Poseidon.HardwareFactory.createImuSensor();
var test        = $.Deferred();

test
.then(wait(5000))
.then(function() {
    console.log("IMU On");
    power.turnOnImu();
})
.then(wait(250))
.then(function() {
    console.log("Fetch 1");
    imu.getHeading().then(function(heading){
        console.log(heading);
    });
})
.then(wait(250))
.then(function() {
    console.log("Fetch 2");
    imu.getHeading().then(function(heading){
        console.log(heading);
    });
})
.then(wait(250))
.done(function() {
    console.log("IMU Off");
    power.turnOffImu();
    power.exit("exit", process.exit);
});

power.connect("run", test.resolve);