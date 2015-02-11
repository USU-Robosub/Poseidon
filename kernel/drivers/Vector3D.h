
#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
    public:
        Vector3D(float val);
        Vector3D(float x = 0, float y = 0, float z = 0);

        void setTo(float newX, float newY, float newZ);

        void setX(float newVal);
        void setY(float newVal);
        void setZ(float newVal);

        float getX();
        float getY();
        float getZ();

    private:
        float x_, y_, z_;

};

#endif /* REGISTRY_H_ */
