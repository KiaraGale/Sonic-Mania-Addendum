// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: HUD Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectHUD *HUD;

void HUD_Update(void)
{
    RSDK_THIS(HUD);

    self->enableTimeFlash = false;
    self->enableRingFlash = false;

#if MANIA_USE_PLUS
    if (self->replayClapAnimator.animationID == 11)
        RSDK.ProcessAnimation(&self->replayClapAnimator);
#endif
}

void HUD_LateUpdate(void)
{
    RSDK_THIS(HUD);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_COMPETITION) {
        for (self->screenID = 0; self->screenID < RSDK.GetVideoSetting(VIDEOSETTING_SCREENCOUNT); ++self->screenID) {
            StateMachine_Run(self->vsStates[self->screenID]);
        }
    }
    else {
        StateMachine_Run(self->state);
    }
#else
    StateMachine_Run(self->state);
#endif

#if GAME_VERSION != VER_100
    if (globals->gameMode < MODE_TIMEATTACK) {
        EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        if (!touchControls) {
            if (SceneInfo->timeEnabled && player->rings >= 50 && player->superState < SUPERSTATE_SUPER
                && SaveGame_GetSaveRAM()->collectedEmeralds >= 0b01111111) {
                if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                    if (Addendum_GetSaveRAM()->emeraldsTransferred) {
                        if (Addendum_GetSaveRAM()->collectedSuperEmeralds == 0b01111111) {
                            if (sku_platform == PLATFORM_PC || sku_platform == PLATFORM_SWITCH || sku_platform == PLATFORM_DEV)
                                HUD_GetActionButtonFrames();

                            if (self->actionPromptPos < TO_FIXED(24))
                                self->actionPromptPos += TO_FIXED(8);
                        }
                        else {
                            if (self->actionPromptPos > -TO_FIXED(32))
                                self->actionPromptPos -= TO_FIXED(8);
                        }
                    }
                    else {
                        if (sku_platform == PLATFORM_PC || sku_platform == PLATFORM_SWITCH || sku_platform == PLATFORM_DEV)
                            HUD_GetActionButtonFrames();

                        if (self->actionPromptPos < TO_FIXED(24))
                            self->actionPromptPos += TO_FIXED(8);
                    }
                }
                else {
                    if (sku_platform == PLATFORM_PC || sku_platform == PLATFORM_SWITCH || sku_platform == PLATFORM_DEV)
                        HUD_GetActionButtonFrames();

                    if (self->actionPromptPos < TO_FIXED(24))
                        self->actionPromptPos += TO_FIXED(8);
                }
            }
            else {
                if (self->actionPromptPos > -TO_FIXED(32))
                    self->actionPromptPos -= TO_FIXED(8);
            }
        }
    }
#if MANIA_USE_PLUS
    else if (globals->gameMode == MODE_TIMEATTACK) {
        if (HUD->showTAPrompt) {
            if (sku_platform == PLATFORM_PC || sku_platform == PLATFORM_SWITCH || sku_platform == PLATFORM_DEV) {
                HUD_GetButtonFrame(&self->superButtonAnimator, KEY_Y);
                HUD_GetButtonFrame(&self->saveReplayButtonAnimator, KEY_Y);
                HUD_GetButtonFrame(&self->thumbsUpButtonAnimator, KEY_START);
            }

            if (self->actionPromptPos < TO_FIXED(24))
                self->actionPromptPos += TO_FIXED(8);
        }
        else {
            if (self->actionPromptPos > -TO_FIXED(64))
                self->actionPromptPos -= TO_FIXED(8);
        }
    }
#endif
#endif
}

void HUD_StaticUpdate(void) {}

void HUD_Draw(void)
{
    RSDK_THIS(HUD);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);
    EntityPlayer *superSonic         = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    AddendumData *addendumData = Addendum_GetSaveRAM();
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    Vector2 drawPos;
    Vector2 scorePos, timePos, ringPos, lifePos, inputPos, itemPos, bossBarPos, bossIconPos, bossNamePos;

    scorePos.x    = self->scorePos.x;
    scorePos.y    = self->scorePos.y;
    timePos.x     = self->timePos.x;
    timePos.y     = self->timePos.y;
    ringPos.x     = self->ringsPos.x;
    ringPos.y     = self->ringsPos.y;
    lifePos.x     = self->lifePos.x;
    lifePos.y     = self->lifePos.y;
    inputPos.x    = self->inputPos.x;
    inputPos.y    = self->inputPos.y;
    itemPos.x     = self->itemPos.x;
    itemPos.y     = self->itemPos.y;
    if (globals->gameMode == MODE_COMPETITION) {
#if MANIA_USE_PLUS
        scorePos.x = self->vsScorePos[SceneInfo->currentScreenID].x;
        scorePos.y = self->vsScorePos[SceneInfo->currentScreenID].y;
        timePos.x  = self->vsTimePos[SceneInfo->currentScreenID].x;
        timePos.y  = self->vsTimePos[SceneInfo->currentScreenID].y;
        ringPos.x  = self->vsRingsPos[SceneInfo->currentScreenID].x;
        ringPos.y  = self->vsRingsPos[SceneInfo->currentScreenID].y;
        lifePos.x  = self->vsLifePos[SceneInfo->currentScreenID].x;
        lifePos.y  = self->vsLifePos[SceneInfo->currentScreenID].y;
        inputPos.x = self->vsInputPos[SceneInfo->currentScreenID].x;
        inputPos.y = self->vsInputPos[SceneInfo->currentScreenID].y;
        itemPos.x  = self->vsItemPos[SceneInfo->currentScreenID].x;
        itemPos.y  = self->vsItemPos[SceneInfo->currentScreenID].y;
#endif

        foreach_active(Player, plr)
        {
            if (plr != player) {
                self->playerIDAnimator.frameID = plr->playerID;
                RSDK.DrawSprite(&self->playerIDAnimator, &plr->position, false);
            }
        }
    }
#if MANIA_USE_PLUS
    else {
        if (HUD->swapCooldown > 0) {
            RSDK.ProcessAnimation(&self->playerIDAnimator);
            RSDK.DrawSprite(&self->playerIDAnimator, &player->position, false);
            --HUD->swapCooldown;
        }
    }
#endif

    if (RSDK.CheckSceneFolder("ERZ") && superSonic->rings <= 10)
        self->ringFlashFrame = ((Zone->persistentTimer >> 3) & 1);
    else
        self->ringFlashFrame = player->rings ? 0 : ((Zone->persistentTimer >> 3) & 1);

#if GAME_VERSION != VER_100
#if MANIA_USE_PLUS
    self->timeFlashFrame = 0;
    if ((SceneInfo->minutes == 9 && isMainGameMode() && addendumOptions->timeLimit == TIMELIMIT_ON) || ActClear->disableTimeBonus)
        self->timeFlashFrame = (Zone->persistentTimer >> 3) & 1;
#else
    if (SceneInfo->minutes == 9 && globals->gameMode < MODE_TIMEATTACK)
        self->timeFlashFrame = (Zone->persistentTimer >> 3) & 1;
#endif
#endif

    // Draw "Score"
    self->hudElementsAnimator.frameID = 0;
    RSDK.DrawSprite(&self->hudElementsAnimator, &scorePos, true);

    // Draw Score
    drawPos.x = scorePos.x + TO_FIXED(97);
    drawPos.y = scorePos.y + TO_FIXED(14);
    HUD_DrawNumbersBase10(&drawPos, player->score, 0);

    // Draw "Time"
#if GAME_VERSION != VER_100
    self->hudElementsAnimator.frameID = self->timeFlashFrame + 1;
#else
    self->hudElementsAnimator.frameID = 1;
