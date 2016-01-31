var express = require('express');
var bodyParser = require('body-parser');
var spawner = require('child_process');
var app = express();

peripherals = spawner.spawn('../Peripherals/Release/Bootstrap');
peripherals.stdout.on('data', function(data) {
	console.log(data);
});

var diveMaster = require('../brain/DiveMaster.js');

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
	cmdString = 'goDirection ' + req.body.forward + ' ' + req.body.strafe + ' ' + req.body.dive;
	peripherals.stdin.write(cmdString + "\n");
	res.send(cmdString);
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
	peripherals.stdin.write("turnOnEscs\n");
	res.send('turnOnEscs');
});

app.get('/turnOffEscs', function(req, res) {
	peripherals.stdin.write("turnOffEscs\n");
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
