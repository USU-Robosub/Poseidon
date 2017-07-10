module.exports = (function () {

    function Vector(x, y, z) {
        this._x = x;
        this._y = y;
        this._z = z;
    }

    Vector.prototype.mag = function () {
        return Math.sqrt(
            this._x * this._x +
            this._y * this._y +
            this._z * this._z
        );
    };

    Vector.prototype.cross = function(other) {
        return new Vector(
            this._y * other._z - this._z * other._y,
            this._z * other._x - this._x * other._z,
            this._x * other._y - this._y * other._x
        );
    };

    Vector.prototype.dot = function(other) {
        return  this._x * other._x +
                this._y * other._y +
                this._z * other._z;
    };

    Vector.prototype.unitize = function() {
        var magnitude = this.mag();
        return new Vector(
            this._x / magnitude,
            this._y / magnitude,
            this._z / magnitude
        );
    };

    Vector.prototype.negate = function() {
        return new Vector( -this._x, -this._y, -this._z );
    };

    Vector.prototype.add = function(other) {
        return new Vector(
            this._x + other._x,
            this._y + other._y,
            this._z + other._z
        );
    };

    Vector.prototype.scaleBy = function(scalar) {
        return new Vector(
            scalar * this._x,
            scalar * this._y,
            scalar * this._z
        );
    };

    Vector.prototype.equals = function (other, error) {
        return  _within(this._x - other._x, error) &&
                _within(this._y - other._y, error) &&
                _within(this._z - other._z, error);
    };

    var _within = function(difference, error) {
        error = error || 0;
        return -error <= difference && difference <= error
    };

    Vector.prototype.rotateAbout = function (axis) {
        var _this = this;
        return { by: function (angle) {
            return _this._rotate(axis, angle);
        }};
    };

    Vector.prototype._rotate  = function(axis, angle) {

        var c = Math.cos(angle);
        var s = Math.sin(angle);
        var u = axis.dot(this)*(1 - c);

        var scaledAxis = axis.scaleBy(u);
        var scaledVector = this.scaleBy(c);
        var scaledCross = axis.cross(this).scaleBy(s);

        return scaledAxis.add(scaledVector).add(scaledCross);
    };

    Vector.prototype.angle = function(other) {
        var thisMag = this.mag();
        var otherMag = other.mag();
        if(thisMag === 0 || otherMag === 0)
            return 180;
        var q = this.dot(other) / (thisMag * otherMag);
        return Math.acos(q);
    };

    Vector.prototype.toString = function () {
        return  "" +
            "<" +
            _sign(this._x) + this._x.toFixed(3) + "," +
            _sign(this._y) + this._y.toFixed(3) + "," +
            _sign(this._z) + this._z.toFixed(3) +
            ">";
    };

    var _sign = function (value) {
        if (value < 0) return '';
        return '+';
    };

    Vector.zero = new Vector(0, 0, 0);
    Vector.one = new Vector(1, 1, 1);
    Vector.look = new Vector(0, 0, 1);
    Vector.right = new Vector(1, 0, 0);
    Vector.up = new Vector(0, 1, 0);

    return Vector;

})();