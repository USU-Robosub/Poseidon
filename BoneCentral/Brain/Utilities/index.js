/**
 * Created by Nathan Copier on 4/28/2016.
 */

var $ = require("jquery-deferred");

module.exports = {

    Wait: function(duration) {
        return function(args){
            return new $.Deferred(function(deferred){
                setTimeout(function(){
                    deferred.resolve(args);
                }, duration)
            });
        };
    },

    Promises: {
        Deferred: $.Deferred,
        WhenAll: $.when
    }
};