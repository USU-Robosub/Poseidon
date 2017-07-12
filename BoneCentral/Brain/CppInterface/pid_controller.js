module.exports = (function() {

    function PidController() {
        this._previousError = 0;
        this._min = -100;
        this._max = 100;
        this._kp = 0.1;
        this._ki = 0.5;
        this._kd = 0.01;
    }

    PidController.prototype.withBounds = function(min, max) {
        this._min = min;
        this._max = max;
    };

    PidController.prototype.withTimeDelta = function (timeDelta) {
        this._timeDelta = timeDelta;
    };
    
    PidController.prototype.calculateAdjustment = function(setPoint, currentMeasurement) {
        var currentError = setPoint - currentMeasurement;
        var errorDifference = currentError-this._previousError;
        this._previousError = currentError;
        var proportion  = this._kp * currentError;
        var integral  = this._ki * currentError * this._timeDelta;
        var derivative  = this._kd * (errorDifference)/this._timeDelta;
        var adjustment = proportion + integral + derivative;
        if(adjustment > this._max)
            return this._max;
        if(adjustment < this._min)
            return this._min;
        return adjustment;
    };
    
    PidController.prototype.calibrate = function(p, i, d) {
        this._kp = p;
        this._ki = i;
        this._kd = d;
    };

    PidController.prototype.reset = function() {
        this._previousError = 0;
    };
    
    return PidController;

})();