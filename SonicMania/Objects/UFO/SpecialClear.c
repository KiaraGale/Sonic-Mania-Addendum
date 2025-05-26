// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: SpecialClear Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectSpecialClear *SpecialClear;

void SpecialClear_Update(void)
{
    RSDK_THIS(SpecialClear);

    if (self->state == SpecialClear_State_ExitFinishMessageMiracle && !UFO_Setup && Addendum_GetSaveRAM()->collectedSuperEmeralds != 0b01111111) {
        self->timer    = 0;
        self->showFade = true;
        RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
        self->state = SpecialClear_State_ExitResults;
    }

    if (SpecialClear->sparkleType) {
        for (int32 i = 0; i != 16; ++i) {
            SpecialClear->sparklePos[i].x =
                SpecialClear->sparkleTarget.x
                + RSDK.Cos256(SpecialClear->sparkleAngle + 0x10 * i) * SpecialClear->sparkleDistance;
            SpecialClear->sparklePos[i].y =
                SpecialClear->sparkleTarget.y
                + RSDK.Sin256(SpecialClear->sparkleAngle + 0x10 * i) * SpecialClear->sparkleDistance;
        }
    }
    switch (SpecialClear->sparkleType) {
        case 1:
            SpecialClear->sparkleAngle += 4;
            SpecialClear->sparkleDistance -= 0x100;
            if (SpecialClear->sparkleDistance < 0)
                SpecialClear->sparkleType = 0;
            break;
        case 2:
            SpecialClear->sparkleAngle -= 4;
            SpecialClear->sparkleDistance += 0x100;
            if (SpecialClear->sparkleDistance >= 0x10000)
                SpecialClear->sparkleType = 0;
            break;
        default: break;
    }
}

void SpecialClear_LateUpdate(void)
{
    RSDK_THIS(SpecialClear);

    StateMachine_Run(self->state);
}

void SpecialClear_StaticUpdate(void) {}

