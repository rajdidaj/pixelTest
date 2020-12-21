#pragma once
#include <list>

using namespace std;

typedef struct
{
    int x;
    int xScale;
    float xAcc;

    int y;
    int yScale;
    float yAcc;

    int h;
    int w;
}PhysChars_t;

class Phys
{
private:
    list<PhysChars_t*> physObjs;

public:
    Phys(void);

    void addPhysObj(PhysChars_t*);
    void run(float);
};