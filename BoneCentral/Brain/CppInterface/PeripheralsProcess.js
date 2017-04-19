/**
 * Created by Nathan Copier on 5/12/2016.
 */

var Spawner = require("child_process");
var Path    = require("path");
var Ports   = require("../Sockets/Ports.json");

var initialize = function () {
    var args = [
        "--dispatcherPort=" + Ports.DispatcherPort
    ];
    var child = Spawner.spawn(Path.resolve(__dirname, "../../Peripherals/Release/Peripherals"), args);
    child.stdout.on("data", function (data) {
        if(data) console.log(data.toString());
    })
};

module.exports = {
    initialize: initialize
};