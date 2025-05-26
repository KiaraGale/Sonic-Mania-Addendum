// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: DebugMode Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectDebugMode *DebugMode;

void DebugMode_Update(void)
{
    RSDK_THIS(DebugMode);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls) {
        DebugMode_HandleTouchInput();
    }

    API_SetAchievementsEnabled(false);

    /*
    if (Zone)
        Zone->stageFinishCallback = StateMachine_None;
    */

    bool32 moved = false;

#if MANIA_USE_PLUS
    if (ControllerInfo[CONT_P1].keyUp.down || (AnalogStickInfoL[CONT_P1].vDelta > 0.3)) {
        self->position.y -= self->velocity.y;
        moved = true;
    }
    else if (ControllerInfo[CONT_P1].keyDown.down || (AnalogStickInfoL[CONT_P1].vDelta < -0.3)) {
        self->position.y += self->velocity.y;
        moved = true;
    }

    if (ControllerInfo[CONT_P1].keyLeft.down || (AnalogStickInfoL[CONT_P1].hDelta < -0.3)) {
        self->position.x -= self->velocity.y;
        moved = true;
    }
    else if (ControllerInfo[CONT_P1].keyRight.down || (AnalogStickInfoL[CONT_P1].hDelta > 0.3)) {
        self->position.x += self->velocity.y;
        moved = true;
    }
#else
    if (ControllerInfo[CONT_P1].keyUp.down || (AnalogStickInfoL[CONT_P1].vDeltaL > 0.3)) {
        self->position.y -= self->velocity.y;
        moved = true;
    }
    else if (ControllerInfo[CONT_P1].keyDown.down || (AnalogStickInfoL[CONT_P1].vDeltaL < -0.3)) {
        self->position.y += self->velocity.y;
        moved = true;
    }

    if (ControllerInfo[CONT_P1].keyLeft.down || (AnalogStickInfoL[CONT_P1].hDeltaL < -0.3)) {
        self->position.x -= self->velocity.y;
        moved = true;
    }
    else if (ControllerInfo[CONT_P1].keyRight.down || (AnalogStickInfoL[CONT_P1].hDeltaL > 0.3)) {
        self->position.x += self->velocity.y;
        moved = true;
    }
#endif

    if (!moved) {
        self->velocity.y = 0;
    }
    else {
        self->velocity.y += 0xC00;
        if (self->velocity.y > TO_FIXED(16))
            self->velocity.y = TO_FIXED(16);
    }

#if GAME_VERSION != VER_100
    bool32 keySpawn = ControllerInfo[CONT_P1].keyY.press;
    bool32 keyBack  = ControllerInfo[CONT_P1].keyX.press;
#else
    bool32 keySpawn = ControllerInfo[CONT_P1].keyX.press;
    bool32 keyBack  = ControllerInfo[CONT_P1].keyY.press;
#endif

    if (ControllerInfo[CONT_P1].keyA.press) {
        ++DebugMode->itemID;
        DebugMode->itemID %= DebugMode->itemCount;
        DebugMode->itemType = 0;
    }
    else if (keyBack) {
        // Do this so we can access the player variables again
        RSDK_THIS(Player);
        self->classID        = Player->classID;
        self->groundVel      = 0;
        self->velocity.x     = 0;
        self->velocity.y     = 0;
        self->state          = Player_State_Air;
        self->collisionPlane = 0;
        self->tileCollisions = TILECOLLISION_DOWN;
        self->interaction    = true;
        self->visible        = true;
        self->drawGroup      = Zone->playerDrawGroup[0];

        SceneInfo->timeEnabled = true;
        if (SceneInfo->minutes == 9 && SceneInfo->seconds == 59 && SceneInfo->milliseconds == 99) {
            SceneInfo->minutes      = 0;
            SceneInfo->seconds      = 0;
            SceneInfo->milliseconds = 0;
        }

        DebugMode->debugActive = false;
    }
    else if (ControllerInfo[CONT_P1].keyA.down) {
        if (ControllerInfo[CONT_P1].keyC.press || keySpawn) {
            if (--DebugMode->itemID < 0)
                DebugMode->itemID = DebugMode->itemCount - 1;

            DebugMode->itemType = 0;
        }

        if (ControllerInfo[CONT_P1].keyB.press) {
        DebugMode->itemType--;

        if (DebugMode->itemType >= DebugMode->itemTypeCount)
            DebugMode->itemType = DebugMode->itemTypeCount - 1;
        }
    }
    else if (ControllerInfo[CONT_P1].keyC.press || keySpawn) {
            StateMachine_Run(DebugMode->spawn[DebugMode->itemID]);
    }
    else if (ControllerInfo[CONT_P1].keyB.press) {
        if (DebugMode->itemType >= DebugMode->itemTypeCount - 1)
            DebugMode->itemType = 0;
        else
        DebugMode->itemType++;
    }
}

void DebugMode_LateUpdate(void) {}

void DebugMode_StaticUpdate(void) {}

void DebugMode_Draw(void) { StateMachine_Run(DebugMode->draw[DebugMode->itemID]); }

void DebugMode_Create(void *data)
{
    RSDK_THIS(DebugMode);

    self->active  = ACTIVE_NORMAL;
    self->visible = true;
}

void DebugMode_StageLoad(void)
{
    DebugMode->itemID      = 0;
    DebugMode->itemCount   = 0;
    DebugMode->debugActive = false;

    for (int32 i = 0; i < DEBUGMODE_OBJECT_COUNT; ++i) {
        DebugMode->classIDs[i] = TYPE_BLANK;
        DebugMode->draw[i]     = StateMachine_None;
        DebugMode->spawn[i]    = DebugMode_NullState;
    }
}

