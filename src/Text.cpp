#include "Text.h"

Text::Text(){}

void Text::SetText(Model* model)
{
    this->model = model;
}

void Text::Rotate(float force)
{
    angle += force;
}

Text::~Text()
{

}
