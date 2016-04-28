var express = require('express');
var bodyParser = require('body-parser');
var spawner = require('child_process');
var CppInterface = require('../Brain/CppInterface');
var Sockets = require('../Brain/Sockets');
var Ports = require('../Brain/Sockets/Ports.json');
var WebLogger = require('./WebLogger');
var app = express();

var dispatcherSocket = Sockets.createSocket(Ports.ThrusterPort);
var thrustController = new CppInterface.ThrustController(dispatcherSocket);
var headLights = new CppInterface.HeadLights(dispatcherSocket);
var powerManager = new CppInterface.PowerManager(dispatcherSocket);
var imuSocket = Sockets.createSocket(Ports.ImuPort);
var imuReader = new CppInterface.ImuReader(imuSocket, imuSocket);

var loggerSocket = Sockets.createSocket(Ports.LoggerPort);
var webLogger = new WebLogger(console);
new CppInterface.CppLogSource(loggerSocket, webLogger);

var args = ["--thrusterPort=" + Ports.ThrusterPort, "--imuPort=" + Ports.ImuPort, "--loggerPort=" + Ports.LoggerPort];
spawner.spawn('../Peripherals/Release/Peripherals', args);

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

// From diveOffset

app.post('/setOffset', function(req, res) {
	var params = req.body;
	thrustController.setOffset(params.front, params.back);
	res.send('');
});

// From Imu
app.get('/turnOnImuSensor', function(req, res) {
    dispatcherSocket.write("turnOnImuSensor\n");
	res.send('turnOnImuSensor');
});

app.get('/turnOffImuSensor', function(req, res) {
    dispatcherSocket.write("turnOffImuSensor\n");
	res.send('turnOffImuSensor');
});

app.get('/getAcceleration', function(req, res) {
    imuReader.getAcceleration().done(function(accel) {
        console.log("Acceleration: " + accel);
    });
	res.send('ran getAcceleration');
});

app.get('/getAngularAcceleration', function(req, res) {
    dispatcherSocket.write("getAngularAcceleration\n");
    res.send('ran getAngularAcceleration');
});

app.get('/getHeading', function(req, res) {
    dispatcherSocket.write("getHeading\n");
	res.send('ran getHeading');
});

app.get('/getInternalTemperature', function(req, res) {
    dispatcherSocket.write("getInternalTemperature\n");
	res.send('getInternalTemperature');
});

app.get('/getInternalPressure', function(req, res) {
    dispatcherSocket.write("getInternalPressure\n");
	res.send('getInternalPressure');
});

app.get('/exit', function(req, res) {
    dispatcherSocket.write("exit\n");
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
