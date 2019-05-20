#include "Triangle.h"
#include <Vector3.h>
#include <ColorRGB.h>

Triangle::Triangle()
{
    normal = Vector3(0,0,0);
    color = ColorRGB(0,0,0);
}

void Triangle::SetNormal(float x, float y, float z)
{
    normal.x = x;
    normal.y = y;
    normal.z = z;
}


void Triangle::SetVertex(int v, Vector3 &vertex)
{
    vertexs[v] = vertex;
}

Triangle::~Triangle()
{

}
