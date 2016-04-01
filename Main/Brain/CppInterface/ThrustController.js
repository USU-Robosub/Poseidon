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

    ThrustController.prototype.faceDirection = function(yaw, pitch){
        var cmdString =
            "faceDirection " + yaw + " " + pitch + "\n";
        this._cmdOut.write(cmdString);
    };

    return ThrustController;

})();