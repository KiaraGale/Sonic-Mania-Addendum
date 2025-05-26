// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: BSS_HUD Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectBSS_HUD *BSS_HUD;

void BSS_HUD_Update(void) {}

void BSS_HUD_LateUpdate(void) {}

void BSS_HUD_StaticUpdate(void) {}

void BSS_HUD_Draw(void)
{
    RSDK_THIS(BSS_HUD);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls) {
        BSS_HUD_DrawTouchControls();
    }

    Vector2 drawPos;
    drawPos.x = TO_FIXED(ScreenInfo->center.x - 141);
    drawPos.y = TO_FIXED(13);
    RSDK.DrawSprite(&self->sphereAnimator, &drawPos, true);

    drawPos.x += TO_FIXED(37);
    drawPos.y = TO_FIXED(17);
    BSS_HUD_DrawNumbers(BSS_Setup->sphereCount, &drawPos);

    drawPos.x = TO_FIXED(ScreenInfo->center.x + 64);
    drawPos.y = TO_FIXED(13);
    RSDK.DrawSprite(&self->ringAnimator, &drawPos, true);

    drawPos.x += TO_FIXED(56);
    drawPos.y = TO_FIXED(17);
    BSS_HUD_DrawNumbers(BSS_Setup->ringCount, &drawPos);
}

void BSS_HUD_Create(void *data)
{
    RSDK_THIS(BSS_HUD);

    if (!SceneInfo->inEditor) {
        self->active        = ACTIVE_NORMAL;
        self->visible       = true;
        self->drawGroup     = DRAWGROUP_COUNT - 1;
        self->updateRange.x = TO_FIXED(128);
        self->updateRange.y = TO_FIXED(128);

        RSDK.SetSpriteAnimation(BSS_HUD->aniFrames, 0, &self->sphereAnimator, true, 0);
        RSDK.SetSpriteAnimation(BSS_HUD->aniFrames, 0, &self->ringAnimator, true, 1);
        RSDK.SetSpriteAnimation(BSS_HUD->aniFrames, 1, &self->numbersAnimator, true, 0);
    }
}

