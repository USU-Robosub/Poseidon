
#include "Vector3D.h"


Vector3D::Vector3D(float val):
    x_(val), y_(val), z_(val)
{}



Vector3D::Vector3D(float x, float y, float z):
    x_(x), y_(y), z_(z)
{}



void Vector3D::setTo(float newVal)
{
    x_ = y_ = z_ = newVal;
}



void Vector3D::setTo(float newX, float newY, float newZ)
{
    setX(newX);
    setY(newY);
    setZ(newZ);
}



void Vector3D::setX(float newVal)
{
    x_ = newVal;
}



void Vector3D::setY(float newVal)
{
    y_ = newVal;
}



void Vector3D::setZ(float newVal)
{
    z_ = newVal;
}



float Vector3D::getX()
{
    return x_;
}



float Vector3D::getY()
{
    return y_;
}



float Vector3D::getZ()
{
    return z_;
}
