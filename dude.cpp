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

    setPixelScale(x, y);

    sprite.LoadFromFile(G_DUDEPATH, NULL);
}

void Dude::draw(void)
{
    printf("x: %d, y: %d\n", ch.x, ch.y);
    engine->DrawSprite(ch.x, ch.y, &sprite);
}

void Dude::setPos(int x, int y)
{
    ch.x = x / ch.xScale;
    ch.y = y / ch.yScale;
}

void Dude::setPixelScale(int x, int y)
{
    ch.xScale = x;
    ch.yScale = y;
}
