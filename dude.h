#pragma once

#include "engine/olcPixelGameEngine.h"
#include "phys.h"

using namespace olc;

class Dude : public PixelGameEngine
{
private:
    PixelGameEngine* engine;
    Sprite sprite;
    int hp;

    void setPixelScale(int, int);

public:
    Dude(void);
    PhysChars_t ch;

    // Init functions
    void init(olc::PixelGameEngine*, int, int);

    // Test functions
    void setPos(int, int);

    // Control functions
    void moveForward(void);
    void moveBack(void);
    void moveJump(void);
    void decHp(int);
    void setHp(int);

    // Draw functions
    void draw();


};