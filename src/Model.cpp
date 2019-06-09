#include "Model.h"
#include <Vector3.h>
#define NULL 0
#define INFINITE 0xFFFFFFFF

Model::Model()
{
    modelSize = 0;
    triangles = NULL;
}

Model::~Model()
{
    delete triangles;
}
