/**
 * Created by Nathan Copier on 4/28/2016.
 */

var $ = require("jquery-deferred");

module.exports = {

    Wait: function (milliseconds) {
        var waitDeferred = $.Deferred();
        setTimeout(waitDeferred.resolve, milliseconds);
        return waitDeferred.promise();
    },

    Promise: $.Deferred
};