#endif
    RSDK.DrawSprite(&self->hudElementsAnimator, &timePos, true);

    if (!self->enableTimeFlash || Zone->persistentTimer & 8) {
        // Draw ":"
        drawPos.x                         = timePos.x + TO_FIXED(52);
        drawPos.y                         = timePos.y - TO_FIXED(2);
        self->hudElementsAnimator.frameID = 12;
        RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

        // Draw Milliseconds
        drawPos.x = timePos.x + TO_FIXED(97);
        drawPos.y = timePos.y + TO_FIXED(14);
        HUD_DrawNumbersBase10(&drawPos, SceneInfo->milliseconds, 2);

        // Draw Seconds
        drawPos.x -= TO_FIXED(9);
        HUD_DrawNumbersBase10(&drawPos, SceneInfo->seconds, 2);

        // Draw Minutes
        drawPos.x -= TO_FIXED(9);
#if MANIA_USE_PLUS
        if (SceneInfo->minutes > 9 && addendumOptions->timeLimit == TIMELIMIT_OFF)
            HUD_DrawNumbersBase10(&drawPos, SceneInfo->minutes, 2);
        else
#endif
            HUD_DrawNumbersBase10(&drawPos, SceneInfo->minutes, 1);
    }

    // Draw "Rings"
    self->hudElementsAnimator.frameID = player->hyperRing ? self->ringFlashFrame + 20 : self->ringFlashFrame + 3;
    RSDK.DrawSprite(&self->hudElementsAnimator, &ringPos, true);

    if (!self->enableRingFlash || Zone->persistentTimer & 8) {
        // Draw Rings
        drawPos.x = ringPos.x + TO_FIXED(97);
        drawPos.y = ringPos.y + TO_FIXED(14);
        if (player->hyperRing)
            HUD_DrawNumbersHyperRing(&drawPos, player->rings);
        else
            HUD_DrawNumbersBase10(&drawPos, player->rings, 0);
    }

    if (RSDK_GET_ENTITY(SLOT_PLAYER1, Player)->classID == DebugMode->classID) {
        if (!touchControls) {
            if (player->camera) {
                // Draw Camera YPos
                drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
                drawPos.y = TO_FIXED(24);
                HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.y);

                // Draw Camera XPos
                drawPos.x -= TO_FIXED(9);
                HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.x);

                // Draw Player YPos
                drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
                drawPos.y += TO_FIXED(16);
                HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.y));

                // Draw Player XPos
                drawPos.x -= TO_FIXED(9);
                HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.x));
            }
        }
    }
#if MANIA_USE_PLUS
    else if (self->actionPromptPos > -TO_FIXED(64) && globals->gameMode == MODE_TIMEATTACK) {
        drawPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x) - self->actionPromptPos;
        drawPos.y = TO_FIXED(20);

        if (API.CheckDLC(DLC_PLUS)) {
            // Draw Replay Save Icon
            RSDK.DrawSprite(&self->replayClapAnimator, &drawPos, true);

            // Draw Replay Save Button
            drawPos.x -= TO_FIXED(28);
            if (HUD->replaySaveEnabled) {
                RSDK.DrawSprite(&self->saveReplayButtonAnimator, &drawPos, true);
            }
            else {
                self->inkEffect = INK_BLEND;
                RSDK.DrawSprite(&self->saveReplayButtonAnimator, &drawPos, true);

                self->inkEffect = INK_NONE;
            }

            drawPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x) - self->actionPromptPos;
            drawPos.y += TO_FIXED(28);
        }
        // Draw Thumbs Up Icon
        RSDK.DrawSprite(&self->thumbsUpIconAnimator, &drawPos, true);

        // Draw Thumbs Up Button
        drawPos.x -= TO_FIXED(28);
        RSDK.DrawSprite(&self->thumbsUpButtonAnimator, &drawPos, true);
    }
#endif
#if GAME_VERSION != VER_100
    else if (self->actionPromptPos > -TO_FIXED(32)) {
        if (!touchControls) {
            // Draw Super Icon
            drawPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x) - self->actionPromptPos;
            drawPos.y = TO_FIXED(20);
            RSDK.DrawSprite(&self->superIconAnimator, &drawPos, true);

            drawPos.x -= TO_FIXED(20);
            bool32 canSuper = true;
#if MANIA_USE_PLUS
            if (Player->canSuperCB)
                canSuper = Player->canSuperCB(true);
#endif
            // Draw Super Button
            if (player->state == Player_State_Air && player->jumpAbilityState == 1 && canSuper) {
                RSDK.DrawSprite(&self->superButtonAnimator, &drawPos, true);
            }
            else {
                self->inkEffect = INK_BLEND;
                RSDK.DrawSprite(&self->superButtonAnimator, &drawPos, true);

                self->inkEffect = INK_NONE;
            }
        }
    }
