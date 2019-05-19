#ifndef OBJECT_H
#define OBJECT_H
#include <Triangle.h>
#include <Vector3.h>

// **********************************************************************
//  Class Object
//
//  Classe que representa qualquer objeto 3d no cenario
// **********************************************************************
class Object
{
    public:
        Triangle triangles[];
        int modelSize;
        float angle;
        Vector3* position;
        bool inGame;

        Object(int modelSize);
        virtual ~Object();

    protected:

    private:
};

#endif // OBJECT_H
