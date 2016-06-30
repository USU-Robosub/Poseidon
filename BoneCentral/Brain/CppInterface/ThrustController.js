/**
 * Created by Nathan Copier on 2/12/2016.
 */

module.exports = (function(){

    function ThrustController(cmdOut){
        this._cmdOut = cmdOut;
    }

    ThrustController.prototype.goDirection = function(forward, strafe, dive) {
        var cmdString =
            "goDirection " + forward + " " + strafe + " " + " " + dive + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.faceDirection = function(yaw, dive){
        var cmdString =
            "faceDirection " + yaw + " " + dive + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.setDiveOffset = function(front, back) {
        var cmdString = "setDiveOffset " + front + " " + back + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.setForwardTrim = function(left, right) {
        var cmdString = "setForwardTrim " + left + " " + right + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.setStrafeTrim = function(left, right) {
        var cmdString = "setStrafeTrim " + left + " " + right + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.setDiveTrim = function(front, back) {
        var cmdString = "setDiveTrim " + front + " " + back + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.thrustForward = function (left, right) {
        var cmdString = "thrustForward " + left + " " + right + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.dive = function (forward, rear) {
        var cmdString = "dive " + forward + " " + rear + "\n";
        this._cmdOut.write(cmdString);
    };

    return ThrustController;

})();