void BSS_HUD_StageLoad(void)
{
    BSS_HUD->aniFrames = RSDK.LoadSpriteAnimation("SpecialBS/HUD.bin", SCOPE_STAGE);

    RSDK.ResetEntitySlot(SLOT_BSS_HUD, BSS_HUD->classID, NULL);

    BSS_HUD->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(BSS_HUD->dpadFrames, 0, &BSS_HUD->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(BSS_HUD->dpadFrames, 1, &BSS_HUD->dpadTouchAnimator, true, 0);
}

void BSS_HUD_DrawNumbers(int32 value, Vector2 *drawPos)
{
    RSDK_THIS(BSS_HUD);

    int32 mult = 1;
    for (int32 i = 0; i < 3; ++i) {
        self->numbersAnimator.frameID = value / mult % 10;
        RSDK.DrawSprite(&self->numbersAnimator, drawPos, true);
        drawPos->x -= TO_FIXED(16);
        mult *= 10;
    }
}

void BSS_HUD_DrawTouchControls(void)
{
    RSDK_THIS(BSS_HUD);

    EntityBSS_Player *player = RSDK_GET_ENTITY(SLOT_PLAYER1, BSS_Player);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    BSS_HUD->dpadPos.x = TO_FIXED(56);
    BSS_HUD->dpadPos.y = TO_FIXED(184);

    BSS_HUD->actionPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 56);
    BSS_HUD->actionPos.y = TO_FIXED(188);

    BSS_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].center.x);
    BSS_HUD->pausePos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * .625);
    self->scale.x = 0x200;
    self->scale.y = 0x200;

    bool32 enabled = player->stateInput == BSS_Player_Input_P1;
    if (enabled) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (BSS_HUD->dpadAlpha < opacity) {
                BSS_HUD->dpadAlpha += 4;
                BSS_HUD->pauseAlpha = BSS_HUD->dpadAlpha << 1;
            }

            // Draw DPad
            self->alpha                       = BSS_HUD->dpadAlpha;
            BSS_HUD->dpadAnimator.frameID = 10;
            RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->dpadPos, true);

            if (player->left) {
                self->alpha                            = opacity;
                BSS_HUD->dpadTouchAnimator.frameID = 6;
                RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->dpadPos, true);
            }
            else {
                self->alpha                       = BSS_HUD->dpadAlpha;
                BSS_HUD->dpadAnimator.frameID = 6;
                RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->dpadPos, true);
            }

            if (player->down) {
                self->alpha                            = opacity;
                BSS_HUD->dpadTouchAnimator.frameID = 9;
                RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->dpadPos, true);

                if (player->left) {
                    BSS_HUD->dpadTouchAnimator.frameID = 14;
                    RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->dpadPos, true);
                }
                else if (player->right) {
                    BSS_HUD->dpadTouchAnimator.frameID = 15;
                    RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->dpadPos, true);
                }
            }
            else {
                self->alpha                       = BSS_HUD->dpadAlpha;
                BSS_HUD->dpadAnimator.frameID = 9;
                RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->dpadPos, true);
            }

            if (player->right) {
                self->alpha                            = opacity;
                BSS_HUD->dpadTouchAnimator.frameID = 7;
                RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->dpadPos, true);
            }
            else {
                self->alpha                       = BSS_HUD->dpadAlpha;
                BSS_HUD->dpadAnimator.frameID = 7;
                RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->dpadPos, true);
            }

            if (player->up) {
                self->alpha                            = opacity;
                BSS_HUD->dpadTouchAnimator.frameID = 8;
                RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->dpadPos, true);

                if (player->left) {
                    BSS_HUD->dpadTouchAnimator.frameID = 12;
                    RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->dpadPos, true);
                }
                else if (player->right) {
                    BSS_HUD->dpadTouchAnimator.frameID = 13;
                    RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->dpadPos, true);
                }
            }
            else {
                self->alpha                       = BSS_HUD->dpadAlpha;
                BSS_HUD->dpadAnimator.frameID = 8;
                RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->dpadPos, true);
            }

            if (!player->up && !player->down && !player->left && !player->right) {
                self->alpha                       = BSS_HUD->dpadAlpha;
                BSS_HUD->dpadAnimator.frameID = 11;
                RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->dpadPos, true);
            }

            RSDKControllerState *controller = &ControllerInfo[player->controllerID];
            bool32 jumpHold                 = controller->keyA.down || controller->keyB.down || controller->keyC.down || controller->keyX.down;
            if (jumpHold) {
                self->alpha                            = opacity;
                BSS_HUD->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->actionPos, true);
            }
            else {
                self->alpha                       = BSS_HUD->dpadAlpha;
                BSS_HUD->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->actionPos, true);
            }
        }
        else {
            BSS_HUD->dpadAlpha  = 0;
            BSS_HUD->pauseAlpha = 0;
        }

        self->alpha                            = BSS_HUD->pauseAlpha;
        BSS_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->pausePos, true);
    }
    else {
        if (BSS_HUD->dpadAlpha > 0) {
            BSS_HUD->dpadAlpha -= 4;
            BSS_HUD->pauseAlpha -= 8;
        }

        self->alpha = BSS_HUD->dpadAlpha;
        if (self->alpha > 0) {
            BSS_HUD->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->dpadPos, true);

            BSS_HUD->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&BSS_HUD->dpadAnimator, &BSS_HUD->actionPos, true);
        }

        if (BSS_HUD->pauseAlpha < 0)
            self->alpha = 0;
        else
            self->alpha = BSS_HUD->pauseAlpha;

        BSS_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&BSS_HUD->dpadTouchAnimator, &BSS_HUD->pausePos, true);
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

int32 BSS_HUD_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy)
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
void BSS_HUD_EditorDraw(void) {}

void BSS_HUD_EditorLoad(void) {}
#endif

void BSS_HUD_Serialize(void) {}
