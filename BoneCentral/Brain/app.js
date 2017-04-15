var Config              = require('./config.json');
var Ports               = require('./Sockets/Ports.json');
var Sockets             = require('./Sockets');
var Peripherals        	= require('./CppInterface/PeripheralsProcess.js');
var HardwareFactory     = require('./CppInterface/Factory.js');
var ModuleFactory       = require('./Modules/ModuleFactory.js');
var Vision              = require('./VisionInterface');

var server              = Sockets.createSocket(Ports.DispatcherPort);
var hardwareFactory     = new HardwareFactory(server);
var moduleFactory       = new ModuleFactory(hardwareFactory);
var visionFactory       = new Vision.Factory();

if(Config.appStartMode === "auto") {
    Peripherals.initialize();
}
else {
    console.log("Entering manual mode: run './Peripherals --dispatcherPort="+
        Ports.DispatcherPort+"'");
}

module.exports = {
    HardwareFactory:    hardwareFactory,
    VisionFactory:      visionFactory,
    ModuleFactory:      moduleFactory
};