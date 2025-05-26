// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: BSS_Player Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectBSS_Player *BSS_Player;

void BSS_Player_Update(void)
{
    RSDK_THIS(BSS_Player);

    EntityBSS_Setup *setup = RSDK_GET_ENTITY(SLOT_BSS_SETUP, BSS_Setup);

    StateMachine_Run(self->stateInput);

    if (self->onGround) {
        if (self->jumpPress) {
            self->velocity.y = -TO_FIXED(16);
            self->onGround   = false;
            RSDK.SetSpriteAnimation(self->aniFrames, 2, &self->animator, false, 0);
            RSDK.PlaySfx(BSS_Player->sfxJump, false, 255);
        }
    }
    else {
        self->gravityStrength += self->velocity.y;

        int32 speed = !setup->speedupLevel ? 16 : setup->speedupLevel;
        self->velocity.y += (speed << 12);
        if (self->gravityStrength >= 0) {
            self->gravityStrength = 0;
            self->onGround        = true;

            if (!self->sidekick) {
                if (self->animator.animationID == 3)
                    setup->globeSpeed >>= 1;

                setup->globeSpeedInc = 2;
            }

            if (setup->speedupLevel)
                RSDK.SetSpriteAnimation(self->aniFrames, 1, &self->animator, false, 0);
            else
                RSDK.SetSpriteAnimation(self->aniFrames, 0, &self->animator, false, 0);
        }
    }

    self->position.y = (self->gravityStrength >> 1) - (self->gravityStrength >> 4);
    self->position.y += SceneInfo->entitySlot ? TO_FIXED(186) : TO_FIXED(170);

    if (self->animator.animationID == 1) {
        self->animator.timer += abs(setup->globeSpeed);
        self->animator.speed = abs(setup->globeSpeed);

        if (self->animator.timer > 0x1F) {
            self->animator.timer &= 0x1F;

            if (setup->globeSpeed <= 0) {
                if (--self->animator.frameID < 0)
                    self->animator.frameID = 11;
            }
            else if (++self->animator.frameID > 11) {
                self->animator.frameID = 0;
            }
        }
    }
    else if (self->animator.animationID >= 2) {
        self->animator.speed = MAX(abs(setup->speedupLevel), 0x10);
        RSDK.ProcessAnimation(&self->animator);
    }

    self->tailAnimator.speed = abs(setup->speedupLevel) + 40;
    RSDK.ProcessAnimation(&self->tailAnimator);
}

void BSS_Player_LateUpdate(void) {}

void BSS_Player_StaticUpdate(void) {}

void BSS_Player_Draw(void)
{
    RSDK_THIS(BSS_Player);

    Vector2 drawPos;
    drawPos.x = TO_FIXED(ScreenInfo->center.x);
    drawPos.y = self->position.y + (SceneInfo->entitySlot * 0x10000);
    RSDK.DrawSprite(&self->animator, &drawPos, true);

    // if we're tails, draw his tails
    if (CHECK_CHARACTER_ID(ID_TAILS, SceneInfo->entitySlot + 1))
        RSDK.DrawSprite(&self->tailAnimator, &drawPos, true);
#if MANIA_USE_PLUS
    // if we're ray, draw his tail
    else if (CHECK_CHARACTER_ID(ID_RAY, SceneInfo->entitySlot + 1))
        RSDK.DrawSprite(&self->tailAnimator, &drawPos, true);
#endif
}

void BSS_Player_Create(void *data)
{
    RSDK_THIS(BSS_Player);
    if (data)
        self->playerID = VOID_TO_INT(data);

    if (!SceneInfo->inEditor) {
        self->active        = ACTIVE_NORMAL;
        self->visible       = true;
        self->drawGroup     = 4;
        self->updateRange.x = TO_FIXED(128);
        self->updateRange.y = TO_FIXED(128);

        switch (GET_CHARACTER_ID(self->playerID)) {
            default:
            case ID_SONIC: self->aniFrames = BSS_Player->sonicFrames; break;

            case ID_TAILS:
                self->aniFrames = BSS_Player->tailsFrames;
                RSDK.SetSpriteAnimation(self->aniFrames, 4, &self->tailAnimator, true, 0);
                break;

            case ID_KNUCKLES: self->aniFrames = BSS_Player->knuxFrames; break;

#if MANIA_USE_PLUS
            case ID_MIGHTY: self->aniFrames = BSS_Player->mightyFrames; break;

            case ID_RAY:
                self->aniFrames = BSS_Player->rayFrames;
                RSDK.SetSpriteAnimation(self->aniFrames, 4, &self->tailAnimator, true, 0);
                break;

            case ID_AMY: self->aniFrames = BSS_Player->amyFrames; break;
#endif
        }

        if (self->playerID == 1) {
            self->stateInput   = BSS_Player_Input_P1;
            self->controllerID = CONT_P1;
            self->sidekick     = false;
        }

        if (self->playerID == 2) {
            self->stateInput   = BSS_Player_Input_P2;
            self->controllerID = CONT_P2;
            self->sidekick     = true;
        }

        RSDK.SetSpriteAnimation(self->aniFrames, 0, &self->animator, true, 0);
    }
}

