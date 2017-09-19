/**
 * Created by Nathan Copier on 4/28/2016.
 */

var utilities = require("../Utilities/index");

module.exports = {init: function () {

    function BumpBuoy() {
    }

    BumpBuoy.prototype.execute = function () {
        this._deferred = utilities.Promises.Deferred();
        this._deferred.resolve();
        return this._deferred;
    };

    BumpBuoy.prototype.kill = function () { };

    return BumpBuoy;

}};
