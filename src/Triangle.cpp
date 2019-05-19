#include "Triangle.h"
#include <Vector3.h>

Triangle::Triangle()
{
}

void Triangle::SetNormal(float x, float y, float z)
{
    normal->x = x;
    normal->y = y;
    normal->z = z;
}


void Triangle::SetVertex(int v, Vector3* vertex)
{
    vertexs[v] = vertex;
}

Triangle::~Triangle()
{
    delete [] vertexs;
    delete normal;
}
