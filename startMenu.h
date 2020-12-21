// Override base class with your custom functionality

#define G_FULLSCREEN_TEXTIX     3
#define G_START_TEXTIX          5

std::string menuStr[] =
{
    "",
    "DEMOTAJM",
    "",
    "FULLSCREEN: ",
    "",
    "START!",
    "",
};

class StartMenu_c : public PixelGameEngine
{
public:
    StartMenu_c()
    {
        // Name you application
        sAppName = "rajdidajs olcStartMenu_c";
    }

public:
    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        Clear(BLACK);
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // Erase previous frame
        Clear(BLACK);

        // Called once per frame, the config menu
        const int32_t numChoices = sizeof(menuStr) / sizeof(std::string);

        vf2d textSize;
        for (int i = 0; i < numChoices; i++)
        {
            // Check for mouse clicks
            HWButton mButton = GetMouse(0);
            if (mButton.bReleased)
            {
                int32_t yPos = GetMouseY();

                // Full screen setting clicked?
                textSize = GetTextSize(menuStr[G_FULLSCREEN_TEXTIX]);
                yPos = GetMouseY();
                if (yPos >= G_FULLSCREEN_TEXTIX * (ScreenHeight() / numChoices) &&
                    yPos <= G_FULLSCREEN_TEXTIX * (ScreenHeight() / numChoices) + textSize.y)
                {
                    fullscreenMode ^= true;
                }
                
                // Start clicked?
                textSize = GetTextSize(menuStr[G_START_TEXTIX]);
                yPos = GetMouseY();
                if (yPos >= G_START_TEXTIX * (ScreenHeight() / numChoices) &&
                    yPos <= G_START_TEXTIX * (ScreenHeight() / numChoices) + textSize.y)
                {
                    olc_Terminate();
                }

            }

            if (fullscreenMode)
            {
                menuStr[G_FULLSCREEN_TEXTIX] = "FULLSCREEN: YES";
            }
            else
            {
                menuStr[G_FULLSCREEN_TEXTIX] = "FULLSCREEN: NO";
            }

            textSize = GetTextSize(menuStr[i]);
            DrawStringPropDecal(
                vf2d(ScreenWidth() / 2.0 - (textSize.x / 2.0), i * (ScreenHeight() / numChoices)),
                menuStr[i],
                Pixel(rand() % 256, rand() % 256, rand() % 256),
                vf2d(1, 1));
        }
        return true;
    }
};