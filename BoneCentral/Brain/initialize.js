#!/usr/bin/env node
/**
 * Created by Nathan Copier on 4/28/2016.
 */

var peripheralsInterface = require("./CppInterface");
var peripheralsFactory = new peripheralsInterface.Factory();
var visionInterface = require("./VisionInterface");
var visionFactory = new visionInterface.Factory();
peripheralsInterface.Peripherals.initialize();
var powerManager = peripheralsFactory.createPowerManager();
powerManager.turnOnImu();
var actionSwitch = peripheralsFactory.createActionSwitch();
var thrustController = peripheralsFactory.createThrustController();


var goThroughGate = require("./GoThroughGate");
var bumpBuoy = require("./BumpBuoy");
var surfaceAtPinger = require("./SurfaceAtPinger");

var runModule = require("./Run");
var Run = runModule.init(
    goThroughGate.init(),
    bumpBuoy.init(),
    surfaceAtPinger.init()
);

var run = null;

var _killSub = function () {
    try {
        console.log("Killing...");
        if (run) run.kill();
        run = null;
    } catch(exception) {
        thrustController.kill();
        throw exception;
    }
};

var _runSub = function() {
    try {
        console.log("Starting...");
        run = new Run(thrustController);
        run.execute();
    } catch(exception) {
        thrustController.kill();
        throw exception;
    }
};

actionSwitch.on("start", _runSub);
actionSwitch.on("kill", _killSub);