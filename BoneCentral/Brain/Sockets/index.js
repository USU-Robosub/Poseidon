/**
 * Created by Nathan Copier on 4/6/2016.
 */

var Streams = require('stream');
var Net = require('net');

module.exports.createSocket = function (port) {
    var input = new Streams.PassThrough();
    var output = new Streams.PassThrough();
    Net.createServer(function (socket) {
        _handleClient(socket, input, output);
    }).listen(port);
    return {Input: input, Output: output};
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