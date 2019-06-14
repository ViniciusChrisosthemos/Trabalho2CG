#ifndef BULLET_H
#define BULLET_H

#include <Object.h>
#include <Vector3.h>

class Bullet : public Object
{
    public:
        float speed;
        int damage;
        Vector3 alfa;

        Bullet();
        void Update(float deltaTime);
        void SetBullet(float angle, Vector3 position, Vector3 target, Model &model,float deltaTime);
        virtual ~Bullet();

    protected:

    private:
};

#endif // BULLET_H
