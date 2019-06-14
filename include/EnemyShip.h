#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include <Object.h>
#include <time.h>
#include <Vector3.h>
#include <Model.h>
#include <Bullet.h>

class EnemyShip : public Object
{
    public:
        Vector3 p0;
        Vector3 p1;
        Vector3 p2;
        Vector3 p3;
        Vector3* target;
        Bullet* bullets;
        Model* bulletModel;
        int MAXBULLETS;
        float fireRate;
        float t;
        float speed;
        time_t nextShoot;
        time_t currentTime;

        EnemyShip();
        void SetEnemyShip(Model* model, Vector3* target, Model* bulletModel);
        void MoveEShip(float deltaTime);
        bool BezieCompleted();
        void SetNewBezie(float maxX, float maxY, float maxZ);
        void LookToTarget();
        bool CanShoot();
        void Shoot(float deltaTime);
        void Update(float deltaTime);
        virtual ~EnemyShip();

    protected:

    private:
};

#endif // ENEMYSHIP_H
