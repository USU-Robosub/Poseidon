/**
 * Created by Nathan Copier on 2/12/2016.
 */

var Spawner = require("child_process");
var Ports = require("../Sockets/Ports.json");
var Path = require("path");

var childProcess = null;

module.exports = {
    HeadLights: require("./Headlights"),
    PowerManager: require("./PowerManager"),
    ThrustController: require("./ThrustController"),
    CppLogSource: require("./CppLogSource"),
    ImuSensor: require("./ImuSensor"),
    Factory: require("./Factory"),
    initializePeripherals: function () {
        var args = [
            "--dispatcherPort=" + Ports.DispatcherPort,
            "--loggerPort=" + Ports.LoggerPort
        ];
        childProcess = Spawner.spawn(Path.resolve(__dirname, "../../Peripherals/Release/Peripherals"), args);
    },
    exitPeripherals: function () {
        // exit child process
    }
};