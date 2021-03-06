/**
 * Created by Nathan Copier on 2/12/2016.
 */

const fs = require("fs");
const path = require("path");

module.exports = (function(){

<<<<<<< HEAD
    const configFileName = path.resolve(__dirname) + "/thrusterConfig.json";
=======
    const configFileName = path.resolve(__dirname) + "thrusterConfig.json";
>>>>>>> 304e928db9a792113303893a07fdcd3e0ae3fad3

    function ThrustController(cmdOut){
        this._cmdOut = cmdOut;
        _ensureConfigFile();
        this._config = _readConfigFile();
        this._sendYawConfig( this._config.yaw );
        this._sendDeltaConfig( this._config.timeDelta );
    }

    var _ensureConfigFile = function () {
        if (fs.existsSync(configFileName)) return;
        var config = {
            move: { p: 0.0, i: 0.0, d: 0.0 },
            yaw: { p: 0.1, i: 0.0, d: 0.0 },
            dive: { p: 0.0, i: 0.0, d: 0.0 },
            timeDelta: 100 //ms
        };
        _save(config);
    };

    var _readConfigFile = function () {
        var bufferedData = fs.readFileSync(configFileName);
        return JSON.parse(bufferedData.toString());
    };

    ThrustController.prototype.start = function () {
        this._cmdOut.write( "startThrusters\n" );
    };

    ThrustController.prototype.move = function (throttle) {
        var cmdString = "move " + throttle + "\n";
        this._cmdOut.write( cmdString );
    };

    ThrustController.prototype.yaw = function (angle) {
        console.log("JSTC Recieved angle: " + angle);
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
        this._config.yaw = configuration;
        _save(this._config);
        this._sendYawConfig(configuration);
    };

    ThrustController.prototype._sendYawConfig = function (configuration) {
        var cmdString =
            "configureYaw " + configuration.p + " " + configuration.i + " " + configuration.d + "\n";
        this._cmdOut.write(cmdString);
    };

    ThrustController.prototype.configureTimeDelta = function (timeDelta) {
        this._config.timeDelta = timeDelta;
        _save(this._config);
        this._sendDeltaConfig(timeDelta);
    };

    ThrustController.prototype._sendDeltaConfig = function (timeDelta) {
        var cmdString = "configureTimeDelta " + timeDelta + "\n";
        this._cmdOut.write(cmdString);
    };

    var _save = function (config) {
        fs.writeFileSync(configFileName, JSON.stringify(config));
    };

    return ThrustController;

})();
