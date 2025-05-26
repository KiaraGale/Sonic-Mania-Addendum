// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: UFO_HUD Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectUFO_HUD *UFO_HUD;

void UFO_HUD_Update(void)
{
    RSDK_THIS(UFO_HUD);

    if (self->scale.x > 0x200) {
        self->scale.x -= 0x10;
        self->scale.y -= 0x10;

        if (self->scale.x <= 0x200) {
            int32 cnt = 32 * UFO_Setup->machPoints / UFO_Setup->machQuotas[UFO_Setup->machLevel];
            RSDK.CopyPalette(self->machPaletteBank, 96, 0, 96, cnt);
            RSDK.CopyPalette(1, cnt + 96, 0, cnt + 96, (uint8)(32 - cnt));
        }
        else {
            RSDK.SetLimitedFade(0, 1, 4, self->scale.x - 0x200, 96, 127);
        }
    }

    if (self->timer > 0)
        self->timer--;

    if (UFO_Setup->rings <= 0 || UFO_Setup->rings >= 10)
        self->showRingCount = true;
    else
        self->showRingCount = (UFO_Setup->timer >> 3) & 1;
}

void UFO_HUD_LateUpdate(void) {}

void UFO_HUD_StaticUpdate(void) {}

void UFO_HUD_Draw(void)
{
    RSDK_THIS(UFO_HUD);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    Vector2 drawPos;
    drawPos.y = 0x240000;
    drawPos.x = ScreenInfo->center.x << 16;
    if (self->scale.x > 0x200)
        self->drawFX = FX_SCALE;

    RSDK.DrawSprite(&self->hudAnimator, &drawPos, true);

    for (int32 i = 0; i <= UFO_Setup->machLevel; ++i) {
        RSDK.DrawSprite(&self->stripeAnimator, &drawPos, true);
        drawPos.x += 0xA0000;
    }

    drawPos.x = ScreenInfo->center.x << 16;
    if (!(self->timer & 4) && self->timer) {
        self->machAnimator.frameID = 3;
        RSDK.DrawSprite(&self->machAnimator, &drawPos, true);
    }
    else if (!self->timer) {
        self->machAnimator.frameID = UFO_Setup->machLevel;
        RSDK.DrawSprite(&self->machAnimator, &drawPos, true);
    }

    self->drawFX = FX_NONE;
    if (self->showRingCount) {
        drawPos.x += 0x200000;
        drawPos.y = 0x250000;
        UFO_HUD_DrawNumbers(&drawPos, UFO_Setup->rings);
    }

    if (touchControls)
        UFO_HUD_DrawTouchControls();
}

void UFO_HUD_Create(void *data)
{
    RSDK_THIS(UFO_HUD);

    if (!SceneInfo->inEditor) {
        self->active          = ACTIVE_NORMAL;
        self->visible         = true;
        self->drawGroup       = 12;
        self->updateRange.x   = 0x800000;
        self->updateRange.y   = 0x800000;
        self->scale.x         = 0x200;
        self->scale.y         = 0x200;
        self->machPaletteBank = 2;

        RSDK.SetSpriteAnimation(UFO_HUD->aniFrames, 0, &self->hudAnimator, true, 0);
        RSDK.SetSpriteAnimation(UFO_HUD->aniFrames, 1, &self->numbersAnimator, true, 0);
        RSDK.SetSpriteAnimation(UFO_HUD->aniFrames, 2, &self->machAnimator, true, 0);
        RSDK.SetSpriteAnimation(UFO_HUD->aniFrames, 3, &self->stripeAnimator, true, 0);
    }
}

