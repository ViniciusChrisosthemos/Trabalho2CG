#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <Vector3.h>

class Triangle
{
    public:
        Vector3* vertexs[3];

        Triangle(Vector3* v1, Vector3* v2, Vector3* v3);
        virtual ~Triangle();

    protected:

    private:
};

#endif // TRIANGLE_H
