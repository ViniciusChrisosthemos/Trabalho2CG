#include "Vector3.h"
#include <math.h>

// **********************************************************************
// Vector3::Vector3()
// Construtor
// **********************************************************************
Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}
// **********************************************************************
// Vector3::Vector3(float x, float y, float z)
// Construtor
// Parametros:
//      x: valor x do vetor
//      y: valor y do vetor
//      z: valor z do vetor
// **********************************************************************
Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
// **********************************************************************
// Vector3 Vector3::UnitVector()
// Retorna um vetor unitário com base no vetor atual da instancia
// **********************************************************************
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
// **********************************************************************
// Vector3 Vector3::Sum(const Vector3 &v)
// Retorna a soma do vetor instanciado com um vetor passado por pamametro
// Paramatros:
//      v: vetor a ser somado na instancia atual
// **********************************************************************
Vector3 Vector3::Sum(const Vector3 &v)
{
    float x = v.x + this->x;
    float y = v.y + this->y;
    float z = v.z + this->z;

    return Vector3(x,y,z);
}
// **********************************************************************
// Vector3 Vector3::Produt(float factor)
// Retorna o produto escalar da instancia com um valor
// Paramatros:
//      factor: valor a ser multiplicado no vetor
// **********************************************************************
Vector3 Vector3::Produt(float factor)
{
    return Vector3(x*factor, y*factor, z*factor);
}
// **********************************************************************
// Vector3 Vector3::ProdVector(const Vector3 &v1)
// Retorna o produto vetorial entre dois vetores, um da instancia atual e outro informado
// Parametros:
//      v1: vetor a ser calculado
// **********************************************************************
Vector3 Vector3::ProdVector(const Vector3 &v1)
{
    Vector3 prodVect;
    prodVect.x = y * v1.z - (z * v1.y);
    prodVect.y = z * v1.x - (x * v1.z);
    prodVect.z = x * v1.y - (y * v1.x);

    return prodVect;
}
// **********************************************************************
// Vector3::~Vector3()
// Desconstrutor
// **********************************************************************
Vector3::~Vector3(){}
