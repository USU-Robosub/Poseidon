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
    
    PID.prototype.update = function(sp, pv) {
        var err = sp-pv;
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