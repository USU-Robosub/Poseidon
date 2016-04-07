var express = require('express');
var bodyParser = require('body-parser');
var spawner = require('child_process');
var app = express();

var stdoutData = ''

peripherals = spawner.spawn('../Peripherals/Release/Bootstrap');
peripherals.stdout.on('data', function(data) {
	stdoutData = data + '\n' + stdoutData;
});



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
	res.send(stdoutData);
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
	var result = peripherals.stdout.read();
	res.send('getAcceleration' + result);
});

app.get('/getAngularAcceleration', function(req, res) {
	peripherals.stdin.write("getAngularAcceleration\n");
	var result = peripherals.stdout.read();
	res.send('getAngularAcceleration' + result);
});

app.get('/getHeading', function(req, res) {
	peripherals.stdin.write("getHeading\n");
	var result = peripherals.stdout.read();
	res.send('getHeading' + result);
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


// Headlight Control
app.get('/headlight', function(req, res) {
	peripherals.stdin.write('switchLights' + "\n");
	res.send('toggled Headlights');
});


app.listen(80, function () {
  console.log('Example app listening on port 80!');
});
