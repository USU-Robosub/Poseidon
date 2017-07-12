/**
 * Created by Nathan Copier on 2/12/2016.
 */

var PidController = require("./pid_controller");
var factory = new require("./factory")();

module.exports = (function(){

    function ThrustController(cmdOut){
        this._yawInterval = null;
        this._isDead = true;
        this._cmdOut = cmdOut;
        this._imu = factory.createImuSensor();
    }

    ThrustController.prototype.goDirection = function(move, secondDive, dive) {
        if (this._isDead) return;
        var cmdString =
            "goDirection " + move + " " + secondDive + " " + " " + dive + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.rotate = function(yaw, pitch, roll){
        if (this._isDead) return;
        var cmdString =
            "rotate " + yaw + " " + pitch + " " + roll + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.move = function (throttle) {
        if (this._isDead) return;
        var cmdString = "move " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.secondaryDive = function (throttle) {
        if (this._isDead) return;
        var cmdString = "secondaryDive " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.dive = function (throttle) {
        if (this._isDead) return;
        var cmdString = "primaryDive " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.yaw = function (throttle) {
        if (this._isDead) return;
        const timeDelta = 0.1;
        var yawPid = new PidController().withTimeDelta(timeDelta);
        this._yawInterval = setInterval(function () {
            this._imu.getHeading().then(function (heading) {
                if (this._isDead) return;
                var azimuth = heading.angles().azimuth;
                var adjustment = yawPid.calculateAdjustment(throttle, azimuth);
                var cmdString = "yaw " + adjustment + "\n";
                this._cmdOut.write(cmdString);
            }.bind(this));
        }.bind(this), timeDelta);
    };

    ThrustController.prototype.pitch = function (throttle) {
        if (this._isDead) return;
        var cmdString = "pitch " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.roll = function (throttle) {
        if (this._isDead) return;
        var cmdString = "roll " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.kill = function () {
        clearInterval(this._yawInterval);
        this._isDead = true;
        var cmdString = "killThrust\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.start = function () {
        this._isDead = false;
    };

    return ThrustController;

})();
