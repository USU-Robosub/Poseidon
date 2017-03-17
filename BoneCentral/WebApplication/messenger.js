var hdwr = require('./hardware.js');

module.exports = {
    // goThroughGate:  hdwr.goThroughGate,
    // terminate:      hdwr.terminate,
    
    exit:           hdwr.exit,
    pullWebLog:     hdwr.pullWebLog,
    
    move:           hdwr.move,
    dive:           hdwr.dive,
    secondaryDive:  hdwr.secondaryDive,
    yaw:            hdwr.yaw,
    pitch:          hdwr.pitch,
    roll:           hdwr.roll,
    goDirection:    hdwr.goDirection,
    rotate:         hdwr.rotate,
    killThrust:     hdwr.killThrust,
    
    turnOnImu:      hdwr.turnOnImu,
    turnOffImu:     hdwr.turnOffImu,
    accelerometer:  hdwr.getAcceleration,
    gyroscope:      hdwr.getAngularAcceleration,
    compass:        hdwr.getHeading,
    getTemperature1:hdwr.getInternalTemperature,
    getTemperature2:hdwr.getExternalTemperature,
    getPressure1:   hdwr.getInternalPressure,
    getPressure2:   hdwr.getExternalPressure,
    
    turnOnEscs:     hdwr.turnOnEscs,
    turnOffEscs:    hdwr.turnOffEscs,
    
    toggleLights:   hdwr.toggleLights,
    
    runScript:      hdwr.runScript
};