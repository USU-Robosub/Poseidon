//
// Created by nfcopier on 7/14/2017.
//

#ifndef PERIPHERALS_VECTOR_H
#define PERIPHERALS_VECTOR_H

#include <math.h>
#include <json.h>
using json = nlohmann::json;

struct VectorAngles {
    float azimuth;
    float inclination;
};

class Vector {

private:
    float x_, y_, z_;

public:
    Vector(float x, float y, float z);

    float X() const { return x_; }
    float Y() const { return y_; }
    float Z() const { return z_; }

    float magnitude() const;

    Vector unitize() const;

    Vector& operator+=(const Vector& other);

    Vector& operator-=(const Vector& other);

    Vector operator-() const;

    Vector& operator*=(const float scalar);

    /**
     * Dot Product Operator
     * @param other
     * @return
     */
    float operator*(const Vector& other) const;

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
    float angleFrom(const Vector& other) const;

    /**
     *
     * @return azimuth and inclination of the vector in radians
     */
    VectorAngles angles() const;

    json toJson() const;


    /**
     * <0, 0, 0>
     */
    static Vector ZERO;
    /**
     * <1, 1, 1>
     */
    static Vector ONE;
    /**
     * <1, 0, 0>
     */
    static Vector LOOK;
    /**
     * <0, 0, 1>
     */
    static Vector RIGHT;
    /**
     * <0, 1, 0>
     */
    static Vector UP;

};

inline Vector operator+(Vector left, const Vector& right) {
    left += right;
    return left;
}

inline Vector operator-(Vector left, const Vector& right) {
    left -= right;
    return left;
}

inline Vector operator*(Vector base, const float scalar) {
    base *= scalar;
    return base;
}

/**
 * Dot Product Operator
 * @param other
 * @return
 */
inline Vector operator*(const float scalar, Vector base) {
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
