#include "Model.h"
#define NULL 0

Model::Model()
{
    modelSize = 0;
    triangles = NULL;
}


Model::~Model()
{
    delete triangles;
}
