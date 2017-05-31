module.exports = (function() {
    function PID() {
        this.dt = 0.1;
        this.perr = 0;
        this.min = -100;
        this.max = 100;
        this.kp = 0.1;
        this.ki = 0.5;
        this.kd = 0.01;
    }
    
    /**
     * Calculates the amount of correction you need to reach the set point.
     * @param {number} setPoint The measurement you want to see from the sensors.
     * @param {number} processValue The last sensor measurement.
     */ 
    PID.prototype.update = function(setPoint, processValue) {
        var err = setPoint-processValue;
        var op  = this.kp*err;
        var oi  = this.ki*err*this.dt;
        var od  = this.kd*(err-this.perr)/this.dt;
        var res = op + oi + od;
        if(res > this.max)
            res = this.max;
        else if(res < this.min)
            res = this.min;
        return res;
    };
    
    PID.prototype.setBounds = function(min, max) {
        this.min = min;
        this.max = max;
    };
    
    PID.prototype.setDelta = function(time) {
        this.dt = time;
    }
    
    PID.prototype.calibrate = function(p, i, d) {
        this.kp = p;
        this.ki = i;
        this.kd = d;
    }
    
    PID.prototype.reset = function() {
        this.perr = 0;
    }
    
    return PID;
})();