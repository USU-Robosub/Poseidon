var express         	= require('express');
var bodyParser      	= require('body-parser');
var fileSystem      	= require('fs');
var path        		= require("path");
var routes              = require('./routes.js');
var WebLogger       	= require('./WebLogger');
var FileLogger      	= require('./FileLogger');
var CppInterface		= require('../Brain/CppInterface');
var VisionInterface		= require("../Brain/VisionInterface");
var GoThroughGate   	= require("../Brain/GoThroughGate");
var ThrustManager   	= require("../Brain/ThrustManager");

var peripheralsFactory = new CppInterface.Factory();
var ThrustManager = require("../Brain/ThrustManager");
var thrustManager = new ThrustManager(peripheralsFactory);

var thrustController = peripheralsFactory.createThrustController();
var headLights = peripheralsFactory.createHeadlights();
var powerManager = peripheralsFactory.createPowerManager();
var imuSensor = peripheralsFactory.createImuSensor();

var fileLogger = new FileLogger("./test.log");
var webLogger = new WebLogger(fileLogger);
peripheralsFactory.createCppLogSource(webLogger);

CppInterface.Peripherals.initialize();

var visionFactoy = new VisionInterface.Factory();
var gateDetector = visionFactoy.createGateDetector(webLogger);

var goThroughGate = new GoThroughGate(visionFactoy, thrustManager, webLogger);

app.use('/', express.static('static'));
app.use(bodyParser.json());
routes(app);

app.listen(80, function () {
  console.log('Example app listening on port 80!');
});
