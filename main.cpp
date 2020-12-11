
// O------------------------------------------------------------------------------O
// | PixelTest_c "Hello World" Program (main.cpp)                                     |
// O------------------------------------------------------------------------------O
#define OLC_PGE_APPLICATION
#include "engine/olcPixelGameEngine.h"
using namespace olc;
bool fullscreenMode = false;

#include "startMenu.h"

#define G_PIXELSCALE_X      4
#define G_PIXELSCALE_Y      4



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
        Clear(DARK_BLUE);
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // Erase previous frame
        //Clear(DARK_BLUE);

        // Called once per frame, draws random coloured pixels
        int x1 = rand() % ScreenWidth();
        int y1 = rand() % ScreenHeight();
        int x2 = rand() % ScreenWidth();
        int y2 = rand() % ScreenHeight();

        DrawLine(x1, x2, y1, y2, Pixel(rand() % 256, rand() % 256, rand() % 256), 0xffffffff);
        return true;
    }
};


int main()
{
    uint32_t xMax = GetSystemMetrics(SM_CXSCREEN) / G_PIXELSCALE_X;
    uint32_t yMax = GetSystemMetrics(SM_CYSCREEN) / G_PIXELSCALE_Y;

    StartMenu_c config;
    if (config.Construct(xMax / 3, yMax / 3, G_PIXELSCALE_X, G_PIXELSCALE_Y, false))
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
            printf("hejdå\n");
        }
    }

    return 0;
}