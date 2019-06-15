#include "Player.h"
#define RADTODEG 0.01745329251
#include <math.h>

Player::Player(int speed)
{
    battery = 100.0f;
    batteryCost = 0.05f;
    this->speed = speed;
    target = new Vector3(0,0,1);
}

Vector3 Player::Move(float deltaTime)
{
    float alfa = speed * deltaTime;
    float angleRad = RADTODEG*angle;
    float x = sin(angleRad) * alfa;
    float z = cos(angleRad) * alfa;

    return Vector3(x,0,z);
}

void Player::Rotate(float deltaTime)
{
    angle += deltaTime * 100;
}

void Player::Charge(int charge)
{
    battery += charge;
    battery = (battery > 100) ? 100:battery;
}

void Player::TakeDamage(int damage)
{
    battery -= damage;
    if(battery <= 0) inGame = false;
}

void Player::Discharge()
{
    battery -= batteryCost;
    if(battery <= 0) inGame = false;
}

Player::~Player()
{
    //dtor
}