#endif

    // Draw Life Icon (aka the Leader Icon if in encore mode)
    int32 lives = self->lives[player->playerID];
    if (addendumOptions->lifeSystem != LIFESYSTEM_INFINITE || globals->gameMode == MODE_ENCORE) {
        if (GET_CHARACTER_ID(2) > 0)
            drawPos.x = touchControls ? lifePos.x - TO_FIXED(28) : lifePos.x;
        else
            drawPos.x = touchControls ? lifePos.x - TO_FIXED(8) : lifePos.x;
        drawPos.y = lifePos.y;
#if MANIA_USE_PLUS
        int32 lives                    = self->lives[player->playerID];
        self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(player->characterID) + (14 * addendumOptions->spriteStyle);

        if (player->characterID == ID_SONIC && player->superState == SUPERSTATE_SUPER)
            self->lifeIconAnimator.frameID = 6 + (14 * addendumOptions->spriteStyle);

        if (player->superState == SUPERSTATE_SUPER && player->miracleState)
            self->lifeIconAnimator.frameID += 7;

        if (self->lifeIconAnimator.frameID < 0) {
            self->lifeIconAnimator.frameID = self->lifeFrameIDs[player->playerID];
            lives--;
        }
        else {
            self->lifeFrameIDs[player->playerID] = self->lifeIconAnimator.frameID;
            self->lives[player->playerID]        = player->lives;
        }
#else
        switch (player->characterID) {
            default:
            case ID_SONIC: self->lifeIconAnimator.frameID = 0; break;
            case ID_TAILS: self->lifeIconAnimator.frameID = 1; break;
            case ID_KNUCKLES: self->lifeIconAnimator.frameID = 2; break;
        }
#endif
        if (player->miracleState) {
            for (int32 c = 0; c < 32; ++c) {
                Player->colorStorage[c] = RSDK.GetPaletteEntry(0, 223 + c);
                RSDK.SetPaletteEntry(0, 223 + c, Player->miracleColors[c]);
            }

            RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

            for (int32 c = 0; c < 32; ++c) {
                RSDK.SetPaletteEntry(0, 223 + c, Player->colorStorage[c]);
            }
        }
        else
            RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

#if MANIA_USE_PLUS
        if (globals->gameMode == MODE_MANIA) {
            if (addendumOptions->coopStyle == COOPSTYLE_MANIA) {
                for (int32 p = 1; p < addendumVar->playerCount; ++p) {
                    if (GET_CHARACTER_ID(p) > 0) {
                        EntityPlayer* buddies = RSDK_GET_ENTITY(p, Player);
                        drawPos.x += TO_FIXED(20);
                        // Draw Buddy Icon
                        self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(buddies->characterID);

                        int32 lives                    = self->lives[buddies->playerID];
                        self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(buddies->characterID) + ((14 * addendumOptions->spriteStyle));

                        if (buddies->characterID == ID_SONIC && buddies->superState == SUPERSTATE_SUPER)
                            self->lifeIconAnimator.frameID = 6 + ((14 * addendumOptions->spriteStyle));

                        if (buddies->superState == SUPERSTATE_SUPER && buddies->miracleState)
                            self->lifeIconAnimator.frameID += (7 + (14 * addendumOptions->spriteStyle));

                        if (self->lifeIconAnimator.frameID < 0) {
                            self->lifeIconAnimator.frameID = self->lifeFrameIDs[buddies->playerID];
                            lives--;
                        }
                        else {
                            self->lifeFrameIDs[buddies->playerID] = self->lifeIconAnimator.frameID;
                            self->lives[buddies->playerID]        = buddies->lives;
                        }

                        if (buddies->miracleState) {
                            for (int32 c = 0; c < 32; ++c) {
                                Player->colorStorage[c] = RSDK.GetPaletteEntry(0, 223 + c);
                                RSDK.SetPaletteEntry(0, 223 + c, Player->miracleColors[c]);
                            }

                            RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

                            for (int32 c = 0; c < 32; ++c) {
                                RSDK.SetPaletteEntry(0, 223 + c, Player->colorStorage[c]);
                            }
                        }
                        else
                            RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);
                    }
                }
            }
        }
    }

    if (globals->gameMode == MODE_ENCORE) {
        for (int32 p = 0; p < PLAYER_COUNT + 1; ++p) {
            if (HUD->stockFlashTimers[p] > 0)
                HUD->stockFlashTimers[p]--;
        }

        drawPos.x += TO_FIXED(20);
        EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
        if (sidekick->classID) {
            // Draw Buddy Icon
            self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(sidekick->characterID);
            if (self->lifeIconAnimator.frameID >= 0 && !(HUD->stockFlashTimers[0] & 4)) {
                if ((sidekick->state != Player_State_Death && sidekick->state != Player_State_Drown && sidekick->state != Player_State_EncoreRespawn)
                    || !sidekick->abilityValues[0]) {

                    int32 lives                    = self->lives[player->playerID];
                    self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(player->characterID) + ((14 * addendumOptions->spriteStyle));

                    if (player->characterID == ID_SONIC && player->superState == SUPERSTATE_SUPER)
                        self->lifeIconAnimator.frameID = 6 + ((14 * addendumOptions->spriteStyle));

                    if (player->superState == SUPERSTATE_SUPER && player->miracleState)
                        self->lifeIconAnimator.frameID += (7 + (14 * addendumOptions->spriteStyle));

                    if (self->lifeIconAnimator.frameID < 0) {
                        self->lifeIconAnimator.frameID = self->lifeFrameIDs[player->playerID];
                        lives--;
                    }
                    else {
                        self->lifeFrameIDs[player->playerID] = self->lifeIconAnimator.frameID;
                        self->lives[player->playerID]        = player->lives;
                    }

                    if (sidekick->miracleState) {
                        for (int32 c = 0; c < 32; ++c) {
                            Player->colorStorage[c] = RSDK.GetPaletteEntry(0, 223 + c);
                            RSDK.SetPaletteEntry(0, 223 + c, Player->miracleColors[c]);
                        }

                        RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

                        for (int32 c = 0; c < 32; ++c) {
                            RSDK.SetPaletteEntry(0, 223 + c, Player->colorStorage[c]);
                        }
                    }
                    else
                        RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);
                }
            }

            // Draw Stock Icons
            drawPos.x += TO_FIXED(20);
            RSDK.SetSpriteAnimation(HUD->aniFrames, 12, &self->lifeIconAnimator, true, 0);
            for (int32 i = 1; i < 5; ++i) {
                self->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(GET_STOCK_ID(i));
                if (self->lifeIconAnimator.frameID >= 0 && !(HUD->stockFlashTimers[i] & 4))
                    RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

                drawPos.x += TO_FIXED(16);
            }

            RSDK.SetSpriteAnimation(HUD->aniFrames, 2, &self->lifeIconAnimator, true, 0);
        }
    }
    else {
        if (addendumOptions->lifeSystem != LIFESYSTEM_INFINITE || globals->gameMode == MODE_ENCORE) {
            // Draw Life Icon "X"
            self->hudElementsAnimator.frameID = 14;
            RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

            // Draw Lives
            drawPos.x += TO_FIXED(48);
            if (player->lives < 10)
                drawPos.x -= TO_FIXED(8);
            if (player->lives > 99)
                drawPos.x += TO_FIXED(8);
            if (player->lives > 999)
                drawPos.x += TO_FIXED(8);
            if (player->lives > 9999)
                drawPos.x += TO_FIXED(8);
            if (player->lives > 99999)
                drawPos.x += TO_FIXED(8);
            if (player->lives > 999999)
                drawPos.x += TO_FIXED(8);
            if (player->lives > 9999999)
                drawPos.x += TO_FIXED(8);
            if (player->lives > 99999999)
                drawPos.x += TO_FIXED(8);
            if (player->lives > 999999999) // there's no way to get the 10,000,000,000 lives needed to break the HUD from this point, the integer limit literally does not allow it
                drawPos.x += TO_FIXED(8);
            HUD_DrawNumbersBase10(&drawPos, lives, 0);
        }
    }
#else
    // Draw Life Icon "X"
    self->hudElementsAnimator.frameID = 14;
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    // Draw Lives
    drawPos.x += TO_FIXED(48);
    if (player->lives < 10)
        drawPos.x -= TO_FIXED(8);
    HUD_DrawNumbersBase10(&drawPos, player->lives, 0);
