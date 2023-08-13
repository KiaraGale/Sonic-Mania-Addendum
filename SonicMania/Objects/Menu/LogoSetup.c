// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: LogoSetup Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectLogoSetup *LogoSetup;

void LogoSetup_Update(void)
{
    RSDK_THIS(LogoSetup);

    StateMachine_Run(self->state);

    ScreenInfo->position.x = 0x100 - ScreenInfo->center.x;
}

void LogoSetup_LateUpdate(void) {}

void LogoSetup_StaticUpdate(void) {}

void LogoSetup_Draw(void)
{
    RSDK_THIS(LogoSetup);

    StateMachine_Run(self->stateDraw);
}

void LogoSetup_Create(void *data)
{
    RSDK_THIS(LogoSetup);

    if (!SceneInfo->inEditor) {
        self->active    = ACTIVE_ALWAYS;
        self->visible   = true;
        self->drawGroup = 12;
        self->state     = sku_region == REGION_JP ? LogoSetup_State_CESAScreen : LogoSetup_State_ShowLogos;
        self->stateDraw = LogoSetup_Draw_Fade;
        self->timer     = 1024;
    }
}

void LogoSetup_StageLoad(void)
{
    LogoSetup->sfxSega = RSDK.GetSfx("Stage/Sega.wav");
    RSDK.ResetEntitySlot(0, LogoSetup->classID, NULL);
    UIPicture->aniFrames = RSDK.LoadSpriteAnimation("Logos/Logos.bin", SCOPE_STAGE);

    int32 characterColor = RSDK.Rand(1, 6);

    if (characterColor == 1) { // Sonic
        RSDK.SetPaletteEntry(0, 128, 0x0168F0);
        RSDK.SetPaletteEntry(0, 129, 0x0878F0);
        RSDK.SetPaletteEntry(0, 130, 0x1888F0);
        RSDK.SetPaletteEntry(0, 131, 0x28A8F0);
        RSDK.SetPaletteEntry(0, 132, 0x68D0F0);
        RSDK.SetPaletteEntry(0, 133, 0x98E0F0);
        RSDK.SetPaletteEntry(0, 134, 0xC8E8E0);
    }

    if (characterColor == 2) { // Tails
        RSDK.SetPaletteEntry(0, 128, 0xDC7800);
        RSDK.SetPaletteEntry(0, 129, 0xE48E00);
        RSDK.SetPaletteEntry(0, 130, 0xEC9D09);
        RSDK.SetPaletteEntry(0, 131, 0xF5B638);
        RSDK.SetPaletteEntry(0, 132, 0xF9CC71);
        RSDK.SetPaletteEntry(0, 133, 0xFDDEA0);
        RSDK.SetPaletteEntry(0, 134, 0xFEE9BD);
    }

    if (characterColor == 3) { // Knux
        RSDK.SetPaletteEntry(0, 128, 0xD00040);
        RSDK.SetPaletteEntry(0, 129, 0xE82858);
        RSDK.SetPaletteEntry(0, 130, 0xF06080);
        RSDK.SetPaletteEntry(0, 131, 0xF08088);
        RSDK.SetPaletteEntry(0, 132, 0xFAA8AE);
        RSDK.SetPaletteEntry(0, 133, 0xFDC4C7);
        RSDK.SetPaletteEntry(0, 134, 0xFED2D4);
    }

    if (characterColor == 4) { // Mighty
        RSDK.SetPaletteEntry(0, 128, 0xA83030);
        RSDK.SetPaletteEntry(0, 129, 0xC84040);
        RSDK.SetPaletteEntry(0, 130, 0xE06868);
        RSDK.SetPaletteEntry(0, 131, 0xF09098);
        RSDK.SetPaletteEntry(0, 132, 0xF8AFB4);
        RSDK.SetPaletteEntry(0, 133, 0xF9C8CB);
        RSDK.SetPaletteEntry(0, 134, 0xFCDFE0);
    }

    if (characterColor == 5) { // Ray
        RSDK.SetPaletteEntry(0, 128, 0xD0A810);
        RSDK.SetPaletteEntry(0, 129, 0xE0C020);
        RSDK.SetPaletteEntry(0, 130, 0xE8D038);
        RSDK.SetPaletteEntry(0, 131, 0xF0E078);
        RSDK.SetPaletteEntry(0, 132, 0xF6EEA2);
        RSDK.SetPaletteEntry(0, 133, 0xF9F5CD);
        RSDK.SetPaletteEntry(0, 134, 0xFBF9DF);
    }

    if (characterColor == 6) { // Amy
        RSDK.SetPaletteEntry(0, 128, 0xD336BC);
        RSDK.SetPaletteEntry(0, 129, 0xEC65C4);
        RSDK.SetPaletteEntry(0, 130, 0xF78DD7);
        RSDK.SetPaletteEntry(0, 131, 0xFABDE4);
        RSDK.SetPaletteEntry(0, 132, 0xFCD4EE);
        RSDK.SetPaletteEntry(0, 133, 0xFDE7F6);
        RSDK.SetPaletteEntry(0, 134, 0xFEF0FA);
    }

    // What... is this for...?
    // LogoSetup is never in any other stages besides category 0, scene 0 (Logos) so this should never be used...
    // However it was even updated for plus which means it has to have been some sort of dev/debug feature

    if (SceneInfo->listPos >= 3) {
        switch (SceneInfo->listPos) {
            case 3: globals->playerID = ID_SONIC; break;
            case 4: globals->playerID = ID_TAILS; break;
            case 5: globals->playerID = ID_KNUCKLES; break;
#if MANIA_USE_PLUS
            case 6: globals->playerID = ID_MIGHTY; break;
            case 7: globals->playerID = ID_RAY; break;
            case 8: globals->playerID = ID_AMY; break;
#endif
            default: break;
        }
    }
}

