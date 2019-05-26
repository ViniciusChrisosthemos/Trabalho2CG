#ifndef PLAYER_H
#define PLAYER_H

#include <Object.h>


class Player : public Object
{
    public:
        int speed;

        Player(int speed);
        void Move(float deltaTime);
        void Rotate(float deltaTime);
        virtual ~Player();

    protected:

    private:
};

#endif // PLAYER_H
