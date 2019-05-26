#include "Player.h"
#define RADTODEG 0.01745329251
#include <math.h>

Player::Player(int speed)
{
    this->speed = speed;
}

void Player::Move(float deltaTime)
{
    float alfa = speed * deltaTime;
    float angleRad = RADTODEG*angle;
    position.x += cos(angleRad) * alfa;
    position.z += sin(angleRad) * alfa;
}

void Player::Rotate(float deltaTime)
{
    angle += deltaTime * 100;
}

Player::~Player()
{
    //dtor
}
