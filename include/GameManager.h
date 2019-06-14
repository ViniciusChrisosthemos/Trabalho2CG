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
        Model* bulletModel;
        Object* objects;
        EnergySpawner* energySpawners;
        EnemyShip* enemys;
        bool** matrix;
        int modelsCont;
        int objectsCont;
        int spawnersCont;
        int enemysCont;
        int MAXX;
        int MAXY;
        int MAXZ;
        int XMATRIX;
        int ZMATRIX;
        int sizeCell;

        GameManager();
        void LoadScenario(char* fileName);
        void DrawScenario();
        void SetsObjectBoundary(const Object* obj);
        void InitMatrix();
        virtual ~GameManager();

    protected:

    private:
};

#endif // GAMEMANAGER_H
