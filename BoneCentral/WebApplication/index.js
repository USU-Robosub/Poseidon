var express         = require('express');
var bodyParser      = require('body-parser');
var fileSystem      = require('fs');
var path        	= require("path");
var WebLogger       = require('./WebLogger');
var FileLogger      = require('./FileLogger');
var CppInterface    = require('../Brain/CppInterface');
var VisionInterface	= require("../Brain/VisionInterface");
var GoThroughGate   = require("../Brain/GoThroughGate");
var ThrustManager   = require("../Brain/ThrustManager");

fileLogger 		  	= new FileLogger("./test.log");
webLogger 			= new WebLogger(fileLogger);
peripheralsFactory	= new CppInterface.Factory();
visionFactoy 	  	= new VisionInterface.Factory();
thrustManager    	= new ThrustManager(peripheralsFactory);
goThroughGate 		= new GoThroughGate(visionFactoy, thrustManager, webLogger);

thrustController    = peripheralsFactory.createThrustController();
powerManager 		= peripheralsFactory.createPowerManager();
imuSensor 			= peripheralsFactory.createImuSensor();
headLights 			= peripheralsFactory.createHeadlights();
gateDetector 		= visionFactoy.createGateDetector(webLogger);

peripheralsFactory.createCppLogSource(webLogger);
CppInterface.Peripherals.initialize();

app             	= express();
app.use('/', express.static('static'));
app.use(bodyParser.json());

app.get("/goThroughGate", function (req, res) {
    goThroughGate.execute().done(function () {
		thrustController.goDirection(0, 0, 0);
	});
    res.send("Going through gate");
});

app.get("/terminate", function (req, res) {
    goThroughGate._shouldQuit = true;
    res.send("Terminated");
});

//From IThruster
app.get('/initialize', function(req, res) {
	res.send('initialize');
});

app.post('/thrust', function(req, res) {
	res.send('thrust ' + req.body.powerLevel);
});


app.get('/stdoutData', function(req, res) {
	res.send(webLogger.pull());
});

app.post('/thrustForward', function (req, res) {
	var params = req.body;
	thrustController.thrustForward(params.left, params.right);
	res.send('');
});

app.post('/dive', function (req, res) {
    var params = req.body;
    thrustController.dive(params.forward, params.rear);
    res.send('');
});

// From IThrustController
app.post('/goDirection', function(req, res) {
	var params = req.body;
	thrustController.goDirection(params.forward, params.strafe, params.dive);
	res.send('');
});

app.post('/faceDirection', function(req, res) {
	thrustController.faceDirection(req.body.yaw, req.body.dive);
	res.send('');
});

// From setForwardTrim

app.post('/setForwardTrim', function(req, res) {
	var params = req.body;
	thrustController.setForwardTrim(params.left, params.right);
	res.send('');
});

// From setStrafeTrim

app.post('/setStrafeTrim', function(req, res) {
	var params = req.body;
	thrustController.setStrafeTrim(params.left, params.right);
	res.send('');
});

// From setDiveTrim

app.post('/setDiveTrim', function(req, res) {
	var params = req.body;
	thrustController.setDiveTrim(params.front, params.back);
	res.send('');
});

// From diveOffset

app.post('/setDiveOffset', function(req, res) {
	var params = req.body;
	thrustController.setDiveOffset(params.front, params.back);
	res.send('');
});

// From Imu
app.get('/turnOnImuSensor', function(req, res) {
	powerManager.turnOnImu();
	res.send('turnOnImuSensor');
});

app.get('/turnOffImuSensor', function(req, res) {
    powerManager.turnOffImu();
	res.send('turnOffImuSensor');
});

app.get('/getAcceleration', function(req, res) {
    imuSensor.getAcceleration().done(function(accel) {
        webLogger.info("Acceleration: " + JSON.stringify(accel));
    });
	res.send('ran getAcceleration');
});

app.get('/getAngularAcceleration', function(req, res) {
    imuSensor.getAngularAcceleration().done(function(accel) {
        webLogger.info("Angular Acceleration: " + JSON.stringify(accel));
    });
    res.send('ran getAngularAcceleration');
});

app.get('/getHeading', function(req, res) {
    imuSensor.getHeading().done(function(heading) {
        webLogger.info("Heading: " + JSON.stringify(heading));
    });
	res.send('ran getHeading');
});

app.get('/getInternalTemperature', function(req, res) {
    imuSensor.getInternalTemperature().done(function(temperature) {
        webLogger.info("Internal Temperature: " + JSON.stringify(temperature));
    });
	res.send('getInternalTemperature');
});

app.get('/getInternalPressure', function(req, res) {
    imuSensor.getInternalPressure().done(function(pressure) {
        webLogger.info("Internal Pressure: " + JSON.stringify(pressure));
    });
	res.send('getInternalPressure');
});

app.get('/getExternalTemperature', function(req, res) {
    imuSensor.getExternalTemperature().done(function(temperature) {
        webLogger.info("External Temperature: " + JSON.stringify(temperature));
    });
    res.send('getExternalTemperature');
});

app.get('/getExternalPressure', function(req, res) {
    imuSensor.getExternalPressure().done(function(pressure) {
        webLogger.info("External Pressure: " + JSON.stringify(pressure));
    });
    res.send('getExternalPressure');
});

app.get('/exit', function(req, res) {
	res.send('exit');
	powerManager.exit();
	process.exit();
});


// From IPowerController {
app.get('/turnOnEscs', function(req, res) {
	powerManager.turnOnEscs();
	res.send('turnOnEscs');
});

app.get('/turnOffEscs', function(req, res) {
	powerManager.turnOffEscs();
	res.send('turnOffEscs');
});


// Headlight Control
app.get('/headlight', function(req, res) {
    headLights.toggleLights();
	res.send('toggled Headlights');
});

app.get('/startSearchingForPoles', function (req, res) {
    gateDetector.startSearching();
    res.send('startSearchingForPoles');
});

app.get('/getPoleCoordinates', function (req, res) {
    gateDetector.getPoleCoordinates().done(function (poleCoords) {
        webLogger.info("Pole Coordinates: " + JSON.stringify(poleCoords));
    });
    res.send('getPoleCoordinates');
});

app.get('/refreshHsv', function (req, res) {
	gateDetector.refreshHsv();
	res.send('refreshHsv');
});

app.get('/stopSearchingForPoles', function (req, res) {
    gateDetector.stopSearching();
    res.send('stopSearchingForPoles');
});

// Script Run
app.post('/runScript', function(req, res) {
	var scriptIndex = req.body.scriptId;
	fileSystem.readdir("./TestScripts", function (err, fileNames) {
		if(fileNames[scriptIndex]) {
            var filePath = path.resolve("TestScripts", fileNames[scriptIndex]);
            if(require.cache[filePath]) delete require.cache[filePath];
			var script = require(filePath);
            script.execute(thrustController, imuSensor, webLogger, headLights, powerManager);
			res.send('ran ' + fileNames[scriptIndex]);
		}
		else {
			res.send('script not found');
		}
	})
});

app.listen(80, function () {
  console.log('Web app listening on port 80!');
});
