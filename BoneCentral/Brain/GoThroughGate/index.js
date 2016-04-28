/**
 * Created by Nathan Copier on 4/28/2016.
 */
$ = require("jquery-deferred");
EventEmitter = require("events");

module.exports = function (peripheralsFactory) {
    var taskPromise = $.Deferred();
    var gateEvents = new EventEmitter();
    // FSM implemented with events
    gateEvents.on("gate:found", _travelToGate);
    gateEvents.on("gate:lost", _reAcquireGate);
    gateEvents.on("gate:passed", function () {
        taskPromise.resolve();
    });
    _searchForGate();
    return taskPromise.promise();
};

var _searchForGate = function () {
    //Begin searching for gate
};

var _reAcquireGate = function () {
    //search for gate again
};

var _travelToGate = function () {
    //travel to gate
};