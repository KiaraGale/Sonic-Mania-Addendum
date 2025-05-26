// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: LevelSelect Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectLevelSelect *LevelSelect;

void LevelSelect_Update(void)
{
    RSDK_THIS(LevelSelect);

#if MANIA_USE_PLUS
    EntityUIText *text = self->pinballLabel;
    if (text)
        text->visible = API.CheckDLC(DLC_PLUS);
#endif

    StateMachine_Run(self->state);

    ScreenInfo->position.x = 0x100 - ScreenInfo->center.x;
}

void LevelSelect_LateUpdate(void) {}

void LevelSelect_StaticUpdate(void)
{
    if (--LevelSelect->bgAniDuration <= 0) {
        ++LevelSelect->bgAniFrame;

        LevelSelect->bgAniFrame &= 3;
        LevelSelect->bgAniDuration = LevelSelect->bgAniDurationTable[LevelSelect->bgAniFrame];

        TileLayer *background = RSDK.GetTileLayer(0);
        background->scrollPos = (background->scrollPos + 0x1000000) & 0x7FF0000;
    }
}

void LevelSelect_Draw(void)
{
    RSDK_THIS(LevelSelect);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls) {
        LevelSelect_DrawTouchUI();
    }

    StateMachine_Run(self->stateDraw);
}

void LevelSelect_Create(void *data)
{
    RSDK_THIS(LevelSelect);

    if (!SceneInfo->inEditor) {
        self->active    = ACTIVE_ALWAYS;
        self->visible   = true;
        self->drawGroup = 12;
        self->state     = LevelSelect_State_Init;
        self->stateDraw = LevelSelect_Draw_Fade;
        self->timer     = 640;
    }
}

