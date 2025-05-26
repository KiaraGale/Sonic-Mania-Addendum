// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: PBL_HUD Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

#if MANIA_USE_PLUS
ObjectPBL_HUD *PBL_HUD;

void PBL_HUD_Update(void)
{
    RSDK_THIS(PBL_HUD);

    StateMachine_Run(self->state);
}

void PBL_HUD_LateUpdate(void) {}

void PBL_HUD_StaticUpdate(void) {}

void PBL_HUD_Draw(void)
{
    RSDK_THIS(PBL_HUD);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    self->position.x = ScreenInfo->center.x << 16;

    if (self->stateDraw) {
        StateMachine_Run(self->stateDraw);
    }
    else {
        RSDK.DrawSprite(&self->displayAnimator, NULL, true);
        RSDK.DrawSprite(&self->baseAnimator, NULL, true);
    }

    if (touchControls)
        PBL_HUD_DrawTouchControls(false);
}

void PBL_HUD_Create(void *data)
{
    RSDK_THIS(PBL_HUD);

    if (!SceneInfo->inEditor) {
        self->visible    = true;
        self->drawGroup  = 12;
        self->active     = ACTIVE_NORMAL;
        self->position.y = 0;
        self->scale.x    = 0x200;
        self->scale.y    = 0x200;

        RSDK.SetSpriteAnimation(PBL_HUD->aniFrames, 0, &self->displayAnimator, true, 0);
        RSDK.SetSpriteAnimation(PBL_HUD->aniFrames, 0, &self->baseAnimator, true, 1);
        RSDK.SetSpriteAnimation(PBL_HUD->aniFrames, 1, &self->textAnimator, true, 0);

        RSDK.InitString(&self->text, "", 64);

        if (globals->gameMode == MODE_ENCORE && !GET_STOCK_ID(4))
            PBL_HUD_DisplayMessage(self, "BONUS STAGE! RESCUE YOUR BUDDIES!", PBL_HUD_MSG_SCROLL_LEFT);
        else
            PBL_HUD_DisplayMessage(self, "BONUS STAGE!", PBL_HUD_MSG_SCROLL_LEFT);
    }
}

