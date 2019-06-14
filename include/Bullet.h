#ifndef BULLET_H
#define BULLET_H

#include <Object.h>
#include <Vector3.h>
#include <time.h>

class Bullet : public Object
{
    public:
        float speed;
        int damage;
        Vector3 alfa;
        time_t currentTime;
        time_t lifeTime;

        Bullet();
        void Update(float deltaTime);
        void SetBullet(float &angle, Vector3 &position, Vector3 &target, Model &model, float lifeTime, float &deltaTime);
        virtual ~Bullet();

    protected:

    private:
};

#endif // BULLET_H