#endif

    if (globals->gameMode == MODE_COMPETITION) {
        // Draw Competition Borders
#if MANIA_USE_PLUS
        switch (HUD->screenBorderType[SceneInfo->currentScreenID]) {
            default:
            case VS_BORDER_NONE: break;

            case VS_BORDER_BOTTOMRIGHT:
                // Along right edge
                RSDK.DrawRect(ScreenInfo->size.x - 1, 0, 1, ScreenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);
                // Along bottom edge
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_BOTTOM:
                // Along bottom edge
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_BOTTOMLEFT:
                // Along left edge (on screen 2)
                RSDK.DrawRect(0, 0, 1, ScreenInfo[1].size.y, 0x000000, 0xFF, INK_NONE, true);
                // Along bottom edge
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_TOPRIGHT:
                // Along right edge
                RSDK.DrawRect(ScreenInfo->size.x - 1, 0, 1, ScreenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);
                // Along top edge (on screen 2 or 3)
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_TOP:
                // Along top edge (on screen 2)
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case VS_BORDER_TOPLEFT:
                // Along left edge (on screen 3 or 4)
                RSDK.DrawRect(0, 0, 1, ScreenInfo[1].size.y, 0x000000, 0xFF, INK_NONE, true);
                // Along top edge (on screen 3 or 4)
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;
        }
#else
        switch (SceneInfo->currentScreenID) {
            case 0:
                // Along right edge (on screen 1)
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case 1:
                // Along left edge (on screen 2)
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            default: break;
        }
#endif
    }
    else if (addendumOptions->coopStyle > COOPSTYLE_MANIA && addendumVar->playerCount > 1 && globals->gameMode == MODE_MANIA) {
        switch (addendumVar->playerCount) {
            default: break;
            case 2:
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case 3:
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(ScreenInfo->size.x - 1, 0, 1, ScreenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, 0, 1, ScreenInfo[1].size.y, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;

            case 4:
                RSDK.DrawRect(ScreenInfo->size.x - 1, 0, 1, ScreenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, 0, 1, ScreenInfo[1].size.y, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, ScreenInfo->size.y - 1, ScreenInfo->size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(ScreenInfo->size.x - 1, 0, 1, ScreenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, 0, 1, ScreenInfo[1].size.y, 0x000000, 0xFF, INK_NONE, true);
                RSDK.DrawRect(0, 0, ScreenInfo[1].size.x, 1, 0x000000, 0xFF, INK_NONE, true);
                break;
        }
    }

    if (!touchControls) {
        if (SceneInfo->debugMode || globals->superSecret || globals->gameMode == MODE_TIMEATTACK) {
            Vector2 inputPos;
            inputPos.x = self->inputPos.x;
            inputPos.y = self->inputPos.y;

            // D-pad
            drawPos.x = inputPos.x;
            drawPos.y = inputPos.y - TO_FIXED(6);
            HUD_DrawInputViewer(&drawPos, player, 0);

            // ABC
            drawPos.x = inputPos.x + TO_FIXED(28);
            drawPos.y = inputPos.y - TO_FIXED(6);
            HUD_DrawInputViewer(&drawPos, player, 1);

            // XYZ
            drawPos.x = inputPos.x + TO_FIXED(28);
            drawPos.y = inputPos.y - TO_FIXED(18);
            HUD_DrawInputViewer(&drawPos, player, 2);

            // Bumpers
            drawPos.x = inputPos.x + TO_FIXED(28);
            drawPos.y = inputPos.y - TO_FIXED(28);
            HUD_DrawInputViewer(&drawPos, player, 3);
        }
    }

    if (!ERZSetup) {
        itemPos.x = self->itemPos.x;
        itemPos.y = self->itemPos.y;

        drawPos.x = itemPos.x;
        drawPos.y = itemPos.y;
        HUD_DrawItemsHUD(&drawPos, player, 0);

        if (self->invincibilityActive)
            drawPos.x = itemPos.x + TO_FIXED(18);
        else
            drawPos.x = itemPos.x;
        drawPos.y = itemPos.y;
        HUD_DrawItemsHUD(&drawPos, player, 1);

        if (self->invincibilityActive && !self->speedShoesActive)
            drawPos.x = itemPos.x + TO_FIXED(18);
        else if (self->speedShoesActive && !self->invincibilityActive)
            drawPos.x = itemPos.x + TO_FIXED(18);
        else if (self->invincibilityActive && self->speedShoesActive)
            drawPos.x = itemPos.x + TO_FIXED(36);
        else
            drawPos.x = itemPos.x;
        drawPos.y = itemPos.y;
        HUD_DrawItemsHUD(&drawPos, player, 2);
    }

    if (touchControls) {
        HUD_DrawMobileHUD();
        HUD_DrawTouchControls();
    }

    if (player->hyperFlashTimer > 0) {
        HUD_HandleHyperFlash(player);
    }
}

void HUD_Create(void *data)
{
    RSDK_THIS(HUD);

    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (!SceneInfo->inEditor) {
#if MANIA_USE_PLUS
        ActClear->disableTimeBonus = false;
#endif

        self->active    = ACTIVE_NORMAL;
        self->visible   = true;
        self->drawGroup = Zone->hudDrawGroup;

        self->scorePos.x    = TO_FIXED(16);
        self->scorePos.y    = TO_FIXED(12);
        self->timePos.x     = TO_FIXED(16);
        self->timePos.y     = TO_FIXED(28);
        self->ringsPos.x    = TO_FIXED(16);
        self->ringsPos.y    = TO_FIXED(44);
        if (globals->gameMode == MODE_ENCORE)
            self->lifePos.x = touchControls ? TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 95) : TO_FIXED(16);
        else
            self->lifePos.x = touchControls ? TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 71) : TO_FIXED(16);
        self->lifePos.y     = touchControls ? TO_FIXED(25) : TO_FIXED(ScreenInfo->size.y - 12);
        self->inputPos.x    = TO_FIXED(16);
        self->inputPos.y    = TO_FIXED(ScreenInfo->size.y - 32);
        self->itemPos.x     = TO_FIXED(16);
        self->itemPos.y     = TO_FIXED(60);
#if GAME_VERSION != VER_100
        self->actionPromptPos = -TO_FIXED(32);
#endif

#if MANIA_USE_PLUS
        for (int32 i = 0; i < SCREEN_COUNT; ++i) {
            self->vsScorePos[i].x = self->scorePos.x;
            self->vsScorePos[i].y = self->scorePos.y;
            self->vsTimePos[i].x  = self->timePos.x;
            self->vsTimePos[i].y  = self->timePos.y;
            self->vsRingsPos[i].x = self->ringsPos.x;
            self->vsRingsPos[i].y = self->ringsPos.y;
            self->vsLifePos[i].x  = touchControls ? TO_FIXED(ScreenInfo[i].size.x - 64) : self->lifePos.x;
            self->vsLifePos[i].y  = self->lifePos.y;
            self->vsInputPos[i].x = self->inputPos.x;
            self->vsInputPos[i].y = self->inputPos.y;
            self->vsItemPos[i].x  = self->itemPos.x;
            self->vsItemPos[i].y  = self->itemPos.y;
        }
#endif

        RSDK.SetSpriteAnimation(HUD->aniFrames, 0, &self->hudElementsAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 1, &self->numbersAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 9, &self->hyperNumbersAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 2, &self->lifeIconAnimator, true, 0);
#if MANIA_USE_PLUS
        RSDK.SetSpriteAnimation(HUD->aniFrames, globals->gameMode == MODE_ENCORE ? 13 : 8, &self->playerIDAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 10, &self->thumbsUpIconAnimator, true, 2);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 10, &self->replayClapAnimator, true, 1);
#else
        RSDK.SetSpriteAnimation(HUD->aniFrames, 8, &self->playerIDAnimator, true, 0);
#endif
        RSDK.SetSpriteAnimation(HUD->aniFrames, 14, &self->readyUpIconAnimator, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 23, &self->itemBoxAnimator1, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 23, &self->itemBoxAnimator2, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 23, &self->itemBoxAnimator3, true, 0);
        RSDK.SetSpriteAnimation(HUD->aniFrames, 16, &self->inputAnimator, true, 0);

#if GAME_VERSION != VER_100
        RSDK.SetSpriteAnimation(HUD->superButtonFrames, 0, &self->superIconAnimator, true, 0);
        HUD_GetActionButtonFrames();
#endif

#if MANIA_USE_PLUS
        RSDK.AddViewableVariable("Show HUD", &self->visible, VIEWVAR_UINT8, false, true);
#endif
    }
}