void SpecialClear_Draw(void)
{
    RSDK_THIS(SpecialClear);

    if (!UFO_Setup && SpecialClear->backgroundFade) {
        RSDK.FillScreen(0xFFFFFF, SpecialClear->backgroundFade, SpecialClear->backgroundFade - 128, SpecialClear->backgroundFade - 256);
    }
    if (SpecialClear->startFadingBackground)
        SpecialClear->backgroundFade -= 0x10;

    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    Vector2 vertPos[4];
    Vector2 drawPos;

    int32 centerX = ScreenInfo->center.x << 16;
    drawPos.x     = centerX - 0x600000;

    if (UFO_Setup) {
        for (int32 c = 0; c < 36; ++c) {
            RSDK.SetPaletteEntry(0, 128 + c, SpecialClear->emeraldPalettes[c + (addendumOptions->emeraldPalette * 36)]);
        }
    }

    // Draw Emeralds
    if (UFO_Setup) {
        for (int32 i = 0; i < 7; ++i) {
            int32 frame = 7;
            if (SaveGame_GetEmerald(i))
                frame = i;
            self->emeraldsAnimator.frameID = frame;
            drawPos.y = addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE ? self->emeraldPositions[i] - 0x70000 : self->emeraldPositions[i];
            RSDK.DrawSprite(&self->emeraldsAnimator, &drawPos, true);
            drawPos.x += 0x200000;
        }
    }

    if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
        drawPos.x = centerX - 0x600000;
        // Draw Time Stones
        for (int32 i = 0; i < 7; ++i) {
            int32 frame = 7;
            if (Addendum_GetTimeStone(i))
                frame = i;
            self->timeStonesAnimator.frameID = frame;
            drawPos.y                        = self->emeraldPositions[i] + 0x130000;
            RSDK.DrawSprite(&self->timeStonesAnimator, &drawPos, true);
            drawPos.x += 0x200000;
        }
    }



    drawPos.x    = self->messagePos2.x;
    drawPos.y    = self->messagePos2.y;
    drawPos.x    = centerX + 2 * drawPos.x;
    vertPos[0].x = drawPos.x - 0x740000;
    vertPos[0].y = drawPos.y - 0x140000;
    vertPos[1].x = 0x680000 + drawPos.x;
    vertPos[2].x = 0x780000 + drawPos.x;
    vertPos[3].x = drawPos.x - 0x640000;
    vertPos[1].y = drawPos.y - 0x140000;
    vertPos[2].y = drawPos.y - 0x40000;
    vertPos[3].y = drawPos.y - 0x40000;
    RSDK.DrawFace(vertPos, 4, 0x00, 0x00, 0x00, 0xFF, INK_NONE);

    if (self->messageType > SC_MSG_SPECIALCLEAR) {
        drawPos.x    = self->messagePos1.x;
        drawPos.y    = self->messagePos1.y;
        drawPos.x    = centerX + 2 * drawPos.x;
        vertPos[0].x = drawPos.x - 0x740000;
        vertPos[0].y = drawPos.y + 0x1C0000;
        vertPos[1].x = 0x680000 + drawPos.x;
        vertPos[2].x = 0x780000 + drawPos.x;
        vertPos[3].x = drawPos.x - 0x640000;
        vertPos[1].y = drawPos.y + 0x1C0000;
        vertPos[2].y = drawPos.y + 0x2C0000;
        vertPos[3].y = drawPos.y + 0x2C0000;
        RSDK.DrawFace(vertPos, 4, 0x00, 0x00, 0x00, 0xFF, INK_NONE);
    }

    drawPos.x = self->messagePos1.x;
    drawPos.y = self->messagePos1.y;
    drawPos.x += centerX;
    switch (self->messageType) {
        case SC_MSG_SPECIALCLEAR:
            self->playerNameAnimator.frameID = 0;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
            break;

        case SC_MSG_GOTEMERALD:
            self->playerNameAnimator.frameID = 1;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            self->playerNameAnimator.frameID = 2;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            drawPos.x = self->messagePos2.x;
            drawPos.y = self->messagePos2.y;
            drawPos.x += centerX;
            self->playerNameAnimator.frameID = 3;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
            break;

        case SC_MSG_ALLEMERALDS:
            self->playerNameAnimator.frameID = 4;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            self->playerNameAnimator.frameID = 5;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            drawPos.x = self->messagePos2.x;
            drawPos.y = self->messagePos2.y;
            drawPos.x += centerX;
            self->playerNameAnimator.frameID = 6;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
            break;

        case SC_MSG_SUPER:
            self->playerNameAnimator.frameID = 7;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            self->playerNameAnimator.frameID = 8;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            self->playerNameAnimator.frameID = 9;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            drawPos.x = self->messagePos2.x;
            drawPos.y = self->messagePos2.y;
            drawPos.x += centerX;
            self->playerNameAnimator.frameID = 10;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            self->playerNameAnimator.frameID = 11;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

            self->playerNameAnimator.frameID = 13;
            RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
            break;

        if (addendumOptions->secondaryGems != SECONDGEMS_NONE) {
            case SC_MSG_GOTSECONDGEM:
                self->playerNameAnimator.frameID = 1;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                self->playerNameAnimator.frameID = 2;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                drawPos.x = self->messagePos2.x;
                drawPos.y = self->messagePos2.y;
                drawPos.x += centerX;
                if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                    self->playerNameAnimator.frameID = 19;
                else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                    self->playerNameAnimator.frameID = 14;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
                break;

            case SC_MSG_ALLSECONDGEMS:
                self->playerNameAnimator.frameID = 4;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                self->playerNameAnimator.frameID = 5;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                drawPos.x = self->messagePos2.x;
                drawPos.y = self->messagePos2.y;
                drawPos.x += centerX;
                if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                    self->playerNameAnimator.frameID = 20;
                else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                    self->playerNameAnimator.frameID = 15;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
                break;

            case SC_MSG_NEWPOWERFORM:
                self->playerNameAnimator.frameID = 7;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                self->playerNameAnimator.frameID = 8;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                self->playerNameAnimator.frameID = 9;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                drawPos.x = self->messagePos2.x;
                drawPos.y = self->messagePos2.y;
                drawPos.x += centerX;
                if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                    self->playerNameAnimator.frameID = 10;
                else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                    self->playerNameAnimator.frameID = 16;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
                    for (int32 c = 0; c < 6; ++c) {
                        SpecialClear->colorStorage[c] = RSDK.GetPaletteEntry(0, 42 + c);
                        RSDK.SetPaletteEntry(0, 42 + c, SpecialClear->miracleColors[c]);
                    }
                }

                if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                    self->playerNameAnimator.frameID = 12;
                else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                    self->playerNameAnimator.frameID = 17;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                    self->playerNameAnimator.frameID = 13;
                else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                    self->playerNameAnimator.frameID = 18;
                RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

                if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
                    for (int32 c = 0; c < 6; ++c) {
                        RSDK.SetPaletteEntry(0, 42 + c, SpecialClear->colorStorage[c]);
                    }
                }
                break;
        }

        default: break;
    }
    drawPos.x = self->scoreBonusPos.x;
    drawPos.y = self->scoreBonusPos.y;
    drawPos.x += centerX - 0x560000;
    self->bonusAnimator.frameID = 4;
    RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

    self->bonusAnimator.frameID = 6;
    drawPos.x += 0x660000;
    RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

    drawPos.x += 0x430000;
    SpecialClear_DrawNumbers(&drawPos, self->score);

    drawPos.x = self->ringBonusPos.x;
    drawPos.y = self->ringBonusPos.y;
    drawPos.x += centerX - 0x560000;
    self->bonusAnimator.frameID = 0;
    RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

    drawPos.x += 3276800;
    self->bonusAnimator.frameID = 3;
    RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

    self->bonusAnimator.frameID = 6;
    drawPos.x += 3407872;
    RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

    drawPos.x += 0x430000;
    SpecialClear_DrawNumbers(&drawPos, self->ringBonus);

    if (self->isBSS) {
        drawPos.x = self->perfectBonusPos.x;
        drawPos.y = self->perfectBonusPos.y;
        drawPos.x += centerX - 0x560000;
        self->bonusAnimator.frameID = 1;
        RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

        drawPos.x += 0x320000;
        self->bonusAnimator.frameID = 3;
        RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

        self->bonusAnimator.frameID = 6;
        drawPos.x += 0x340000;
        RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

        drawPos.x += 0x430000;
        SpecialClear_DrawNumbers(&drawPos, self->perfectBonus);
    }
    else {
        drawPos.x = self->machBonusPos.x;
        drawPos.y = self->machBonusPos.y;
        drawPos.x += centerX - 0x560000;
        self->bonusAnimator.frameID = 2;
        RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

        drawPos.x += 0x320000;
        self->bonusAnimator.frameID = 3;
        RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

        self->bonusAnimator.frameID = 6;
        drawPos.x += 0x340000;
        RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

        drawPos.x += 0x430000;
        SpecialClear_DrawNumbers(&drawPos, self->machBonus);
    }

    if (self->hasContinues) {
        drawPos.x = self->continuePos.x;
        drawPos.y = self->continuePos.y;
        drawPos.x += centerX - 0x560000;
        self->bonusAnimator.frameID = 5;
        RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

        if (self->continueIconVisible) {
            drawPos.x += 0xB00000;
            drawPos.y += 0xA0000;
            RSDK.DrawSprite(&self->continueAnimator, &drawPos, true);
        }
    }

    if (SpecialClear->sparkleType) {
        for (int32 i = 0; i != 16; ++i) {
            RSDK.DrawSprite(&self->sparkleAnimator[i], &SpecialClear->sparklePos[i], false);
            RSDK.ProcessAnimation(&self->sparkleAnimator[i]);
        }
    }

    if (self->showFade)
        RSDK.FillScreen(self->fillColor, self->timer, self->timer - 128, self->timer - 256);
}