bool32 LogoSetup_ImageCallback(void)
{
    if (LogoSetup->timer > 120
        && (ControllerInfo->keyA.press || ControllerInfo->keyB.press || ControllerInfo->keyStart.press || LogoSetup->timer >= 300)) {
        return true;
    }

    LogoSetup->timer++;
    return false;
}

void LogoSetup_State_CESAScreen(void)
{
    RSDK_THIS(LogoSetup);

    LogoSetup->timer = 0;
#if MANIA_USE_PLUS
    RSDK.LoadImage("CESA.png", 60.0, 2.0, LogoSetup_ImageCallback);
#else
    RSDK.LoadImage("CESA.tga", 60.0, 2.0, LogoSetup_ImageCallback);
#endif

    self->timer = 1024;
    self->state = LogoSetup_State_ShowLogos;
}

void LogoSetup_State_ShowLogos(void)
{
    RSDK_THIS(LogoSetup);

    if (self->timer <= 0) {
        if (!ScreenInfo->position.y)
            RSDK.PlaySfx(LogoSetup->sfxSega, false, 0xFF);

        self->timer     = 0;
        self->state     = LogoSetup_State_FadeToNextLogos;
        self->stateDraw = StateMachine_None;
    }
    else {
        self->timer -= 16;
    }
}

void LogoSetup_State_FadeToNextLogos(void)
{
    RSDK_THIS(LogoSetup);

    if (++self->timer > 120 || (self->timer > 30 && ControllerInfo->keyStart.press)) {
        self->timer     = 0;
        self->state     = LogoSetup_State_NextLogos;
        self->stateDraw = LogoSetup_Draw_Fade;
    }
}

void LogoSetup_State_NextLogos(void)
{
    RSDK_THIS(LogoSetup);

    if (self->timer >= 1024) {
        if (ScreenInfo->position.y >= SCREEN_YSIZE) {
            ++SceneInfo->listPos;
            RSDK.LoadScene();
        }
        else {
            ScreenInfo->position.y += SCREEN_YSIZE;
            self->state     = LogoSetup_State_ShowLogos;
            self->stateDraw = LogoSetup_Draw_Fade;
            self->timer     = 0x400;
        }
    }
    else {
        self->timer += 16;
    }
}

void LogoSetup_Draw_Fade(void)
{
    RSDK_THIS(LogoSetup);

    RSDK.FillScreen(0x000000, self->timer, self->timer, self->timer);
}

#if GAME_INCLUDE_EDITOR
void LogoSetup_EditorDraw(void) {}

void LogoSetup_EditorLoad(void) {}
#endif

void LogoSetup_Serialize(void) {}
