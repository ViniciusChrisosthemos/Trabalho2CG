#include "Bullet.h"
#include <math.h>
#include <Model.h>
#include <stdio.h>
#define RADTODEG 0.01745329251

Bullet::Bullet(){}

void Bullet::Update(float deltaTime)
{
    position = position.Sum(alfa.Produt(speed * deltaTime));
}

void Bullet::SetBullet(float angle, Vector3 position, Vector3 target, Model &model, float deltaTime)
{
    this->model = &model;
    this->position = position;
    speed = 50.0f;
    damage = 10;

    alfa = Vector3(target.x - position.x, target.y - position.y, target.z - position.z);
    alfa = alfa.UnitVector();
}

Bullet::~Bullet()
{
    delete model;
}
