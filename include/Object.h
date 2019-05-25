#ifndef OBJECT_H
#define OBJECT_H
#include <Triangle.h>
#include <Vector3.h>
#include <Model.h>

// **********************************************************************
//  Class Object
//
//  Classe que representa qualquer objeto 3d no cenario
// **********************************************************************
class Object
{
    public:
        Vector3 position;
        Model* model;
        float angle;
        bool inGame;

        Object();
        void SetObject(Vector3 pos, Model* model, float angle);
        void Render();
        virtual ~Object();

    protected:

    private:
};

#endif // OBJECT_H