void HUD_StageLoad(void)
{
    HUD->aniFrames = RSDK.LoadSpriteAnimation("Global/HUD.bin", SCOPE_STAGE);
#if GAME_VERSION != VER_100
    HUD->superButtonFrames = RSDK.LoadSpriteAnimation("Global/SuperButtons.bin", SCOPE_STAGE);
#endif
#if MANIA_USE_PLUS
    HUD->bossFrames = RSDK.LoadSpriteAnimation("Global/BossBar.bin", SCOPE_STAGE);
#endif

#if MANIA_USE_PLUS
    HUD->sfxClick    = RSDK.GetSfx("Stage/Click.wav");
    HUD->sfxStarpost = RSDK.GetSfx("Global/StarPost.wav");

    HUD->showTAPrompt = false;

    EntityCompetitionSession *session = CompetitionSession_GetSession();
    if (globals->gameMode == MODE_COMPETITION) {
        HUD->screenBorderType[0] = session->screenBorderType[0];
        HUD->screenBorderType[1] = session->screenBorderType[1];
        HUD->screenBorderType[2] = session->screenBorderType[2];
        HUD->screenBorderType[3] = session->screenBorderType[3];
    }

    HUD->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(HUD->dpadFrames, 0, &HUD->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(HUD->dpadFrames, 1, &HUD->dpadTouchAnimator, true, 0);
#endif
}

void HUD_DrawNumbersBase10(Vector2 *drawPos, int32 value, int32 digitCount)
{
    RSDK_THIS(HUD);

    if (!digitCount && value > 0) {
        int32 v = value;
        while (v > 0) {
            ++digitCount;
            v /= 10;
        }
    }
    else {
        if (!digitCount && value <= 0)
            digitCount = 1;
    }

    int32 digit = 1;
    while (digitCount--) {
        self->numbersAnimator.frameID = value / digit % 10;
        RSDK.DrawSprite(&self->numbersAnimator, drawPos, true);
        digit *= 10;
        drawPos->x -= TO_FIXED(8);
    }
}

void HUD_DrawNumbersBase16(Vector2 *drawPos, int32 value)
{
    RSDK_THIS(HUD);

    int32 mult = 1;
    for (int32 i = 4; i; --i) {
        self->numbersAnimator.frameID = value / mult & 0xF;
        RSDK.DrawSprite(&self->numbersAnimator, drawPos, true);
        drawPos->x -= TO_FIXED(8);
        mult *= 16;
    }
}

void HUD_DrawNumbersHyperRing(Vector2 *drawPos, int32 value)
{
    RSDK_THIS(HUD);

    int32 cnt   = 0;
    int32 mult  = 1;
    int32 mult2 = 1;
    if (value <= 0) {
        cnt = 1;
    }
    else {
        int32 v = value;
        while (v) {
            ++cnt;
            v /= 10;
        }
    }

    if (cnt > 0) {
        while (cnt--) {
            if (self->ringFlashFrame == 1)
                RSDK.SetSpriteAnimation(HUD->aniFrames, 25, &self->hyperNumbersAnimator, true, value / mult % 10);
            else
                RSDK.SetSpriteAnimation(HUD->aniFrames, 9, &self->hyperNumbersAnimator, true, value / mult % 10);

            RSDK.DrawSprite(&self->hyperNumbersAnimator, drawPos, true);
            drawPos->x -= TO_FIXED(8);
            mult = 10 * mult2;
            mult2 *= 10;
        }
    }

    if (self->ringFlashFrame == 1)
        RSDK.SetSpriteAnimation(HUD->aniFrames, 25, &self->hyperNumbersAnimator, true, 10);
    else
        RSDK.SetSpriteAnimation(HUD->aniFrames, 9, &self->hyperNumbersAnimator, true, 10);
    drawPos->x -= TO_FIXED(4);
    RSDK.DrawSprite(&self->hyperNumbersAnimator, drawPos, true);
}

#if GAME_VERSION != VER_100
void HUD_GetButtonFrame(Animator *animator, int32 buttonID)
{
    int32 gamepadType = UIButtonPrompt_GetGamepadType();
    if (API_GetConfirmButtonFlip() && buttonID <= 1)
        buttonID ^= 1;

    // Gamepad
    if (gamepadType != UIBUTTONPROMPT_KEYBOARD && (gamepadType < UIBUTTONPROMPT_KEYBOARD_FR || gamepadType > UIBUTTONPROMPT_KEYBOARD_SP)) {
        RSDK.SetSpriteAnimation(HUD->superButtonFrames, gamepadType, animator, true, buttonID);
    }
    else {
        // Keyboard
        EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
#if MANIA_USE_PLUS
        int32 id = API_GetInputDeviceID(player->controllerID);
#else
        int32 id = INPUT_NONE;
#endif
        int32 contID = id == INPUT_UNASSIGNED ? CONT_P1 : player->controllerID;

        int32 map = 0;
        switch (buttonID) {
            default: break;
            case 0: map = ControllerInfo[contID].keyA.keyMap; break;
            case 1: map = ControllerInfo[contID].keyB.keyMap; break;
            case 2: map = ControllerInfo[contID].keyX.keyMap; break;
            case 3: map = ControllerInfo[contID].keyY.keyMap; break;
            case 4: map = ControllerInfo[contID].keyStart.keyMap; break;
        }

        int32 frame = UIButtonPrompt_MappingsToFrame(map);
        RSDK.SetSpriteAnimation(HUD->superButtonFrames, 1, animator, true, frame);
    }
}
void HUD_GetActionButtonFrames(void)
{
    RSDK_THIS(HUD);

    HUD_GetButtonFrame(&self->superButtonAnimator, KEY_Y);
#if MANIA_USE_PLUS
    HUD_GetButtonFrame(&self->saveReplayButtonAnimator, KEY_Y);
    HUD_GetButtonFrame(&self->thumbsUpButtonAnimator, KEY_START);
    HUD_GetButtonFrame(&self->readyUpButtonAnimator, KEY_Y);
#endif
}
#endif

void HUD_State_MoveIn(void)
{
    RSDK_THIS(HUD);

#if MANIA_USE_PLUS
    StateMachine(*state) = NULL;
    Vector2 *scorePos = NULL, *timePos = NULL, *ringsPos = NULL, *lifePos = NULL, *inputPos = NULL, *itemPos = NULL;
    int32 *targetPos = NULL;

    if (globals->gameMode == MODE_COMPETITION) {
        state     = &self->vsStates[SceneInfo->currentScreenID];
        scorePos  = &self->vsScorePos[SceneInfo->currentScreenID];
        timePos   = &self->vsTimePos[SceneInfo->currentScreenID];
        ringsPos  = &self->vsRingsPos[SceneInfo->currentScreenID];
        lifePos   = &self->vsLifePos[SceneInfo->currentScreenID];
        inputPos  = &self->vsInputPos[SceneInfo->currentScreenID];
        itemPos   = &self->vsItemPos[SceneInfo->currentScreenID];
        targetPos = &self->vsTargetPos[SceneInfo->currentScreenID];
    }
    else {
        state     = &self->state;
        scorePos  = &self->scorePos;
        timePos   = &self->timePos;
        ringsPos  = &self->ringsPos;
        itemPos   = &self->itemPos;
        inputPos  = &self->inputPos;
        lifePos   = &self->lifePos;
        targetPos = &self->targetPos;
    }

    if (scorePos->x < *targetPos)
        scorePos->x += TO_FIXED(8);

    if (timePos->x < *targetPos)
        timePos->x += TO_FIXED(8);

    if (ringsPos->x < *targetPos)
        ringsPos->x += TO_FIXED(8);

    if (itemPos->x < *targetPos)
        itemPos->x += TO_FIXED(8);

    if (inputPos->x < *targetPos)
        inputPos->x += TO_FIXED(8);

    if (lifePos->x < *targetPos)
        lifePos->x += TO_FIXED(8);
    else
        *state = StateMachine_None;
#else
    if (self->scorePos.x < self->targetPos)
        self->scorePos.x += TO_FIXED(8);

    if (self->timePos.x < self->targetPos)
        self->timePos.x += TO_FIXED(8);

    if (self->ringsPos.x < self->targetPos)
        self->ringsPos.x += TO_FIXED(8);

    if (self->lifePos.x < self->targetPos)
        self->lifePos.x += TO_FIXED(8);
    else
        self->state = StateMachine_None;
#endif
}

void HUD_State_MoveOut(void)
{
    RSDK_THIS(HUD);

#if MANIA_USE_PLUS
    Vector2 *scorePos = NULL, *timePos = NULL, *ringsPos = NULL, *lifePos = NULL, *inputPos = NULL, *itemPos = NULL;
    StateMachine(*state) = NULL;

    if (globals->gameMode == MODE_COMPETITION) {
        state    = &self->vsStates[self->screenID];
        scorePos = &self->vsScorePos[self->screenID];
        timePos  = &self->vsTimePos[self->screenID];
        ringsPos = &self->vsRingsPos[self->screenID];
        lifePos  = &self->vsLifePos[self->screenID];
        inputPos = &self->vsInputPos[self->screenID];
        itemPos  = &self->vsItemPos[self->screenID];
    }
    else {
        state    = &self->state;
        scorePos = &self->scorePos;
        timePos  = &self->timePos;
        ringsPos = &self->ringsPos;
        lifePos  = &self->lifePos;
        inputPos = &self->inputPos;
        itemPos  = &self->itemPos;
    }

    scorePos->x -= TO_FIXED(8);

    if (timePos->x - scorePos->x > TO_FIXED(16))
        timePos->x -= TO_FIXED(8);

    if (ringsPos->x - timePos->x > TO_FIXED(16))
        ringsPos->x -= TO_FIXED(8);

    if (itemPos->x - ringsPos->x > TO_FIXED(16))
        itemPos->x -= TO_FIXED(8);

    if (inputPos->x - itemPos->x > TO_FIXED(16))
        inputPos->x -= TO_FIXED(8);

    if (lifePos->x - inputPos->x > TO_FIXED(16))
        lifePos->x -= TO_FIXED(8);

    if (lifePos->x < -TO_FIXED(80)) {
        if (globals->gameMode == MODE_COMPETITION) {
            *state = StateMachine_None;
            CompSession_DeriveWinner(self->screenID, FINISHTYPE_GAMEOVER);
            EntityGameOver *gameOver   = RSDK_GET_ENTITY(self->screenID + Player->playerCount, GameOver);
            EntityCompetition *manager = Competition->sessionManager;

            if (!manager || manager->timer) {
                RSDK.ResetEntity(gameOver, GameOver->classID, INT_TO_VOID(false));
                gameOver->playerID = self->screenID;
            }
            else {
                RSDK.ResetEntity(gameOver, GameOver->classID, INT_TO_VOID(true));
                RSDK.SetEngineState(ENGINESTATE_FROZEN);
                SceneInfo->timeEnabled = false;
                gameOver->playerID     = self->screenID;
            }
        }
        else {
            destroyEntity(self);
        }
    }
#else
    self->scorePos.x -= TO_FIXED(8);

    if (self->timePos.x - self->scorePos.x > TO_FIXED(16))
        self->timePos.x -= TO_FIXED(8);

    if (self->ringsPos.x - self->timePos.x > TO_FIXED(16))
        self->ringsPos.x -= TO_FIXED(8);

    if (self->lifePos.x - self->ringsPos.x > TO_FIXED(16))
        self->lifePos.x -= TO_FIXED(8);

    if (self->lifePos.x < -TO_FIXED(64))
        destroyEntity(self);
#endif
}

void HUD_MoveIn(EntityHUD *hud)
{
    hud->targetPos = hud->scorePos.x;
    hud->scorePos.x -= TO_FIXED(0x100);
    hud->timePos.x -= TO_FIXED(0x110);
    hud->ringsPos.x -= TO_FIXED(0x120);
    hud->itemPos.x -= TO_FIXED(0x130);
    hud->inputPos.x -= TO_FIXED(0x140);
    hud->lifePos.x -= TO_FIXED(0x150);
    hud->state = HUD_State_MoveIn;
}

void HUD_MoveOut(void)
{
    foreach_active(HUD, hud) { hud->state = HUD_State_MoveOut; }
}

void HUD_EnableRingFlash(void)
{
    foreach_all(HUD, hud)
    {
        if (hud)
            hud->enableRingFlash = true;
        foreach_break;
    }
}

int32 HUD_CharacterIndexFromID(int32 characterID)
{
    int32 id = -1;
    for (int32 i = characterID; i > 0; ++id, i >>= 1)
        ;
    return id;
}

void HUD_DrawInputViewer(Vector2 *drawPos, EntityPlayer *player, int32 drawType)
{
    RSDK_THIS(HUD);
    EntityPauseMenu *pauseMenu      = RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);
    RSDKControllerState *controller = &ControllerInfo[player->controllerID];
    RSDKAnalogState *analog         = &AnalogStickInfoL[player->controllerID];
    RSDKTriggerState *Ltrigger      = &TriggerInfoL[player->controllerID];
    RSDKTriggerState *Rtrigger      = &TriggerInfoR[player->controllerID];

    if (drawType == 0) {
        RSDK.SetSpriteAnimation(HUD->aniFrames, 15, &self->inputAnimator, true, 0);
        RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

        RSDK.SetSpriteAnimation(HUD->aniFrames, 16, &self->inputAnimator, true, 0);
        if (pauseMenu->classID != PauseMenu->classID) {
            if ((controller->keyUp.press || controller->keyUp.down) || (analog->keyUp.press || analog->keyUp.down)) {
                self->inputAnimator.frameID = 1;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

            if ((controller->keyDown.press || controller->keyDown.down) || (analog->keyDown.press || analog->keyDown.down)) {
                self->inputAnimator.frameID = 2;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

            if ((controller->keyLeft.press || controller->keyLeft.down) || (analog->keyLeft.press || analog->keyLeft.down)) {
                self->inputAnimator.frameID = 3;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

            if ((controller->keyRight.press || controller->keyRight.down) || (analog->keyRight.press || analog->keyRight.down)) {
                self->inputAnimator.frameID = 4;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);
        }
    }

    if (drawType == 1) {
        RSDK.SetSpriteAnimation(HUD->aniFrames, 17, &self->inputAnimator, true, 0);
        RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

        RSDK.SetSpriteAnimation(HUD->aniFrames, 18, &self->inputAnimator, true, 0);
        if (pauseMenu->classID != PauseMenu->classID) {
            if (controller->keyA.press || controller->keyA.down) {
                self->inputAnimator.frameID = 1;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

            if (controller->keyB.press || controller->keyB.down) {
                self->inputAnimator.frameID = 2;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

            if (controller->keyC.press || controller->keyC.down) {
                self->inputAnimator.frameID = 3;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);
        }
    }

    if (drawType == 2) {
        RSDK.SetSpriteAnimation(HUD->aniFrames, 19, &self->inputAnimator, true, 0);
        RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

        RSDK.SetSpriteAnimation(HUD->aniFrames, 20, &self->inputAnimator, true, 0);
        if (pauseMenu->classID != PauseMenu->classID) {
            if (controller->keyX.press || controller->keyX.down) {
                self->inputAnimator.frameID = 1;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

            if (controller->keyY.press || controller->keyY.down) {
                self->inputAnimator.frameID = 2;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

            if (controller->keyZ.press || controller->keyZ.down) {
                self->inputAnimator.frameID = 3;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);
        }
    }

    if (drawType == 3) {
        RSDK.SetSpriteAnimation(HUD->aniFrames, 21, &self->inputAnimator, true, 0);
        RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

        RSDK.SetSpriteAnimation(HUD->aniFrames, 22, &self->inputAnimator, true, 0);
        if (pauseMenu->active != ACTIVE_ALWAYS) {
            if (Ltrigger->keyBumper.press || Ltrigger->keyBumper.down) {
                self->inputAnimator.frameID = 1;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);

            if (Rtrigger->keyBumper.press || Rtrigger->keyBumper.down) {
                self->inputAnimator.frameID = 2;
            }
            else {
                self->inputAnimator.frameID = 0;
            }
            RSDK.DrawSprite(&self->inputAnimator, drawPos, true);
        }
    }
}

void HUD_DrawItemsHUD(Vector2 *drawPos, EntityPlayer *player, int32 drawType)
{
    RSDK_THIS(HUD);

    if (drawType == 0) {
        if (player->state != Player_State_Transform && player->superState != SUPERSTATE_SUPER) {
            if (player->invincibleTimer > 0) {
                self->invincibilityActive = true;
                if (player->invincibleTimer > 180) {
                    self->itemBoxAnimator1.frameID = 5;
                }
                else {
                    if (player->invincibleTimer & 4)
                        self->itemBoxAnimator1.frameID = 0;
                    if (player->invincibleTimer & 8)
                        self->itemBoxAnimator1.frameID = 5;
                }
            }
            else {
                self->itemBoxAnimator1.frameID = 0;
                self->invincibilityActive      = false;
            }
        }
        else {
            if (player->rings > 0) {
                self->invincibilityActive = true;
                if (player->rings > 3) 
                    self->itemBoxAnimator1.frameID = 12;
                else {
                    if (player->superRingLossTimer & 8)
                        self->itemBoxAnimator1.frameID = 0;
                    else
                        self->itemBoxAnimator1.frameID = 12;
                }
            }
            else {
                self->itemBoxAnimator1.frameID = 0;
                self->invincibilityActive      = false;
            }
        }

        RSDK.DrawSprite(&self->itemBoxAnimator1, drawPos, true);
    }

    if (drawType == 1) {
        if (player->speedShoesTimer > 0) {
            self->speedShoesActive = true;
            if (player->speedShoesTimer > 180) {
                switch (player->characterID) {
                    default:
                    case ID_SONIC: self->itemBoxAnimator2.frameID = 6; break;
                    case ID_TAILS: self->itemBoxAnimator2.frameID = 7; break;
                    case ID_KNUCKLES: self->itemBoxAnimator2.frameID = 8; break;
                    case ID_MIGHTY: self->itemBoxAnimator2.frameID = 9; break;
                    case ID_RAY: self->itemBoxAnimator2.frameID = 10; break;
                    case ID_AMY: self->itemBoxAnimator2.frameID = 11; break;
                }
            }
            else {
                switch (player->characterID) {
                    default:
                    case ID_SONIC:
                        if (player->speedShoesTimer & 8)
                            self->itemBoxAnimator2.frameID = 0;
                        else
                            self->itemBoxAnimator2.frameID = 6;
                        break;

                    case ID_TAILS:
                        if (player->speedShoesTimer & 8)
                            self->itemBoxAnimator2.frameID = 0;
                        else
                            self->itemBoxAnimator2.frameID = 7;
                        break;

                    case ID_KNUCKLES:
                        if (player->speedShoesTimer & 8)
                            self->itemBoxAnimator2.frameID = 0;
                        else
                            self->itemBoxAnimator2.frameID = 8;
                        break;

                    case ID_MIGHTY:
                        if (player->speedShoesTimer & 8)
                            self->itemBoxAnimator2.frameID = 0;
                        else
                            self->itemBoxAnimator2.frameID = 9;
                        break;

                    case ID_RAY:
                        if (player->speedShoesTimer & 8)
                            self->itemBoxAnimator2.frameID = 0;
                        else
                            self->itemBoxAnimator2.frameID = 10;
                        break;

                    case ID_AMY:
                        if (player->speedShoesTimer & 8)
                            self->itemBoxAnimator2.frameID = 0;
                        else
                            self->itemBoxAnimator2.frameID = 11;
                        break;
                }
            }
        }
        else {
            self->itemBoxAnimator2.frameID = 0;
            self->speedShoesActive         = false;
        }

        RSDK.DrawSprite(&self->itemBoxAnimator2, drawPos, true);
    }

    if (drawType == 2) {
        if (player->shield > SHIELD_NONE) {
            self->shieldActive = true;
            switch (player->shield) {
                default:
                case SHIELD_BLUE: self->itemBoxAnimator3.frameID = 1; break;
                case SHIELD_BUBBLE: self->itemBoxAnimator3.frameID = 2; break;
                case SHIELD_FIRE: self->itemBoxAnimator3.frameID = 3; break;
                case SHIELD_LIGHTNING: self->itemBoxAnimator3.frameID = 4; break;
            }
        }
        else {
            self->itemBoxAnimator3.frameID = 0;
            self->shieldActive            = false;
        }

        RSDK.DrawSprite(&self->itemBoxAnimator3, drawPos, true);
    }
}

void HUD_DrawTouchControls(void)
{
    RSDK_THIS(HUD);

    int32 playerID       = SceneInfo->currentScreenID;
    EntityPlayer *player = RSDK_GET_ENTITY(playerID, Player);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    HUD->dpadPos.x = TO_FIXED(56);
    HUD->dpadPos.y = TO_FIXED(184);

    HUD->actionPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 56);
    HUD->actionPos.y = TO_FIXED(184);

#if GAME_VERSION != VER_100
    HUD->superPos.x = HUD->actionPos.x - TO_FIXED(48);
    HUD->superPos.y = HUD->actionPos.y - TO_FIXED(48);
#endif

    HUD->swapPos.x = HUD->actionPos.x - TO_FIXED(48);
    HUD->swapPos.y = HUD->actionPos.y;

    if (globals->gameMode == MODE_ENCORE)
        HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 109);
    else {
        if (GET_CHARACTER_ID(2) > 0)
            HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 109);
        else
            HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 89);
    }
    HUD->pausePos.y = TO_FIXED(16);

    HUD->auxPos.x = HUD->actionPos.x;
    HUD->auxPos.y = HUD->actionPos.y - TO_FIXED(48);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * .625);
    self->scale.x = 0x200;
    self->scale.y = 0x200;

    bool32 canMove = player->stateInput == Player_Input_P1;
    canMove |= player->stateInput == MegaChopper_Input_GrabbedP1;
    canMove |= player->stateInput == Gachapandora_Player_StateInput_P1Grabbed;
#if MANIA_USE_PLUS
    canMove |= player->stateInput == EncoreIntro_PlayerInput_BuddySel;
#endif

    bool32 canJump = player->stateInput == Player_Input_P1;
    canJump |= player->stateInput == MegaChopper_Input_GrabbedP1;
    canJump |= player->stateInput == Gachapandora_Player_StateInput_P1Grabbed;

#if GAME_VERSION != VER_100
    bool32 canSuper = canJump && Player_CanTransform(player);
#endif
#if MANIA_USE_PLUS
    bool32 canSwap = canJump && globals->gameMode == MODE_ENCORE && !HUD->swapCooldown && Player_CheckValidState(player) && Player_CanSwap(player);
    bool32 canAux  = canJump;
#endif

    bool32 canPause = canMove;

#if GAME_VERSION != VER_100
    Vector2 superPos = HUD->superPos;
#endif
#if MANIA_USE_PLUS
    Vector2 swapPos = HUD->swapPos;
    Vector2 auxPos  = HUD->auxPos;
#endif

    RSDKControllerState *controller = &ControllerInfo[player->controllerID];

    for (int32 c = 0; c < 6; ++c) {
        switch (GET_CHARACTER_ID(1)) {
            default: break;
            case ID_SONIC:
                HUD->colorStorage[c] = RSDK.GetPaletteEntry(0, 42 + c);
                RSDK.SetPaletteEntry(0, 42 + c, Player->superPalette_Sonic[c]);
                break;

            case ID_TAILS:
                HUD->colorStorage[c] = RSDK.GetPaletteEntry(0, 42 + c);
                RSDK.SetPaletteEntry(0, 42 + c, Player->superPalette_Tails[c]);
                break;

            case ID_KNUCKLES:
                HUD->colorStorage[c] = RSDK.GetPaletteEntry(0, 42 + c);
                RSDK.SetPaletteEntry(0, 42 + c, Player->superPalette_Knux[c]);
                break;

            case ID_MIGHTY:
                HUD->colorStorage[c] = RSDK.GetPaletteEntry(0, 42 + c);
                RSDK.SetPaletteEntry(0, 42 + c, Player->superPalette_Mighty[c]);
                break;

            case ID_RAY:
                HUD->colorStorage[c] = RSDK.GetPaletteEntry(0, 42 + c);
                RSDK.SetPaletteEntry(0, 42 + c, Player->superPalette_Ray[1 + c]);
                break;

            case ID_AMY:
                HUD->colorStorage[c] = RSDK.GetPaletteEntry(0, 42 + c);
                RSDK.SetPaletteEntry(0, 42 + c, Player->superPalette_Amy[c]);
                break;
        }
    }

    if (canMove) {
        if (HUD->dpadAlpha[playerID] < opacity)
            HUD->dpadAlpha[playerID] += 4;

        // Draw DPad
        self->alpha                   = HUD->dpadAlpha[playerID];
        HUD->dpadAnimator.frameID = 10;
        RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->dpadPos, true);

        if (player->classID == Player->classID ? player->left : controller->keyLeft.down) {
            self->alpha                        = opacity;
            HUD->dpadTouchAnimator.frameID = 6;
            RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->dpadPos, true);
        }
        else {
            self->alpha                   = HUD->dpadAlpha[playerID];
            HUD->dpadAnimator.frameID = 6;
            RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->dpadPos, true);
        }

        if (player->classID == Player->classID ? player->down : controller->keyDown.down) {
            self->alpha                        = opacity;
            HUD->dpadTouchAnimator.frameID = 9;
            RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->dpadPos, true);

            if (player->classID == Player->classID ? player->left : controller->keyLeft.down) {
                HUD->dpadTouchAnimator.frameID = 14;
                RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->dpadPos, true);
            }
            else if (player->classID == Player->classID ? player->right : controller->keyRight.down) {
                HUD->dpadTouchAnimator.frameID = 15;
                RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->dpadPos, true);
            }
        }
        else {
            self->alpha                   = HUD->dpadAlpha[playerID];
            HUD->dpadAnimator.frameID = 9;
            RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->dpadPos, true);
        }

        if (player->classID == Player->classID ? player->right : controller->keyRight.down) {
            self->alpha                        = opacity;
            HUD->dpadTouchAnimator.frameID = 7;
            RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->dpadPos, true);
        }
        else {
            self->alpha                   = HUD->dpadAlpha[playerID];
            HUD->dpadAnimator.frameID = 7;
            RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->dpadPos, true);
        }

        if (player->classID == Player->classID ? player->up : controller->keyUp.down) {
            self->alpha                        = opacity;
            HUD->dpadTouchAnimator.frameID = 8;
            RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->dpadPos, true);

            if (player->classID == Player->classID ? player->left : controller->keyLeft.down) {
                HUD->dpadTouchAnimator.frameID = 12;
                RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->dpadPos, true);
            }
            else if (player->classID == Player->classID ? player->right : controller->keyRight.down) {
                HUD->dpadTouchAnimator.frameID = 13;
                RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->dpadPos, true);
            }
        }
        else {
            self->alpha                   = HUD->dpadAlpha[playerID];
            HUD->dpadAnimator.frameID = 8;
            RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->dpadPos, true);
        }

        if (player->classID == Player->classID
                ? (!player->up && !player->down && !player->left && !player->right)
                : (!controller->keyUp.down && !controller->keyDown.down && !controller->keyLeft.down && !controller->keyRight.down)) {
            self->alpha                   = HUD->dpadAlpha[playerID];
            HUD->dpadAnimator.frameID = 11;
            RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->dpadPos, true);
        }
    }
    else {
        if (HUD->dpadAlpha[playerID] > 0) {
            HUD->dpadAlpha[playerID] -= 4;
        }

        self->alpha = HUD->dpadAlpha[playerID];
        if (self->alpha > 0) {
            HUD->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->dpadPos, true);
        }
    }

    if (canJump) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (HUD->jumpAlpha[playerID] < opacity)
                HUD->jumpAlpha[playerID] += 4;

            if (player->classID == Player->classID ? player->jumpHold : controller->keyC.down) {
                self->alpha                        = opacity;
                HUD->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->actionPos, true);
            }
            else {
                self->alpha                   = HUD->jumpAlpha[playerID];
                HUD->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->actionPos, true);
            }
        }
        else {
            HUD->jumpAlpha[playerID] = 0;
        }
    }
    else {
        if (HUD->jumpAlpha[playerID] > 0)
            HUD->jumpAlpha[playerID] -= 4;

        self->alpha = HUD->jumpAlpha[playerID];
        if (self->alpha > 0) {
            HUD->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&HUD->dpadAnimator, &HUD->actionPos, true);
        }
    }

