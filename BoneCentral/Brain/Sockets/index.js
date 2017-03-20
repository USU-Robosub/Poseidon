/**
 * Created by Nathan Copier on 4/6/2016.
 */

var Streams = require('stream');
var Net     = require('net');
var $       = require('../Utilities').Promises

module.exports.createSocket = function (port) {
    var input     = new Streams.PassThrough();
    var output    = new Streams.PassThrough();
    var onExit    = $.Deferred();
    var onConnect = $.Deferred();
    
    Net.createServer(function (socket) {
        _handleClient(socket, input, output);
        socket.on("close", function() {
            onExit.resolve();
        });
        onConnect.resolve();
    }).listen(port);
    
    return {
        Input: input,
        Output: output,
        Events: {
            OnConnect: onConnect.promise(),
            OnExit: onExit.promise()
        }
    };
};

var _handleClient = function (socket, input, output) {
    _pipeError(socket, output);
    socket.pipe(output);
    input.pipe(socket);
};

var _pipeError = function (socket, passThrough) {
    socket.on("error", function (err) {
        if (err === "Error: read ECONNRESET") return;
        passThrough.emit("error", err)
    });
};