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
        Object gameoverObject;
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
        int WIDTHSCREEN = 50;
        int HEIGHTSCREEN = 200;

        GameManager();
        void LoadScenario(char* fileName);
        void DrawScenario();
        void SetsObjectBoundary(const Vector3* position, const Model* model);
        bool CanMove(Vector3 position);
        void InitMatrix();
        virtual ~GameManager();

    protected:

    private:
};

#endif // GAMEMANAGER_H