void SpecialClear_Create(void *data)
{
    RSDK_THIS(SpecialClear);
    int32 playerID = GET_CHARACTER_ID(1);

    if (!SceneInfo->inEditor) {
        self->active    = ACTIVE_NORMAL;
        self->visible   = true;
        self->drawGroup = 14;
        self->timer     = 512;
        self->fillColor = 0xF0F0F0;
        self->showFade  = true;
        self->state     = SpecialClear_State_SetupDelay;

        if (RSDK.CheckSceneFolder("SpecialBS")) {
            // Blue Spheres...?
            // This screen doesn't show up in regular BSS gameplay

            self->isBSS     = true;
            self->ringBonus = 100 * BSS_Setup->rings;
            if (!BSS_Setup->ringCount)
                self->perfectBonus = 50000;

            self->messageType = SC_MSG_SPECIALCLEAR;
        }
        else {
            if (UFO_Setup)
                RSDK.CopyPalette(7, 0, 0, 0, 128);

            self->isBSS = false;
            if (UFO_Setup) {
                self->ringBonus = 100 * UFO_Setup->rings;
                self->machBonus = 1000 * (UFO_Setup->machLevel + 10 * UFO_Setup->scoreBonus);
            }
            else {
                self->ringBonus = 100 * addendumVar->carryOverValue[3];
                self->machBonus = 1000 * (addendumVar->carryOverValue[1] + 10 * addendumVar->carryOverValue[2]);
            }

            SpecialClear->failedStage = addendumVar->carryOverValue[0];
            SpecialClear->specialStageID = addendumVar->carryOverValue[4];

            if (globals->gameMode < MODE_TIMEATTACK && self->machBonus + self->ringBonus >= 10000)
                self->hasContinues = true;

            SaveRAM *saveRAM                 = SaveGame_GetSaveRAM();
            AddendumData *addendumData       = Addendum_GetSaveRAM();
            AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
            self->score      = saveRAM->score;
            self->score1UP   = saveRAM->score1UP;
            self->lives      = saveRAM->lives;

            if (saveRAM->collectedEmeralds != 0b01111111)
                self->messageType = SpecialClear->failedStage ? SC_MSG_SPECIALCLEAR : SC_MSG_GOTEMERALD;
            
            if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                if (saveRAM->collectedEmeralds == 0b01111111) {
                    if (SpecialClear->specialStageID > 6) {
                        if (!SpecialClear->failedStage)
                            self->messageType = SC_MSG_GOTSECONDGEM;
                        else
                            self->messageType = SC_MSG_SPECIALCLEAR;
                    }
                    else
                        self->messageType = SC_MSG_ALLEMERALDS;
                }
                else {
                    if (!SpecialClear->failedStage)
                        self->messageType = SC_MSG_GOTEMERALD;
                    else
                        self->messageType = SC_MSG_SPECIALCLEAR;
                }

                if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedSuperEmeralds != 0b01111111)
                    self->messageType = SpecialClear->failedStage ? SC_MSG_SPECIALCLEAR : SC_MSG_GOTSECONDGEM;

                if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedSuperEmeralds >= 0b01111111)
                    self->messageType = SC_MSG_ALLSECONDGEMS;
            }
            else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
                if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones == 0b00000000) {
                    if (UFO_Setup->specialStageID <= 6)
                        self->messageType = SC_MSG_ALLEMERALDS;
                    else
                        self->messageType = SC_MSG_SPECIALCLEAR;
                }

                if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones == CLAMP(addendumData->collectedTimeStones, 0b00000001, 0b00111111))
                    self->messageType = UFO_Setup->timedOut ? SC_MSG_SPECIALCLEAR : SC_MSG_GOTSECONDGEM;

                if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones == 0b01111111)
                    self->messageType = SC_MSG_ALLSECONDGEMS;
            }
            else {
                if (saveRAM->collectedEmeralds == 0b01111111)
                    self->messageType = SC_MSG_ALLEMERALDS;
                else
                    self->messageType = SC_MSG_SPECIALCLEAR;
            }
        }

        // "Player Got A"
        self->messagePos1.x = 0x1400000;
        self->messagePos1.y = 0x580000;

        // "Chaos Emerald"
        self->messagePos2.x = -0x1400000;
        self->messagePos2.y = 0x700000;

        self->scoreBonusPos.x = 0x1E80000;
        self->scoreBonusPos.y = 0x9C0000;

        self->ringBonusPos.x = 0x3080000;
        self->ringBonusPos.y = 0xAC0000;

        self->machBonusPos.x = 0x4280000;
        self->machBonusPos.y = 0xBC0000;

        // this is still here and fully functional, however this object is never shown after BSS, so its unused
        self->perfectBonusPos.x = 0x4280000;
        self->perfectBonusPos.y = 0xBC0000;
        self->continuePos.x     = 0x5480000;
        self->continuePos.y     = 0xCC0000;

        if (UFO_Setup) {
            RSDK.CopyPalette(1, 0, 0, 128, 48);
            RSDK.CopyPalette(1, 48, 0, 176, 48);
        }

        for (int32 i = 0; i < 7; ++i) {
            self->emeraldPositions[i] = 0x1100000 + (i * 0x200000);
            self->emeraldSpeeds[i]    = -0xA0000 + (i * -0xA000);
        }

        for (int32 i = 0; i < 7; ++i) {
            self->timeStonePositions[i] = 0x1100000 + (i * 0x200000);
            self->timeStoneSpeeds[i]    = -0xA0000 + (i * -0xA000);
        }

        RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_BONUS, &self->bonusAnimator, true, 0);
        RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_NUMBERS, &self->numbersAnimator, true, 0);
        RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_EMERALDS, &self->emeraldsAnimator, true, 0);
        RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_TIMESTONES, &self->timeStonesAnimator, true, 0);

        switch (GET_CHARACTER_ID(1)) {
            default:
            case ID_SONIC: RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_SONIC, &self->playerNameAnimator, true, 0);