void LevelSelect_StageLoad(void)
{
    LevelSelect->sfxFail = RSDK.GetSfx("Stage/Fail.wav");
#if MANIA_USE_PLUS
    LevelSelect->sfxRing     = RSDK.GetSfx("Global/Ring.wav");
    LevelSelect->sfxEmerald  = RSDK.GetSfx("Special/Emerald.wav");
    LevelSelect->sfxContinue = RSDK.GetSfx("Special/Continue.wav");
    LevelSelect->sfxMedalGot = RSDK.GetSfx("Special/MedalCaught.wav");
#endif

    RSDK.ResetEntitySlot(0, LevelSelect->classID, NULL);

    UIPicture->aniFrames = RSDK.LoadSpriteAnimation("LSelect/Icons.bin", SCOPE_STAGE);
    UIText->aniFrames    = RSDK.LoadSpriteAnimation("LSelect/Text.bin", SCOPE_STAGE);

    LevelSelect->startMusicID = 0;
    LevelSelect->soundTestMax = 0;
    foreach_all(Music, music)
    {
        if (!LevelSelect->startMusicID) {
            LevelSelect->startMusicID = RSDK.GetEntitySlot(music);
        }
        ++LevelSelect->soundTestMax;
    }
    ++LevelSelect->startMusicID;
    --LevelSelect->soundTestMax;

    globals->medalMods |= MEDAL_DEBUGMODE;
#if MANIA_USE_PLUS
    LevelSelect->cheatCodePtrs[0]  = LevelSelect->cheat_RickyMode;
    LevelSelect->cheatCodePtrs[1]  = LevelSelect->cheat_AllEmeralds;
    LevelSelect->cheatCodePtrs[2]  = LevelSelect->cheat_MaxContinues;
    LevelSelect->cheatCodePtrs[3]  = LevelSelect->cheat_SwapGameMode;
    LevelSelect->cheatCodePtrs[4]  = LevelSelect->cheat_UnlockAllMedals;
    LevelSelect->cheatCodePtrs[5]  = LevelSelect->cheat_SuperDash;
    LevelSelect->cheatCodePtrs[6]  = LevelSelect->cheat_MaxControl;
    LevelSelect->cheatCodePtrs[7]  = LevelSelect->cheat_ToggleSuperMusic;
    LevelSelect->cheatCodePtrs[8]  = LevelSelect->cheat_AllTimeStones;
    LevelSelect->cheatCodePtrs[9]  = LevelSelect->cheat_AllSuperEmeralds;
    LevelSelect->cheatCodePtrs[10] = LevelSelect->cheat_Secret;

    LevelSelect->checkCheatActivated[0]  = LevelSelect_Cheat_RickyMode;
    LevelSelect->checkCheatActivated[1]  = LevelSelect_Cheat_AllEmeralds;
    LevelSelect->checkCheatActivated[2]  = LevelSelect_Cheat_MaxContinues;
    LevelSelect->checkCheatActivated[3]  = LevelSelect_Cheat_SwapGameMode;
    LevelSelect->checkCheatActivated[4]  = LevelSelect_Cheat_UnlockAllMedals;
    LevelSelect->checkCheatActivated[5]  = LevelSelect_Cheat_SuperDash;
    LevelSelect->checkCheatActivated[6]  = LevelSelect_Cheat_MaxControl;
    LevelSelect->checkCheatActivated[7]  = LevelSelect_Cheat_ToggleSuperMusic;
    LevelSelect->checkCheatActivated[8]  = LevelSelect_Cheat_AllTimeStones;
    LevelSelect->checkCheatActivated[9]  = LevelSelect_Cheat_AllSuperEmeralds;
    LevelSelect->checkCheatActivated[10] = LevelSelect_Cheat_Secret;

    LevelSelect->cheatCodePos[0]  = 0;
    LevelSelect->cheatCodePos[1]  = 0;
    LevelSelect->cheatCodePos[2]  = 0;
    LevelSelect->cheatCodePos[3]  = 0;
    LevelSelect->cheatCodePos[4]  = 0;
    LevelSelect->cheatCodePos[5]  = 0;
    LevelSelect->cheatCodePos[6]  = 0;
    LevelSelect->cheatCodePos[7]  = 0;
    LevelSelect->cheatCodePos[8]  = 0;
    LevelSelect->cheatCodePos[9]  = 0;
    LevelSelect->cheatCodePos[10] = 0;
#endif
    LevelSelect->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(LevelSelect->dpadFrames, 0, &LevelSelect->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(LevelSelect->dpadFrames, 1, &LevelSelect->dpadTouchAnimator, true, 0);

    LevelSelect->touchDir = -1;

    LevelSelect->allEmeralds = false;
}

#if MANIA_USE_PLUS
void LevelSelect_Cheat_AllEmeralds(void)
{
    Music_FadeOut(0.125);
    RSDK.PlaySfx(LevelSelect->sfxEmerald, false, 255);

    for (int32 e = 0; e < 7; ++e) SaveGame_SetEmerald(e);

    if (Addendum_GetOptionsRAM()->secondaryGems == SECONDGEMS_SUPEREMERALD)
        LevelSelect->allEmeralds = true;
}

void LevelSelect_Cheat_ToggleSuperMusic(void)
{
    RSDK.PlaySfx(LevelSelect->sfxRing, false, 255);
    globals->superMusicEnabled ^= 1;
}

void LevelSelect_Cheat_MaxContinues(void)
{
    RSDK.PlaySfx(LevelSelect->sfxContinue, false, 255);
    SaveGame_GetSaveRAM()->continues = 99;
}

void LevelSelect_Cheat_MaxControl(void)
{
    RSDK.PlaySfx(LevelSelect->sfxRing, false, 255);
    globals->medalMods &= ~MEDAL_NODROPDASH;
    globals->medalMods |= MEDAL_INSTASHIELD;
    globals->medalMods |= MEDAL_PEELOUT;
}

void LevelSelect_Cheat_RickyMode(void)
{
    RSDK.PlaySfx(LevelSelect->sfxRing, false, 255);
    globals->secrets ^= SECRET_RICKYMODE;
}

void LevelSelect_Cheat_SuperDash(void)
{
    RSDK.PlaySfx(LevelSelect->sfxRing, false, 255);
    globals->secrets ^= SECRET_SUPERDASH;
}

void LevelSelect_Cheat_SwapGameMode(void)
{
    if (API.CheckDLC(DLC_PLUS)) {
        RSDK.PlaySfx(LevelSelect->sfxRing, false, 255);
        if (globals->gameMode == MODE_ENCORE) {
            globals->gameMode = MODE_MANIA;
        }
        else {
            globals->gameMode = MODE_ENCORE;
            if (globals->medalMods & MEDAL_P2SONIC || MEDAL_P2TAILS || MEDAL_P2KNUX || MEDAL_P2MIGHTY || MEDAL_P2RAY || MEDAL_P2AMY)
                globals->medalMods &= MEDAL_P2NONE;
        }
    }
}

void LevelSelect_Cheat_UnlockAllMedals(void)
{
    if (globals->superSecret && (globals->secrets & SECRET_RICKYMODE)) {
        RSDK.PlaySfx(LevelSelect->sfxMedalGot, false, 255);
        GameProgress_UnlockAll();
        GameProgress_LockAllSpecialClear();
    }
    else {
        RSDK.PlaySfx(LevelSelect->sfxRing, false, 255);
    }
}

void LevelSelect_Cheat_AllSuperEmeralds(void)
{
    if (Addendum_GetOptionsRAM()->secondaryGems == SECONDGEMS_SUPEREMERALD) {
        if (LevelSelect->allEmeralds) {
            Music_FadeOut(0.125);
            RSDK.PlaySfx(LevelSelect->sfxContinue, false, 255);
            RSDK.PlaySfx(LevelSelect->sfxEmerald, false, 254);

            for (int32 e = 0; e < 7; ++e) Addendum_SetSuperEmerald(e);
        }
    }
}

void LevelSelect_Cheat_AllTimeStones(void)
{
    if (Addendum_GetOptionsRAM()->secondaryGems == SECONDGEMS_TIMESTONE) {
        Music_FadeOut(0.125);
        RSDK.PlaySfx(LevelSelect->sfxEmerald, false, 255);

        for (int32 t = 0; t < 7; ++t) Addendum_SetTimeStone(t);
    }
}

void LevelSelect_Cheat_Secret(void)
{
    Music_FadeOut(0.125);
    RSDK.PlaySfx(LevelSelect->sfxAltRing, false, 255);
    addendumVar->secretMovesets = true;
}
#endif

void LevelSelect_Draw_Fade(void)
{
    RSDK_THIS(LevelSelect);
    RSDK.FillScreen(0x000000, self->timer, self->timer - 128, self->timer - 256);
}

void LevelSelect_State_Init(void)
{
    RSDK_THIS(LevelSelect);

    int32 labelPos[32];
    int32 lastY = 0;
    foreach_all(UIText, labelPosPtrL)
    {
        if (labelPosPtrL->position.x < 0x1000000 && labelPosPtrL->position.y > lastY) {
            lastY                        = labelPosPtrL->position.y;
            labelPos[self->labelCount++] = labelPosPtrL->position.y;
        }
    }

    foreach_all(UIText, labelL)
    {
        if (labelL->position.x < 0x1000000) {
            for (int32 i = 0; i < self->labelCount; ++i) {
                if (labelL->position.y == labelPos[i]) {
                    switch (labelL->align) {
                        case UITEXT_ALIGN_LEFT: self->zoneNameLabels[i] = labelL; break;

                        default:
                        case UITEXT_ALIGN_CENTER: break;

                        case UITEXT_ALIGN_RIGHT: self->stageIDLabels[i] = labelL; break;
                    }
                }
            }
        }
    }

    if (self->labelCount > 0)
        memset(labelPos, 0, sizeof(int32) * self->labelCount);

    lastY = 0;

    foreach_all(UIText, labelPosPtrR)
    {
        if (labelPosPtrR->position.x > 0x1000000 && labelPosPtrR->position.y > lastY) {
            lastY                        = labelPosPtrR->position.y;
            labelPos[self->labelCount++] = labelPosPtrR->position.y;
        }
    }

    foreach_all(UIText, labelR)
    {
        if (labelR->position.x > 0x1000000 && self->labelCount > 0) {
            for (int32 i = 0; i < self->labelCount; ++i) {
                if (labelR->position.y == labelPos[i]) {
                    switch (labelR->align) {
                        case UITEXT_ALIGN_LEFT: self->zoneNameLabels[i] = labelR; break;

                        default:
                        case UITEXT_ALIGN_CENTER: break;

                        case UITEXT_ALIGN_RIGHT: self->stageIDLabels[i] = labelR;
#if MANIA_USE_PLUS
                            if (!labelR->data0 && labelR->data1 == 15)
                                self->pinballLabel = labelR;
#endif
                            break;
                    }
                }
            }
        }
    }

    for (int32 i = 0; i < self->labelCount; ++i) {
        if (!self->zoneNameLabels[i]) {
            for (int32 v = i; v >= 0; --v) {
                if (self->zoneNameLabels[v]) {
                    self->zoneNameLabels[i] = self->zoneNameLabels[v];
                    break;
                }
            }
        }
    }

    LevelSelect_SetLabelHighlighted(true);

    foreach_all(UIText, soundTestLabel)
    {
        if (soundTestLabel->align == UITEXT_ALIGN_CENTER) {
            self->soundTestLabel  = soundTestLabel;
            soundTestLabel->align = UITEXT_ALIGN_LEFT;
        }
    }

    self->leaderCharacterID   = HUD_CharacterIndexFromID(GET_CHARACTER_ID(1)) + 1;
    self->sidekickCharacterID = HUD_CharacterIndexFromID(GET_CHARACTER_ID(2)) + 1;

    foreach_all(UIPicture, picture)
    {
        if (picture->listID == 1) {
            self->zoneIcon = picture;

            // Bug Details(?):
            // frameID is equal to... playerID...?
            // this feels like a slight oversight, though idk what it is meant to be
            picture->animator.frameID = self->leaderCharacterID;
        }
        else if (picture->listID == 3) {
            if (picture->frameID)
                self->player2Icon = picture;
            else
                self->player1Icon = picture;
        }
    }

    self->stageIDLabels[self->labelCount - 1] = self->soundTestLabel;

    LevelSelect_ManagePlayerIcon();

    self->state = LevelSelect_State_FadeIn;
}

void LevelSelect_State_FadeIn(void)
{
    RSDK_THIS(LevelSelect);

    if (self->timer <= 0) {
        self->timer     = 0;
        self->state     = LevelSelect_State_Navigate;
        self->stateDraw = StateMachine_None;
    }
    else {
        self->timer -= 16;
    }
}

void LevelSelect_State_Navigate(void)
{
    RSDK_THIS(LevelSelect);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls) {
        LevelSelect_HandleTouchInput();
    }

    bool32 confirmPress = API_GetConfirmButtonFlip() ? ControllerInfo->keyB.press : ControllerInfo->keyA.press;

    if (ControllerInfo->keyUp.down || AnalogStickInfoL->keyUp.down) {
        self->timer = (self->timer + 1) & 0xF;

        if (self->timer == 1) {
            LevelSelect_SetLabelHighlighted(false);
#if MANIA_USE_PLUS
            if (--self->labelID == 28 && !API.CheckDLC(DLC_PLUS))
#endif
                --self->labelID;

            if (self->labelID < 0)
                self->labelID = self->labelCount - 1;

            LevelSelect_SetLabelHighlighted(true);
        }
    }
    else if (ControllerInfo->keyDown.down || AnalogStickInfoL->keyDown.down) {
        self->timer = (self->timer + 1) & 0xF;
        if (self->timer == 1) {
            LevelSelect_SetLabelHighlighted(false);

#if MANIA_USE_PLUS
            if (++self->labelID == 28 && !API.CheckDLC(DLC_PLUS))
#endif
                ++self->labelID;

            if (self->labelID == self->labelCount)
                self->labelID = 0;

            LevelSelect_SetLabelHighlighted(true);
        }
    }
    else if (AnalogStickInfoL->keyLeft.press || ControllerInfo->keyLeft.press || ControllerInfo->keyRight.press || AnalogStickInfoL->keyRight.press) {
        self->timer = 0;

        if (self->labelID >= self->labelCount - 1) {
            if (AnalogStickInfoL->keyLeft.press || ControllerInfo->keyLeft.press) {
                if (--self->soundTestID < 0)
                    self->soundTestID = LevelSelect->soundTestMax - 1;
            }
            else if (++self->soundTestID >= LevelSelect->soundTestMax) {
                self->soundTestID = 0;
            }

            EntityUIText *soundTest  = self->soundTestLabel;
            soundTest->text.chars[0] = self->soundTestID >> 4;
            soundTest->text.chars[1] = self->soundTestID & 0xF;
        }
        else {
            LevelSelect_HandleColumnChange();
        }
    }
    else if (confirmPress || ControllerInfo->keyStart.press) {
        if (self->labelID < self->labelCount - 1 || ControllerInfo->keyStart.press) {
#if MANIA_USE_PLUS
            if (self->labelID != 28 || API.CheckDLC(DLC_PLUS))
                LevelSelect_HandleNewStagePos();
            else
                RSDK.PlaySfx(LevelSelect->sfxFail, false, 255);
#else
            LevelSelect_HandleNewStagePos();
#endif
        }
        else {
            EntityMusic *track = RSDK_GET_ENTITY(self->soundTestID + LevelSelect->startMusicID, Music);
            Music_PlayTrackPtr(track);

#if MANIA_USE_PLUS
            self->offsetUFO = self->soundTestID % 14;
            self->offsetBSS = self->soundTestID & 0x1F;
            for (int32 i = 0; i < 10; ++i) {
                if (self->soundTestID != LevelSelect->cheatCodePtrs[i][LevelSelect->cheatCodePos[i]]) {
                    LevelSelect->cheatCodePos[i] = 0;
                }
                else {
                    LevelSelect->cheatCodePos[i]++;
                    if (LevelSelect->cheatCodePtrs[i][LevelSelect->cheatCodePos[i]] == 255) {
                        LevelSelect->checkCheatActivated[i]();
                        LevelSelect->cheatCodePos[i] = 0;
                    }
                }
            }
#endif
        }
    }
#if GAME_VERSION == VER_100
    else if (TouchInfo->count) {

        self->timer = (self->timer + 1) & 0xF;
        if (self->timer == 1) {
            int32 selectedLabel = -1;

            int32 labelID = self->labelCount - 1;
            for (int32 l = 0; l < self->labelCount; ++l, labelID--) {
                EntityUIText *label = self->zoneNameLabels[labelID];

                if (label && labelID != self->labelID) {
                    int32 xOff = 5 * (label->text.length * 0.5);

                    for (int32 f = 0; f < TouchInfo->count; ++f) {
                        float tx = TouchInfo->x[f] * ScreenInfo->size.x;
                        float ty = TouchInfo->y[f] * ScreenInfo->size.y;

                        if (tx > ((label->position.x >> 16) - xOff) && tx < (xOff + (label->position.x >> 16))) {
                            if (ty < ((label->position.y >> 16) + 10) && ty > ((label->position.y >> 16) - 10))
                                selectedLabel = labelID;
                        }
                    }
                }
            }

            if (selectedLabel == -1) {
                labelID = self->labelCount - 1;
                for (int32 l = 0; l < self->labelCount; ++l) {
                    EntityUIText *label = self->stageIDLabels[labelID];

                    if (label && labelID != self->labelID) {
                        int32 xOff = 5 * (label->text.length * 0.5);

                        for (int32 f = 0; f < TouchInfo->count; ++f) {
                            float tx = TouchInfo->x[f] * ScreenInfo->size.x;
                            float ty = TouchInfo->y[f] * ScreenInfo->size.y;

                            if (tx > ((label->position.x >> 16) - xOff) && tx < (xOff + (label->position.x >> 16))) {
                                if (ty < ((label->position.y >> 16) + 10) && ty > ((label->position.y >> 16) - 10))
                                    selectedLabel = labelID;
                            }
                        }
                    }
                    labelID--;
                }
            }

            for (int32 f = 0; f < TouchInfo->count; ++f) {
                float tx = TouchInfo->x[f] * ScreenInfo->size.x;
                float ty = TouchInfo->y[f] * ScreenInfo->size.y;

                if (tx > 250.0 && ty > 170.0 && tx < 310.0 && ty < 230.0)
                    LevelSelect_HandleNewStagePos();
            }

            if (selectedLabel != -1) {
                LevelSelect_SetLabelHighlighted(false);
                self->labelID = selectedLabel;
                LevelSelect_SetLabelHighlighted(true);
            }
        }
    }
#endif
    else {
        self->timer = 0;
    }

    if (ControllerInfo->keyX.press) {
        ++self->leaderCharacterID;
        LevelSelect_ManagePlayerIcon();
    }

    if (ControllerInfo->keyY.press) {
        ++self->sidekickCharacterID;
        LevelSelect_ManagePlayerIcon();
    }

    EntityUIPicture *zoneIcon = self->zoneIcon;
    if (self->labelID >= self->labelCount - 1)
        RSDK.SetSpriteAnimation(UIPicture->aniFrames, 2, &zoneIcon->animator, true, self->leaderCharacterID);
    else
        RSDK.SetSpriteAnimation(UIPicture->aniFrames, 1, &zoneIcon->animator, true, self->stageIDLabels[self->labelID]->data1);
}

