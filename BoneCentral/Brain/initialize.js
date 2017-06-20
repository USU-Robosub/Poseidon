/**
 * Created by Nathan Copier on 4/28/2016.
 */

var Utilities = require("./Utilities");
var peripheralsInterface = require("./CppInterface");
var peripheralsFactory = new peripheralsInterface.Factory();
var visionInterface = require("./VisionInterface");
var visionFactory = new visionInterface.Factory();
peripheralsInterface.Peripherals.initialize();
var powerManager = peripheralsFactory.createPowerManager();
powerManager.turnOnEscs();
powerManager.turnOnImu();
var ThrustManager = require("./ThrustManager");
var thrustManager = new ThrustManager(peripheralsFactory);
var actionSwitch = peripheralsFactory.createActionSwitch();
var thrustController = peripheralsFactory.createThrustController();


var GoThroughGate = require("./GoThroughGate");
var bumpBuoy = require("./BumpBuoy");
var surfaceAtPinger = require("./SurfaceAtPinger");

var _killSub = function () {

    console.log("Killing...");
    thrustController.kill();
};

var _runSub = function() {
    console.log("Diving...");
    thrustController.dive(0.8);
    Utilities.Wait(1000).then( function () {
        console.log("Thrusting...");
        thrustController.goDirection(0.2, 0, 0.8);
        return {};
    })
};

actionSwitch.on("start",  _runSub);
actionSwitch.on("kill", _killSub);

// Utilities.Wait(500).then( function () {
//     var gTg = new GoThroughGate(visionFactory, thrustManager, console);
//     return gTg.execute();
// }).then(function(){
//     bumpBuoy(peripheralsFactory)
// }).then(function () {
//     surfaceAtPinger(peripheralsFactory)
// });


powerManager.turnOffImu();
powerManager.turnOffEscs();
powerManager.exit();