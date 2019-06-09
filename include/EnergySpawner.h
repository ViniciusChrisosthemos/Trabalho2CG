#ifndef ENERGYSPAWNER_H
#define ENERGYSPAWNER_H

#include <Object.h>
#include <time.h>
#include <Vector3.h>

class EnergySpawner : public Object
{
    public:
        bool active;
        int energyCharge;
        int countdown;
        time_t nextTimeActive;
        time_t currentTime;

        EnergySpawner();
        EnergySpawner(Model *model, Vector3 position);
        void Update();
        virtual ~EnergySpawner();

    protected:

    private:
};

#endif // ENERGYSPAWNER_H