void LevelSelect_State_FadeOut(void)
{
    RSDK_THIS(LevelSelect);

    if (self->timer >= 1024)
        RSDK.LoadScene();
    else
        self->timer += 16;
}

void LevelSelect_ManagePlayerIcon(void)
{
    RSDK_THIS(LevelSelect);

    EntityUIPicture *player1 = self->player1Icon;
    EntityUIPicture *player2 = self->player2Icon;

    switch (self->leaderCharacterID) {
        case LSELECT_PLAYER_SONIC:
        case LSELECT_PLAYER_TAILS:
        case LSELECT_PLAYER_KNUCKLES: player1->animator.frameID = self->leaderCharacterID; break;
#if MANIA_USE_PLUS
        case LSELECT_PLAYER_MIGHTY:
        case LSELECT_PLAYER_RAY:
        case LSELECT_PLAYER_AMY:
            if (!API.CheckDLC(DLC_PLUS))
                self->leaderCharacterID = LSELECT_PLAYER_SONIC;

            player1->animator.frameID = self->leaderCharacterID;
            break;
#endif

        default:
            self->leaderCharacterID   = LSELECT_PLAYER_SONIC;
            player1->animator.frameID = LSELECT_PLAYER_SONIC;
            break;
    }

    switch (self->sidekickCharacterID) {
        case LSELECT_PLAYER_SONIC:
        case LSELECT_PLAYER_TAILS:
        case LSELECT_PLAYER_KNUCKLES: player2->animator.frameID = self->sidekickCharacterID; break;
#if MANIA_USE_PLUS
        case LSELECT_PLAYER_MIGHTY:
        case LSELECT_PLAYER_RAY:
        case LSELECT_PLAYER_AMY:
            if (!API.CheckDLC(DLC_PLUS))
                self->sidekickCharacterID = LSELECT_PLAYER_SONIC;

            player2->animator.frameID = self->sidekickCharacterID;
            break;
#endif

        default:
            self->sidekickCharacterID = LSELECT_PLAYER_NONE;
            player2->animator.frameID = LSELECT_PLAYER_NONE;
            break;
    }
}