#if MANIA_USE_PLUS
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_SONIC);
#else
                RSDK.SetSpriteAnimation(SpecialClear->continueFrames, 0, &self->continueAnimator, true, SC_ANI_TAILS);
#endif
                break;

            case ID_TAILS: RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_TAILS, &self->playerNameAnimator, true, 0);
#if MANIA_USE_PLUS
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_TAILS);
#else
                RSDK.SetSpriteAnimation(SpecialClear->continueFrames, 0, &self->continueAnimator, true, SC_ANI_TAILS);
#endif
                break;

            case ID_KNUCKLES: RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_KNUX, &self->playerNameAnimator, true, 0);
#if MANIA_USE_PLUS
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_KNUX);
#else
                RSDK.SetSpriteAnimation(SpecialClear->continueFrames, 0, &self->continueAnimator, true, SC_ANI_TAILS);
#endif
                break;

#if MANIA_USE_PLUS
            case ID_MIGHTY:
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_MIGHTY, &self->playerNameAnimator, true, 0);
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_MIGHTY);
                break;

            case ID_RAY:
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_RAY, &self->playerNameAnimator, true, 0);
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_RAY);
                break;

            case ID_AMY:
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_AMY, &self->playerNameAnimator, true, 0);
                RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, (SC_ANI_RAY) + 1);
                break;
#endif
        }
    }
}

void SpecialClear_StageLoad(void)
{
    SpecialClear->aniFrames = RSDK.LoadSpriteAnimation("Special/Results.bin", SCOPE_STAGE);
#if !MANIA_USE_PLUS
    SpecialClear->continueFrames = RSDK.LoadSpriteAnimation("Players/Continue.bin", SCOPE_STAGE);
#endif

    SpecialClear->sfxScoreAdd    = RSDK.GetSfx("Global/ScoreAdd.wav");
    SpecialClear->sfxScoreTotal  = RSDK.GetSfx("Global/ScoreTotal.wav");
    SpecialClear->sfxEvent       = RSDK.GetSfx("Special/Event.wav");
    SpecialClear->sfxSpecialWarp = RSDK.GetSfx("Global/SpecialWarp.wav");
    SpecialClear->sfxContinue    = RSDK.GetSfx("Special/Continue.wav");
    SpecialClear->sfxEmerald     = RSDK.GetSfx("Special/Emerald.wav");
    SpecialClear->sfxTimeStone   = RSDK.GetSfx("Special/TimeStone.wav");
    SpecialClear->sfx1up         = RSDK.GetSfx("Global/1up.wav");

    SpecialClear->sparkleAniFrames = RSDK.LoadSpriteAnimation("Cutscene/Emeralds.bin", SCOPE_STAGE);
    SpecialClear->startFadingBackground = false;
    SpecialClear->backgroundFade        = 0x200;
    SpecialClear->sparkleType           = 0;
}

void SpecialClear_DrawNumbers(Vector2 *pos, int32 value)
{
    RSDK_THIS(SpecialClear);

    int32 cnt = value;

    int32 digitCount = value ? 0 : 1;
    while (cnt > 0) {
        ++digitCount;
        cnt /= 10;
    }

    int32 digit = 1;
    while (digitCount) {
        self->numbersAnimator.frameID = value / digit % 10;
        RSDK.DrawSprite(&self->numbersAnimator, pos, true);
        digit *= 10;
        pos->x -= 0x90000;
        --digitCount;
    }
}

void SpecialClear_GiveScoreBonus(int32 score)
{
    RSDK_THIS(SpecialClear);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    self->score += score;
    if (self->score > 9999999)
        self->score = 9999999;

    if (self->score >= self->score1UP) {
        if (globals->gameMode != MODE_TIMEATTACK && globals->gameMode != MODE_ENCORE) {
            if (addendumOptions->lifeSystem != LIFESYSTEM_INFINITE) {
                if (addendumOptions->lifeSystem == LIFESYSTEM_MANIA) {
                    if (self->lives < 99) {
                        self->lives++;
                        RSDK.PlaySfx(SpecialClear->sfx1up, false, 0xFF);
                    }
                }
                else {
                    self->lives++;
                    RSDK.PlaySfx(SpecialClear->sfx1up, false, 0xFF);
                }
            }
        }

        while (self->score1UP <= self->score) self->score1UP += 50000;
    }
}

#if MANIA_USE_PLUS
void SpecialClear_SaveCB(bool32 success)
{
    RSDK_THIS(SpecialClear);

    UIWaitSpinner_FinishWait();
    self->saveInProgress = false;
}
#else
void SpecialClear_SaveCB(void)
{
    RSDK_THIS(SpecialClear);

    UIWaitSpinner_FinishWait();
    self->saveInProgress = false;
}
#endif

