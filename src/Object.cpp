#include "Object.h"
#include <Triangle.h>
#include <Vector3.h>
#include <Model.h>
#include <stdio.h>

// **********************************************************************
// Object::Object()
// Construtor
// **********************************************************************
Object::Object()
{
    angle = 0;
    position = Vector3(0,0,0);
    inGame = true;
}
// **********************************************************************
// void Object::SetObject(Vector3 pos, Model* model, float angle)
// Define um objeto
// Parametros:
//      pos: posição do objeto
//      model: modelo do objeto
//      angle: angulo do objeto
// **********************************************************************
void Object::SetObject(Vector3 pos, Model* model, float angle)
{
    position = pos;
    this->model = model;
    this->angle = angle;
}
// **********************************************************************
// void Object::SetPosition(float x, float y, float z)
// Define a posição do objeto
// Parametros:
//      x: valor do x da nova posição
//      y: valor do y da nova posição
//      z: valor do Z da nova posição
// **********************************************************************
void Object::SetPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}
// **********************************************************************
// Object::~Object()
// Desconstrutor
// **********************************************************************
Object::~Object(){}
