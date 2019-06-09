#ifndef MODEL_H
#define MODEL_H
#include <Triangle.h>

class Model
{
    public:
        Triangle* triangles;
        float width;
        float height;
        unsigned int modelSize;

        Model();
        virtual ~Model();

    protected:

    private:
};

#endif // MODEL_H