void DebugMode_NullState(void) {}

void DebugMode_AddObject(uint16 id, void (*draw)(void), void (*spawn)(void))
{
    if (DebugMode->itemCount < DEBUGMODE_OBJECT_COUNT) {
        DebugMode->classIDs[DebugMode->itemCount] = id;
        DebugMode->draw[DebugMode->itemCount]     = draw;
        DebugMode->spawn[DebugMode->itemCount]    = spawn;
        DebugMode->itemCount++;
    }
}

void DebugMode_HandleTouchInput(void)
{
    RSDK_THIS(DebugMode);

    RSDKControllerState *controller = &ControllerInfo[CONT_P1];

    int32 tx = 0, ty = 0;
    if (HUD_CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, &tx, &ty) >= 0) {
        tx -= 56;
        ty -= 184;

        switch (((RSDK.ATan2(tx, ty) + 16) & 0xFF) >> 5) {
        case 0:
            ControllerInfo->keyRight.down |= true;
            controller->keyRight.down = true;
            break;

        case 1:
            ControllerInfo->keyRight.down |= true;
            controller->keyRight.down = true;

            ControllerInfo->keyDown.down |= true;
            controller->keyDown.down = true;
            break;

        case 2:
            ControllerInfo->keyDown.down |= true;
            controller->keyDown.down = true;
            break;

        case 3:
            ControllerInfo->keyDown.down |= true;
            controller->keyDown.down = true;

            ControllerInfo->keyLeft.down |= true;
            controller->keyLeft.down = true;
            break;

        case 4:
            ControllerInfo->keyLeft.down |= true;
            controller->keyLeft.down = true;
            break;

        case 5:
            ControllerInfo->keyLeft.down |= true;
            controller->keyLeft.down = true;

            ControllerInfo->keyUp.down |= true;
            controller->keyUp.down = true;
            break;

        case 6:
            ControllerInfo->keyUp.down |= true;
            controller->keyUp.down = true;
            break;

        case 7:
            ControllerInfo->keyUp.down |= true;
            controller->keyUp.down = true;

            ControllerInfo->keyRight.down |= true;
            controller->keyRight.down = true;
            break;
        }
    }

    if (DebugMode->itemType == 0xFF)
        DebugMode->itemType = DebugMode->itemTypeCount ? (DebugMode->itemTypeCount - 1) : 0;

    tx = 0, ty = 0;
    if (HUD_CheckTouchRect(ScreenInfo->center.x - 48, 0, ScreenInfo->center.x + 48, 56, &tx, &ty) >= 0) {
        if (tx > ScreenInfo->center.x) {
        if (!Player->touchJump) {
            DebugMode->itemType++;
            if (DebugMode->itemType >= DebugMode->itemTypeCount) {
                DebugMode->itemType      = 0;
                DebugMode->itemTypeCount = 0;

                DebugMode->itemID++;
                if (DebugMode->itemID >= DebugMode->itemCount)
                    DebugMode->itemID = 0;
            }
        }

        Player->touchJump = true;
        }
        else {
        if (!Player->touchJump) {
            DebugMode->itemType--;

            if (DebugMode->itemType == 0xFF) {
                DebugMode->itemTypeCount = 0;

                DebugMode->itemID--;
                if (DebugMode->itemID < 0)
                    DebugMode->itemID = DebugMode->itemCount - 1;
            }
        }

        Player->touchJump = true;
        }
    }
    else {
        switch (HUD_CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, SCREEN_YSIZE, NULL, NULL)) {
        case -1: Player->touchJump = false; break;

        case 0:
            ControllerInfo->keyC.down = true;
            controller->keyC.down     = true;
            if (!Player->touchJump) {
                ControllerInfo->keyC.press = true;
                controller->keyC.press     = true;
            }
            Player->touchJump = controller->keyC.down;
            break;
        }
    }

    bool32 touchedDebug = false;
    if (HUD_CheckTouchRect(0, 0, 112, 56, NULL, NULL) >= 0) {
#if GAME_VERSION != VER_100
        ControllerInfo->keyX.down = true;
        controller->keyX.down     = true;
#else
        ControllerInfo->keyY.down  = true;
        controller->keyY.down      = true;
#endif
        touchedDebug = true;
    }

    if (!Player->touchDebug && touchedDebug) {
#if GAME_VERSION != VER_100
        ControllerInfo->keyX.press = true;
        controller->keyX.press     = true;
#else
        ControllerInfo->keyY.press = true;
        controller->keyY.press     = true;
#endif
    }
#if GAME_VERSION != VER_100
    Player->touchDebug = controller->keyX.down;
#else
    Player->touchDebug = controller->keyY.down;
#endif

    // funny S1/S2 2013 level select thingie!!
    if (HUD_CheckTouchRect(ScreenInfo->size.x - 88, 0, ScreenInfo->size.x, 40, NULL, NULL) >= 0 || controller->keyStart.press || Unknown_pausePress) {
        if (SceneInfo->state == ENGINESTATE_REGULAR) {
            RSDK.SetScene("Presentation", "Level Select");
            Zone_StartFadeOut(20, 0x000000);
            Music_FadeOut(0.025);
        }
    }
}

#if GAME_INCLUDE_EDITOR
void DebugMode_EditorDraw(void) {}

void DebugMode_EditorLoad(void) {}
#endif

void DebugMode_Serialize(void) {}