void SpecialClear_State_SetupDelay(void)
{
    RSDK_THIS(SpecialClear);

    if (self->timer <= 0) {
        self->timer    = 0;
        self->showFade = false;
        self->state    = SpecialClear_State_EnterText;

        Music_PlayTrack(TRACK_ACTCLEAR);
    }
    else {
        self->timer -= 16;
    }
}

void SpecialClear_State_EnterText(void)
{
    RSDK_THIS(SpecialClear);

    if (self->messagePos1.x > 0)
        self->messagePos1.x -= 0x100000;

    if (self->messagePos2.x < 0) {
        self->messagePos2.x += 0x100000;
    }

    if (++self->timer == 48) {
        self->timer = 0;
        self->state = SpecialClear_State_AdjustText;
    }
}

void SpecialClear_State_AdjustText(void)
{
    RSDK_THIS(SpecialClear);

    self->messagePos1.y -= 0x10000;
    self->messagePos2.y -= 0x10000;

    if (++self->timer == 48) {
        self->timer = 0;
        self->state = SpecialClear_State_EnterBonuses;
    }
}

void SpecialClear_HandleEmeraldAppear(void)
{
    RSDK_THIS(SpecialClear);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    int32 stopPosEmerald = self->messageType == SC_MSG_SPECIALCLEAR ? 0x680000 : 0x700000;

    for (int32 i = 0; i < 7; ++i) {
        self->emeraldSpeeds[i] += 0x4000;
        self->emeraldPositions[i] += self->emeraldSpeeds[i];

        if (self->emeraldPositions[i] > stopPosEmerald && self->emeraldSpeeds[i] >= 0) {
            self->emeraldPositions[i] = stopPosEmerald;
            self->emeraldSpeeds[i]    = -(self->emeraldSpeeds[i] >> 1);
        }
    }

    if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
        int32 stopPosTimeStone = self->messageType == SC_MSG_SPECIALCLEAR ? 0x780000 : 0x800000;

        for (int32 i = 0; i < 7; ++i) {
            self->timeStoneSpeeds[i] += 0x4000;
            self->timeStonePositions[i] += self->timeStoneSpeeds[i];

            if (self->timeStonePositions[i] > stopPosTimeStone && self->timeStoneSpeeds[i] >= 0) {
                self->timeStonePositions[i] = stopPosTimeStone;
                self->timeStoneSpeeds[i]    = -(self->timeStoneSpeeds[i] >> 1);
            }
        }
    }
}

void SpecialClear_State_EnterBonuses(void)
{
    RSDK_THIS(SpecialClear);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (self->scoreBonusPos.x > 0)
        self->scoreBonusPos.x -= 0x100000;

    if (self->ringBonusPos.x > 0)
        self->ringBonusPos.x -= 0x100000;

    if (self->perfectBonusPos.x > 0)
        self->perfectBonusPos.x -= 0x100000;

    if (self->machBonusPos.x > 0)
        self->machBonusPos.x -= 0x100000;

    if (self->continuePos.x <= 0) {
        if (self->messageType == SC_MSG_ALLEMERALDS) {
            API_UnlockAchievement(&achievementList[ACH_EMERALDS]);
        }
        if (self->messageType == SC_MSG_ALLSECONDGEMS) {
            if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                API_UnlockAchievement(&achievementList[ACH_EMERALDS]);
            else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                API_UnlockAchievement(&achievementList[ACH_TIMESTONES]);
        }

        self->state = SpecialClear_State_ScoreShownDelay;
    }
    else {
        self->continuePos.x -= 0x100000;
    }

    SpecialClear_HandleEmeraldAppear();
}

void SpecialClear_State_ScoreShownDelay(void)
{
    RSDK_THIS(SpecialClear);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (++self->timer == 120) {
        self->timer = 0;
        self->state = SpecialClear_State_TallyScore;

        switch (self->messageType) {
            case SC_MSG_GOTEMERALD:
            case SC_MSG_ALLEMERALDS:
                RSDK.PlaySfx(SpecialClear->sfxEmerald, false, 0xFF);
                break;

            case SC_MSG_GOTSECONDGEM:
            case SC_MSG_ALLSECONDGEMS:
                if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                    RSDK.PlaySfx(SpecialClear->sfxTimeStone, false, 0xFF);
                break;
        }
    }

    SpecialClear_HandleEmeraldAppear();
}

