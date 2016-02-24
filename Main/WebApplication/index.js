var express = require('express');
var bodyParser = require('body-parser');
var spawner = require('child_process');
var CppInterface = require('../Brain/CppInterface');
var ConsoleLogger = require('./ConsoleLogger');
var app = express();

peripherals = spawner.spawn('../Peripherals/Release/Bootstrap');

var thrustController = new CppInterface.ThrustController(peripherals.stdin);
var headLights = new CppInterface.HeadLights(peripherals.stdin);
var powerManager = new CppInterface.PowerManager(peripherals.stdin);
var logger = new CppInterface.CppLogger(peripherals.stdout, new ConsoleLogger());

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
	cmdString = 'faceDirection ' + req.body.yaw;
	peripherals.stdin.write(cmdString + "\n");
	res.send(cmdString);
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


app.listen(80, function () {
  console.log('Example app listening on port 80!');
});
