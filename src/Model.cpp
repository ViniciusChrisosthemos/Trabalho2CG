#include "Model.h"
#include <Vector3.h>
#define NULL 0
#define INFINITE 0xFFFFFFFF

// **********************************************************************
// Model::Model()
// Construtor
// **********************************************************************
Model::Model()
{
    modelSize = 0;
    triangles = NULL;
    scale = 1.0f;
}
// **********************************************************************
// void Model::SetScale(float scale)
// Define a escala do modelo, alterando seu envelope
// Parametros:
//      scale: escala do modelo
// **********************************************************************
void Model::SetScale(float scale)
{
    this->scale = scale;
    height = height * scale;
    width = width * scale;
    depth = depth * scale;
}
// **********************************************************************
// Model::~Model()
// Desconstrutor
// **********************************************************************
Model::~Model()
{
    delete triangles;
}
