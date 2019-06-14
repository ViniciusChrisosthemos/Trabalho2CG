#ifndef PLAYER_H
#define PLAYER_H

#include <Object.h>
#include <Vector3.h>

class Player : public Object
{
    public:
        float battery;
        float batteryCost;
        int speed;
        Vector3* target;

        Player(int speed);
        void Move(float deltaTime);
        void Rotate(float deltaTime);
        virtual ~Player();

    protected:

    private:
};

#endif // PLAYER_H
