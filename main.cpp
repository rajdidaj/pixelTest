
// O------------------------------------------------------------------------------O
// | pixelTest "Hello World" Program (main.cpp)                                     |
// O------------------------------------------------------------------------------O
#define OLC_PGE_APPLICATION
#include "engine/olcPixelGameEngine.h"

#define G_PIXELSCALE_X      4
#define G_PIXELSCALE_Y      4
#define G_FULLSCREENMODE    true

using namespace olc;

// Override base class with your custom functionality
class pixelTest : public PixelGameEngine
{
public:
    pixelTest()
    {
        HWND wnd = GetActiveWindow();
        if (wnd != NULL)
        {
            printf("hej! %x\n", wnd);
        }
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

    pixelTest demo;
    if (demo.Construct(xMax, yMax, G_PIXELSCALE_X, G_PIXELSCALE_Y, G_FULLSCREENMODE))
    {
        demo.Start();
        printf("hejdå\n");
    }
    return 0;
}