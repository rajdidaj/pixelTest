
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
Phys phys;

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
        phys.addPhysObj(&dude.ch);

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // Erase previous frame
        Clear(G_BGCOLOR);

        // Check for keypresses at least every millisecond
        Key keys[] = { A, LEFT, D, RIGHT, SPACE };
        for (int k = 0; k < sizeof(keys) / sizeof(Key); k++)
        {
            static bool jumpLatch = false;
            static int jumpCtr = 0;
            bool jump = false;

            HWButton key = GetKey(keys[k]);
            if (fElapsedTime >= 0.001)
            {
                switch (k)
                {
                case 0: case 1:
                    if (key.bPressed || key.bHeld)
                    {
                        dude.moveBack();
                    }
                    break;

                case 2: case 3:
                    if (key.bPressed || key.bHeld)
                    {
                        dude.moveForward();
                    }
                    break;

                case 4:
                    if (key.bPressed && !jumpLatch)
                    {
                        jumpLatch = true;
                        jump = true;
                    }
                    else if (key.bReleased && jumpLatch)
                    {
                        jumpLatch = false;
                    }

                    if (jump && (jumpCtr < 2))
                    {
                        dude.moveJump();                        
                        jumpCtr++;
                    }
                    else if (dude.ch.yAcc == 0.0)
                    {
                        jumpCtr = 0;
                    }
                    break;

                default:
                    break;
                }
            }
        }


        phys.run(fElapsedTime);
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