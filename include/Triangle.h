#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <Vector3.h>
#include <ColorRGB.h>
// **********************************************************************
//  Class Triangle
//
//  Classe que representa um triangulo
// **********************************************************************
class Triangle
{
    public:
        Vector3 vertexs[3];
        ColorRGB color;
        Vector3 normal;

        Triangle();
        void SetNormal(float x, float y, float z);
        void SetVertex(int v, Vector3 &vertex);
        void NormalizeVertexs(float offset);
        virtual ~Triangle();

    protected:

    private:
};

#endif // TRIANGLE_H
