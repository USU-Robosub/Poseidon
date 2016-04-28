/**
 * Created by Nathan Copier on 4/6/2016.
 */

var Streams = require('stream');
var Net = require('net');

module.exports.createSocket = function (port) {
    var passThrough = new Streams.PassThrough();
    Net.createServer(function (socket) {
        _handleClient(socket, passThrough);
    }).listen(port);
    return passThrough;
};

var _handleClient = function (socket, passThrough) {
    _pipeError(socket, passThrough);
    socket.pipe(passThrough);
    passThrough.pipe(socket);
};

var _pipeError = function (socket, passThrough) {
    socket.on("error", function (err) {
        if (err === "Error: read ECONNRESET") return;
        passThrough.emit("error", err)
    });
};