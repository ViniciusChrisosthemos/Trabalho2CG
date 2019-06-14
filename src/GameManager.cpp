#include "GameManager.h"
#include <stdio.h>
#include <math.h>

GameManager::GameManager()
{

}

void GameManager::SetsObjectBoundary(const Object* obj)
{
    int minX = (int)(obj->position.x - obj->model->width);
    int maxX = (int)(obj->position.x + obj->model->width);
    int minZ = (int)(obj->position.z - obj->model->depth);
    int maxZ = (int)(obj->position.z + obj->model->depth);

    minX = (minX < 0) ? 0:minX;
    minZ = (minZ < 0) ? 0:minZ;

    maxX = (maxX > MAXX) ? MAXX:maxX;
    maxZ = (maxZ > MAXZ) ? MAXZ:maxZ;

    for(int i=minZ; i<maxZ; i++)
    {
        for(int j=minX; j<maxX; j++)
        {
            matrix[i][j] = false;
        }
    }
}

void GameManager::InitMatrix()
{
    matrix = new bool*[MAXZ];
    for(int i=0; i<MAXZ; i++)
    {
         matrix[i] = new bool[MAXX];
         for(int j=0; j<MAXX; j++)
         {
             matrix[i][j] = true;
         }
    }
}

GameManager::~GameManager()
{
    delete spawnerModel;
    delete energySpawners;
    delete models;
    delete enemyModel;
    delete enemys;
    delete objects;
    delete bulletModel;
}
