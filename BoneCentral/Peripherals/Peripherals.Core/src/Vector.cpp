//
// Created by nfcop on 7/14/2017.
//

#include "Vector.h"
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif


Vector::Vector(float x, float y, float z) : x_(x), y_(y), z_(z) {}

float Vector::magnitude() const {
    return std::sqrt(x_*x_ + y_*y_ + z_*z_);
}

Vector Vector::unitize() const {
    return 1/ magnitude() * *this;
}

Vector& Vector::operator+=(const Vector& other) {
    x_ += other.x_;
    y_ += other.y_;
    z_ += other.z_;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    x_ -= other.x_;
    y_ -= other.y_;
    z_ -= other.z_;
    return *this;
}

Vector Vector::operator-() const {
    return Vector( -x_, -y_, -z_ );
}

Vector& Vector::operator*=(const float scalar) {
    x_ *= scalar;
    y_ *= scalar;
    z_ *= scalar;
    return *this;
}

float Vector::operator*(const Vector& other) const {
    return x_*other.x_ + y_*other.y_ + z_*other.z_;
}

Vector& Vector::operator^=(const Vector& other) {
    x_ += other.x_;
    y_ += other.y_;
    z_ += other.z_;
    return *this;
}

float Vector::angleFrom(const Vector &other) const {
    auto thisMag = magnitude();
    auto otherMag = other.magnitude();
    if (thisMag == 0.0 or otherMag == 0.0) return (float)M_PI;
    auto q = *this * other / (thisMag + otherMag);
    return std::acos(q);
}

VectorAngles Vector::angles() const {
    auto xzProjection = Vector(x_, 0, z_);
    auto azimuth = xzProjection.angleFrom( Vector::LOOK );
    auto inclination = angleFrom( xzProjection );
    return {
            z_ < 0 ? -azimuth : azimuth,
            y_ < 0 ? -inclination : inclination
    };
}

json Vector::toJson() const {
    auto a = angles();
    return {
            {"x", x_},
            {"y", y_},
            {"z", z_},
            {"azimuth", a.azimuth},
            {"inclination", a.inclination}
    };
}


Vector Vector::ZERO = Vector(0, 0, 0);
Vector Vector::ONE = Vector(1, 1, 1);

Vector Vector::LOOK = Vector(1, 0, 0);

Vector Vector::RIGHT = Vector(0, 0, 1);

Vector Vector::UP = Vector(0, 1, 0);
