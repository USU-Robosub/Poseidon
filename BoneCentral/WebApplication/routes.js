module.exports = function(app, msngr) {
    app.get("/goThroughGate", function (req, res) {
        msngr.goThroughGate();
        res.send("Going through gate");
    });
    
    app.get("/terminate", function (req, res) {
        msngr.terminate();
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
    	res.send(msngr.pullWebLog());
    });
    
    // From IThrustController
    app.post('/move', function (req, res) {
        msngr.move(req.body.throttle)
        res.send('');
    });
    
    app.post('/secondaryDive', function (req, res) {
        msngr.secondaryDive(req.body.throttle);
        res.send('');
    });
    
    app.post('/dive', function (req, res) {
        msngr.dive(req.body.throttle);
        res.send('');
    });
    
    app.post('/yaw', function (req, res) {
        msngr.yaw(req.body.throttle);
        res.send('');
    });
    
    app.post('/pitch', function (req, res) {
        msngr.pitch(req.body.throttle);
        res.send('');
    });
    
    app.post('/roll', function (req, res) {
        msngr.roll(req.body.throttle);
        res.send('');
    });
    
    app.post('/goDirection', function(req, res) {
    	var params = req.body;
    	msngr.goDirection(params.move, params.secondaryDive, params.dive);
    	res.send('');
    });
    
    app.post('/rotate', function(req, res) {
    	var params = req.body;
    	msngr.rotate(params.yaw, params.pitch, params.roll);
    	res.send('');
    });
    
    app.get('/killThrust', function(req, res) {
    	msngr.killThrust();
    	res.send('killThrust');
    });
    
    // From Imu
    app.get('/turnOnImuSensor', function(req, res) {
    	msngr.turnOnImu();
    	res.send('turnOnImuSensor');
    });
    
    app.get('/turnOffImuSensor', function(req, res) {
        msngr.turnOffImu();
    	res.send('turnOffImuSensor');
    });
    
    app.get('/getAcceleration', function(req, res) {
        msngr.accelerometer();
    	res.send('ran getAcceleration');
    });
    
    app.get('/getAngularAcceleration', function(req, res) {
        msngr.gyroscope();
        res.send('ran getAngularAcceleration');
    });
    
    app.get('/getHeading', function(req, res) {
        msngr.compass();
    	res.send('ran getHeading');
    });
    
    app.get('/getInternalTemperature', function(req, res) {
        msngr.getTemperature1();
    	res.send('getInternalTemperature');
    });
    
    app.get('/getInternalPressure', function(req, res) {
        msngr.getPressure1();
    	res.send('getInternalPressure');
    });
    
    app.get('/getExternalTemperature', function(req, res) {
        msngr.getTemperature2();
        res.send('getExternalTemperature');
    });
    
    app.get('/getExternalPressure', function(req, res) {
        msngr.getPressure2();
        res.send('getExternalPressure');
    });
    
    // From Process
    app.get('/exit', function(req, res) {
    	res.send('exit');
    	msngr.exit();
    });
    
    
    // From IPowerController {
    app.get('/turnOnEscs', function(req, res) {
    	msngr.turnOnEscs();
    	res.send('turnOnEscs');
    });
    
    app.get('/turnOffEscs', function(req, res) {
    	msngr.turnOffEscs();
    	res.send('turnOffEscs');
    });
    
    
    // Headlight Control
    app.get('/headlight', function(req, res) {
        msngr.toggleLights();
    	res.send('toggled Headlights');
    });
    
    app.get('/startSearchingForPoles', function (req, res) {
        msngr.startPoleSearch();
        res.send('startSearchingForPoles');
    });
    
    app.get('/getPoleCoordinates', function (req, res) {
        msngr.getPoleLocation();
        res.send('getPoleCoordinates');
    });
    
    app.get('/refreshHsv', function (req, res) {
    	msngr.refreshHSV();
    	res.send('refreshHsv');
    });
    
    app.get('/stopSearchingForPoles', function (req, res) {
        msngr.stopPoleSearch();
        res.send('stopSearchingForPoles');
    });
    
    // Script Run
    app.post('/runScript', function(req, res) {
    	res.send(msngr.runScript(req.body.scriptId));
    });
}