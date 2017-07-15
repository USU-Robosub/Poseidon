//
// Created by nfcop on 7/14/2017.
//

#ifndef PERIPHERALS_VECTOR_H
#define PERIPHERALS_VECTOR_H

#include <math.h>
#include <json.h>
using json = nlohmann::json;

struct VectorAngles {
    double azimuth;
    double inclination;
};

class Vector {

private:
    double x_, y_, z_;

public:
    Vector(double x, double y, double z) : x_(x) {}

    double magnitude() const;

    Vector unitize() const;

    Vector& operator+=(const Vector& other);

    Vector& operator-=(const Vector& other);

    Vector operator-() const;

    Vector& operator*=(const double scalar);

    /**
     * Dot Product Operator
     * @param other
     * @return
     */
    double operator*(const Vector& other) const;

    /**
     * Cross Product Operator
     * @param other
     * @return
     */
    Vector& operator^=(const Vector& other);

    /**
     *
     * @param other
     * @return the magnitude of the angle between the two vectors in radians
     */
    double angleFrom(const Vector& other) const;

    /**
     *
     * @return azimuth and inclination of the vector in radians
     */
    VectorAngles angles() const;

    json toJson() const;


    /**
     * <0, 0, 0>
     */
    static Vector ZERO = Vector(0, 0, 0);
    /**
     * <1, 1, 1>
     */
    static Vector ONE = Vector(1, 1, 1);
    /**
     * <1, 0, 0>
     */
    static Vector LOOK = Vector(1, 0, 0);
    /**
     * <0, 0, 1>
     */
    static Vector RIGHT = Vector(0, 0, 1);
    /**
     * <0, 1, 0>
     */
    static Vector LEFT = Vector(0, 1, 0);

};

inline Vector operator+(Vector left, const Vector& right) {
    left += right;
    return left;
}

inline Vector operator-(Vector left, const Vector& right) {
    left -= right;
    return left;
}

inline Vector operator*(Vector base, const double scalar) {
    base *= scalar;
    return base;
}

/**
 * Dot Product Operator
 * @param other
 * @return
 */
inline Vector operator*(const double scalar, Vector base) {
    base *= scalar;
    return base;
}

/**
 * Cross Product Operator
 * @param other
 * @return
 */
inline Vector operator^(Vector left, const Vector& right) {
    left ^= right;
    return left;
}

#endif //PERIPHERALS_VECTOR_H
