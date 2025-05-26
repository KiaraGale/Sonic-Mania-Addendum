// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: SpecialRing Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectSpecialRing *SpecialRing;

color hyperRingColors[6][6] = {
    { 0x707000, 0xB4B400, 0xEAEB00, 0xFCFC6C, 0xFCFCB4, 0xFCFCFC },
    { 0x7C5A7C, 0x9D729D, 0xBD89BD, 0xE8BAE8, 0xFCD8FC, 0xFCFCFC },
    { 0x455C73, 0x577B9E, 0x6C8FB2, 0x8CB6DE, 0xB4D8FC, 0xFCFCFC },
    { 0x29652A, 0x2C872C, 0x24B424, 0x48D848, 0x90FC90, 0xFCFCFC },
    { 0x728A42, 0x8CB53B, 0xADD43A, 0xC4EC51, 0xD8FC6C, 0xFCFCFC },
    { 0x8A7228, 0xB49024, 0xD8B424, 0xEDCA3B, 0xFCD86C, 0xFCFCFC }
};

void SpecialRing_Update(void)
{
    RSDK_THIS(SpecialRing);

    StateMachine_Run(self->state);
}

void SpecialRing_LateUpdate(void) {}

void SpecialRing_StaticUpdate(void) {}

void SpecialRing_Draw(void)
{
    RSDK_THIS(SpecialRing);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    SpecialRing->hyperTimer++;

    if (SpecialRing->hyperTimer > 4) {
        SpecialRing->hyperTimer = 0;
        SpecialRing->hyperColorState++;
    }

    if (SpecialRing->hyperColorState > 5)
        SpecialRing->hyperColorState = 0;

    if (self->state == SpecialRing_State_Flash) {
        self->direction = self->warpAnimator.frameID > 8;

        if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
            int32 hyperState = SpecialRing->hyperColorState;
            for (int32 s = 0; s < 6; s++) {
                SpecialRing->colorStorage[s] = RSDK.GetPaletteEntry(0, 42 + s);
                RSDK.SetPaletteEntry(0, 42 + s, hyperRingColors[hyperState][s]);
            }
        }
        else if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
            for (int32 s = 0; s < 6; s++) {
                SpecialRing->colorStorage[s] = RSDK.GetPaletteEntry(0, 42 + s);
                RSDK.SetPaletteEntry(0, 42 + s, SpecialRing->silverRingColors[s]);
            }
        }

        RSDK.DrawSprite(&self->warpAnimator, NULL, false);

        if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
            for (int32 s = 0; s < 6; s++)
                RSDK.SetPaletteEntry(0, 42 + s, SpecialRing->colorStorage[s]);
        }
        else if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
            for (int32 s = 0; s < 6; s++)
                RSDK.SetPaletteEntry(0, 42 + s, SpecialRing->colorStorage[s]);
        }
    }
    else {
        RSDK.Prepare3DScene(SpecialRing->sceneIndex);
        if (self->enabled) {
            if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                int32 hyperState = SpecialRing->hyperColorState;
                RSDK.AddModelTo3DScene(SpecialRing->modelIndex, SpecialRing->sceneIndex, S3D_SOLIDCOLOR_SHADED_BLENDED, &self->matWorld, &self->matNormal, SpecialRing->hyperRingColors[hyperState]);
            }
            else if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                RSDK.AddModelTo3DScene(SpecialRing->modelIndex, SpecialRing->sceneIndex, S3D_SOLIDCOLOR_SHADED_BLENDED, &self->matWorld, &self->matNormal, 0xF0F0F0);
            else
                RSDK.AddModelTo3DScene(SpecialRing->modelIndex, SpecialRing->sceneIndex, S3D_SOLIDCOLOR_SHADED_BLENDED, &self->matWorld, &self->matNormal, 0xF0F000);
        }
        else
            RSDK.AddModelTo3DScene(SpecialRing->modelIndex, SpecialRing->sceneIndex, S3D_WIREFRAME_SHADED, &self->matWorld, &self->matNormal, 0x609090);
        RSDK.Draw3DScene(SpecialRing->sceneIndex);
    }
}

