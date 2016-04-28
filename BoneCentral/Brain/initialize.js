/**
 * Created by Nathan Copier on 4/28/2016.
 */

var CppInterface = require("./CppInterface");
var cppInterfaceFactory = new CppInterface.Factory();
var powerManager = cppInterfaceFactory.createPowerManager();
powerManager.turnOnEscs();