void LevelSelect_SetLabelHighlighted(bool32 highlight)
{
    RSDK_THIS(LevelSelect);

    EntityUIText *zoneName = self->zoneNameLabels[self->labelID];
    if (zoneName)
        zoneName->highlighted = highlight;

    EntityUIText *stageID = self->stageIDLabels[self->labelID];
    if (stageID)
        stageID->highlighted = highlight;
}

void LevelSelect_HandleColumnChange(void)
{
    RSDK_THIS(LevelSelect);

    EntityUIText *curLabel = self->stageIDLabels[self->labelID];
    if (!curLabel)
        curLabel = self->zoneNameLabels[self->labelID];

    int32 distance         = 0x1000000;
    EntityUIText *labelPtr = NULL;
    if (curLabel->position.x < 0x1000000) {
        foreach_active(UIText, label)
        {
            if (label->position.x > 0x1000000) {
                int32 pos = abs(label->position.y - curLabel->position.y);
                if (pos < distance) {
                    distance = pos;
                    labelPtr = label;
                }
            }
        }
    }
    else {
        foreach_active(UIText, label)
        {
            if (label->position.x < 0x1000000) {
                int32 dist = abs(label->position.y - curLabel->position.y);
                if (dist < distance) {
                    distance = dist;
                    labelPtr = label;
                }
            }
        }
    }

    int32 labelID = self->labelID;
    for (int32 i = 0; i < self->labelCount; ++i) {
        if (self->stageIDLabels[i] == labelPtr || self->zoneNameLabels[i] == labelPtr) {
            labelID = i;
            break;
        }
    }

    if (self->labelID != labelID) {
        LevelSelect_SetLabelHighlighted(false);

        self->labelID = labelID;
        LevelSelect_SetLabelHighlighted(true);
    }
}

