#include "Bullet.h"
#include <math.h>
#include <Model.h>
#include <stdio.h>
#include <stdlib.h>
#define RADTODEG 0.01745329251

Bullet::Bullet()
{
    inGame = false;
}

void Bullet::Update(float deltaTime)
{
    time(&currentTime);
    if((currentTime > lifeTime) | (position.y < -1)) inGame = false;
    else position = position.Sum(alfa.Produt(speed * deltaTime));
}

void Bullet::SetBullet(float &angle, Vector3 &position, Vector3 &target, Model *model, float lifeTime, float &deltaTime)
{
    this->model = model;
    this->position = position;
    speed = 100.0f;
    damage = 10;

    alfa = Vector3(target.x - position.x, target.y - position.y, target.z - position.z);
    alfa = alfa.UnitVector();

    time(NULL);
    time(&currentTime);
    this->lifeTime = currentTime + lifeTime;

    inGame = true;
}

Bullet::~Bullet()
{
    delete model;
}
