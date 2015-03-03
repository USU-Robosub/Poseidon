
var net = new WebTCP('localhost', 9999);

// standard socket options
options = {
    encoding: "utf-8",
    timeout: 0,
    noDelay: true, // disable/enable Nagle algorithm
    keepAlive: true, //default is false
    initialDelay: 0 // for keepAlive. default is 0
}

// Create a socket. You can specify host and port of any TCP server here
var socket = net.createSocket("localhost", 4322, options);

// On connection callback
socket.on('connect', function(){
    console.log('Socket confirmed open');
})

// This gets called every time new data for this socket is received
socket.on('data', function(data) {
    console.log(Date.now());
    console.log("Socket received: " + data);
});

socket.on('end', function(data) {
    console.log("Socket is now closed");
});


$("#go").click(function() {
    // Send data to the server
    console.log(Date.now());
    socket.write("hello world");
});
