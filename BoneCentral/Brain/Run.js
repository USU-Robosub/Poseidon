/**
 * Created by floris on 6/29/17.
 */

utilities = require("./Utilities");

module.exports = {init: function (GoThroughGate, BumpBuoy, SurfaceAtPinger) {


    function Run(thrustController) {
        this._thrustController = thrustController;
        this._thrustController.start();
        this._createTasks();
    }

    Run.prototype._createTasks = function () {
        this._goThroughGate = new GoThroughGate(this._thrustController);
        this._bumpBuoy = new BumpBuoy(this._thrustController);
        this._surfaceAtPinger = new SurfaceAtPinger(this._thrustController);
    };

    Run.prototype.execute = function () {
        this._thrustController.configureTimeDelta( 100 );
        utilities.Wait(50).then(function () {
            console.log("Going through gate");
            return this._goThroughGate.execute();
        }.bind(this)).then(function () {
            console.log("Bumping a buoy");
            return this._bumpBuoy.execute();
        }.bind(this)).then(function () {
            console.log("Surfacing at pinger");
            return this._surfaceAtPinger.execute();
        }.bind(this)).then(function () {
            console.log("Run cleared!")
            this._isDead = true;
            return this._thrustController.kill();
        }.bind(this));
    };

    Run.prototype.kill = function () {
        if (this._isDead) return;
        this._killTasks();
        this._thrustController.kill();
    };

    Run.prototype._killTasks = function () {
        this._goThroughGate.kill();
        this._bumpBuoy.kill();
        this._surfaceAtPinger.kill();
    };

    return Run;

}};