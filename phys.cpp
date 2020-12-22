#include "phys.h"

#define CHARS(x) (*x)

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
        if (CHARS(it)->yAcc != 0.0)
        {
            CHARS(it)->yAcc -= (dT * 50);
            CHARS(it)->y -= CHARS(it)->yAcc;
        }

        if (CHARS(it)->y >= CHARS(it)->yMax)
        {
            CHARS(it)->yAcc = 0.0;
            CHARS(it)->y = CHARS(it)->yMax;
        }
        //printf("Acc: %f\n", CHARS(it)->yAcc);

    }
}