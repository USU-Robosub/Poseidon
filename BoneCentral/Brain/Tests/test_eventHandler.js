var EventHandler = require("../Utilities/EventHandler.js");

var event = new EventHandler();

event.addEventListener("Test1", function() {
    console.log("Test1");
});
event.addEventListener("Test2", function() {
    console.log("Test2");
});
event.addEventListener("Test3", function() {
    console.log("Test3");
});

console.log("3 Listeners Added");
event.call();

event.removeEventListener("Test1");

console.log("1 Listener Removed");
event.call();