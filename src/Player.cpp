#include "Player.h"
#define RADTODEG 0.01745329251
#include <math.h>

Player::Player(int speed)
{
    battery = 100.0f;
    batteryCost = 5.0f;
    this->speed = speed;
    target = new Vector3(0,1,10);
}

Vector3 Player::Move(float deltaTime)
{
    float alfa = speed * deltaTime;
    float angleRad = RADTODEG*angle;
    float x = position.x + sin(angleRad) * alfa;
    float z = position.z + cos(angleRad) * alfa;

    return Vector3(x, position.y, z);
}

void Player::Rotate(float deltaTime)
{
    angle += deltaTime * 100;
}

Player::~Player()
{
    //dtor
}
