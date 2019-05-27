#include "Player.h"
#define RADTODEG 0.01745329251
#include <math.h>

Player::Player(int speed)
{
    battery = 100.0f;
    batteryCost = 5.0f;
    this->speed = speed;
    target = new Vector3(0,0,10);
}

void Player::Move(float deltaTime)
{
    float alfa = speed * deltaTime;
    float angleRad = RADTODEG*angle;
    position.x += sin(angleRad) * alfa;
    position.z += cos(angleRad) * alfa;

    target->x = position.x;
    target->z = position.z + 10;
}

void Player::Rotate(float deltaTime)
{
    angle += deltaTime * 100;
}

Player::~Player()
{
    //dtor
}