#if GAME_VERSION != VER_100
    if (canSuper) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (HUD->superAlpha[playerID] < opacity)
                HUD->superAlpha[playerID] += 4;

            if (!player->onGround && ControllerInfo[player->controllerID].keyY.down) {
                self->alpha                        = opacity;
                HUD->dpadTouchAnimator.frameID = 3;
                RSDK.DrawSprite(&HUD->dpadTouchAnimator, &superPos, true);
            }
            else {
                self->alpha                   = HUD->superAlpha[playerID];
                HUD->dpadAnimator.frameID = 3;
                RSDK.DrawSprite(&HUD->dpadAnimator, &superPos, true);
            }
        }
        else {
            HUD->superAlpha[playerID] = 0;
        }
    }
    else {
        if (HUD->superAlpha[playerID] > 0)
            HUD->superAlpha[playerID] -= 4;

        self->alpha = HUD->superAlpha[playerID];
        if (self->alpha > 0) {
            HUD->dpadAnimator.frameID = 3;
            RSDK.DrawSprite(&HUD->dpadAnimator, &superPos, true);
        }
    }
#endif

#if MANIA_USE_PLUS
    if (canSwap) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (HUD->swapAlpha[playerID] < opacity)
                HUD->swapAlpha[playerID] += 4;

            if (player->onGround && ControllerInfo[player->controllerID].keyY.down) {
                self->alpha                        = opacity;
                HUD->dpadTouchAnimator.frameID = 4;
                RSDK.DrawSprite(&HUD->dpadTouchAnimator, &swapPos, true);
            }
            else {
                self->alpha                   = HUD->swapAlpha[playerID];
                HUD->dpadAnimator.frameID = 4;
                RSDK.DrawSprite(&HUD->dpadAnimator, &swapPos, true);
            }
        }
        else {
            HUD->swapAlpha[playerID] = 0;
        }
    }
    else {
        if (HUD->swapAlpha[playerID] > 0)
            HUD->swapAlpha[playerID] -= 4;

        self->alpha = HUD->swapAlpha[playerID];
        if (self->alpha > 0) {
            HUD->dpadAnimator.frameID = 4;
            RSDK.DrawSprite(&HUD->dpadAnimator, &swapPos, true);
        }
    }
