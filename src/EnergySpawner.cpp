#include "EnergySpawner.h"
#include <Model.h>
#include <time.h>
#include <stdio.h>

EnergySpawner::EnergySpawner(){}

EnergySpawner::EnergySpawner(Model *model, Vector3 position)
{
    time(0);

    active = true;
    angle = 0.0f;
    countdown = 5;
    energyCharge = 50;
    inGame = true;
    time(&currentTime);
    nextTimeActive = currentTime;
    this->position = position;
    this->model = model;
}

void EnergySpawner::Update()
{
    if(!active)
    {
        time(&currentTime);
        if(currentTime >= nextTimeActive)
        {
            nextTimeActive = currentTime + countdown;
            active = true;
        }
    }
}

EnergySpawner::~EnergySpawner()
{
    //dtor
}