void SpecialClear_State_TallyScore(void)
{
    RSDK_THIS(SpecialClear);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (!UFO_Setup) {
        if (!SpecialClear->failedStage && !SpecialClear->startFadingBackground) {
            SpecialClear->startFadingBackground = true;
            EntityCamera *camera                = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
            EntityHPZEmerald *emerald           = SpecialClear->SortedSuperEmeralds[SpecialClear->specialStageID - 7];
            camera->position.x                  = emerald->position.x;
            camera->position.y                  -= TO_FIXED(264);
            camera->state                       = StateMachine_None;

            camera->boundsT -= TO_FIXED(1024);
            camera->boundsL -= TO_FIXED(1024);
            camera->boundsR += TO_FIXED(1024);

            RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 1, &emerald->emeraldAnimator, true, 1);
        }
    }

    if (touchControls) {
        if (TouchInfo->count && !ControllerInfo->keyStart.down)
            ControllerInfo->keyStart.press = true;
    }

    if (self->ringBonus > 0) {
        self->ringBonus -= 100;
        SpecialClear_GiveScoreBonus(100);
    }

    if (self->perfectBonus > 0) {
        self->perfectBonus -= 100;
        SpecialClear_GiveScoreBonus(100);
    }

    if (self->machBonus > 0) {
        self->machBonus -= 100;
        SpecialClear_GiveScoreBonus(100);
    }

    if (ControllerInfo->keyA.press || ControllerInfo->keyStart.press) {
        SpecialClear_GiveScoreBonus(self->machBonus + self->ringBonus + self->perfectBonus);
        self->ringBonus    = 0;
        self->perfectBonus = 0;
        self->machBonus    = 0;
    }

    if (self->machBonus + self->ringBonus + self->perfectBonus <= 0) {
        self->timer = 0;
        if (self->hasContinues)
            self->state = SpecialClear_State_ShowTotalScore_Continues;
        else
            self->state = SpecialClear_State_ShowTotalScore_NoContinues;

        RSDK.PlaySfx(SpecialClear->sfxScoreTotal, false, 0xFF);
    }
    else if (++self->timer == 2) {
        self->timer = 0;
        RSDK.PlaySfx(SpecialClear->sfxScoreAdd, false, 0xFF);
    }
}

void SpecialClear_State_ShowTotalScore_Continues(void)
{
    RSDK_THIS(SpecialClear);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (self->timer == 120) {
        RSDK.PlaySfx(SpecialClear->sfxContinue, false, 0xFF);

        if (globals->continues < 25)
            globals->continues++;
    }
    else if (self->timer > 120) {
        self->continueIconVisible = (self->timer >> 3) & 1;
    }

    if (self->timer >= 360) {
        SaveRAM *saveRAM                 = SaveGame_GetSaveRAM();
        AddendumData *addendumData       = Addendum_GetSaveRAM();
        AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
        saveRAM->score                   = self->score;
        globals->restartScore            = self->score;

        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
            if (addendumData->emeraldsTransferred) {
                if (self->timer >= 419) {
                    self->timer = 0;
                    if (!SpecialClear->failedStage || addendumData->collectedSuperEmeralds == 0b01111111) {
                        self->timer = 0;
                        self->state = SpecialClear_State_WaitToRevealSuperEmerald;
                    }
                    else {
                        self->timer    = 0;
                        self->showFade = true;
                        RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
                        self->state = SpecialClear_State_ExitResults;
                    }
                }
            }
            else {
                if (saveRAM->collectedEmeralds == 0b01111111) {
                    if (UFO_Setup->specialStageID <= 6) {
                        self->timer = 0;
                        self->state = SpecialClear_State_ExitFinishMessageSuper;
                    }
                }
                else {
                    self->timer    = 0;
                    self->showFade = true;
                    RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
                    self->state = SpecialClear_State_ExitResults;
                }
            }
        }
        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
            if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones == 0b00000000) {
                if (UFO_Setup->specialStageID <= 6) {
                    self->timer = 0;
                    self->state = SpecialClear_State_ExitFinishMessageSuper;
                }
                else {
                    self->timer    = 0;
                    self->showFade = true;
                    RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
                    self->state = SpecialClear_State_ExitResults;
                }
            }
            else if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones == 0b01111111) {
                self->timer = 0;
                self->state = SpecialClear_State_ExitFinishMessageMiracle;
            }
            else {
                self->timer    = 0;
                self->showFade = true;
                RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
                self->state = SpecialClear_State_ExitResults;
            }
        }
    }

    self->timer++;
}

void SpecialClear_State_ShowTotalScore_NoContinues(void)
{
    RSDK_THIS(SpecialClear);

    if (++self->timer >= 120) {
        SaveRAM *saveRAM                 = SaveGame_GetSaveRAM();
        AddendumData *addendumData       = Addendum_GetSaveRAM();
        AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
        saveRAM->score                   = self->score;
        globals->restartScore            = self->score;

        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
            if (addendumData->emeraldsTransferred) {
                if (self->timer >= 179) {
                    self->timer = 0;
                    if (!SpecialClear->failedStage || addendumData->collectedSuperEmeralds == 0b01111111) {
                        self->timer = 0;
                        self->state = SpecialClear_State_WaitToRevealSuperEmerald;
                    }
                    else {
                        self->timer    = 0;
                        self->showFade = true;
                        RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
                        self->state = SpecialClear_State_ExitResults;
                    }
                }
                else
                    self->timer++;
            }
            else {
                if (saveRAM->collectedEmeralds == 0b01111111) {
                    if (UFO_Setup->specialStageID <= 6) {
                        self->timer = 0;
                        self->state = SpecialClear_State_ExitFinishMessageSuper;
                    }
                }
                else {
                    self->timer    = 0;
                    self->showFade = true;
                    RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
                    self->state = SpecialClear_State_ExitResults;
                }
            }
        }
        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
            if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones == 0b00000000) {
                if (UFO_Setup->specialStageID <= 6) {
                    self->timer = 0;
                    self->state = SpecialClear_State_ExitFinishMessageSuper;
                }
                else {
                    self->timer    = 0;
                    self->showFade = true;
                    RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
                    self->state = SpecialClear_State_ExitResults;
                }
            }
            else if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones == 0b01111111) {
                self->timer = 0;
                self->state = SpecialClear_State_ExitFinishMessageMiracle;
            }
            else {
                self->timer    = 0;
                self->showFade = true;
                RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
                self->state = SpecialClear_State_ExitResults;
            }
        }
    }
}