void LevelSelect_HandleNewStagePos(void)
{
    RSDK_THIS(LevelSelect);

    EntityUIText *curLabel = self->stageIDLabels[self->labelID];
    if (!curLabel)
        curLabel = self->zoneNameLabels[self->labelID];

    if (curLabel->selectable) {
        char buffer[32];
        RSDK.GetCString(buffer, &curLabel->tag);
        RSDK.SetScene(buffer, "");
        SceneInfo->listPos += curLabel->data0;

#if MANIA_USE_PLUS
        if (self->labelID == self->labelCount - 4)
            SceneInfo->listPos += self->offsetUFO;
        else if (self->labelID == self->labelCount - 3)
            SceneInfo->listPos += self->offsetBSS;
        else if (globals->gameMode == MODE_ENCORE)
            SceneInfo->listPos = Zone_GetListPos_EncoreMode();
#endif

        int32 leaderID = 0;
        if (self->leaderCharacterID > 0)
            leaderID = 1 << (self->leaderCharacterID - 1);

        int32 sidekickID = 0;
        if (self->sidekickCharacterID > 0)
            sidekickID = 1 << (self->sidekickCharacterID - 1);

        globals->playerID = leaderID | (sidekickID << 8);

        // MSZ1K check
        if (CHECK_CHARACTER_ID(ID_KNUCKLES, 1) && curLabel->data0 == 15)
            ++SceneInfo->listPos;

        self->timer     = 0;
        self->state     = LevelSelect_State_FadeOut;
        self->stateDraw = LevelSelect_Draw_Fade;
        Music_FadeOut(0.1);
    }
    else {
        RSDK.PlaySfx(LevelSelect->sfxFail, false, 255);
    }
}

