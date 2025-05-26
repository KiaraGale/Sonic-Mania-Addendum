// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: PuyoLevelSelect Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectPuyoLevelSelect *PuyoLevelSelect;

void PuyoLevelSelect_Update(void)
{
    RSDK_THIS(PuyoLevelSelect);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls)
        PuyoLevelSelect_HandleTouchInput();

    if (self->canSelectLevels) {
        self->visible = !self->ready;

        int32 controllerID = self->playerID + 1;

        RSDKControllerState *controller = &ControllerInfo[controllerID];

        self->up   = controller->keyUp.press || AnalogStickInfoL[controllerID].keyUp.press;
        self->down = controller->keyDown.press || AnalogStickInfoL[controllerID].keyDown.press;

        if (API_GetConfirmButtonFlip()) {
            self->confirmPress = controller->keyB.press;
            self->backPress    = controller->keyA.press;
        }
        else {
            self->confirmPress = controller->keyA.press;
            self->backPress    = controller->keyB.press;
        }

        PuyoLevelSelect_HandleMenuMovement();
    }
    else {
        self->visible = false;
    }
}

void PuyoLevelSelect_LateUpdate(void) {}

void PuyoLevelSelect_StaticUpdate(void) {}

void PuyoLevelSelect_Draw(void) { PuyoLevelSelect_DrawSprites(); }

void PuyoLevelSelect_Create(void *data)
{
    RSDK_THIS(PuyoLevelSelect);

    self->active        = ACTIVE_NORMAL;
    self->drawGroup     = 10;
    self->visible       = true;
    self->updateRange.x = 0x800000;
    self->updateRange.y = 0x800000;
}

void PuyoLevelSelect_StageLoad(void)
{
    PuyoLevelSelect->aniFrames = RSDK.LoadSpriteAnimation("Puyo/PuyoUI.bin", SCOPE_STAGE);

    PuyoLevelSelect->sfxMenuBleep  = RSDK.GetSfx("Global/MenuBleep.wav");
    PuyoLevelSelect->sfxMenuAccept = RSDK.GetSfx("Global/MenuAccept.wav");
}

void PuyoLevelSelect_DrawSprites(void)
{
    RSDK_THIS(PuyoLevelSelect);

    Vector2 drawPos;
    drawPos.x       = self->position.x + 0x30000;
    drawPos.y       = self->position.y + 0x30000;
    self->inkEffect = INK_BLEND;
    self->alpha     = 0x7F;
    RSDK.SetSpriteAnimation(PuyoLevelSelect->aniFrames, 0, &self->frameAnimator, true, 1);
    RSDK.DrawSprite(&self->frameAnimator, &drawPos, false);

    drawPos.x -= 0x30000;
    drawPos.y -= 0x30000;
    self->inkEffect = INK_NONE;
    RSDK.SetSpriteAnimation(PuyoLevelSelect->aniFrames, 0, &self->frameAnimator, true, 0);
    RSDK.DrawSprite(&self->frameAnimator, &drawPos, false);

    drawPos.x = self->position.x;
    drawPos.y = self->position.y - 0x500000;
    RSDK.SetSpriteAnimation(PuyoLevelSelect->aniFrames, 1, &self->labelAnimator, true, 1);
    RSDK.DrawSprite(&self->labelAnimator, &drawPos, false);

    drawPos.x = self->position.x;
    drawPos.y = self->position.y - 0x310000;

    // Draw Levels
    for (int32 i = 0; i < 5; ++i) {
        if (i != self->optionID || (!(Zone->timer & 4))) {
            RSDK.SetSpriteAnimation(PuyoLevelSelect->aniFrames, (i != self->optionID) + 4, &self->labelAnimator, true, i + 1);
            RSDK.DrawSprite(&self->labelAnimator, &drawPos, false);
        }
        drawPos.y += 0x180000;
    }
}

