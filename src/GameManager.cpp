#include "GameManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
    for(int z=0; z<MAXZMATRIX; z++)
    {
        delete matrixConstraints[z];
    }

    delete spawnerModel;
    delete energySpawners;
    delete matrixConstraints;
    delete models;
    delete enemyModel;
    delete enemys;
    delete objects;
    delete bulletModel;
}
