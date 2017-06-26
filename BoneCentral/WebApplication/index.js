var express         	= require('express');
var bodyParser      	= require('body-parser');
var fileSystem      	= require('fs');
var path        		= require("path");
var WebLogger       	= require('./WebLogger');
var FileLogger      	= require('./FileLogger');
var CppInterface		= require('../Brain/CppInterface');
var VisionInterface		= require("../Brain/VisionInterface");
var GoThroughGate   	= require("../Brain/GoThroughGate").init();
var ThrustManager   	= require("../Brain/ThrustManager");

var fileLogger 		  	= new FileLogger("./test.log");
var webLogger 			= new WebLogger(fileLogger);
var peripheralsFactory	= new CppInterface.Factory();
var visionFactoy 	  	= new VisionInterface.Factory();
var thrustManager    	= new ThrustManager(peripheralsFactory);

var thrustController    = peripheralsFactory.createThrustController();
var powerManager 		= peripheralsFactory.createPowerManager();
var imuSensor 			= peripheralsFactory.createImuSensor();
var headLights 			= peripheralsFactory.createHeadlights();
var gateDetector 		= visionFactoy.createGateDetector(webLogger);

peripheralsFactory.createCppLogSource(webLogger);
CppInterface.Peripherals.initialize();

app             	= express();
app.use('/', express.static('static'));
app.use(bodyParser.json());

app.get("/goThroughGate", function (req, res) {
    new GoThroughGate(thrustController).execute().done(function () {
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

// From IThrustController
app.post('/move', function (req, res) {
    var params = req.body;
    thrustController.move(params.throttle);
    res.send('');
});

// From IThrustController
app.post('/secondaryDive', function (req, res) {
    var params = req.body;
    thrustController.secondaryDive(params.throttle);
    res.send('');
});

// From IThrustController
app.post('/dive', function (req, res) {
    var params = req.body;
    thrustController.dive(params.throttle);
    res.send('');
});

// From IThrustController
app.post('/yaw', function (req, res) {
    var params = req.body;
    thrustController.yaw(params.throttle);
    res.send('');
});

// From IThrustController
app.post('/pitch', function (req, res) {
    var params = req.body;
    thrustController.pitch(params.throttle);
    res.send('');
});

// From IThrustController
app.post('/roll', function (req, res) {
    var params = req.body;
    thrustController.roll(params.throttle);
    res.send('');
});

// From IThrustController
app.post('/goDirection', function(req, res) {
	var params = req.body;
	thrustController.goDirection(params.move, params.secondaryDive, params.dive);
	res.send('');
});

// From IThrustController
app.post('/rotate', function(req, res) {
	var params = req.body;
	thrustController.rotate(params.yaw, params.pitch, params.roll);
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
app.get('/startThrusters', function(req, res) {
    thrustController.start();
	res.send('startThrusters');
});

app.get('/killThrusters', function(req, res) {
    thrustController.kill();
	res.send('killThrusters');
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
