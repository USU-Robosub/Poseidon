/**
 * Created by Nathan Copier on 2/12/2016.
 */

var Spawner = require("child_process");
var Ports = require("../Sockets/Ports.json");

module.exports = {
    HeadLights: require("./Headlights"),
    PowerManager: require("./PowerManager"),
    ThrustController: require("./ThrustController"),
    CppLogSource: require("./CppLogSource"),
    ImuSensor: require("./ImuSensor"),
    Factory: require("./Factory"),
    initializePeripherals: function () {
        var args = [
            "--thrusterPort=" + Ports.ThrusterPort,
            "--imuPort=" + Ports.ImuPort,
            "--loggerPort=" + Ports.LoggerPort
        ];
        Spawner.spawn("../../Peripherals/Release/Peripherals", args)
    }
};