void BSS_Player_StageLoad(void)
{
    BSS_Player->sonicFrames  = RSDK.LoadSpriteAnimation("SpecialBS/Sonic.bin", SCOPE_STAGE);
    BSS_Player->tailsFrames  = RSDK.LoadSpriteAnimation("SpecialBS/Tails.bin", SCOPE_STAGE);
    BSS_Player->knuxFrames   = RSDK.LoadSpriteAnimation("SpecialBS/Knuckles.bin", SCOPE_STAGE);
    BSS_Player->mightyFrames = RSDK.LoadSpriteAnimation("SpecialBS/Mighty.bin", SCOPE_STAGE);
    BSS_Player->rayFrames    = RSDK.LoadSpriteAnimation("SpecialBS/Ray.bin", SCOPE_STAGE);
    BSS_Player->amyFrames    = RSDK.LoadSpriteAnimation("SpecialBS/Amy.bin", SCOPE_STAGE);

    if (globals->playerID == ID_NONE)
        globals->playerID = ID_DEFAULT_PLAYER;

    RSDK.ResetEntitySlot(SLOT_PLAYER1, BSS_Player->classID, ((void *)1));
    if (GET_CHARACTER_ID(2) != 0)
        RSDK.ResetEntitySlot(SLOT_PLAYER2, BSS_Player->classID, ((void *)2));

    BSS_Player->sfxJump = RSDK.GetSfx("Global/Jump.wav");
}

void BSS_Player_Input_P1(void)
{
    RSDK_THIS(BSS_Player);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls) {
        BSS_Player_HandleTouchInput();
    }

    if (self->controllerID < PLAYER_COUNT) {
        RSDKControllerState *controller = &ControllerInfo[self->controllerID];
        RSDKAnalogState *stick          = &AnalogStickInfoL[self->controllerID];

        self->up    = controller->keyUp.down;
        self->down  = controller->keyDown.down;
        self->left  = controller->keyLeft.down;
        self->right = controller->keyRight.down;

        self->up |= stick->keyUp.down;
        self->down |= stick->keyDown.down;
        self->left |= stick->keyLeft.down;
        self->right |= stick->keyRight.down;

#if MANIA_USE_PLUS
        self->up |= stick->vDelta > 0.3;
        self->down |= stick->vDelta < -0.3;
        self->left |= stick->hDelta < -0.3;
        self->right |= stick->hDelta > 0.3;
#else
        self->up |= stick->vDeltaL > 0.3;
        self->down |= stick->vDeltaL < -0.3;
        self->left |= stick->hDeltaL < -0.3;
        self->right |= stick->hDeltaL > 0.3;
#endif

        if (self->left && self->right) {
            self->left  = false;
            self->right = false;
        }
        self->jumpPress = controller->keyA.press || controller->keyB.press || controller->keyC.press || controller->keyX.press;

        if (controller->keyStart.press || Unknown_pausePress) {
            if (SceneInfo->state == ENGINESTATE_REGULAR) {
                EntityPauseMenu *pauseMenu = RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);
                if (!pauseMenu->classID) {
                    RSDK.ResetEntitySlot(SLOT_PAUSEMENU, PauseMenu->classID, NULL);
                    pauseMenu->triggerPlayer  = RSDK.GetEntitySlot(self);
                    pauseMenu->disableRestart = true;
                }
            }
        }
    }
}

void BSS_Player_Input_P2(void)
{
    RSDK_THIS(BSS_Player);
    EntityBSS_Player *player1       = RSDK_GET_ENTITY(SLOT_PLAYER1, BSS_Player);
    RSDKControllerState *controller = &ControllerInfo[self->controllerID];
    RSDKAnalogState *stick          = &AnalogStickInfoL[self->controllerID];

    BSS_Player->upPressState <<= 1;
    BSS_Player->upPressState |= controller->keyUp.down || stick->keyUp.down || stick->vDelta > 0.3;
    BSS_Player->upPressState &= 0xFFFF;

    self->up = BSS_Player->upPressState >> 15;

    BSS_Player->jumpPressState <<= 1;
    BSS_Player->jumpPressState |= player1->jumpPress;
    BSS_Player->jumpPressState &= 0xFFFF;

    self->jumpPress = BSS_Player->jumpPressState >> 15;
}

void BSS_Player_HandleTouchInput(void)
{
    RSDK_THIS(BSS_Player);

    if (self->controllerID < PLAYER_COUNT) {
        RSDKControllerState *controller = &ControllerInfo[self->controllerID];

        int32 tx = 0, ty = 0;
        if (BSS_HUD_CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, &tx, &ty) >= 0) {
            tx -= 56;
            ty -= 184;

            switch (((RSDK.ATan2(tx, ty) + 32) & 0xFF) >> 6) {
                case 0:
                    ControllerInfo->keyRight.down |= true;
                    controller->keyRight.down = true;
                    break;

                case 1:
                    ControllerInfo->keyDown.down |= true;
                    controller->keyDown.down = true;
                    break;

                case 2:
                    ControllerInfo->keyLeft.down |= true;
                    controller->keyLeft.down = true;
                    break;

                case 3:
                    ControllerInfo->keyUp.down |= true;
                    controller->keyUp.down = true;
                    break;
            }
        }

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (BSS_HUD_CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedJump           = true;
        }

        bool32 touchedPause = false;
        if (BSS_HUD_CheckTouchRect(ScreenInfo->center.x - 0x80, 0, ScreenInfo->center.x + 80, 0x40, NULL, NULL) >= 0) {
            ControllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        if (!BSS_Player->touchJump && touchedJump) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        BSS_Player->touchJump = controller->keyA.down;

        if (!BSS_Player->touchPause && touchedPause) {
            ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        BSS_Player->touchPause = controller->keyStart.down;
    }
}

#if GAME_INCLUDE_EDITOR
void BSS_Player_EditorDraw(void)
{
    RSDK_THIS(BSS_Player);

    RSDK.SetSpriteAnimation(BSS_Player->sonicFrames, 0, &self->animator, false, 0);

    RSDK.DrawSprite(&self->animator, NULL, true);
}

void BSS_Player_EditorLoad(void) { BSS_Player->sonicFrames = RSDK.LoadSpriteAnimation("SpecialBS/Sonic.bin", SCOPE_STAGE); }
#endif

void BSS_Player_Serialize(void) {}
