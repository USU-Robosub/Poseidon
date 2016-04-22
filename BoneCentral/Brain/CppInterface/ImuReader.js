/**
 * Created by Nathan Copier on 2/17/2016.
 */
const EventEmitter = require('events').EventEmitter;
const util = require('util');

module.exports = (function(){

    function ImuReader(iStream, oStream){
        EventEmitter.call(this);
        this._iStream = iStream;
        this._oStream = oStream;
    }
    util.inherits(ImuReader, EventEmitter);

    ImuReader.prototype.readData = function(){
        var self = this;
        this._iStream.once("readable", function(){
            self.emit("dataReady", JSON.parse(self.readData()));
        });
        this._oStream.write("readData\n");
    };

    return ImuReader;

})();