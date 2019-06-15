#include <EnemyShip.h>
#include <stdlib.h>
#include <time.h>
#include <Vector3.h>
#include <math.h>
#include <stdio.h>
#include <Model.h>
#define DEGTORAD 57.2957795131

// **********************************************************************
// EnemyShip()
// Construtor da Classe EnemyShip
// **********************************************************************
EnemyShip::EnemyShip()
{

}
// **********************************************************************
// void EnemyShip::SetEnemyShip(Model* model, Vector3* target, Model* bulletModel)
// Define os atributos de uma nave inimiga
// Parametros:
//      model: modelo do objeto para ser renderizado
//      target: alvo em que a nave inimiga irá perseguir
//      bulletModel: modelo do disparo da nave para ser renderizado
// **********************************************************************
void EnemyShip::SetEnemyShip(Model* model, Vector3* target, Model* bulletModel)
{
        this->target = target;
        this->model = model;
        this->bulletModel = bulletModel;
        position = Vector3(0,5,0);
        p0 = Vector3(0,5,0);
        p1 = Vector3(0,5,0);
        p2 = Vector3(0,5,0);
        p3 = Vector3(0,5,0);
        fireRate = rand()%3 + 2;
        time(NULL);
        time(&currentTime);
        nextShoot = currentTime + fireRate;
        t = 0;
        speed = rand()%3 + 3;

        MAXBULLETS = 3;
        bullets = new Bullet[MAXBULLETS];
}
// **********************************************************************
// void MoveEShip(float deltaTime)
// Move a nave inimiga, alterando o valor de t na equação da Bézire,
// se t == 1, calcula o segundo ponto e gera o terceiro com base na posição do target
// Parametros:
//      deltaTime: tempo entre cada frame para calcular o deslocamento
// **********************************************************************
void EnemyShip::MoveEShip(float deltaTime)
{
    float aux = 1-t;
    position.x = pow(aux,3)*p0.x + 3*t*pow(aux,2)*p1.x + 3*t*t*aux*p2.x + t*t*t*p3.x;
    position.y = pow(aux,3)*p0.y + 3*t*pow(aux,2)*p1.y + 3*t*t*aux*p2.y + t*t*t*p3.y;
    position.z = pow(aux,3)*p0.z + 3*t*pow(aux,2)*p1.z + 3*t*t*aux*p2.z + t*t*t*p3.z;
    t += deltaTime/speed;
    //LookToTarget();
}
// **********************************************************************
// void LookToTarget()
// Define o angulo da nave em relação ao seu target(nave do jogador)
// **********************************************************************
void EnemyShip::LookToTarget()
{
    Vector3 v1 = Vector3(target->x - position.x, 0,target->z - position.z);
    Vector3 v2 = Vector3(1, 0, 0);

    float scaleProduct = v1.x*v2.x + v1.z*v2.z;
    float module = sqrt(v1.x*v1.x + v1.z*v1.z)*sqrt(v2.x*v2.x + v2.z*v2.z);
    float newAngle = acos(scaleProduct/module) * DEGTORAD;

    angle = (target->z < position.z) ? -newAngle:newAngle;
    printf("%f %f\n", target->x, target->z);
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
// **********************************************************************
// void EnemyShip::Shoot(float deltaTime)
// Ativa uma bala(Bullet) para ser processada no cenário
// Parametros:
//      deltaTime: tempo entre cada frame para calcular o deslocamento
// **********************************************************************
void EnemyShip::Shoot(float deltaTime)
{
    for(int i=0; i<MAXBULLETS; i++)
    {
        if(!bullets[i].inGame)
        {
            bullets[i].SetBullet(angle, position, *target, bulletModel, 3.0f, deltaTime);
            break;
        }
    }
}
// **********************************************************************
// void EnemyShip::Update(float deltaTime)
// Atualiza os atributos da nave inimiga
// Parametros:
//      deltaTime: tempo entre cada frame para calcular o deslocamento
// **********************************************************************
void EnemyShip::Update(float deltaTime)
{
    MoveEShip(deltaTime);

    if(CanShoot())
    {
        Shoot(deltaTime);
    }

    for(int i=0; i<MAXBULLETS; i++)
    {
        if(bullets[i].inGame)
        {
            bullets[i].Update(deltaTime);
        }
    }
}
// **********************************************************************
// bool EnemyShip::BezieCompleted()
// Informa se a bezie da nave foi completada
// **********************************************************************
bool EnemyShip::BezieCompleted()
{
    return t >= 1.0f;
}
// **********************************************************************
// void EnemyShip::SetNewBezie(float maxX, float maxY, float maxZ)
// Recalcula a bezie com base nos limites do cenário
// Parametros:
//      maxX: valor máximo de x
//      maxY: valor máximo de y
//      maxZ: valor máximo de z
// **********************************************************************
void EnemyShip::SetNewBezie(float maxX, float maxY, float maxZ)
{
    t = 0;

    p0.x = p3.x;
    p0.y = p3.y;
    p0.z = p3.z;

    p1.x = p3.x*2.0 - p2.x;
    p1.y = p3.y*2.0 - p2.y;
    p1.z = p3.z*2.0 - p2.z;

    p2.x = rand()% (int) maxX;
    p2.y = rand()% (int) maxY+15;
    p2.z = rand()% (int) maxZ;

    srand(target->x);
    if(rand()%2 == 0)
    {
        p3.x = rand()% (int) maxX;
        p3.y = rand()% (int) maxY+15;
        p3.z = rand()% (int) maxZ;
    }else
    {
        p3.x = target->x;
        p3.y = rand()% (int) maxY+15;
        p3.z = target->z;
    }
}

// **********************************************************************
// ~EnemyShip()
// Desconstrutor da Classe EnemyShip
// **********************************************************************
EnemyShip::~EnemyShip(){}
