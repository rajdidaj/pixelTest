
// O------------------------------------------------------------------------------O
// | PixelTest_c "Hello World" Program (main.cpp)                                     |
// O------------------------------------------------------------------------------O
#include "engine/olcPixelGameEngine.h"
using namespace olc;
bool fullscreenMode = true;

#include "startMenu.h"
#include "dude.h"

#define G_PIXELSCALE_X      2
#define G_PIXELSCALE_Y      2

#define G_STARPATH          "resources/star.png"
#define G_BGCOLOR           BLACK

Sprite spr;
Dude dude;

// Override base class with your custom functionality
class PixelTest_c : public PixelGameEngine
{
public:
    PixelTest_c()
    {
        // Name you application
        sAppName = "rajdidajs olcPixelTest";
    }

public:
    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        Clear(G_BGCOLOR);
        SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
        spr.LoadFromFile(G_STARPATH, NULL);

        dude.init(this, G_PIXELSCALE_X, G_PIXELSCALE_Y);

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // Erase previous frame
        Clear(G_BGCOLOR);

        // Called once per frame, draws random coloured pixels
        Key keys[] = { LEFT , RIGHT, SPACE };
        for (int k = 0; k < sizeof(keys) / sizeof(Key); k++)
        {
            HWButton key = GetKey(keys[k]);
            if ((key.bReleased || key.bHeld) && (fElapsedTime >= 0.001))
            {
                switch (k)
                {
                case 0:
                    dude.moveBack();
                    break;

                case 1:
                    dude.moveForward();
                    break;

                case 2:
                    dude.moveJump();
                    break;

                default:
                    break;
                }
            }
        }

        dude.draw();

        HWButton esc = GetKey(ESCAPE);
        if (esc.bReleased)
        {
            olc_Terminate();
        }
        return true;
    }
};


int main()
{
    uint32_t xMax = GetSystemMetrics(SM_CXSCREEN) / G_PIXELSCALE_X;
    uint32_t yMax = GetSystemMetrics(SM_CYSCREEN) / G_PIXELSCALE_Y;

    StartMenu_c config;
    if (config.Construct(xMax / 2, yMax / 3, G_PIXELSCALE_X, G_PIXELSCALE_Y, false))
    {
        config.Start();
    }

    PixelTest_c demo;

    if (fullscreenMode)
    {
        if (demo.Construct(xMax, yMax, G_PIXELSCALE_X, G_PIXELSCALE_Y, fullscreenMode))
        {
            demo.Start();
            printf("hejdå\n");
        }
    }
    else
    {
        if (demo.Construct(xMax / 2, yMax / 2, G_PIXELSCALE_X, G_PIXELSCALE_Y, fullscreenMode))
        {
            demo.Start();
        }
    }

    return 0;
}