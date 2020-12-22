#include "dude.h"
#define G_DUDEPATH          "resources/dude.png"
#define G_DUDEHEIGHT        32
#define G_DUDEWIDTH         32

// Constructor
Dude::Dude(void)
{
    setPixelScale(1, 1);
    setPos(0, 0);
    ch.h = G_DUDEHEIGHT;
    ch.w = G_DUDEWIDTH;
}

void Dude::init(olc::PixelGameEngine* engine_p, int x, int y)
{
    engine = engine_p;

    ch.xMax = engine->ScreenWidth() - (G_DUDEWIDTH * ch.xScale);
    ch.yMax = engine->ScreenHeight() - (G_DUDEHEIGHT * ch.yScale) * 2;
    ch.xAcc = 0.0;
    ch.yAcc = 0.0;

    setPixelScale(x, y);

    sprite.LoadFromFile(G_DUDEPATH, NULL);
    setPos(0, ch.yMax);

}

void Dude::draw(void)
{
    engine->DrawSprite(ch.x, ch.y, &sprite);
}

void Dude::setPos(int x, int y)
{
    ch.x = x;
    ch.y = y;
}

void Dude::setPixelScale(int x, int y)
{
    ch.xScale = x;
    ch.yScale = y;
}

void Dude::moveForward()
{
    setPos(ch.x + 1, ch.y);
}

void Dude::moveBack()
{
    setPos(ch.x - 1, ch.y);
}

void Dude::moveJump()
{
    ch.yAcc = 5;
}