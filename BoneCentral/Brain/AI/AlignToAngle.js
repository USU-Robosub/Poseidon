var $           = require('../Utilities').Promises
var wait        = require('../Utilities').Wait;
var vector      = require('../Utilities/vector.js');
var ctools      = require('../Utilities/compassTools.js');
var PID         = require('../Utilities/pid.js');
var Poseidon    = require('../app.js');

var upInterval,
    time        = 1.0,
    pid_sp      = 0;
var pid         = new PID();
var imu         = Poseidon.HardwareFactory.createImuSensor();
var power       = Poseidon.HardwareFactory.createPowerManager();
var engine      = Poseidon.HardwareFactory.createThrustController();
var start       = $.Deferred();
var finish      = $.Deferred();
const DELTA     = 150;
const TRANSFORM = 180.0;

pid.setDelta(DELTA);
pid.setBounds(-TRANSFORM, TRANSFORM);
pid.calibrate(0.1, 0.5, 0.01);



start
.then(function() {
    console.log("- System Online -");
    power.turnOnEscs();
    power.turnOnImu();
})
.then(function() {
    upInterval = setInterval(function(){
        update();
        killOutOfTime();
    }, DELTA);
});

finish
.then(function() {
    console.log("- Shutting Down -");
    power.turnOffImu();
    power.turnOffEscs();
    power.exit()
    .then(process.exit);
})

power.connect()
.then(function(){
    console.log("Ready? GO!");
    start.resolve();
});



function update() {
    var waitHeading = $.Deferred();
    var waitAccel   = $.Deferred();
    
    imu.getHeading().done(function(data) {
        waitHeading.resolve(data);
    });
    imu.getAcceleration().done(function(data){
        waitAccel.resolve(data);
    });
    
    $.WhenAll(waitHeading, waitAccel)
    .done(function(cdata,adata) {
        // console.log(cdata);
        // console.log(adata);
    //     var compass = vector.v3(cData.X,cData.Y,cData.Z);
    //     var accel   = vector.v3(aData.X,aData.Y,aData.Z);
        
    //     var pid_pv  = ctools.degrees(compass, accel);
    //     var adj     = pid.update(pid_sp, pid_pv) / TRANSFORM;
    //     console.log("Adjust: " + (adj*100).toFixed(2) + "%");
    //     engine.yaw(adj);
    });
}

function killOutOfTime() {
    time = time - (DELTA/1000.0);
    if(time <= 0) {
        clearInterval(upInterval);
        finish.resolve();
    }
}