#include "Triangle.h"
#include <Vector3.h>

Triangle::Triangle(Vector3* v1, Vector3* v2, Vector3* v3)
{
    vertexs[0] = v1;
    vertexs[1] = v2;
    vertexs[2] = v3;
}

void Triangle::SetNormal(float x, float y, float z)
{
    normal->x = x;
    normal->y = y;
    normal->z = z;
}

Triangle::~Triangle()
{
    delete [] vertexs;
    delete normal;
}