#endif

    if (canAux) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (HUD->auxAlpha[playerID] < opacity)
                HUD->auxAlpha[playerID] += 8;

            if (TriggerInfoR[player->controllerID].keyBumper.down) {
                self->alpha                    = opacity;
                HUD->dpadTouchAnimator.frameID = 2;
                RSDK.DrawSprite(&HUD->dpadTouchAnimator, &auxPos, true);
            }
            else {
                self->alpha               = HUD->auxAlpha[playerID];
                HUD->dpadAnimator.frameID = 2;
                RSDK.DrawSprite(&HUD->dpadAnimator, &auxPos, true);
            }
        }
        else {
            HUD->auxAlpha[playerID] = 0;
        }
    }
    else {
        if (HUD->auxAlpha[playerID] > 0)
            HUD->auxAlpha[playerID] -= 8;

        self->alpha = HUD->auxAlpha[playerID];
        if (self->alpha > 0) {
            HUD->dpadAnimator.frameID = 2;
            RSDK.DrawSprite(&HUD->dpadAnimator, &auxPos, true);
        }
    }

    for (int32 c = 0; c < 6; ++c) {
        RSDK.SetPaletteEntry(0, 42 + c, HUD->colorStorage[c]);
    }

    if (canPause) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (HUD->pauseAlpha[playerID] < opacity)
                HUD->pauseAlpha[playerID] += 8;

            self->alpha                    = HUD->pauseAlpha[playerID];
            HUD->dpadTouchAnimator.frameID = 5;
            RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->pausePos, true);
        }
        else {
            HUD->pauseAlpha[playerID] = 0;
        }
    }
    else {
        if (HUD->pauseAlpha[playerID] > 0)
            HUD->pauseAlpha[playerID] -= 8;

        self->alpha = HUD->pauseAlpha[playerID];
        if (self->alpha > 0) {
            HUD->dpadTouchAnimator.frameID = 5;
            RSDK.DrawSprite(&HUD->dpadTouchAnimator, &HUD->pausePos, true);
        }
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

void HUD_DrawMobileHUD(void)
{
    RSDK_THIS(HUD);

    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);
    Vector2 drawPos;

    if (DebugMode && RSDK_GET_ENTITY(SLOT_PLAYER1, Player)->classID == DebugMode->classID) {
        if (player->camera) {
            // Draw Camera YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y = TO_FIXED(42);
            HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.y);

            // Draw Camera XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.x);

            // Draw Player YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y += TO_FIXED(16);
            HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.y));

            // Draw Player XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.x));
        }
    }
