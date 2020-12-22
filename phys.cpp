#include "phys.h"

#define OBJ(x) (*x)

Phys::Phys(void)
{
    physObjs.clear();
}

// Insert a new physics object into the list
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
        // Calculate y axis, gravity for each object
        if (OBJ(it)->yAcc != 0.0)
        {
            OBJ(it)->yAcc -= (dT * 50);
            OBJ(it)->y -= OBJ(it)->yAcc;
        }

        if (OBJ(it)->y >= OBJ(it)->yMax)
        {
            OBJ(it)->yAcc = 0.0;
            OBJ(it)->y = OBJ(it)->yMax;
        }
        //printf("Acc: %f\n", OBJ(it)->yAcc);

    }
}