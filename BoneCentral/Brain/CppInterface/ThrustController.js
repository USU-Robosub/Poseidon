/**
 * Created by Nathan Copier on 2/12/2016.
 */

module.exports = (function(){

    function ThrustController(cmdOut){
        this._isDead = true;
        this._cmdOut = cmdOut;
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
        var cmdString = "yaw " + throttle + "\n";
        this._cmdOut.write(cmdString);
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
        this._isDead = true;
        var cmdString = "killThrust\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.start = function () {
        this._isDead = false;
    };

    return ThrustController;

})();
