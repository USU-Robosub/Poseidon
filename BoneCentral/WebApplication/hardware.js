var fileSystem      	= require('fs');
var path        		= require("path");
var Poseidon    		= require('../Brain/app.js');

var WebLogger       	= require('./WebLogger');
var FileLogger      	= require('./FileLogger');

var fileLogger 		  	= new FileLogger("./test.log");
var webLogger 			= new WebLogger(fileLogger);

var thrustController    = Poseidon.HardwareFactory.createThrustController();
var powerManager 		= Poseidon.HardwareFactory.createPowerManager();
var imuSensor 			= Poseidon.HardwareFactory.createImuSensor();
var headLights 			= Poseidon.HardwareFactory.createHeadlights();

function DMSG(x) {
    console.log(x);
}

module.exports = {
    pullWebLog: function() {
        return webLogger.pull();
    },
    
    move: function(value) {
        DMSG("Moving: " + value);
        thrustController.move(value);
    },
    dive: function(value) {
        DMSG("Diving: " + value);
        thrustController.dive(value);
    },
    secondaryDive: function(value) {
        DMSG("Diving2: " + value);
        thrustController.secondaryDive(value);
    },
    yaw: function(value) {
        DMSG("Yawing: " + value);
        thrustController.yaw(value);
    },
    pitch: function(value) {
        DMSG("Pitching: " + value);
        thrustController.pitch(value);
    },
    roll: function(value) {
        DMSG("Rolling: " + value);
        thrustController.roll(value);
    },
    goDirection: function(move, dive, dive2) {
        DMSG("Go Direction: " + move + ", " + dive2 + ", " + dive);
        thrustController.goDirection(move, dive2, dive);
    },
    rotate: function(yaw, pitch, roll) {
        DMSG("Rotate: " + yaw + ", " + pitch + ", " + roll);
        thrustController.rotate(yaw, pitch, roll);
    },
    killThrust: function() {
        DMSG("Kill Thrusters");
        thrustController.kill();
    },
    
    turnOnImu: function() {
        powerManager.turnOnImu();
    },
    turnOffImu: function() {
        powerManager.turnOffImu();
    },
    getAcceleration: function() {
        imuSensor.getAcceleration().done(function(accel) {
            webLogger.info("Acceleration: " + JSON.stringify(accel));
        });
    },
    getAngularAcceleration: function() {
        imuSensor.getAngularAcceleration().done(function(accel) {
            webLogger.info("Angular Acceleration: " + JSON.stringify(accel));
        });
    },
    getHeading: function() {
        imuSensor.getHeading().done(function(heading) {
            webLogger.info("Heading: " + JSON.stringify(heading));
        });
    },
    getInternalTemperature: function() {
        imuSensor.getInternalTemperature().done(function(temperature) {
            webLogger.info("Internal Temperature: " + JSON.stringify(temperature));
        });
    },
    getExternalTemperature: function() {
        imuSensor.getExternalTemperature().done(function(temperature) {
            webLogger.info("External Temperature: " + JSON.stringify(temperature));
        });
    },
    getInternalPressure: function() {
        imuSensor.getInternalPressure().done(function(pressure) {
            webLogger.info("Internal Pressure: " + JSON.stringify(pressure));
        });
    },
    getExternalPressure: function() {
        imuSensor.getExternalPressure().done(function(pressure) {
            webLogger.info("External Pressure: " + JSON.stringify(pressure));
        });
    },
    
    exit: function() {
        powerManager.exit();
    	powerManager.exit("end", process.exit);
    },
    
    turnOnEscs: function() {
        DMSG("Turn On Escs");
        powerManager.turnOnEscs();
    },
    turnOffEscs: function() {
        DMSG("Turn Off Escs");
        powerManager.turnOffEscs();
    },
    
    toggleLights: function() {
        DMSG("Toggle Lights");
        headLights.toggleLights();
    },
    
    runScript: function(index) {
        fileSystem.readdir("./TestScripts", function (err, fileNames) {
    		if(fileNames[index]) {
                var filePath = path.resolve("TestScripts", fileNames[index]);
                if(require.cache[filePath]) delete require.cache[filePath];
    			var script = require(filePath);
                script.execute(thrustController, imuSensor, webLogger, headLights, powerManager);
    			return ('ran ' + fileNames[index]);
    		}
    		else {
    			return ('script not found');
    		}
    	})
    }
};