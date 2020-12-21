#include "phys.h"

Phys::Phys(void)
{
    physObjs.clear();
}

void Phys::addPhysObj(PhysChars_t* obj)
{
    physObjs.insert(physObjs.end(), obj);
}

// Run the physics on all physics objects
void Phys::run(float dT)
{
    list<PhysChars_t*>::iterator it;
    for (it = physObjs.begin(); it != physObjs.end(); ++it)
    {
        // Calculate physics for each object
        if ((*it)->yAcc != 0.0)
        {
            printf("Acc: %f\n", (*it)->yAcc);
            (*it)->yAcc -= (dT * 98);
            (*it)->y -= (*it)->yAcc;
        }

        if ((*it)->y <= 0)
        {
            (*it)->yAcc = 0.0;
            (*it)->y = 0;
        }
        else if( (*it)->y >= (*it)->yMax)
        {
            (*it)->yAcc = 0.0;
            (*it)->y = (*it)->yMax;
        }

    }
}