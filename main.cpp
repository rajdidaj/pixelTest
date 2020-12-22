
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

static void userInput(PixelGameEngine*, float);

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
        userInput(this, fElapsedTime);

        static float decTimer = 0.0;
        decTimer += fElapsedTime;
        if (decTimer >= 0.005)
        {
            decTimer = 0.0;

            dude.decHp(2);
            if (!dude.getHp())
            {
                dude.setHp(-1);
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
        //config.Start();
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

// Checks for user input on all applicable keys
static void userInput(PixelGameEngine* engine,float fElapsedTime)
{
    enum keyIndex
    {
        KEY_LEFT = 0,
        KEY_LEFT_ALTERNATIVE,
        KEY_RIGHT,
        KEY_RIGHT_ALTERNATIVE,
        KEY_JUMP,
        KEY_JUMP_ALTERNATIVE,
        KEY_BOOST,
        KEY_BOOST_ALTERNATIVE,
        
        KEY_MAX
    };
    
    static enum Key keys[KEY_MAX] = { (enum Key)0 };
    static bool initFlag = true;

    if (initFlag)
    {
        // KEY_LEFT
        keys[KEY_LEFT] = A;
        keys[KEY_LEFT_ALTERNATIVE] = LEFT;
        // KEY_RIGHT
        keys[KEY_RIGHT] = D;
        keys[KEY_RIGHT_ALTERNATIVE] = RIGHT;
        //  KEY_JUMP
        keys[KEY_JUMP] = SPACE;
        keys[KEY_JUMP_ALTERNATIVE] = UP;
        // KEY_BOOST
        keys[KEY_BOOST] = SHIFT;
        keys[KEY_BOOST_ALTERNATIVE] = X;

        initFlag = false;
    }
   
    for (int k = 0; k < KEY_MAX; k++)
    {
        static bool jumpLatch = false;
        static int jumpCtr = 0;
        bool jump = false;

        HWButton key = engine->GetKey(keys[k]);
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
}