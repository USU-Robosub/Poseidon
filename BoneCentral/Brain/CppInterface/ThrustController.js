/**
 * Created by Nathan Copier on 2/12/2016.
 */

module.exports = (function(){

    function ThrustController(cmdOut){
        this._cmdOut = cmdOut;
    }

    ThrustController.prototype.goDirection = function(move, secondDive, dive) {
        var cmdString =
            "goDirection " + move + " " + secondDive + " " + " " + dive + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.rotate = function(yaw, pitch, roll){
        var cmdString =
            "rotate " + yaw + " " + pitch + " " + roll + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.move = function (throttle) {
        var cmdString = "move " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.secondaryDive = function (throttle) {
        var cmdString = "secondaryDive " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.dive = function (throttle) {
        var cmdString = "primaryDive " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.yaw = function (throttle) {
        var cmdString = "yaw " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.pitch = function (throttle) {
        var cmdString = "pitch " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.roll = function (throttle) {
        var cmdString = "roll " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.kill = function () {
        var cmdString = "killThrust\n";
        this._cmdOut.write(cmdString);
    };

    return ThrustController;

})();