void PBL_HUD_StageLoad(void)
{
    PBL_HUD->aniFrames = RSDK.LoadSpriteAnimation("Pinball/Backglass.bin", SCOPE_STAGE);

    PBL_HUD->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(PBL_HUD->dpadFrames, 0, &PBL_HUD->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(PBL_HUD->dpadFrames, 1, &PBL_HUD->dpadTouchAnimator, true, 0);
}

void PBL_HUD_DisplayMessage(EntityPBL_HUD *entity, const char *message, int32 type)
{
    if (entity->state != PBL_HUD_StateMessage_FlashThenCrane && entity->state != PBL_HUD_State_RevealCrane
        && entity->state != PBL_HUD_State_HideCrane) {
        RSDK.SetString(&entity->text, message);
        RSDK.SetSpriteString(PBL_HUD->aniFrames, 1, &entity->text);

        entity->stateDraw = PBL_HUD_Draw_Message;

        switch (type) {
            case PBL_HUD_MSG_SCROLL_LEFT_SLOW:
                entity->offset.x = 0x410000;
                entity->state    = PBL_HUD_StateMessage_ScrollLeftSlow;
                entity->timer    = 12 * entity->text.length + 128;
                break;

            case PBL_HUD_MSG_SCROLL_LEFT:
                entity->offset.x = 0x410000;
                entity->state    = PBL_HUD_StateMessage_ScrollLeftFast;
                entity->timer    = 6 * entity->text.length + 64;
                break;

            case PBL_HUD_MSG_SCROLL_RIGHT_SLOW:
                entity->state    = PBL_HUD_StateMessage_ScrollRightSlow;
                entity->timer    = 12 * entity->text.length + 128;
                entity->offset.x = -0x410000 - 0xC0000 * entity->text.length;
                break;

            case PBL_HUD_MSG_SCROLL_RIGHT:
                entity->state    = PBL_HUD_StateMessage_ScrollRightFast;
                entity->timer    = 6 * entity->text.length + 64;
                entity->offset.x = -0x410000 - 0xC0000 * entity->text.length;
                break;

            case PBL_HUD_MSG_SHOW_RISE:
                entity->offset.y   = 0x120000;
                entity->timer      = -9;
                entity->velocity.y = -0x20000;
                entity->state      = PBL_HUD_StateMessage_ShowMove;
                entity->offset.x   = -0x60000 * entity->text.length;
                break;

            case PBL_HUD_MSG_SHOW_FALL:
                entity->offset.y   = -0x120000;
                entity->timer      = -9;
                entity->velocity.y = 0x20000;
                entity->state      = PBL_HUD_StateMessage_ShowMove;
                entity->offset.x   = -0x60000 * entity->text.length;
                break;

            case PBL_HUD_MSG_FLASH:
                entity->state    = PBL_HUD_StateMessage_Flash;
                entity->timer    = 60;
                entity->offset.x = -0x60000 * entity->text.length;
                break;

            case PBL_HUD_MSG_FLASH_CRANE:
                entity->state    = PBL_HUD_StateMessage_FlashThenCrane;
                entity->timer    = 60;
                entity->offset.x = -0x60000 * entity->text.length;
                break;

            default: break;
        }
    }
}

void PBL_HUD_StateMessage_ScrollLeftSlow(void)
{
    RSDK_THIS(PBL_HUD);

    if (self->timer <= 0) {
        self->state     = StateMachine_None;
        self->stateDraw = PBL_HUD_Draw_Score;
    }
    else {
        self->timer--;
        if (!(self->timer & 1))
            self->offset.x -= 0x20000;
    }
}

void PBL_HUD_StateMessage_ScrollLeftFast(void)
{
    RSDK_THIS(PBL_HUD);

    if (self->timer <= 0) {
        self->state     = StateMachine_None;
        self->stateDraw = PBL_HUD_Draw_Score;
    }
    else {
        self->offset.x -= 0x20000;
        self->timer--;
    }
}
void PBL_HUD_StateMessage_ScrollRightSlow(void)
{
    RSDK_THIS(PBL_HUD);

    if (self->timer <= 0) {
        self->state     = StateMachine_None;
        self->stateDraw = PBL_HUD_Draw_Score;
    }
    else {
        self->timer--;

        if (!(self->timer & 1))
            self->offset.x += 0x20000;
    }
}

void PBL_HUD_StateMessage_ScrollRightFast(void)
{
    RSDK_THIS(PBL_HUD);

    if (self->timer <= 0) {
        self->state     = StateMachine_None;
        self->stateDraw = PBL_HUD_Draw_Score;
    }
    else {
        self->offset.x += 0x20000;
        self->timer--;
    }
}

void PBL_HUD_StateMessage_ShowMove(void)
{
    RSDK_THIS(PBL_HUD);

    if (self->timer < 0 || self->timer > 60)
        self->offset.y += self->velocity.y;

    if (++self->timer > 90) {
        self->timer     = 0;
        self->offset.y  = 0;
        self->state     = StateMachine_None;
        self->stateDraw = PBL_HUD_Draw_Score;
    }
}

void PBL_HUD_StateMessage_Flash(void)
{
    RSDK_THIS(PBL_HUD);

    if (self->timer <= 0) {
        self->state     = StateMachine_None;
        self->stateDraw = PBL_HUD_Draw_Score;
    }
    else {
        self->timer--;

        if ((self->timer & 7) < 4)
            self->stateDraw = StateMachine_None;
        else
            self->stateDraw = PBL_HUD_Draw_Message;
    }
}

void PBL_HUD_StateMessage_FlashThenCrane(void)
{
    RSDK_THIS(PBL_HUD);

    if (self->timer <= 0) {
        self->state     = PBL_HUD_State_RevealCrane;
        self->stateDraw = PBL_HUD_Draw_Basic;
        self->drawFX    = FX_SCALE;

        foreach_active(PBL_Crane, crane) { crane->state = PBL_Crane_State_CreatePrizes; }
    }
    else {
        self->timer--;

        if ((self->timer & 7) < 4)
            self->stateDraw = StateMachine_None;
        else
            self->stateDraw = PBL_HUD_Draw_Message;
    }
}

void PBL_HUD_Draw_Basic(void)
{
    RSDK_THIS(PBL_HUD);

    RSDK.DrawSprite(&self->displayAnimator, NULL, true);
}

void PBL_HUD_Draw_Message(void)
{
    RSDK_THIS(PBL_HUD);

    RSDK.DrawSprite(&self->displayAnimator, NULL, true);
    RSDK.DrawSprite(&self->baseAnimator, NULL, true);

    Vector2 position;
    position.x = self->position.x + self->offset.x;
    position.y = self->position.y + self->offset.y;

    RSDK.SetClipBounds(SceneInfo->currentScreenID, ScreenInfo->center.x - 55, 40, ScreenInfo->center.x + 56, 58);

    RSDK.DrawText(&self->textAnimator, &position, &self->text, 0, 0, 0, 1, 0, 0, true);

    RSDK.SetClipBounds(SceneInfo->currentScreenID, 0, 0, ScreenInfo->size.x, ScreenInfo->size.y);
}

void PBL_HUD_Draw_Score(void)
{
    RSDK_THIS(PBL_HUD);

    int32 score = PBL_Setup->score;
    int32 count = 0;
    int32 mult  = 1;

    while (score > 0) {
        ++count;
        score /= 10;
    }

    Vector2 drawPos;
    drawPos.x = self->position.x + 0x320000;
    drawPos.y = self->position.y;
    RSDK.DrawSprite(&self->displayAnimator, NULL, true);
    RSDK.DrawSprite(&self->baseAnimator, NULL, true);

    int32 div = 10;
    while (count > 0) {
        self->textAnimator.frameID = PBL_Setup->score / mult % div;
        RSDK.DrawSprite(&self->textAnimator, &drawPos, true);

        drawPos.x -= 0xC0000;
        mult *= 10;
        --count;
    }

    self->textAnimator.frameID = 0;
}

void PBL_HUD_State_RevealCrane(void)
{
    RSDK_THIS(PBL_HUD);

    self->scale.x += 4;
    self->position.y -= 0x40000;

    if (self->position.y < -0x480000) {
        self->state   = StateMachine_None;
        self->visible = false;
    }
}

void PBL_HUD_State_HideCrane(void)
{
    RSDK_THIS(PBL_HUD);

    self->scale.x -= 4;
    self->position.y += 0x40000;

    if (self->position.y >= 0) {
        self->position.y = 0;
        self->scale.x    = 0x200;
        self->scale.y    = 0x200;
        self->drawFX     = FX_NONE;
        self->state      = StateMachine_None;
        self->stateDraw  = PBL_HUD_Draw_Score;

        foreach_all(PBL_Player, player)
        {
            player->active     = ACTIVE_NORMAL;
            player->velocity.y = 0;
        }
    }
}

void PBL_HUD_DrawTouchControls(bool32 craneControls)
{
    RSDK_THIS(PBL_HUD);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    PBL_HUD->dpadPos.x = TO_FIXED(56);
    PBL_HUD->dpadPos.y = TO_FIXED(184);

    PBL_HUD->actionPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 56);
    PBL_HUD->actionPos.y = TO_FIXED(188);

    PBL_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 64);
    PBL_HUD->pausePos.y = TO_FIXED(16);

    self->inkEffect = INK_NONE;
    self->drawFX    = FX_SCALE;

    int32 opacity = 0x100;
    self->scale.x = 0x200;
    self->scale.y = 0x200;

    bool32 enabled = true;
    if (enabled) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (PBL_HUD->dpadAlpha < opacity) {
                PBL_HUD->dpadAlpha += 4;
                PBL_HUD->pauseAlpha = PBL_HUD->dpadAlpha << 1;
            }

            if (craneControls) {
                foreach_active(PBL_Crane, crane)
                {
                    if (crane->classID == PBL_Crane->classID) {
                        // Draw DPad
                        self->alpha                   = PBL_HUD->dpadAlpha;
                        PBL_HUD->dpadAnimator.frameID = 10;
                        RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);

                        if (PBL_Crane->touchDir == 2 || ControllerInfo->keyLeft.down) {
                            self->alpha                        = opacity;
                            PBL_HUD->dpadTouchAnimator.frameID = 6;
                            RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);
                        }
                        else {
                            self->alpha                   = PBL_HUD->dpadAlpha;
                            PBL_HUD->dpadAnimator.frameID = 6;
                            RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
                        }

                        // Down Input else statement; down input isn't used here
                        self->alpha                   = PBL_HUD->dpadAlpha;
                        PBL_HUD->dpadAnimator.frameID = 9;
                        RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);

                        if (PBL_Crane->touchDir == 0 || ControllerInfo->keyRight.down) {
                            self->alpha                        = opacity;
                            PBL_HUD->dpadTouchAnimator.frameID = 7;
                            RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);
                        }
                        else {
                            self->alpha                   = PBL_HUD->dpadAlpha;
                            PBL_HUD->dpadAnimator.frameID = 7;
                            RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
                        }

                        // Up Input else statement; up input isn't used here
                        self->alpha                   = PBL_HUD->dpadAlpha;
                        PBL_HUD->dpadAnimator.frameID = 8;
                        RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);

                        if (PBL_Crane->touchDir != 2 && PBL_Crane->touchDir != 0) {
                            self->alpha                   = PBL_HUD->dpadAlpha;
                            PBL_HUD->dpadAnimator.frameID = 11;
                            RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
                        }

                        if (PBL_Crane->touchDown) {
                            self->alpha                        = opacity;
                            PBL_HUD->dpadTouchAnimator.frameID = 1;
                            RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->actionPos, true);
                        }
                        else {
                            self->alpha                   = PBL_HUD->dpadAlpha;
                            PBL_HUD->dpadAnimator.frameID = 1;
                            RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->actionPos, true);
                        }
                    }
                }
            }
            else {
                // Draw DPad
                self->alpha                   = PBL_HUD->dpadAlpha;
                PBL_HUD->dpadAnimator.frameID = 10;
                RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);

                if (ControllerInfo->keyLeft.down) {
                    self->alpha                        = opacity;
                    PBL_HUD->dpadTouchAnimator.frameID = 6;
                    RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);
                }
                else {
                    self->alpha                   = PBL_HUD->dpadAlpha;
                    PBL_HUD->dpadAnimator.frameID = 6;
                    RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
                }

                if (ControllerInfo->keyDown.down) {
                    self->alpha                        = opacity;
                    PBL_HUD->dpadTouchAnimator.frameID = 9;
                    RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);

                    if (ControllerInfo->keyLeft.down) {
                        PBL_HUD->dpadTouchAnimator.frameID = 14;
                        RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);
                    }
                    else if (ControllerInfo->keyRight.down) {
                        PBL_HUD->dpadTouchAnimator.frameID = 15;
                        RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);
                    }
                }
                else {
                    self->alpha                   = PBL_HUD->dpadAlpha;
                    PBL_HUD->dpadAnimator.frameID = 9;
                    RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
                }

                if (ControllerInfo->keyRight.down) {
                    self->alpha                        = opacity;
                    PBL_HUD->dpadTouchAnimator.frameID = 7;
                    RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);
                }
                else {
                    self->alpha                   = PBL_HUD->dpadAlpha;
                    PBL_HUD->dpadAnimator.frameID = 7;
                    RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
                }

                if (ControllerInfo->keyUp.down) {
                    self->alpha                        = opacity;
                    PBL_HUD->dpadTouchAnimator.frameID = 8;
                    RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);

                    if (ControllerInfo->keyLeft.down) {
                        PBL_HUD->dpadTouchAnimator.frameID = 12;
                        RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);
                    }
                    else if (ControllerInfo->keyRight.down) {
                        PBL_HUD->dpadTouchAnimator.frameID = 13;
                        RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->dpadPos, true);
                    }
                }
                else {
                    self->alpha                   = PBL_HUD->dpadAlpha;
                    PBL_HUD->dpadAnimator.frameID = 8;
                    RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
                }

                if (!ControllerInfo->keyUp.down && !ControllerInfo->keyDown.down && !ControllerInfo->keyLeft.down
                    && !ControllerInfo->keyRight.down) {
                    self->alpha                   = PBL_HUD->dpadAlpha;
                    PBL_HUD->dpadAnimator.frameID = 11;
                    RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
                }

                if (ControllerInfo->keyA.down || ControllerInfo->keyB.down || ControllerInfo->keyC.down || ControllerInfo->keyX.down) {
                    self->alpha                        = opacity;
                    PBL_HUD->dpadTouchAnimator.frameID = 1;
                    RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->actionPos, true);
                }
                else {
                    self->alpha                   = PBL_HUD->dpadAlpha;
                    PBL_HUD->dpadAnimator.frameID = 1;
                    RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->actionPos, true);
                }
            }
        }
        else {
            PBL_HUD->dpadAlpha  = 0;
            PBL_HUD->pauseAlpha = 0;
        }

        self->alpha                        = PBL_HUD->pauseAlpha;
        PBL_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->pausePos, true);
    }
    else {
        if (PBL_HUD->dpadAlpha > 0) {
            PBL_HUD->dpadAlpha -= 4;
            PBL_HUD->pauseAlpha -= 8;
        }

        self->alpha = PBL_HUD->dpadAlpha;
        if (self->alpha > 0) {
            PBL_HUD->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);

            PBL_HUD->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&PBL_HUD->dpadAnimator, &PBL_HUD->dpadPos, true);
        }

        if (PBL_HUD->pauseAlpha < 0)
            self->alpha = 0;
        else
            self->alpha = PBL_HUD->pauseAlpha;

        PBL_HUD->dpadTouchAnimator.frameID = 5;
        RSDK.DrawSprite(&PBL_HUD->dpadTouchAnimator, &PBL_HUD->pausePos, true);
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

int32 PBL_HUD_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy)
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
void PBL_HUD_EditorDraw(void)
{
    RSDK_THIS(PBL_HUD);

    RSDK.SetSpriteAnimation(PBL_HUD->aniFrames, 0, &self->displayAnimator, true, 0);
    RSDK.SetSpriteAnimation(PBL_HUD->aniFrames, 0, &self->baseAnimator, true, 1);

    RSDK.DrawSprite(&self->displayAnimator, NULL, false);
}

void PBL_HUD_EditorLoad(void) { PBL_HUD->aniFrames = RSDK.LoadSpriteAnimation("Pinball/Backglass.bin", SCOPE_STAGE); }
#endif

void PBL_HUD_Serialize(void) {}
#endif
