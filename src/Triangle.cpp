#include "Triangle.h"
#include <Vector3.h>
#include <ColorRGB.h>

// **********************************************************************
// Triangle::Triangle()
// Construtor
// **********************************************************************
Triangle::Triangle()
{
    normal = Vector3(0,0,0);
    color = ColorRGB(0,0,0);
}
// **********************************************************************
// void Triangle::SetNormal(float x, float y, float z)
// Define os valores do vetor normal do triangulo
// Parametros:
//      x: valor x da normal
//      y: valor y da normal
//      z: valor z da normal
// **********************************************************************
void Triangle::SetNormal(float x, float y, float z)
{
    normal.x = x;
    normal.y = y;
    normal.z = z;
}
// **********************************************************************
// void Triangle::SetVertex(int v, Vector3 &vertex)
// Define um vertice em uma posição especifica do triangulo
// Parametros:
//      v: indice do vertice
//      vertex: vertice
// **********************************************************************
void Triangle::SetVertex(int v, Vector3 &vertex)
{
    vertexs[v] = vertex;
}
// **********************************************************************
// void Triangle::NormalizeVertexs(float offset)
// Método que normaliza os verteces do objeto, deixando-os em relação a base
// Parametros:
//      offset: quantidade necessria para deixar o objeto na base
// **********************************************************************
void Triangle::NormalizeVertexs(float offset)
{
    for(int i=0; i<3; i++)
    {
        vertexs[i].y += offset;
    }
}

// **********************************************************************
// Triangle::~Triangle()
// Desconstrutor
// **********************************************************************
Triangle::~Triangle(){}
