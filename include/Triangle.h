#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <Vector3.h>

// **********************************************************************
//  Class Triangle
//
//  Classe que representa um triangulo
// **********************************************************************
class Triangle
{
    public:
        Vector3* vertexs[3];
        Vector3* normal;

        Triangle(Vector3* v1, Vector3* v2, Vector3* v3);
        void SetNormal(float x, float y, float z);
        virtual ~Triangle();

    protected:

    private:
};

#endif // TRIANGLE_H
