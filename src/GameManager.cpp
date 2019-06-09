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

    delete matrixConstraints;
    delete models;
    delete objects;
}
