#include "Object.h"
#include <Triangle.h>
#include <Vector3.h>
#include <Model.h>
#include <stdio.h>

Object::Object()
{
    angle = 0;
    position = Vector3(0,0,0);
    inGame = true;
}

void Object::SetObject(Vector3 pos, Model* model, float angle, float scale)
{
    position = pos;
    this->model = model;
    this->angle = angle;
    this->scale = scale;
}

void Object::SetPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

Object::~Object()
{
}
