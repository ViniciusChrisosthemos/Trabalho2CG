#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <Model.h>
#include <Object.h>
#include <string>
#include <EnergySpawner.h>
#include <EnemyShip.h>
#include <Bullet.h>

class GameManager
{
    public:
        Model* spawnerModel;
        Model* models;
        Model* enemyModel;
        Model* bullet;
        Object* objects;
        EnergySpawner* energySpawners;
        EnemyShip* enemys;
        Bullet* bullets;
        char** matrixConstraints;
        int modelsCont;
        int objectsCont;
        int spawnersCont;
        int enemysCont;
        int MAXXMATRIX;
        int MAXZMATRIX;
        int sizeCell;

        GameManager();
        void LoadScenario(char* fileName);
        void DrawScenario();
        virtual ~GameManager();

    protected:

    private:
};

#endif // GAMEMANAGER_H
