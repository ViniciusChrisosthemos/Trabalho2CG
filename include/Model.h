#ifndef MODEL_H
#define MODEL_H
#include <Triangle.h>

class Model
{
    public:
        Triangle* triangles;
        float width;
        float height;
        float depth;
        float scale;
        unsigned int modelSize;

        Model();
        void SetScale(float scale);
        virtual ~Model();

    protected:

    private:
};

#endif // MODEL_H
