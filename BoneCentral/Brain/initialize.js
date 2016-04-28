/**
 * Created by Nathan Copier on 4/28/2016.
 */

var CppInterface = require("./CppInterface");
var Utilities = require("./Utilities");
var cppInterfaceFactory = new CppInterface.Factory();
CppInterface.initializePeripherals();
var powerManager = cppInterfaceFactory.createPowerManager();
powerManager.turnOnEscs();
powerManager.turnOnImu();



var goThroughGate = require("./GoThroughGate");
var bumpBuoy = require("./BumpBuoy");
var surfaceAtPinger = require("./SurfaceAtPinger");

Utilities.Wait(500).then(
    goThroughGate(cppInterfaceFactory)
).then(function(){
    bumpBuoy(cppInterfaceFactory)
}).then(function () {
    surfaceAtPinger(cppInterfaceFactory)
});


powerManager.turnOffImu();
powerManager.turnOffEscs();
CppInterface.exitPeripherals();