// - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//                       DiveMaster                      //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - //

function DiveMaster() {
	this.NEUTRAL = 0;
	this.FULL_AHEAD = 0.99;
	this.FULL_REVERSE = -0.99;

	this.setForwardThrust = function(velocity) {
		console.log("setForwardThrust " + velocity);
	};
	this.setDiveThrust = function(velocity) {
		console.log("setDiveThrust " + velocity);
	};
	this.setStrafeThrust = function(velocity) {
		console.log("setStrafeThrust " + velocity);
	};
	this.setYawThrust = function(velocity) {
		console.log("setYawThrust " + velocity);
	};
}

module.exports = DiveMaster;




// - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//                        Sockets                        //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - //

var net = require('net');
var client = new net.Socket();

client.connect(5080, '0.0.0.0', function() {
	console.log('Connected');
	// TODO: Server Commands
	client.write('Hello, server! Love, Client.');
});

client.on('data', function(data) {
	// TODO: Server Messages
	console.log('Received: ' + data);
});

client.on('close', function() {
	console.log('Connection closed');
	// client.destroy();
});

client.on('error', function(e){});

console.log("Ready!");