void SpecialRing_Create(void *data)
{
    RSDK_THIS(SpecialRing);

    if (!SceneInfo->inEditor) {
        self->active        = ACTIVE_BOUNDS;
        self->visible       = true;
        self->updateRange.x = TO_FIXED(144);
        self->updateRange.y = TO_FIXED(144);
        self->drawFX        = FX_FLIP;
        if (self->planeFilter > 0 && ((uint8)self->planeFilter - 1) & 2)
            self->drawGroup = Zone->objectDrawGroup[1];
        else
            self->drawGroup = Zone->objectDrawGroup[0];
        self->state = SpecialRing_State_Idle;

        RSDK.SetSpriteAnimation(SpecialRing->aniFrames, 0, &self->warpAnimator, true, 0);
    }
}

void SpecialRing_StageLoad(void)
{
    SpecialRing->aniFrames = RSDK.LoadSpriteAnimation("Global/SpecialRing.bin", SCOPE_STAGE);

    SpecialRing->modelIndex = RSDK.LoadMesh("Global/SpecialRing.bin", SCOPE_STAGE);
    SpecialRing->sceneIndex = RSDK.Create3DScene("View:SpecialRing", 512, SCOPE_STAGE);

    SpecialRing->hitbox.left   = -18;
    SpecialRing->hitbox.top    = -18;
    SpecialRing->hitbox.right  = 18;
    SpecialRing->hitbox.bottom = 18;

    // sets diffuse colour (overrides)
    RSDK.SetDiffuseColor(SpecialRing->sceneIndex, 0xA0, 0xA0, 0xA0);
    // sets diffuse intensity (0-8 means more diffuse, any more and it'll start darkening to black (9-12), any greater than 11 is full black)
    RSDK.SetDiffuseIntensity(SpecialRing->sceneIndex, 8, 8, 8);
    // sets specular (highlight) intensity (16-0, 16 = none, 0 = all)
    RSDK.SetSpecularIntensity(SpecialRing->sceneIndex, 14, 14, 14);

    SpecialRing->sfxSpecialRing = RSDK.GetSfx("Global/SpecialRing.wav");
    SpecialRing->sfxSpecialWarp = RSDK.GetSfx("Global/SpecialWarp.wav");

    DEBUGMODE_ADD_OBJ(SpecialRing);

    foreach_all(SpecialRing, ring)
    {
        if (ring->id <= 0 || globals->gameMode == MODE_TIMEATTACK || globals->gameMode == MODE_COMPETITION) {
            ring->enabled = false;
        }
        else {
            ring->enabled = !SaveGame_GetCollectedSpecialRing(ring->id);

            if (globals->specialRingID == ring->id) {
                for (int32 p = 0; p < Player->playerCount; ++p) {
                    EntityPlayer *player = RSDK_GET_ENTITY(p, Player);

                    player->position.x = ring->position.x;
                    player->position.y = ring->position.y + TO_FIXED(16);
                    if (!p) {
                        if (globals->gameMode != MODE_COMPETITION) {
                            EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
                            player->position.x = player1->position.x;
                            player->position.y = player1->position.y;
                            player->direction  = player1->direction;
                            if (player1->direction) {
                                player->position.x += TO_FIXED(16 * p);
                            }
                            else {
                                player->position.x -= TO_FIXED(16 * p);
                            }

                            for (int32 f = 0; f < 0x10; ++f) {
                                Player->leaderPositionBuffer[player->playerID][f].x = player->position.x;
                                Player->leaderPositionBuffer[player->playerID][f].y = player->position.y;
                            }
                        }
                    }
                }

                SceneInfo->milliseconds = globals->tempMilliseconds;
                SceneInfo->seconds      = globals->tempSeconds;
                SceneInfo->minutes      = globals->tempMinutes;
            }
        }
    }

    if (SceneInfo->activeCategory != 9)
        globals->specialRingID = 0;
}

void SpecialRing_DebugDraw(void)
{
    RSDK.SetSpriteAnimation(Ring->aniFrames, 1, &DebugMode->animator, true, 0);
    RSDK.DrawSprite(&DebugMode->animator, NULL, false);
}
void SpecialRing_DebugSpawn(void)
{
    RSDK_THIS(SpecialRing);

    EntitySpecialRing *specialRing = CREATE_ENTITY(SpecialRing, NULL, self->position.x, self->position.y);
    specialRing->enabled           = true;
}

