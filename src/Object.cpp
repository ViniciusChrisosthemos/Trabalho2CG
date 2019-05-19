#include "Object.h"
#include <Triangle.h>
#include <Vector3.h>

Object::Object()
{
    angle = 0;
    position = new Vector3(0,0,0);
    inGame = true;
}

Object::~Object()
{
    delete position;
}
