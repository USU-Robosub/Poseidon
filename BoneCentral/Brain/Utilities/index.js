/**
 * Created by Nathan Copier on 4/28/2016.
 */

var $ = require("jquery-deferred");
var nodeUtils = require("util");

module.exports = {

    inherits: nodeUtils.inherits,

    Wait: function (milliseconds) {
        var waitDeferred = $.Deferred();
        setTimeout(waitDeferred.resolve, milliseconds);
        return waitDeferred.promise();
    },

    Promises: {
        Deferred: $.Deferred,
        WhenAll: $.when
    }
};