void PuyoLevelSelect_HandleMenuMovement(void)
{
    RSDK_THIS(PuyoLevelSelect);

    if (self->ready) {
        if (self->backPress)
            self->ready = false;
    }
    else if (self->up || self->down) {
        if (self->up)
            --self->optionID;

        if (self->down)
            ++self->optionID;

        if (self->optionID >= 5)
            self->optionID -= 5;

        if (self->optionID < 0)
            self->optionID += 5;

        RSDK.PlaySfx(PuyoLevelSelect->sfxMenuBleep, false, 255);
    }
    else if (self->confirmPress) {
        self->ready = true;
        RSDK.PlaySfx(PuyoLevelSelect->sfxMenuAccept, false, 255);
    }
}

void PuyoLevelSelect_HandleTouchInput(void)
{
    RSDK_THIS(PuyoLevelSelect);

    if (self->canSelectLevels) {
        self->visible = !self->ready;

        int32 controllerID = self->playerID + 1;

        RSDKControllerState *controller = &ControllerInfo[controllerID];

        // fixes a bug with button vs touch
        bool32 touched = false;

        int32 tx = 0, ty = 0;
        if (PuyoGame_CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, &tx, &ty) >= 0) {
            tx -= 56;
            ty -= 184;

            switch (((RSDK.ATan2(tx, ty) + 32) & 0xFF) >> 6) {
                case 0: break;

                case 1:
                    ControllerInfo->keyDown.down |= true;
                    controller->keyDown.down = true;
                    touched                  = true;
                    break;

                case 2: break;

                case 3:
                    ControllerInfo->keyUp.down |= true;
                    controller->keyUp.down = true;
                    touched                = true;
                    break;
            }
        }

        if (!GET_BIT(PuyoLevelSelect->touchFlags, 0) && touched) {
            ControllerInfo->keyUp.press |= ControllerInfo->keyUp.down;
            controller->keyUp.press |= controller->keyUp.down;
        }

        if (!GET_BIT(PuyoLevelSelect->touchFlags, 1) && touched) {
            ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;
            controller->keyDown.press |= controller->keyDown.down;
        }
        SET_BIT(PuyoLevelSelect->touchFlags, controller->keyUp.down, 0);
        SET_BIT(PuyoLevelSelect->touchFlags, controller->keyDown.down, 1);

        int32 halfX = ScreenInfo->center.x / 2;

        bool32 touchedJump = false;
        if (PuyoGame_CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->center.x + halfX, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyB.down |= true;
            controller->keyB.down = true;
            touched               = true;
        }

        bool32 touchedPause = false;
        if (PuyoGame_CheckTouchRect(ScreenInfo->center.x + halfX, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touched               = true;
        }

        if (!GET_BIT(PuyoLevelSelect->touchFlags, 2) && touched) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }

        if (!GET_BIT(PuyoLevelSelect->touchFlags, 3) && touched) {
            ControllerInfo->keyB.press |= ControllerInfo->keyB.down;
            controller->keyB.press |= controller->keyB.down;
        }

        SET_BIT(PuyoLevelSelect->touchFlags, controller->keyA.down, 2);
        SET_BIT(PuyoLevelSelect->touchFlags, controller->keyB.down, 3);
    }
}

#if GAME_INCLUDE_EDITOR
void PuyoLevelSelect_EditorDraw(void) { PuyoLevelSelect_DrawSprites(); }

void PuyoLevelSelect_EditorLoad(void)
{
    PuyoLevelSelect->aniFrames = RSDK.LoadSpriteAnimation("Puyo/PuyoUI.bin", SCOPE_STAGE);

    RSDK_ACTIVE_VAR(PuyoLevelSelect, playerID);
    RSDK_ENUM_VAR("Player 1", PUYOGAME_PLAYER1);
    RSDK_ENUM_VAR("Player 2", PUYOGAME_PLAYER2);
}
#endif

void PuyoLevelSelect_Serialize(void) { RSDK_EDITABLE_VAR(PuyoLevelSelect, VAR_ENUM, playerID); }