void LevelSelect_HandleTouchInput(void)
{
    RSDK_THIS(LevelSelect);

    uint8 dir = -1;

    int32 tx = 0, ty = 0;
    if (LevelSelect_CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, &tx, &ty) >= 0) {
        tx -= 56;
        ty -= 184;

        switch (((RSDK.ATan2(tx, ty) + 32) & 0xFF) >> 6) {
            case 0:
                ControllerInfo->keyRight.down |= true;
                dir = 0;
                break;

            case 1:
                ControllerInfo->keyDown.down |= true;
                dir = 1;
                break;

            case 2:
                ControllerInfo->keyLeft.down |= true;
                dir = 2;
                break;

            case 3:
                ControllerInfo->keyUp.down |= true;
                dir = 3;
                break;
        }
    }

    InputState *confirmButton = API_GetConfirmButtonFlip() ? &ControllerInfo->keyB : &ControllerInfo->keyA;

    int32 jumpX = ScreenInfo->size.x - 104;
    int32 jumpY = 140;

    // fixes a bug with button vs touch
    bool32 touchedConfirm = false;
    if (LevelSelect_CheckTouchRect(jumpX, jumpY, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
        confirmButton->down |= true;
        touchedConfirm = true;
    }

    bool32 touchedSwap = false;
    if (LevelSelect_CheckTouchRect(jumpX, jumpY - 64, ScreenInfo->size.x, jumpY, NULL, NULL) >= 0) {
        ControllerInfo->keyX.down |= true;
        touchedSwap = true;
    }

    bool32 touchedSwapP2 = false;
    if (LevelSelect_CheckTouchRect(jumpX - 64, jumpY, jumpX, ScreenInfo->size.x, NULL, NULL) >= 0) {
        ControllerInfo->keyY.down |= true;
        touchedSwapP2 = true;
    }

    if (dir != LevelSelect->touchDir && ControllerInfo->keyUp.down)
        ControllerInfo->keyUp.press |= ControllerInfo->keyUp.down;

    if (dir != LevelSelect->touchDir && ControllerInfo->keyDown.down)
        ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;

    if (dir != LevelSelect->touchDir && ControllerInfo->keyLeft.down)
        ControllerInfo->keyLeft.press |= ControllerInfo->keyLeft.down;

    if (dir != LevelSelect->touchDir && ControllerInfo->keyRight.down)
        ControllerInfo->keyRight.press |= ControllerInfo->keyRight.down;

    if (!LevelSelect->touchConfirm && touchedConfirm)
        confirmButton->press |= confirmButton->down;

    if (!LevelSelect->touchSwap && touchedSwap)
        ControllerInfo->keyX.press |= ControllerInfo->keyX.down;
    LevelSelect->touchSwap = ControllerInfo->keyX.down;

    if (!LevelSelect->touchSwapP2 && touchedSwapP2)
        ControllerInfo->keyY.press |= ControllerInfo->keyY.down;
    LevelSelect->touchSwapP2 = ControllerInfo->keyY.down;

    LevelSelect->touchConfirm = confirmButton->down;
    LevelSelect->touchDir     = dir;
}

