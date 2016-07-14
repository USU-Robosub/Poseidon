/**
 * Created by floris on 7/14/16.
 */

module.exports = function () {

    function Gate(poles) {
        this._poleCount = poles.length;
        if (poles.length === 1) {
            this._gateCenter = null;
            var poleCenter = _calculatePoleCenter(poles[0]);
            if (poleCenter.X < 0) {
                this._leftPole = poleCenter;
                this._rightPole = null;
            }
            else {
                this._leftPole = null;
                this._rightPole = poleCenter;
            }
        }
        else if (poles.length === 2) {
            if (poles[0].X < poles[1].X) {
                this._leftPole = poles[0];
                this._rightPole = poles[1];
            }
            else {
                this._leftPole = poles[1];
                this._rightPole = poles[0];
            }
            this._gateCenter = _calculateGateCenter(poles);
        }
        else {
            this._leftPole = this._rightPole = this._gateCenter = null;
        }
    }

    var _calculateGateCenter = function(poleLeft, poleRight) {
        var xTotal = poleLeft.X + poleRight.X;
        var yTotal = poleLeft.Y + poleRight.Y;
        return {X: xTotal/2, Y: yTotal/2};
    };

    var _calculatePoleCenter = function (pole) {
        var xTotal = 0, yTotal = 0;
        for (var i = 0; i < 4; i++) {
            xTotal += (+pole[i].X);
            yTotal += (+pole[i].Y);
        }
        return {X: xTotal/4, Y: yTotal/4};
    };

    Gate.prototype.getGateCenter = function () {
        return this._gateCenter;
    };

    Gate.prototype.getLeftPole = function () {
        return this._leftPole;
    };

    Gate.prototype.getLeftPole = function () {
        return this._rightPole;
    };

    Gate.prototype.getPoleCount = function () {
        return this._poleCount;
    };

    Gate.prototype.getOffsetFrom = function (gate) {
        var thisPole = this._leftPole || this._rightPole;
        var leftOffset = thisPole.X - gate.getLeftPole().X;
        var rightOffset = thisPole.X - gate.getLeftPole().X;
        if (Math.abs(leftOffset) < Math.abs(rightOffset)) return leftOffset;
        return rightOffset;
    };

    return Gate;

};