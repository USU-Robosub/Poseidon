var express = require('express');
var bodyParser = require('body-parser');
var spawner = require('child_process');
var CppInterface = require('../Brain/CppInterface');
var Sockets = require('../Brain/Sockets');
var Ports = require('../Brain/Sockets/Ports.json');
var app = express();

var dispatcherSocket = Sockets.createSocket(Ports.ThrusterPort);
var thrustController = new CppInterface.ThrustController(dispatcherSocket);
var headLights = new CppInterface.HeadLights(dispatcherSocket);
var powerManager = new CppInterface.PowerManager(dispatcherSocket);

var loggerSocket = Sockets.createSocket(Ports.LoggerPort);
new CppInterface.CppLogSource(loggerSocket, console);

peripherals = spawner.spawn('../Peripherals/Release/Bootstrap', ["--thrusterPort=" + Ports.ThrusterPort, "--loggerPort=" + Ports.LoggerPort]);


app.use('/', express.static('static'));
app.use(bodyParser.json());

//From IThruster
app.get('/initialize', function(req, res) {
	res.send('initialize');
});

app.post('/thrust', function(req, res) {
	res.send('thrust ' + req.body.powerLevel);
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
app.get('/getForwardAccel', function(req, res) {
	res.send('getForwardAccel');
});

app.get('/getStrafeAccel', function(req, res) {
	res.send('getStrafeAccel');
});

app.get('/getDiveAccel', function(req, res) {
	res.send('getDiveAccel');
});

app.get('/getForwardAngle', function(req, res) {
	res.send('getForwardAngle');
});

app.get('/getStrafeAngle', function(req, res) {
	res.send('getStrafeAngle');
});

app.get('/getDiveAngle', function(req, res) {
	res.send('getDiveAngle');
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

// From DiveMaster.js
app.post('/setForwardThrust', function(req, res) {
	// res.send(diveMaster.setForwardThrust(req.body.velocity));
	res.send('diveMaster.setForwardThrust(' + req.body.velocity + ')');
});

app.post('/setDiveThrust', function(req, res) {
	// res.send(diveMaster.setDiveThrust(req.body.velocity));
	res.send('diveMaster.setDiveThrust(' + req.body.velocity + ')');
});

app.post('/setStrafeThrust', function(req, res) {
	// res.send(diveMaster.setStrafeThrust(req.body.velocity));
	res.send('diveMaster.setStrafeThrust(' + req.body.velocity + ')');
});

app.post('/setYawThrust', function(req, res) {
	// res.send(diveMaster.setYawThrust(req.body.velocity));
	res.send('diveMaster.setYawThrust(' + req.body.velocity + ')');
});


// Headlight Control
app.get('/headlight', function(req, res) {
    headLights.toggleLights();
	res.send('toggled Headlights');
});


app.listen(80, function () {
  console.log('Example app listening on port 80!');
});
