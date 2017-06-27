/**
 * Created by Nathan Copier on 4/28/2016.
 */

var utilities = require("../Utilities/index");

module.exports = {init: function () {

    function SurfaceAtPinger() {
    }

    SurfaceAtPinger.prototype.execute = function () {
        this._deferred = utilities.Promises.Deferred();
        this._deferred.resolve();
    };

    SurfaceAtPinger.prototype.kill = function () { };

    return SurfaceAtPinger;

}};