void SpecialRing_State_Idle(void)
{
    RSDK_THIS(SpecialRing);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    self->angleZ = (self->angleZ + 4) & 0x3FF;
    self->angleY = (self->angleY + 4) & 0x3FF;

    Vector2 range;
    range.x = TO_FIXED(128);
    range.y = TO_FIXED(128);
    if (!RSDK.CheckOnScreen(self, &range))
        self->scale.x = 0;

    if (self->scale.x >= 0x140)
        self->scale.x = 0x140;
    else
        self->scale.x += ((0x168 - self->scale.x) >> 5);

    RSDK.MatrixScaleXYZ(&self->matTransform, self->scale.x, self->scale.x, self->scale.x);
    RSDK.MatrixTranslateXYZ(&self->matTransform, self->position.x, self->position.y, 0, false);
    RSDK.MatrixRotateXYZ(&self->matWorld, 0, self->angleY, self->angleZ);
    RSDK.MatrixMultiply(&self->matWorld, &self->matWorld, &self->matTransform);
    RSDK.MatrixRotateX(&self->matTempRot, 0x1E0);
    RSDK.MatrixRotateXYZ(&self->matNormal, 0, self->angleY, self->angleZ);
    RSDK.MatrixMultiply(&self->matNormal, &self->matNormal, &self->matTempRot);

    if (self->enabled && self->scale.x > 0x100) {
        foreach_active(Player, player)
        {
            if ((self->planeFilter <= 0 || player->collisionPlane == (((uint8)self->planeFilter - 1) & 1)) && !player->sidekick) {
                if (Player_CheckCollisionTouch(player, self, &SpecialRing->hitbox) && SceneInfo->timeEnabled) {
                    self->sparkleRadius = TO_FIXED(16);
                    self->state         = SpecialRing_State_Flash;

                    if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                        if (!SaveGame_AllChaosEmeralds() && self->id || !Addendum_AllSuperEmeralds() && self->id) {
                            player->visible        = false;
                            player->active         = ACTIVE_NEVER;
                            SceneInfo->timeEnabled = false;
                        }
                        else {
                            if (addendumOptions->coopStyle == COOPSTYLE_TOGETHER) {
                                for (int32 p = 0; p < addendumVar->playerCount; ++p) {
                                    EntityPlayer* player = RSDK_GET_ENTITY(p, Player);
                                    Player_GiveRings(player, 50, true);
                                }
                            }
                            else
                                Player_GiveRings(player, 50, true);
                        }

                        if (self->id > 0) {
                            if (!SaveGame_AllChaosEmeralds() || !Addendum_AllSuperEmeralds())
                                globals->specialRingID = self->id;

                            SaveGame_SetCollectedSpecialRing(self->id);
                        }
                    }
                    else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
                        if (!SaveGame_AllChaosEmeralds() && self->id || !Addendum_AllTimeStones() && self->id) {
                            player->visible        = false;
                            player->active         = ACTIVE_NEVER;
                            SceneInfo->timeEnabled = false;
                        }
                        else {
                            if (addendumOptions->coopStyle == COOPSTYLE_TOGETHER) {
                                for (int32 p = 0; p < addendumVar->playerCount; ++p) {
                                    EntityPlayer* player = RSDK_GET_ENTITY(p, Player);
                                    Player_GiveRings(player, 50, true);
                                }
                            }
                            else
                                Player_GiveRings(player, 50, true);
                        }

                        if (self->id > 0) {
                            if (!SaveGame_AllChaosEmeralds() || !Addendum_AllTimeStones())
                                globals->specialRingID = self->id;

                            SaveGame_SetCollectedSpecialRing(self->id);
                        }
                    }
                    else {
                        if (!SaveGame_AllChaosEmeralds() && self->id) {
                            player->visible        = false;
                            player->active         = ACTIVE_NEVER;
                            SceneInfo->timeEnabled = false;
                        }
                        else {
                            if (addendumOptions->coopStyle == COOPSTYLE_TOGETHER) {
                                for (int32 p = 0; p < addendumVar->playerCount; ++p) {
                                    EntityPlayer* player = RSDK_GET_ENTITY(p, Player);
                                    Player_GiveRings(player, 50, true);
                                }
                            }
                            else
                                Player_GiveRings(player, 50, true);
                        }

                        if (self->id > 0) {
                            if (!SaveGame_AllChaosEmeralds())
                                globals->specialRingID = self->id;

                            SaveGame_SetCollectedSpecialRing(self->id);
                        }
                    }

                    RSDK.PlaySfx(SpecialRing->sfxSpecialRing, false, 0xFE);
                }
            }
        }
    }
}
void SpecialRing_State_Flash(void)
{
    RSDK_THIS(SpecialRing);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    RSDK.ProcessAnimation(&self->warpAnimator);

    if (!(Zone->timer & 3)) {
        for (int32 i = 0; i < 3; ++i) {
            int32 x             = self->position.x + RSDK.Rand(-TO_FIXED(32), TO_FIXED(2)) + self->sparkleRadius;
            int32 y             = self->position.y + RSDK.Rand(-TO_FIXED(32), TO_FIXED(32));
            EntityRing *sparkle = CREATE_ENTITY(Ring, NULL, x, y);

            sparkle->state     = Ring_State_Sparkle;
            sparkle->stateDraw = SpecialRing_Draw_Sparkles;
            sparkle->active    = ACTIVE_NORMAL;
            sparkle->visible   = false;
            sparkle->drawGroup = Zone->objectDrawGroup[0];
            RSDK.SetSpriteAnimation(Ring->aniFrames, i % 3 + 2, &sparkle->animator, true, 0);
            int32 cnt = sparkle->animator.frameCount;
            if (sparkle->animator.animationID == 2) {
                sparkle->alpha = 0xE0;
                cnt >>= 1;
            }
            sparkle->maxFrameCount  = cnt - 1;
            sparkle->animator.speed = RSDK.Rand(6, 8);
            sparkle->timer          = 2 * i;
        }

        self->sparkleRadius -= TO_FIXED(8);
    }

    if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
        if (SaveGame_AllChaosEmeralds() && Addendum_AllSuperEmeralds() || !self->id) {
            if (self->warpAnimator.frameID == self->warpAnimator.frameCount - 1)
                destroyEntity(self);
        }
        else if (self->warpAnimator.frameID == self->warpAnimator.frameCount - 1) {
            self->warpTimer = 0;
            self->visible   = false;
            self->state     = SpecialRing_State_Warp;
        }
    }
    else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
        if (SaveGame_AllChaosEmeralds() && Addendum_AllTimeStones() || !self->id) {
            if (self->warpAnimator.frameID == self->warpAnimator.frameCount - 1)
                destroyEntity(self);
        }
        else if (self->warpAnimator.frameID == self->warpAnimator.frameCount - 1) {
            self->warpTimer = 0;
            self->visible   = false;
            self->state     = SpecialRing_State_Warp;
        }
    }
    else {
        if (SaveGame_AllChaosEmeralds() || !self->id) {
            if (self->warpAnimator.frameID == self->warpAnimator.frameCount - 1)
                destroyEntity(self);
        }
        else if (self->warpAnimator.frameID == self->warpAnimator.frameCount - 1) {
            self->warpTimer = 0;
            self->visible   = false;
            self->state     = SpecialRing_State_Warp;
        }
    }
}
void SpecialRing_State_Warp(void)
{
    RSDK_THIS(SpecialRing);
    SaveRAM *saveRAM                 = SaveGame_GetSaveRAM();
    AddendumData *addendumData       = Addendum_GetSaveRAM();
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (++self->warpTimer == 30) {
        SaveGame_SaveGameState();
        RSDK.PlaySfx(SpecialRing->sfxSpecialWarp, false, 0xFE);
        destroyEntity(self);

        if (saveRAM->collectedEmeralds == 0b00000000)
            saveRAM->nextSpecialStage = 0;

        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
            if (saveRAM->collectedEmeralds >= 0b01111111) {
                addendumVar->doHPZResults = false;
                saveRAM->storedStageID = SceneInfo->listPos;
                RSDK.SetScene("Addendum", "Super Emerald Chamber");

                Zone_StartFadeOut(8, 0xF0F0F0);
                Music_Stop();
            }
            else {
                saveRAM->storedStageID = SceneInfo->listPos;
                RSDK.SetScene("Special Stage", "");
                SceneInfo->listPos += saveRAM->nextSpecialStage;

                Zone_StartFadeOut(8, 0xF0F0F0);
                Music_Stop();
            }
        }
        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
            // this statement allows for easy compatibility with pre-Addendum files that already have all Chaos Emeralds
            if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones != 0b01111111) {
                switch (addendumData->collectedTimeStones) {
                    case 0b00000000: saveRAM->nextSpecialStage = 7; break;
                    case 0b00000001: saveRAM->nextSpecialStage = 8; break;
                    case 0b00000011: saveRAM->nextSpecialStage = 9; break;
                    case 0b00000111: saveRAM->nextSpecialStage = 10; break;
                    case 0b00001111: saveRAM->nextSpecialStage = 11; break;
                    case 0b00011111: saveRAM->nextSpecialStage = 12; break;
                    case 0b00111111: saveRAM->nextSpecialStage = 13; break;
                }
            }

            saveRAM->storedStageID = SceneInfo->listPos;
            RSDK.SetScene("Special Stage", "");
            SceneInfo->listPos += saveRAM->nextSpecialStage;

            Zone_StartFadeOut(8, 0xF0F0F0);
            Music_Stop();
        }
        else {
            saveRAM->storedStageID = SceneInfo->listPos;
            RSDK.SetScene("Special Stage", "");
            SceneInfo->listPos += saveRAM->nextSpecialStage;

            Zone_StartFadeOut(8, 0xF0F0F0);
            Music_Stop();
        }
    }
}

