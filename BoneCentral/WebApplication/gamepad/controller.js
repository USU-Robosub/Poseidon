if(navigator.userAgent.search("Firefox") == -1 && navigator.userAgent.search("Chrome") == -1){
  alert("Gamepad support is only for Firefox and Chrome. Other browsers may not connect to your gamepad properly.");
}

var gamepad = new Gamepad();

gamepad.bind(Gamepad.Event.CONNECTED, function(device) {
	// a new gamepad connected
  console.log("connected");
});

gamepad.bind(Gamepad.Event.DISCONNECTED, function(device) {
	// gamepad disconnected
  console.log("disconnected");
});

gamepad.bind(Gamepad.Event.UNSUPPORTED, function(device) {
    // an unsupported gamepad connected (add new mapping)
    alert("The connected gamepad is unsupported");
});

gamepad.bind(Gamepad.Event.BUTTON_DOWN, function(e) {
    // e.control of gamepad e.gamepad pressed down
    //console.log("button_down", e.gamepad);
});

gamepad.bind(Gamepad.Event.BUTTON_UP, function(e) {
    // e.control of gamepad e.gamepad released
    //console.log("button_up");
});

var timer = Rx.Observable.timer(200, 10);

function getValue(x){ return x.value; }
function sameValue(a, b){ return Math.abs(a - b) < 0.01; }
function checkAxis(name, x){ return x.axis == name; }
function deadZone(x) { return Math.abs(x) < 0.2 ? 0 : x; }
function modmod(x, n) { return x - Math.floor(x/n) * n; }
function getAngle(a, b, n) { return modmod(a - b + n, n * 2) - n }

var throttle = timer.map(function() {
  return gamepad.gamepads[0].state["LEFT_BOTTOM_SHOULDER"];
}).map(deadZone);

var brake = timer.map(function() {
  return gamepad.gamepads[0].state["RIGHT_BOTTOM_SHOULDER"];
}).map(deadZone);

var speed = Rx.Observable.combineLatest([throttle, brake])
  .throttle(100)
  .map(function(x){
    return x[0] - x[1];
  })
  .map(deadZone)
  .distinctUntilChanged(null, sameValue);

var steering = timer.map(function() {
  return gamepad.gamepads[0].state["LEFT_STICK_X"];
}).map(deadZone).throttle(100);

var angle = 0;
var heading = steering.map(function(x) {
  angle += x * 0.05;
  return angle;
}).throttle(200).distinctUntilChanged(null, sameValue);

var depthThrottle = 0;
var depth = timer.map(function() {
  return gamepad.gamepads[0].state["RIGHT_STICK_Y"];
}).map(deadZone).throttle(100).map(function(x) {
  depthThrottle += x * 0.05;
  return Math.min(Math.max(Math.abs(depthThrottle) < 0.05 ? 0 : depthThrottle, -1), 1);
}).throttle(100).distinctUntilChanged(null, sameValue);

if (!gamepad.init()) {
	// Your browser does not support gamepads, get the latest Google Chrome or Firefox
  alert("Gamepad are not supported for this browser")
}

/*throttle.subscribe(function(x) {
  console.log("Throttle: ", x);
});*/

/*brake.subscribe(function(x) {
  console.log("Brake: ", x);
});*/

var speedColorDiv = document.getElementById("speed_color");
var speedDisplayDiv = document.getElementById("speed_display");
var steeringImg = document.getElementById("steering_img");
var steeringDisplayDiv = document.getElementById("steering_display");
var headingImg = document.getElementById("heading_img");
var headingDisplayDiv = document.getElementById("heading_display");
var diveColorDiv = document.getElementById("dive_color");
var diveDisplayDiv = document.getElementById("dive_display");

function toHex(x){
  return ("00" + x.toString(16).slice(-2)).slice(-2)
}

speed.subscribe(function(x) {
  console.log("Throttle: ", x);
  var forward = Math.floor(Math.max(x, 0) * 255);
  var backward = Math.floor(Math.max(-x, 0) * 255);
  speedColorDiv.style.backgroundColor = "#" + toHex(255 - forward) + toHex(255 - backward) + /*toHex(255 - forward - backward)*/ "00";
  speedDisplayDiv.innerHTML = "Throttle: " + Math.round(x * 100) + "%";

  fetch("/move", {
    method: "POST",
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({"throttle": x.toString()})
  })
});

depth.subscribe(function(x) {
  console.log("Dive throttle: ", x);
  var forward = Math.floor(Math.max(x, 0) * 255);
  var backward = Math.floor(Math.max(-x, 0) * 255);
  diveColorDiv.style.backgroundColor = "#" + toHex(255 - forward) + toHex(255 - backward) + /*toHex(255 - forward - backward)*/ "00";
  diveDisplayDiv.innerHTML = "Dive throttle: " + Math.round(x * 100) + "%";

  fetch("/dive", {
    method: "POST",
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({"throttle": x.toString()})
  })
});

steering.subscribe(function(x) {
  //console.log("Angle: ", angle);
  var deg = x * 135;
  steeringImg.style.webkitTransform = 'rotate('+deg+'deg)';
  steeringImg.style.mozTransform    = 'rotate('+deg+'deg)';
  steeringImg.style.msTransform     = 'rotate('+deg+'deg)';
  steeringImg.style.oTransform      = 'rotate('+deg+'deg)';
  steeringImg.style.transform       = 'rotate('+deg+'deg)';
});

heading.subscribe(function(x) {
  var angle = getAngle(x * Math.PI, 0, Math.PI);
  var deg = getAngle(x * 180, 0, 180);
  console.log("Angle: ", angle);
  headingImg.style.webkitTransform = 'rotate('+deg+'deg)';
  headingImg.style.mozTransform    = 'rotate('+deg+'deg)';
  headingImg.style.msTransform     = 'rotate('+deg+'deg)';
  headingImg.style.oTransform      = 'rotate('+deg+'deg)';
  headingImg.style.transform       = 'rotate('+deg+'deg)';
  headingDisplayDiv.innerHTML = "Target heading: " + Math.round(deg) + "°";

  fetch("/yaw", {
    method: "POST",
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({"angle": angle.toString()})
  })
});
