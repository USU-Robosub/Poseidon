var Config              = require('./config.json');
var Ports               = require('./Sockets/Ports.json');
var Sockets             = require('./Sockets');
var Peripherals        	= require('./CppInterface/PeripheralsProcess.js');
var HardwareFactory     = require('./CppInterface/Factory.js');
var Vision              = require('./VisionInterface');

var server              = Sockets.createSocket(Ports.DispatcherPort);
var logServer           = Sockets.createSocket(Ports.LoggerPort);
var hardwareFactory     = new HardwareFactory(server, logServer);
var visionFactory       = new Vision.Factory();

if(Config.appStartMode === "auto") {
    Peripherals.initialize();
}
else {
    console.log("Entering manual mode: run './Periphers --dispatcherPort="+
        Ports.DispatcherPort+" --loggerPort="+Ports.LoggerPort+"'");
}

module.exports = {
    HardwareFactory:    hardwareFactory,
    VisionFactory:      visionFactory
};