void LevelSelect_DrawTouchUI(void)
{
    RSDK_THIS(LevelSelect);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    LevelSelect->dpadPos.x = TO_FIXED(56);
    LevelSelect->dpadPos.y = TO_FIXED(184);

    LevelSelect->confirmPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 56);
    LevelSelect->confirmPos.y = TO_FIXED(188);

    LevelSelect->swapPos.x = LevelSelect->confirmPos.x;
    LevelSelect->swapPos.y = LevelSelect->confirmPos.y - TO_FIXED(64);

    LevelSelect->swapP2Pos.x = LevelSelect->confirmPos.x - TO_FIXED(64);
    LevelSelect->swapP2Pos.y = LevelSelect->confirmPos.y;

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * 0.625);
    self->scale.x = 0x200;
    self->scale.y = 0x200;

    InputState *confirmButton = API_GetConfirmButtonFlip() ? &ControllerInfo->keyB : &ControllerInfo->keyA;

    bool32 canMove    = true;
    bool32 canConfirm = true;
    bool32 canSwap    = true;
    bool32 canSwapP2  = true;

    if (canMove) {
        if (LevelSelect->dpadAlpha < opacity)
            LevelSelect->dpadAlpha += 4;

        // Draw DPad
        self->alpha                           = LevelSelect->dpadAlpha;
        LevelSelect->dpadAnimator.frameID = 10;
        RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->dpadPos, true);

        if (LevelSelect->touchDir == 2 || ControllerInfo->keyLeft.down) {
            self->alpha                                = opacity;
            LevelSelect->dpadTouchAnimator.frameID = 6;
            RSDK.DrawSprite(&LevelSelect->dpadTouchAnimator, &LevelSelect->dpadPos, true);
        }
        else {
            self->alpha                           = LevelSelect->dpadAlpha;
            LevelSelect->dpadAnimator.frameID = 6;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->dpadPos, true);
        }

        if (LevelSelect->touchDir == 1 || ControllerInfo->keyDown.down) {
            self->alpha                                = opacity;
            LevelSelect->dpadTouchAnimator.frameID = 9;
            RSDK.DrawSprite(&LevelSelect->dpadTouchAnimator, &LevelSelect->dpadPos, true);
        }
        else {
            self->alpha                           = LevelSelect->dpadAlpha;
            LevelSelect->dpadAnimator.frameID = 9;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->dpadPos, true);
        }

        if (LevelSelect->touchDir == 0 || ControllerInfo->keyRight.down) {
            self->alpha                                = opacity;
            LevelSelect->dpadTouchAnimator.frameID = 7;
            RSDK.DrawSprite(&LevelSelect->dpadTouchAnimator, &LevelSelect->dpadPos, true);
        }
        else {
            self->alpha                           = LevelSelect->dpadAlpha;
            LevelSelect->dpadAnimator.frameID = 7;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->dpadPos, true);
        }

        if (LevelSelect->touchDir == 3 || ControllerInfo->keyUp.down) {
            self->alpha                                = opacity;
            LevelSelect->dpadTouchAnimator.frameID = 8;
            RSDK.DrawSprite(&LevelSelect->dpadTouchAnimator, &LevelSelect->dpadPos, true);
        }
        else {
            self->alpha                           = LevelSelect->dpadAlpha;
            LevelSelect->dpadAnimator.frameID = 8;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->dpadPos, true);
        }

        if ((!ControllerInfo->keyUp.down && !ControllerInfo->keyDown.down && !ControllerInfo->keyLeft.down && !ControllerInfo->keyRight.down)) {
            self->alpha               = LevelSelect->dpadAlpha;
            LevelSelect->dpadAnimator.frameID = 11;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->dpadPos, true);
        }
    }
    else {
        if (LevelSelect->dpadAlpha > 0) {
            LevelSelect->dpadAlpha -= 4;
        }

        self->alpha = LevelSelect->dpadAlpha;
        if (self->alpha > 0) {
            LevelSelect->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->dpadPos, true);
        }
    }

    if (canConfirm) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (LevelSelect->confirmAlpha < opacity)
                LevelSelect->confirmAlpha += 4;

            if (confirmButton->down) {
                self->alpha                                = opacity;
                LevelSelect->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&LevelSelect->dpadTouchAnimator, &LevelSelect->confirmPos, true);
            }
            else {
                self->alpha                           = LevelSelect->confirmAlpha;
                LevelSelect->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->confirmPos, true);
            }
        }
        else {
            LevelSelect->confirmAlpha = 0;
        }
    }
    else {
        if (LevelSelect->confirmAlpha > 0)
            LevelSelect->confirmAlpha -= 4;

        self->alpha = LevelSelect->confirmAlpha;
        if (self->alpha > 0) {
            LevelSelect->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->confirmPos, true);
        }
    }

    if (canSwap) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (LevelSelect->swapAlpha < opacity)
                LevelSelect->swapAlpha += 4;

            if (ControllerInfo->keyX.down) {
                self->alpha                                = opacity;
                LevelSelect->dpadTouchAnimator.frameID = 4;
                RSDK.DrawSprite(&LevelSelect->dpadTouchAnimator, &LevelSelect->swapPos, true);
            }
            else {
                self->alpha                           = LevelSelect->swapAlpha;
                LevelSelect->dpadAnimator.frameID = 4;
                RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->swapPos, true);
            }
        }
        else {
            LevelSelect->swapAlpha = 0;
        }
    }
    else {
        if (LevelSelect->swapAlpha > 0)
            LevelSelect->swapAlpha -= 4;

        self->alpha = LevelSelect->swapAlpha;
        if (self->alpha > 0) {
            LevelSelect->dpadAnimator.frameID = 4;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->swapPos, true);
        }
    }

    if (canSwapP2) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (LevelSelect->swapP2Alpha < opacity)
                LevelSelect->swapP2Alpha += 4;

            if (ControllerInfo->keyY.down) {
                self->alpha                                = opacity;
                LevelSelect->dpadTouchAnimator.frameID = 4;
                RSDK.DrawSprite(&LevelSelect->dpadTouchAnimator, &LevelSelect->swapP2Pos, true);
            }
            else {
                self->alpha                           = LevelSelect->swapP2Alpha;
                LevelSelect->dpadAnimator.frameID = 4;
                RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->swapP2Pos, true);
            }
        }
        else {
            LevelSelect->swapP2Alpha = 0;
        }
    }
    else {
        if (LevelSelect->swapP2Alpha > 0)
            LevelSelect->swapP2Alpha -= 4;

        self->alpha = LevelSelect->swapP2Alpha;
        if (self->alpha > 0) {
            LevelSelect->dpadAnimator.frameID = 4;
            RSDK.DrawSprite(&LevelSelect->dpadAnimator, &LevelSelect->swapP2Pos, true);
        }
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

int32 LevelSelect_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32* fx, int32* fy)
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
void LevelSelect_EditorDraw(void) {}

void LevelSelect_EditorLoad(void)
{
    if (UIPicture)
        UIPicture->aniFrames = RSDK.LoadSpriteAnimation("LSelect/Icons.bin", SCOPE_STAGE);

    if (UIText)
        UIText->aniFrames = RSDK.LoadSpriteAnimation("LSelect/Text.bin", SCOPE_STAGE);
}
#endif

void LevelSelect_Serialize(void) {}
