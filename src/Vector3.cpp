#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::UnitVector()
{
    float module, x = this->x, y = this->y, z = this->z;

    module = sqrt(x*x + y*y + z*z);

    if(module != 0.0f)
    {
        x /= module;
        y /= module;
        z /= module;
    }

    return Vector3(x,y,z);
}

Vector3 Vector3::Sum(const Vector3 &v)
{
    float x = v.x + this->x;
    float y = v.y + this->y;
    float z = v.z + this->z;

    return Vector3(x,y,z);
}

Vector3 Vector3::Produt(float factor)
{
    return Vector3(x*factor, y*factor, z*factor);
}

Vector3::~Vector3()
{
    //dtor
}
