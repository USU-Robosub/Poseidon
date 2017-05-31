var $           = require('../Utilities').Promises;
var vector      = require('../Utilities/vector.js');
var ctools      = require('../Utilities/compassTools.js');
var PID         = require('../Utilities/pid.js');

module.exports = (function(){
    const DELTA    = 150; // ms
    const BOUNDS   = 180;
    
    function DynamicEngine(hardware) {
        this.imu        = hardware.createImuSensor();
        this.engine     = hardware.createThrustController();
        this.activeYaw  = false;
        this.activeDive = false;
        this.isRunning  = false;
        this.yawSP      = 0;
        this.diveSP     = 0;
        this.yawPID     = new PID();
        this.divePID    = new PID();
        
        this.yawPID.setDelta(DELTA);
        this.yawPID.setBounds(-BOUNDS, BOUNDS);
        this.yawPID.calibrate(0.6, 0.2, 0);
        
        this.divePID.setDelta(DELTA);
        this.divePID.setBounds(-BOUNDS, BOUNDS);
        this.divePID.calibrate(0.2, 0, 0);
    }
    
    DynamicEngine.prototype.yaw = function(degress) {
        this.yawSP = degress;
    };
    
    DynamicEngine.prototype.dive = function(meters) {
        this.diveSP = meters;
    };
    
    DynamicEngine.prototype.start = function(target) {
             if(target === "yaw" ) { this.activeYaw  = true; }
        else if(target === "dive") { this.activeDive = true; }
        
        if(!this.isRunning) {
            var obj = this;
            this.update = setInterval(function() {
                if(obj.activeYaw ) _updateYaw( obj.imu, obj.yawPID , obj.yawSP , obj.engine);
                if(obj.activeDive) _updateDive(obj.imu, obj.divePID, obj.diveSP, obj.engine);
            }, DELTA);
            this.isRunning = true;
        }
    };
    
    DynamicEngine.prototype.stop = function(target) {
        if(target === "yaw" ) {
            this.activeYaw  = false;
            this.engine.yaw(0);
        }
        else if(target === "dive") {
            this.activeDive = false;
            this.engine.dive(0);
        }
        else {
            clearInterval(this.update);
            this.engine.yaw(0);
            this.engine.dive(0);
            this.isRunning = false;
        }
    };
    
    function _updateYaw (imu, yawPID, yawSP, engine) {
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
            var pid_pv  = transformDegrees(deg, yawSP);
            var adj     = yawPID.update(yawSP, pid_pv) / BOUNDS;
            
            console.log(deg.toFixed(2)+"|"+pid_pv.toFixed(2)+"; Yaw Adjust: " + (adj*100).toFixed(2) + "%\t | " + adj.toFixed(2));
            engine.yaw(adj);
        });
    };
    
    function _updateDive(imu, divePID, diveSP, engine) {
        imu.getInternalPressure().done(function(pdata) {
            var pid_pv  = pdata.Value;
            var adj     = divePID.update(diveSP, pid_pv) / BOUNDS;
            console.log("Depth Adjust: " + (adj*100).toFixed(2) + "%\t | " + adj.toFixed(2));
            engine.dive(-adj);
        });
    };
    
    function transformDegrees(source, target) {
        var res = source - target;
        if(res > BOUNDS)
            res = res - 2*BOUNDS;
        else if(res <= -BOUNDS)
            res = res + 2*BOUNDS;
        return res;
    }
    
    return DynamicEngine;
})();