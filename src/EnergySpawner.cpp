#include "EnergySpawner.h"
#include <Model.h>
#include <time.h>
#include <stdio.h>
// **********************************************************************
// EnergySpawner::EnergySpawner()
// Construtor
// **********************************************************************
EnergySpawner::EnergySpawner(){}
// **********************************************************************
// EnergySpawner::EnergySpawner(Model *model, Vector3 position)
// Construtor
// Parametros:
//      model: modelo do objeto para ser renderizado
//      position: posi��o do obj
// **********************************************************************
EnergySpawner::EnergySpawner(Model *model, Vector3 position)
{
    time(0);

    angle = 0.0f;
    countdown = 5;
    energyCharge = 50;
    inGame = true;
    time(&currentTime);
    nextTimeActive = currentTime;
    this->position = position;
    this->model = model;
}

// **********************************************************************
// void EnergySpawner::Update()
// Atualiza dos atributos da classe
// **********************************************************************
void EnergySpawner::Update()
{
    if(!inGame)
    {
        time(&currentTime);
        if(currentTime >= nextTimeActive)
        {
            nextTimeActive = currentTime + countdown;
            inGame = true;
        }
    }else
    {
        angle += 10.0f;
    }
}
// **********************************************************************
// EnergySpawner::~EnergySpawner()
// Desconstrutor
// **********************************************************************
EnergySpawner::~EnergySpawner(){}
