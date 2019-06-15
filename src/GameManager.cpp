#include "GameManager.h"
#include <stdio.h>
#include <math.h>

// **********************************************************************
// GameManager::GameManager()
// Construtor
// **********************************************************************
GameManager::GameManager()
{

}
// **********************************************************************
// void GameManager::SetsObjectBoundary(const Vector3* position, const Model* model)
// Defini o espaço que um objeto irá ocupar no espaço
// Parametros:
//      position: posição do objeto
//      model: modelo do objeto
// **********************************************************************
void GameManager::SetsObjectBoundary(const Vector3* position, const Model* model)
{
    int minX = (int)(position->x - model->width);
    int maxX = (int)(position->x + model->width);
    int minZ = (int)(position->z - model->depth);
    int maxZ = (int)(position->z + model->depth);

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
// **********************************************************************
// void GameManager::InitMatrix()
// Inicia a matriz de restrições espacias, usada para verificar sem um objeto
// pode se deslocar para um certo ponto
// **********************************************************************
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
// **********************************************************************
// bool GameManager::CanMove(Vector3 position)
// Verifica se a posição informada está em um local com um objeto presente
// Parametro:
//      position: ponto em que o objeto quer se deslocar
// **********************************************************************
bool GameManager::CanMove(Vector3 position)
{
    if(position.x > MAXX) return false;
    if(position.x < 0) return false;
    if(position.z > MAXZ) return false;
    if(position.z < 0) return false;
    int x = (int) position.x;
    int z = (int) position.z;

    return matrix[z][x];
}
// **********************************************************************
// GameManager::~GameManager()
// Desconstrutor
// **********************************************************************
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
