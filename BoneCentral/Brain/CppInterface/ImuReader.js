/**
 * Created by Nathan Copier on 2/17/2016.
 */
var $ = require("jquery-deferred");
const util = require('util');

module.exports = (function(){

    function ImuReader(iStream, oStream){
        this._iStream = iStream;
        this._oStream = oStream;
    }

    ImuReader.prototype.getAcceleration = function () {
        var p = $.Deferred();
        var self = this;
        this._iStream.once("data", function (data) {
            p.resolve(data);
        });
        self._oStream.write("getAcceleration\n");
        return p;
    };

    return ImuReader;

})();