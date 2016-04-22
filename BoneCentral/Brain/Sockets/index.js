/**
 * Created by Nathan Copier on 4/6/2016.
 */

var Streams = require('stream');
var Net = require('net');

module.exports.createSocket = function (port) {
    var passThrough = new Streams.PassThrough();
    Net.createServer(function (socket) {
        socket.pipe(passThrough);
        passThrough.pipe(socket);
    }).listen(port);
    return passThrough;
};