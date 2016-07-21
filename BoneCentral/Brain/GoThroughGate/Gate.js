/**
 * Created by floris on 7/14/16.
 */

module.exports = (function () {

    function Gate(poles) {
        this._poleCount = poles.length;
        if (poles.length === 1) {
            _constructFromOnePole.call(this, poles[0]);
        }
        else if (poles.length === 2) {
            _constructFromTwoPoles.call(this, poles[0], poles[1]);
        }
        else {
            this._leftPole = this._rightPole = this._gateCenter = null;
        }
    }

    var _constructFromOnePole = function (pole) {
        this._gateCenter = null;
        var poleCenter = _calculatePoleCenter(pole);
        if (poleCenter.X < 0) {
            this._leftPole = poleCenter;
            this._rightPole = null;
        }
        else {
            this._leftPole = null;
            this._rightPole = poleCenter;
        }
    };

    var _constructFromTwoPoles = function (pole1, pole2) {
        if (pole1.X < pole2.X) {
            this._leftPole = pole1;
            this._rightPole = pole2;
        }
        else {
            this._leftPole = pole2;
            this._rightPole = pole1;
        }
        this._gateCenter = _calculateGateCenter(pole1, pole2);
    };

    var _calculateGateCenter = function(poleLeft, poleRight) {
        var left = _calculatePoleCenter(poleLeft);
        var right = _calculatePoleCenter(poleRight);
        var xTotal = (+left.X) + (+right.X);
        var yTotal = (+left.Y) + (+right.Y);
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

    Gate.prototype.getRightPole = function () {
        return this._rightPole;
    };

    Gate.prototype.getPoleCount = function () {
        console.log("Pole Count: " + this._poleCount);
        return this._poleCount;
    };

    Gate.prototype.getOffsetFrom = function (gate) {
        var thisPole = this._leftPole || this._rightPole;
        var leftOffset = thisPole.X - gate.getLeftPole().X;
        var rightOffset = thisPole.X - gate.getRightPole().X;
        if (Math.abs(leftOffset) < Math.abs(rightOffset)) return leftOffset;
        return rightOffset;
    };

    return Gate;

})();