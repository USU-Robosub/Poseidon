/**
 * Created by Nathan Copier on 2/12/2016.
 */

module.exports = (function(){

    function ThrustController(cmdOut){
        this._cmdOut = cmdOut;
    }

    ThrustController.prototype.start = function () {
        this._cmdOut.write( "startThrusters" );
    };

    ThrustController.prototype.move = function (throttle) {
        var cmdString = "move " + throttle + "\n";
        this._cmdOut.write( cmdString );
    };

    ThrustController.prototype.yaw = function (angle) {
        var cmdString = "yaw " + angle + "\n";
        this._cmdOut.write( cmdString );
    };

    ThrustController.prototype.dive = function (throttle) {
        var cmdString = "dive " + throttle + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.kill = function () {
        var cmdString = "killThrusters\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.configureYaw = function(configuration) {
        var cmdString =
            "configureYaw " + configuration.p + " " + configuration.i + " " + configuration.d + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.configureTimeDelta = function (timeDelta) {
        var cmdString = "configureTimeDelta " + timeDelta + "\n";
        this._cmdOut.write(cmdString);
    };

    return ThrustController;

})();
