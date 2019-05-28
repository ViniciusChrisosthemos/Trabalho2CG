#include <EnemyShip.h>
#include <stdlib.h>
#include <time.h>
#include <Vector3.h>
#include <math.h>
#include <stdio.h>
#include <Model.h>

// **********************************************************************
// EnemyShip()
// **********************************************************************
EnemyShip::EnemyShip(Model* model, Vector3* target)
{
        this->target = target;

        fireRate = rand()%3 + 2;
        time(NULL);
        time(&currentTime);
        nextShoot = currentTime + fireRate;
        t = 0;
        speed = rand()%3 + 3;
    }
// **********************************************************************
// ~EnemyShip()
// Desconstrutor da Classe EnemyShip
// **********************************************************************
EnemyShip::~EnemyShip()
{

}
// **********************************************************************
// void MoveEShip()
// Move a nave inimiga, alterando o valor de t na equação da Bézire,
// se t == 1, calcula o segundo ponto e gera o terceiro com base na posição do target
// **********************************************************************
void EnemyShip::MoveEShip(float _deltaTime)
{/*
    float aux = 1-t;
    coordinate->x = pow(aux,3)*p0->x + 3*t*pow(aux,2)*p1->x + 3*t*t*aux*p2->x + t*t*t*p3->x;
    coordinate->y = pow(aux,3)*p0->y + 3*t*pow(aux,2)*p1->y + 3*t*t*aux*p2->y + t*t*t*p3->y;
    t += 1.0 / (speed/_deltaTime);
    LookToTarget();

    if(t > 1)
    {
        t = 0;
        p0->x = p3->x;
        p0->y = p3->y;

        float nextX = p3->x*2.0 - p2->x;
        float nextY = p3->y*2.0 - p2->y;
        float x = nextX,y = nextY,m1;

        //Limita a continuação de derivada a não passar da tela
        if(nextX >= xLimit)
        {
            x = xLimit;
            m1 =  (nextY - p3->y)/ (nextX - p3->x);
            y = p3->y + (xLimit - p3->x) * m1;

        }else if(nextX <= 0)
        {
            x = 0;
            m1 = (nextY - p3->y) / (nextX - p3->x);
            y = p3->y + (0 - p3->x) * m1;
        }

        if(nextY >= yLimit)
        {
            m1 = (nextX - p3->x) / (nextY - p3->y);
            x = p3->x + (yLimit - p3->y) * m1;
            y = yLimit;
        }else if(nextY <= 0)
        {
            m1 = (nextX - p3->x) / (nextY - p3->y);
            x = p3->x + (0 - p3->y) * m1;
            y = 0;
        }

        p1->x = x;
        p1->y = y;

        p2->x = rand()%xLimit;
        p2->y = rand()%yLimit;

        if(rand()%2)
        {
            p3->x = target->x;
            p3->y = target->y;
        }else
        {
            p3->x = rand()%xLimit;
            p3->y = rand()%yLimit;
        }
    };*/
}
// **********************************************************************
// void LookToTarget()
// Define o angulo da nave em relação ao seu target(nave do jogador)
// **********************************************************************
void EnemyShip::LookToTarget()
{/*
    Position v1 = Position(target->x - coordinate->x, target->y - coordinate->y);
    Position v2 = Position(xLimit - coordinate->x, 0);

    float scaleProduct = v1.x*v2.x + v1.y*v2.y;
    float module = sqrt(v1.x*v1.x + v1.y*v1.y)*sqrt(v2.x*v2.x + v2.y*v2.y);
    float newAngle = acos(scaleProduct/module) * (180/M_PI);

    angle = (target->y < coordinate->y) ? -newAngle:newAngle;*/
}
// **********************************************************************
// void Shoot()
// Dispara uma bala no cenario
// **********************************************************************
void EnemyShip::Shoot()
{/*
    Bullet* bullet = new Bullet(new Position(coordinate->x,coordinate->y),angle,xLimit,yLimit, bulletModel);
    bullets->push_back(bullet);*/
}
// **********************************************************************
// bool CanShoot()
// Verifica se a nave pode atirar, calculo em relação ao tempo do ultimo disparo
// **********************************************************************
bool EnemyShip::CanShoot()
{
    time(&currentTime);

    if(currentTime >= nextShoot)
    {
        nextShoot = currentTime + fireRate;
        return true;
    }
    return false;
}
