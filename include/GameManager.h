#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <Model.h>
#include <Object.h>
#include <string>

class GameManager
{
    public:
        Model* models;
        Object* objects;
        int modelsCont;
        int objectsCont;
        int MAXX;
        int MAXY;
        int MAXZ;
        int sizeCell;

        GameManager();
        void LoadScenario(char* fileName);
        void DrawScenario();
        virtual ~GameManager();

    protected:

    private:
};

#endif // GAMEMANAGER_H