void UFO_HUD_StageLoad(void)
{
    UFO_HUD->aniFrames = RSDK.LoadSpriteAnimation("SpecialUFO/HUD.bin", SCOPE_STAGE);

    RSDK.ResetEntitySlot(SLOT_UFO_HUD, UFO_HUD->classID, NULL);

    UFO_HUD->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(UFO_HUD->dpadFrames, 0, &UFO_HUD->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(UFO_HUD->dpadFrames, 1, &UFO_HUD->dpadTouchAnimator, true, 0);
}

void UFO_HUD_CheckLevelUp(void)
{
    EntityUFO_HUD *hud = RSDK_GET_ENTITY(SLOT_UFO_HUD, UFO_HUD);

    if (UFO_Setup->machPoints >= UFO_Setup->machQuotas[UFO_Setup->machLevel]) {
        UFO_Setup->machPoints -= UFO_Setup->machQuotas[UFO_Setup->machLevel];

        if (UFO_Setup->machLevel >= 2) {
            ++UFO_Setup->scoreBonus;
            hud->timer = 60;
        }
        else {
            if (++UFO_Setup->machLevel == 2)
                hud->machPaletteBank = 3;
        }

        UFO_Player_ChangeMachState();

        hud->scale.x = 0x300;
        hud->scale.y = 0x300;
        RSDK.PlaySfx(UFO_Sphere->sfxMachSpeed, false, 0xFF);
    }

    if (hud->scale.x == 0x200) {
        int32 cnt = 32 * UFO_Setup->machPoints / UFO_Setup->machQuotas[UFO_Setup->machLevel];
        RSDK.CopyPalette(hud->machPaletteBank, 96, 0, 96, cnt);
        RSDK.CopyPalette(1, cnt + 96, 0, cnt + 96, (uint8)(32 - cnt));
    }
}

void UFO_HUD_LevelUpMach(void)
{
    EntityUFO_HUD *hud    = RSDK_GET_ENTITY(SLOT_UFO_HUD, UFO_HUD);
    // UFO_Setup->machPoints = 0;

    if (UFO_Setup->machLevel >= 2) {
        ++UFO_Setup->scoreBonus;
        hud->timer = 60;
    }
    else {
        if (++UFO_Setup->machLevel == 2)
            hud->machPaletteBank = 3;
    }

    UFO_Player_ChangeMachState();

    hud->scale.x = 0x300;
    hud->scale.y = 0x300;
    RSDK.PlaySfx(UFO_Sphere->sfxMachSpeed, false, 255);
}

void UFO_HUD_DrawNumbers(Vector2 *drawPos, int32 value)
{
    RSDK_THIS(UFO_HUD);

    int32 mult = 1;
    for (int32 i = 0; i < 3; ++i) {
        self->numbersAnimator.frameID = value / mult % 10;
        RSDK.DrawSprite(&self->numbersAnimator, drawPos, true);
        drawPos->x -= 0x100000;
        mult *= 10;
    }
}

void UFO_HUD_DrawTouchControls(void)
{
    RSDK_THIS(UFO_HUD);

    EntityUFO_Player *player = RSDK_GET_ENTITY(SLOT_PLAYER1, UFO_Player);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    UFO_HUD->dpadPos.x = TO_FIXED(56);
    UFO_HUD->dpadPos.y = TO_FIXED(184);

    UFO_HUD->actionPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 56);
    UFO_HUD->actionPos.y = TO_FIXED(188);

    UFO_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 64);
    UFO_HUD->pausePos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * 0.625);
    self->scale.x = 0x200;
    self->scale.y = 0x200;

    bool32 enabled = player->stateInput == UFO_Player_Input_P1;
    if (enabled) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (UFO_HUD->dpadAlpha < opacity) {
                UFO_HUD->dpadAlpha += 4;
                UFO_HUD->pauseAlpha = UFO_HUD->dpadAlpha << 1;
            }

            // Draw DPad
            self->alpha                       = UFO_HUD->dpadAlpha;
            UFO_HUD->dpadAnimator.frameID = 10;
            RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->dpadPos, true);

            if (player->left) {
                self->alpha                            = opacity;
                UFO_HUD->dpadTouchAnimator.frameID = 6;
                RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->dpadPos, true);
            }
            else {
                self->alpha                       = UFO_HUD->dpadAlpha;
                UFO_HUD->dpadAnimator.frameID = 6;
                RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->dpadPos, true);
            }

            if (player->down) {
                self->alpha                            = opacity;
                UFO_HUD->dpadTouchAnimator.frameID = 9;
                RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->dpadPos, true);

                if (player->left) {
                    UFO_HUD->dpadTouchAnimator.frameID = 14;
                    RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->dpadPos, true);
                }
                else if (player->right) {
                    UFO_HUD->dpadTouchAnimator.frameID = 15;
                    RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->dpadPos, true);
                }
            }
            else {
                self->alpha                       = UFO_HUD->dpadAlpha;
                UFO_HUD->dpadAnimator.frameID = 9;
                RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->dpadPos, true);
            }

            if (player->right) {
                self->alpha                            = opacity;
                UFO_HUD->dpadTouchAnimator.frameID = 7;
                RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->dpadPos, true);
            }
            else {
                self->alpha                       = UFO_HUD->dpadAlpha;
                UFO_HUD->dpadAnimator.frameID = 7;
                RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->dpadPos, true);
            }

            if (player->up) {
                self->alpha                            = opacity;
                UFO_HUD->dpadTouchAnimator.frameID = 8;
                RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->dpadPos, true);

                if (player->left) {
                    UFO_HUD->dpadTouchAnimator.frameID = 12;
                    RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->dpadPos, true);
                }
                else if (player->right) {
                    UFO_HUD->dpadTouchAnimator.frameID = 13;
                    RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->dpadPos, true);
                }
            }
            else {
                self->alpha                       = UFO_HUD->dpadAlpha;
                UFO_HUD->dpadAnimator.frameID = 8;
                RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->dpadPos, true);
            }

            if (!player->up && !player->down && !player->left && !player->right) {
                self->alpha                       = UFO_HUD->dpadAlpha;
                UFO_HUD->dpadAnimator.frameID = 11;
                RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->dpadPos, true);
            }

            if (player->jumpHold) {
                self->alpha                            = opacity;
                UFO_HUD->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->actionPos, true);
            }
            else {
                self->alpha                       = UFO_HUD->dpadAlpha;
                UFO_HUD->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->actionPos, true);
            }
        }
        else {
            UFO_HUD->dpadAlpha  = 0;
            UFO_HUD->pauseAlpha = 0;
        }

        self->alpha                            = UFO_HUD->pauseAlpha;
        UFO_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->pausePos, true);
    }
    else {
        if (UFO_HUD->dpadAlpha > 0) {
            UFO_HUD->dpadAlpha -= 4;
            UFO_HUD->pauseAlpha -= 8;
        }

        self->alpha = UFO_HUD->dpadAlpha;
        if (self->alpha > 0) {
            UFO_HUD->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->dpadPos, true);

            UFO_HUD->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&UFO_HUD->dpadAnimator, &UFO_HUD->actionPos, true);
        }

        if (UFO_HUD->pauseAlpha < 0)
            self->alpha = 0;
        else
            self->alpha = UFO_HUD->pauseAlpha;

        UFO_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&UFO_HUD->dpadTouchAnimator, &UFO_HUD->pausePos, true);
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

int32 UFO_HUD_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy)
{
    if (fx)
        *fx = 0;
    if (fy)
        *fy = 0;

    for (int32 t = 0; t < TouchInfo->count; ++t) {
        int32 tx = (int32)(TouchInfo->x[t] * ScreenInfo->size.x);
        int32 ty = (int32)(TouchInfo->y[t] * ScreenInfo->size.y);

        if (TouchInfo->down[t]) {
            if (tx >= x1 && ty >= y1 && tx <= x2 && ty <= y2) {
                if (fx)
                    *fx = tx;
                if (fy)
                    *fy = ty;

                return t;
            }
        }
    }

    return -1;
}

#if GAME_INCLUDE_EDITOR
void UFO_HUD_EditorDraw(void) {}

void UFO_HUD_EditorLoad(void) {}
#endif

void UFO_HUD_Serialize(void) {}
