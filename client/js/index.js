
var net = new WebTCP('localhost', 9999);
setTimeout(function () {
    var val = $("#sidebar textarea").val();
    if (net.ready)
        $("#sidebar textarea").val("Client software is ready.\n" + val);
    else
        $("#sidebar textarea").val("init.sh is not running!\n" + val);
}, 500);

// standard socket options
options = {
    encoding: "utf-8",
    timeout: 0,
    noDelay: true, // disable/enable Nagle algorithm
    keepAlive: true, //default is false
    initialDelay: 0 // for keepAlive. default is 0
}

// Create a socket
var ip = $("#connection input").val();
if (ip == undefined || ip == "")
    ip = "localhost";
var socket = net.createSocket(ip, 4322, options);

setTimeout(function () {
    var jsonData = {};
    jsonData['effect'] = "network";
    jsonData['action'] = "ping";
    socket.write(JSON.stringify(jsonData));
}, 750);



// https://stackoverflow.com/questions/770523/escaping-strings-in-javascript
String.prototype.addSlashes = function() {
   return this.replace(/[\\"']/g, '\\$&').replace(/\u0000/g, '\\0');
}



// On connection callback
socket.on('connect', function(){
    var val = $("#sidebar textarea").val();
    $("#sidebar textarea").val("TCP connection established.\n" + val);
    $("#connection button").css({ "background-color": "green" });
    $("#connection button").val("Connected");
});

// This gets called every time new data for this socket is received
socket.on('data', function(data) {
    data = data.trim();
    console.log("Client received: \"" + data + "\"");

    var obj = JSON.parse(data);
    if (obj['return'] != "pong") {
        var val = $("#sidebar textarea").val();
        if (obj['return'] == "sensors")
            $("#sidebar textarea").val(obj['sampleSensor'] + "\n" + val);
        else
            $("#sidebar textarea").val(obj['return'] + "\n" + val);
    }
});

socket.on('end', function(data) {
    var val = $("#sidebar textarea").val();
    $("#sidebar textarea").val(val + "Sub connection closed.\n");
    $("#connection button").css({ "background-color": "red" });
    $("#connection button").val("Connect");
});




//make forward slider
$("#forwardThrust .slider").slider({
    max: 1,
    min: -1,
    step: 0.025,
    slide: function(event, ui) {
        $("#forwardThrust label span").html(ui.value);

        var jsonData = {};
        jsonData['effect'] = "thrust";
        jsonData['action'] = "set forward";
        jsonData['value'] = ui.value;

        console.log(jsonData);
        socket.write(JSON.stringify(jsonData));
    }
});

//make panning slider
$("#panThrust .slider").slider({
    max: 1,
    min: -1,
    step: 0.025,
    slide: function(event, ui) {
        $("#panThrust label span").html(ui.value);

        var jsonData = {};
        jsonData['effect'] = "thrust";
        jsonData['action'] = "set pan";
        jsonData['value'] = ui.value;

        console.log(jsonData);
        socket.write(JSON.stringify(jsonData));
    }
});

//make diving slider
$("#diveThrust .slider").slider({
    max: 1,
    min: -1,
    step: 0.025,
    slide: function(event, ui) {
        $("#diveThrust label span").html(ui.value);

        var jsonData = {};
        jsonData['effect'] = "thrust";
        jsonData['action'] = "set dive";
        jsonData['value'] = ui.value;

        console.log(jsonData);
        socket.write(JSON.stringify(jsonData));
    }
});

//make yaw slider
$("#yawThrust .slider").slider({
    max: 1,
    min: -1,
    step: 0.025,
    slide: function(event, ui) {
        $("#yawThrust label span").html(ui.value);

        var jsonData = {};
        jsonData['effect'] = "thrust";
        jsonData['action'] = "set yaw";
        jsonData['value'] = ui.value;

        console.log(jsonData);
        socket.write(JSON.stringify(jsonData));
    }
});



$("#connection button").click(function() {
    var ip = $("#connection input").val();
    if (ip == undefined || ip == "")
        ip = "localhost";

    socket = net.createSocket(ip, 4322, options);
    console.log(socket);
});

$("#sensors #get").click(function() {

    var jsonData = {};
    jsonData['effect'] = "get";
    jsonData['action'] = "sensors";

    console.log(jsonData);
    socket.write(JSON.stringify(jsonData));
});
/*
$("#sensors #speed").click(function() {

    var jsonData = {};
    jsonData['effect'] = "power";
    jsonData['action'] = "enable power";

    console.log(jsonData);
    socket.write(JSON.stringify(jsonData));
});
*/
