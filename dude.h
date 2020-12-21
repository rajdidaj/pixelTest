//#pragma once

#include "engine/olcPixelGameEngine.h"

using namespace olc;

typedef struct
{
    int x;
    int xScale;
    int y;
    int yScale;

    int h;
    int w;
}DudeChars_t;

class Dude : public PixelGameEngine
{
private:
    void setPixelScale(int, int);
    DudeChars_t ch;
    Sprite sprite;
    PixelGameEngine* engine;

public:
    Dude(void);

    // Init functions
    void init(olc::PixelGameEngine*, int, int);

    // Test functions
    void setPos(int, int);

    // Control functions
    void moveForward(void);
    void moveBack(void);
    void moveJump(void);

    // Draw functions
    void draw(void);


};