void SpecialClear_State_ExitFinishMessageSuper(void)
{
    RSDK_THIS(SpecialClear);

    self->messagePos1.x += 0x180000;
    self->messagePos2.x -= 0x180000;

    if (++self->timer == 30) {
        self->timer       = 0;
        self->messageType = SC_MSG_SUPER;
        self->state       = SpecialClear_State_EnterSuperMessage;
    }
}

void SpecialClear_State_ExitFinishMessageMiracle(void)
{
    RSDK_THIS(SpecialClear);

    self->messagePos1.x += 0x180000;
    self->messagePos2.x -= 0x180000;

    if (++self->timer == 30) {
        self->timer       = 0;
        self->messageType = SC_MSG_NEWPOWERFORM;
        self->state       = SpecialClear_State_EnterSuperMessage;
    }
}

void SpecialClear_State_EnterSuperMessage(void)
{
    RSDK_THIS(SpecialClear);

    if (self->messagePos1.x > 0)
        self->messagePos1.x -= 0x180000;

    if (self->messagePos2.x >= 0) {
        RSDK.PlaySfx(SpecialClear->sfxEvent, false, 0xFF);
        self->state = SpecialClear_State_ShowSuperMessage;
    }
    else {
        self->messagePos2.x += 0x180000;
    }
}

void SpecialClear_State_ShowSuperMessage(void)
{
    RSDK_THIS(SpecialClear);

    if (++self->timer == 160) {
        self->timer    = 0;
        self->showFade = true;
        RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
        self->state = SpecialClear_State_ExitResults;
    }
}

void SpecialClear_State_ExitFadeOut(void)
{
    RSDK_THIS(SpecialClear);

    if (self->fillColor) {
        self->fillColor -= 0x080808;
    }
    else if (!self->saveInProgress) {
        EntityMenuParam *param = MenuParam_GetParam();

        if (param->bssSelection == BSS_SELECTION_EXTRAS) {
            RSDK.SetScene("Presentation", "Menu");
            RSDK.LoadScene();
        }
        else {
            SaveRAM *saveRAM = SaveGame_GetSaveRAM();
#if MANIA_USE_PLUS
            if (globals->gameMode == MODE_ENCORE)
                RSDK.SetScene("Encore Mode", "");
            else
#endif
                RSDK.SetScene("Mania Mode", "");

            SceneInfo->listPos = saveRAM->storedStageID;
            RSDK.LoadScene();
        }
    }
}

void SpecialClear_State_ExitResults(void)
{
    RSDK_THIS(SpecialClear);

    if (self->timer >= 768) {
        self->state = SpecialClear_State_ExitFadeOut;

        if (globals->gameMode < MODE_TIMEATTACK && globals->saveSlotID != NO_SAVE_SLOT) {
            self->saveInProgress = true;
            UIWaitSpinner_StartWait();
            if (Addendum_GetOptionsRAM()->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                if (SpecialClear->specialStageID <= 6)
                    GameProgress_TrackGameProgress(SpecialClear_SaveCB);
                else
                    Addendum_TrackGameProgress(SpecialClear_SaveCB);
            }
            else if (Addendum_GetOptionsRAM()->secondaryGems == SECONDGEMS_TIMESTONE) {
                if (UFO_Setup->specialStageID <= 6)
                    GameProgress_TrackGameProgress(SpecialClear_SaveCB);
                else
                    Addendum_TrackGameProgress(SpecialClear_SaveCB);
            }
            else {
                GameProgress_TrackGameProgress(SpecialClear_SaveCB);
            }
        }
    }
    else {
        self->timer += 8;
    }
}

void SpecialClear_State_WaitToRevealSuperEmerald(void)
{
    RSDK_THIS(SpecialClear);
    LogHelpers_Print("WaitToRevealSuperEmerald");

    ++self->timer;
    LogHelpers_Print("timer value is %d", self->timer);
    if (self->hasContinues)
        self->continueIconVisible = ((self->timer + 179) >> 3) & 1;
    if (self->timer >= 60) {
        self->timer = 0;
        EntityCamera *camera      = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
        EntityHPZEmerald *emerald = SpecialClear->SortedSuperEmeralds[SpecialClear->specialStageID - 7];
        camera->position.x        = emerald->position.x;
        Camera_SetupLerp(CAMERA_LERP_NORMAL, 0, camera->position.x, camera->position.y + TO_FIXED(264), 1);
        self->state = SpecialClear_State_RevealSuperEmerald;
    }
}

void SpecialClear_State_RevealSuperEmerald(void)
{
    RSDK_THIS(SpecialClear);
    EntityCamera *camera      = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
    EntityHPZEmerald *emerald = SpecialClear->SortedSuperEmeralds[SpecialClear->specialStageID - 7];

    if (!self->timer)
        emerald->overlayOnly = true;

    ++self->timer;
    if (self->hasContinues)
        self->continueIconVisible = ((self->timer + 239) >> 3) & 1;

    if (self->timer >= 24) {
        if (self->messagePos1.x != 0x1400000)
            self->messagePos1.x += 0x180000;
        if (self->messagePos2.x != -0x1400000)
            self->messagePos2.x -= 0x180000;
    }
    if (self->timer >= 42 && self->scoreBonusPos.x != 0x1E80000)
        self->scoreBonusPos.x += 0x100000;
    if (self->timer >= 60 && self->ringBonusPos.x != 0x3080000)
        self->ringBonusPos.x += 0x100000;
    if (self->timer >= 78) {
        if (self->machBonusPos.x != 0x4280000)
            self->machBonusPos.x += 0x100000;
        if (self->perfectBonusPos.x != 0x4280000)
            self->perfectBonusPos.x += 0x100000;
    }
    if (self->timer >= 96 && self->continuePos.x != 0x5480000)
        self->continuePos.x += 0x100000;

    RSDKScreenInfo *screen = &ScreenInfo[camera->screenID];
    if (screen->size.y + screen->position.y >= camera->boundsB) {
        RSDK.PlaySfx(HPZIntro->sfxTwinkle, false, 0xFF);
        self->timer = 0;
        self->state                   = SpecialClear_State_ActivateSuperEmerald;
        SpecialClear->sparkleType     = 1;
        SpecialClear->sparkleTarget   = emerald->position;
        SpecialClear->sparkleAngle    = 0;
        SpecialClear->sparkleDistance = 0xE000;
        for (int32 i = 0; i != 16; ++i) {
            SpecialClear->sparklePos[i].x = SpecialClear->sparkleTarget.x + RSDK.Cos256(0x10 * i) * SpecialClear->sparkleDistance;
            SpecialClear->sparklePos[i].y = SpecialClear->sparkleTarget.y + RSDK.Sin256(0x10 * i) * SpecialClear->sparkleDistance;
            RSDK.SetSpriteAnimation(SpecialClear->sparkleAniFrames, 1, &self->sparkleAnimator[i], true, i % 16);
        }
    }
}

