var $           = require('../Utilities').Promises
var wait        = require('../Utilities').Wait;
var vector      = require('../Utilities/vector.js');
var ctools      = require('../Utilities/compassTools.js');
var PID         = require('../Utilities/pid.js');
var Poseidon    = require('../app.js');

var upInterval,
    time        = 15.0,
    pid_sp      = 0,
    target      = 90;
var pid         = new PID();
var imu         = Poseidon.HardwareFactory.createImuSensor();
var power       = Poseidon.HardwareFactory.createPowerManager();
var engine      = Poseidon.HardwareFactory.createThrustController();
const DELTA     = 150;
const TRANSFORM = 180.0;

pid.setDelta(DELTA);
pid.setBounds(-TRANSFORM, TRANSFORM);

// - Calibrating the PID -
// Step 1: Set Kp, Ki, and Kd = 0
// Step 2: Set Kp = 0 -> u until oscillating consistently
// Step 3: Set Ku = u and measure oscillation period
// Step 4: Set Tu = period
var Ku = 0.5, Tu = 4;
// pid.calibrate(0.6*Ku, Tu/2, Tu/8);
pid.calibrate(0.6, 0.2, 0);


power.connect("begin", function(){
    console.log("Ready? GO!");
    start();
});

function start() {
    console.log("- System Online -");
    power.turnOnEscs();
    power.turnOnImu();
    engine.move(1);
    upInterval = setInterval(function(){
        update();
        killOutOfTime();
    }, DELTA);
}

function finish() {
    console.log("- Shutting Down -");
    engine.kill();
    power.turnOffImu();
    power.turnOffEscs();
    power.exit("end", process.exit);
}



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
        var compass = vector.v3(cdata.Z,cdata.Y,-cdata.X);
        var accel   = vector.v3(adata.Z,adata.Y,-adata.X);
        
        var deg     = ctools.degrees(compass, accel);
        var pid_pv  = transformDegrees(deg, target);
        var adj     = pid.update(pid_sp, pid_pv) / TRANSFORM;
        console.log(deg.toFixed(2)+"|"+pid_pv.toFixed(2)+"; Adjust: " + (adj*100).toFixed(2) + "%\t | " + adj.toFixed(2));
        engine.yaw(adj);
    });
}

function transformDegrees(source, target) {
    var res = source - target;
    if(res > TRANSFORM)
        res = res - 2*TRANSFORM;
    else if(res <= -TRANSFORM)
        res = res + 2*TRANSFORM;
    return res;
}

function killOutOfTime() {
    time = time - (DELTA/1000.0);
    if(time <= 0) {
        clearInterval(upInterval);
        finish();
    }
}