#if MANIA_USE_PLUS
    else if (self->actionPromptPos > -TO_FIXED(64) && globals->gameMode == MODE_TIMEATTACK) {
        drawPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x) - self->actionPromptPos;
        drawPos.y = TO_FIXED(48);

        if (API.CheckDLC(DLC_PLUS)) {
            // Draw Replay Save Icon
            RSDK.DrawSprite(&self->replayClapAnimator, &drawPos, true);
            drawPos.y += TO_FIXED(28);
        }
        // Draw Thumbs Up Icon
        RSDK.DrawSprite(&self->thumbsUpIconAnimator, &drawPos, true);
    }
#endif
}

int32 HUD_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy)
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

void HUD_HandleHyperFlash(EntityPlayer *player)
{
    RSDK_THIS(HUD);
    if (player->hyperFlashTimer != 0) {
        RSDK.FillScreen(0xFFFFFF, player->hyperFlashTimer, player->hyperFlashTimer - 16, player->hyperFlashTimer - 32);
        player->hyperFlashTimer -= 16;
    }
}

#if GAME_INCLUDE_EDITOR
void HUD_EditorDraw(void)
{
    RSDK_THIS(HUD);
    RSDK.SetSpriteAnimation(HUD->aniFrames, 0, &self->hudElementsAnimator, true, 0);
    RSDK.DrawSprite(&self->hudElementsAnimator, NULL, false);
}

void HUD_EditorLoad(void) { HUD->aniFrames = RSDK.LoadSpriteAnimation("Editor/EditorIcons.bin", SCOPE_STAGE); }
#endif

void HUD_Serialize(void) {}
