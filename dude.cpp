#include "dude.h"
#define G_DUDEPATH          "resources/dude.png"
#define G_DUDEHEIGHT        64      // Full height of the dude
#define G_DUDEWIDTH         29      // Full width of the dude
#define G_DUDEOFFSET        33      // Offset to the empty dude template
#define G_HEALTHEIGHT       2       // Height of a health slice
#define G_DEFAULT_HP        1000

// Constructor
Dude::Dude(void)
{
    setPixelScale(1, 1);
    setPos(0, 0);
    ch.h = G_DUDEHEIGHT;
    ch.w = G_DUDEWIDTH;
    setHp(-1);
}

void Dude::init(olc::PixelGameEngine* engine_p, int x, int y)
{
    engine = engine_p;

    ch.xMax = engine->ScreenWidth() - (G_DUDEWIDTH * ch.xScale);
    ch.yMax = engine->ScreenHeight() - (G_DUDEHEIGHT * ch.yScale);
    ch.xAcc = 0.0;
    ch.yAcc = 0.0;

    setPixelScale(x, y);

    sprite.LoadFromFile(G_DUDEPATH, NULL);
    setPos(0, ch.yMax);

}

void Dude::draw(void)
{
    //engine->DrawSprite(ch.x, ch.y, &sprite);

    // Main body (full HP)
    engine->DrawPartialSprite(ch.x, ch.y, &sprite, 
        G_DUDEOFFSET, 0, G_DUDEWIDTH, G_DUDEHEIGHT);

    // Overlay the empty HP depeding on health amount
    int healthY = G_DUDEHEIGHT - (((float)G_DUDEHEIGHT / (float)G_DEFAULT_HP) * (float)hp);
    engine->DrawPartialSprite(ch.x, ch.y + healthY, &sprite,
        0, healthY, G_DUDEWIDTH, G_DUDEHEIGHT);
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

void Dude::decHp(int val)
{
    if (hp > 0)
    {
        hp -= val;
    }

    if (hp < 0)
    {
        hp = 0;
    }
}

void Dude::incHp(int val)
{
    if (hp < G_DEFAULT_HP)
    {
        hp += val;
    }

    if (hp > G_DEFAULT_HP)
    {
        hp = G_DEFAULT_HP;
    }
}

int Dude::getHp(void)
{
    return hp;
}

// Set a new HP value, a negative value will set it to default
void Dude::setHp(int newHp)
{
    if (newHp >= 0)
    {
        hp = newHp;
    }
    else
    {
        hp = G_DEFAULT_HP;
    }
}
