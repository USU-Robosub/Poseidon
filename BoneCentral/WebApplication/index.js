var express = require('express');
var bodyParser = require('body-parser');
var CppInterface = require('../Brain/CppInterface');
var WebLogger = require('./WebLogger');
var app = express();

var interfaceFactory = new CppInterface.Factory();

var thrustController = interfaceFactory.createThrustController();
var headLights = interfaceFactory.createHeadlights();
var powerManager = interfaceFactory.createPowerManager();
var imuSensor = interfaceFactory.createImuSensor();

var webLogger = new WebLogger(console);
interfaceFactory.createCppLogSource(webLogger);

CppInterface.initializePeripherals();

app.use('/', express.static('static'));
app.use(bodyParser.json());

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
app.post('/goDirection', function(req, res) {
	var params = req.body;
	thrustController.goDirection(params.forward, params.strafe, params.dive);
	res.send('');
});

app.post('/faceDirection', function(req, res) {
	thrustController.faceDirection(req.body.yaw);
	res.send('');
});

// From diveOffset

app.post('/setOffset', function(req, res) {
	var params = req.body;
	thrustController.setOffset(params.front, params.back);
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
	powerManager.exit();
	res.send('exit');
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

// Script Run
app.post('/runScript', function(req, res) {
	var scripts = [

	];

	try {
		var response = '' + eval(scripts[req.body.scriptId]);
		return response;
	}
	catch(err) {
		res.send('' + err)
		return;
	}
});


app.listen(80, function () {
  console.log('Example app listening on port 80!');
});