void SpecialRing_Draw_Sparkles(void)
{
    RSDK_THIS(Ring);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
        int32 hyperState = SpecialRing->hyperColorState;
        for (int32 s = 0; s < 6; s++) {
            SpecialRing->colorStorage[s] = RSDK.GetPaletteEntry(0, 42 + s);
            RSDK.SetPaletteEntry(0, 42 + s, hyperRingColors[hyperState][s]);
        }
    }
    else if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
        for (int32 s = 0; s < 6; s++) {
            SpecialRing->colorStorage[s] = RSDK.GetPaletteEntry(0, 42 + s);
            RSDK.SetPaletteEntry(0, 42 + s, SpecialRing->silverRingColors[s]);
        }
    }

    if (self->alpha == 0xE0) {
        self->animator.frameID += 16;
        self->inkEffect = INK_ADD;
        RSDK.DrawSprite(&self->animator, NULL, false);

        self->inkEffect = INK_NONE;
        self->animator.frameID -= 16;
    }
    RSDK.DrawSprite(&self->animator, NULL, false);

    if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
        for (int32 s = 0; s < 6; s++) RSDK.SetPaletteEntry(0, 42 + s, SpecialRing->colorStorage[s]);
    }
    else if (SaveGame_AllChaosEmeralds() && addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
        for (int32 s = 0; s < 6; s++) RSDK.SetPaletteEntry(0, 42 + s, SpecialRing->colorStorage[s]);
    }
}

#if GAME_INCLUDE_EDITOR
void SpecialRing_EditorDraw(void)
{
    RSDK_THIS(SpecialRing);

    RSDK.SetSpriteAnimation(SpecialRing->aniFrames, 0, &self->warpAnimator, true, 7);
    RSDK.DrawSprite(&self->warpAnimator, NULL, false);
}

void SpecialRing_EditorLoad(void)
{
    SpecialRing->aniFrames = RSDK.LoadSpriteAnimation("Global/SpecialRing.bin", SCOPE_STAGE);

    RSDK_ACTIVE_VAR(SpecialRing, planeFilter);
    RSDK_ENUM_VAR("None", PLANEFILTER_NONE);
    RSDK_ENUM_VAR("AL", PLANEFILTER_AL);
    RSDK_ENUM_VAR("BL", PLANEFILTER_BL);
    RSDK_ENUM_VAR("AH", PLANEFILTER_AH);
    RSDK_ENUM_VAR("BH", PLANEFILTER_BH);
}
#endif

void SpecialRing_Serialize(void)
{
    RSDK_EDITABLE_VAR(SpecialRing, VAR_ENUM, id);
    RSDK_EDITABLE_VAR(SpecialRing, VAR_ENUM, planeFilter);
}
