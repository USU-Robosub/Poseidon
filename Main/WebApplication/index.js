var express = require('express');
var bodyParser = require('body-parser');
var spawner = require('child_process');
var CppInterface = require('../Brain/CppInterface');
var WebLogger = require('./WebLogger');
var app = express();


var peripherals = spawner.spawn('../Peripherals/Release/Bootstrap');

var webLogger = new WebLogger(console);

var thrustController = new CppInterface.ThrustController(peripherals.stdin);
var headLights = new CppInterface.HeadLights(peripherals.stdin);
var powerManager = new CppInterface.PowerManager(peripherals.stdin);
new CppInterface.CppLogSource(peripherals.stdout, webLogger);

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
	thrustController.faceDirection(req.body.yaw)
	res.send('');
});


// From Imu
app.get('/turnOnImuSensor', function(req, res) {
	peripherals.stdin.write("turnOnImuSensor\n");
	res.send('turnOnImuSensor');
});

app.get('/turnOffImuSensor', function(req, res) {
	peripherals.stdin.write("turnOffImuSensor\n");
	res.send('turnOffImuSensor');
});

app.get('/getAcceleration', function(req, res) {
	peripherals.stdin.write("getAcceleration\n");
	res.send('ran getAcceleration');
});

app.get('/getAngularAcceleration', function(req, res) {
	peripherals.stdin.write("getAngularAcceleration\n");
	res.send('ran getAngularAcceleration');
});

app.get('/getHeading', function(req, res) {
	peripherals.stdin.write("getHeading\n");
	res.send('ran getHeading');
});

app.get('/getInternalTemperature', function(req, res) {
	peripherals.stdin.write("getInternalTemperature\n");
	res.send('getInternalTemperature');
});

app.get('/getInternalPressure', function(req, res) {
	peripherals.stdin.write("getInternalPressure\n");
	res.send('getInternalPressure');
});

app.get('/exit', function(req, res) {
	peripherals.stdin.write("exit\n");
	res.send('exit');
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