void SpecialClear_State_ActivateSuperEmerald(void)
{
    RSDK_THIS(SpecialClear);

    ++self->timer;
    LogHelpers_Print("timer is %d", self->timer);

    if (self->timer < 225) {
        EntityHPZEmerald *emerald = SpecialClear->SortedSuperEmeralds[SpecialClear->specialStageID - 7];
        emerald->overlayTimer = self->timer / 2.67857142857142;
        LogHelpers_Print("overlayTimer is %d", emerald->overlayTimer);
    }

    if (self->timer == 225) {
        EntityHPZEmerald *emerald = SpecialClear->SortedSuperEmeralds[SpecialClear->specialStageID - 7];
        emerald->superEmeraldObtained = true;
        emerald->forceActive          = true;
        emerald->overlayOnly          = false;
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 2, &emerald->emeraldAnimator, false, emerald->emeraldID);
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 3, &emerald->overlayAnimator, false, emerald->emeraldID);
        RSDK.PlaySfx(HPZIntro->sfxEmeraldFlying, false, 0xFF);
        addendumVar->doHPZResults = false;
    }

    if (self->timer >= 254) {
        self->timer = 0;
        if (Addendum_GetSaveRAM()->collectedSuperEmeralds == 0b01111111) {
            EntityCamera *camera   = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
            RSDKScreenInfo *screen = &ScreenInfo[camera->screenID];
            Camera_SetupLerp(CAMERA_LERP_NORMAL, 0, TO_FIXED(576), TO_FIXED(676), 1);
            self->state = SpecialClear_State_RevealMasterEmerald;
        }
        else {
            self->showFade  = true;
            self->fillColor = 0x000000;
            self->state     = SpecialClear_State_ExitResults;
        }
    }
}

void SpecialClear_State_RevealMasterEmerald(void)
{
    RSDK_THIS(SpecialClear);

    EntityCamera *camera = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
    if (FROM_FIXED(camera->position.x) == FROM_FIXED(camera->endLerpPos.x)) {
        self->timer = 0;
        RSDK.PlaySfx(HPZIntro->sfxTwinkle, false, 0xFF);
        self->state                   = SpecialClear_State_ActivateMasterEmerald;
        SpecialClear->sparkleType     = 2;
        SpecialClear->sparkleTarget.x = TO_FIXED(576);
        SpecialClear->sparkleTarget.y = TO_FIXED(584);
        SpecialClear->sparkleAngle    = 0;
        SpecialClear->sparkleDistance = 0;
        for (int32 i = 0; i != 16; ++i) {
            SpecialClear->sparklePos[i].x =
                SpecialClear->sparkleTarget.x + RSDK.Cos256(0x10 * i) * SpecialClear->sparkleDistance;
            SpecialClear->sparklePos[i].y =
                SpecialClear->sparkleTarget.y + RSDK.Sin256(0x10 * i) * SpecialClear->sparkleDistance;
            RSDK.SetSpriteAnimation(SpecialClear->sparkleAniFrames, 1, &self->sparkleAnimator[i], true, i % 16);
        }
    }
}

void SpecialClear_State_ActivateMasterEmerald(void)
{
    RSDK_THIS(SpecialClear);

    ++self->timer;
    if (self->timer >= 60) {
        self->timer         = 0;
        self->messagePos1.y = 0xB80000;
        self->messagePos2.y = 0xD00000;
        self->messageType   = SC_MSG_NEWPOWERFORM;
        self->state         = SpecialClear_State_EnterHyperMessage;
    }
}

void SpecialClear_State_EnterHyperMessage(void)
{
    RSDK_THIS(SpecialClear);

    if (self->messagePos1.x > 0)
        self->messagePos1.x -= 0x180000;

    if (self->messagePos2.x >= 0) {
        RSDK.PlaySfx(SpecialClear->sfxEvent, false, 0xFF);
        self->state = SpecialClear_State_ShowHyperMessage;
    }
    else {
        self->messagePos2.x += 0x180000;
    }
}

void SpecialClear_State_ShowHyperMessage(void)
{
    RSDK_THIS(SpecialClear);

    if (++self->timer == 160) {
        self->timer     = 0;
        self->showFade  = true;
        self->fillColor = 0x000000;
        self->state     = SpecialClear_State_ExitResults;
    }
}

#if GAME_INCLUDE_EDITOR
void SpecialClear_EditorDraw(void) {}

void SpecialClear_EditorLoad(void) {}
#endif

void SpecialClear_Serialize(void) {}
