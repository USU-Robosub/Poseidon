/**
 * Created by Nathan Copier on 5/26/2016.
 */

var GateDetector = require("./GateDetector");
var Sockets = require('../Sockets');
var Ports = require('../Sockets/Ports.json');

module.exports = (function () {

    var visionSocket = Sockets.createSocket(Ports.VisionPort);

    function Factory() {}

    Factory.prototype.createGateDetector = function (logger) {
        return new GateDetector(visionSocket.Output, visionSocket.Input, logger)
    };

    return Factory;

})();