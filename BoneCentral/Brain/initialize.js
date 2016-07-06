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


var GoThroughGate = require("./GoThroughGate");
var bumpBuoy = require("./BumpBuoy");
var surfaceAtPinger = require("./SurfaceAtPinger");

Utilities.Wait(500).then( function () {
    var gTg = new GoThroughGate(visionFactory, peripheralsFactory);
    return gTg.execute();
}).then(function(){
    bumpBuoy(peripheralsFactory)
}).then(function () {
    surfaceAtPinger(peripheralsFactory)
});


powerManager.turnOffImu();
powerManager.turnOffEscs();
powerManager.exit();