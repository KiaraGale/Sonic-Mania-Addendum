// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: HPZEmerald Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectHPZEmerald *HPZEmerald;

void HPZEmerald_Update(void)
{
    RSDK_THIS(HPZEmerald);
    AddendumData *addendumData = Addendum_GetSaveRAM();
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    RSDK.ProcessAnimation(&self->emeraldAnimator);
    RSDK.ProcessAnimation(&self->overlayAnimator);

    if (self->solid) {
        if (self->type != HPZEMERALD_MASTER) {
            foreach_active(Player, player) { Player_CheckCollisionPlatform(player, self, self->hitbox); }

            // check if in the "Addendum" scene category (used to distinguish between HPZ Emerald Chamber and LRZ3 Heavy King arena)
            if (SceneInfo->activeCategory == 9) {
                if (Player_CheckCollisionPlatform(player1, self, self->hitbox)) {
                    if (addendumData->emeraldsTransferred) {
                        if (!self->superEmeraldObtained) {
                            player1->stateInput = StateMachine_None;
                            CutsceneSeq_LockPlayerControl(player1);
                            player1->velocity.x = 0;
                            player1->velocity.y = 0;
                            player1->groundVel  = 0;
                            player1->state      = Player_State_Static;
                            RSDK.SetSpriteAnimation(player1->aniFrames, ANI_IDLE, &player1->animator, false, 0);

                            if (self->warpTimer == 15) {
                                RSDK.SetScene("Special Stage", "");
                                SceneInfo->listPos += (self->emeraldID) + 7;

                                RSDK.PlaySfx(HPZEmerald->sfxSpecialWarp, false, 0xFF);
                                Zone_StartFadeOut(10, 0xF0F0F0);
                                Music_FadeOut(0.05);
                            }
                            else
                                self->warpTimer++;
                        }
                    }
                }
            }
        }

        foreach_active(HeavyKing, king)
        {
            if (king->bodyAnimator.animationID != 5 && !king->onGround
                && RSDK.CheckObjectCollisionPlatform(self, self->hitbox, king, &HeavyKing->hitboxBody, true)) {
                Camera_ShakeScreen(0, 0, 3);
                RSDK.PlaySfx(HeavyKing->sfxImpact2, false, 255);
            }
        }
    }

    if (!self->onGround) {
        self->velocity.y += 0x3800;
        self->position.y += self->velocity.y;

        if (self->position.y >= self->startPos.y && self->velocity.y > 0) {
            self->position.y = self->startPos.y;
            self->velocity.y = -(self->velocity.y >> 1);

            if (!self->velocity.y)
                self->onGround = true;
        }
    }

    RSDK.SetPaletteEntry(0, 214, 0xB0D8D8);
    RSDK.SetPaletteEntry(0, 215, 0xC8E8E0);

    if (self->forceActive) {
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 2, &self->emeraldAnimator, false, self->emeraldID);
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 3, &self->overlayAnimator, false, self->emeraldID);
    }
}

void HPZEmerald_LateUpdate(void) {}

void HPZEmerald_StaticUpdate(void) {}

void HPZEmerald_Draw(void)
{
    RSDK_THIS(HPZEmerald);
    AddendumData *addendumData       = Addendum_GetSaveRAM();
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    EntityPauseMenu *pauseMenu       = RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);

    self->inkEffect = INK_NONE;

    for (int32 c = 0; c < 5; ++c) {
        RSDK.SetPaletteEntry(0, 208 + c, HPZEmerald->masterColors[c]);
    }
    
    for (int32 c = 0; c < 6; ++c) {
        RSDK.SetPaletteEntry(0, 215 + c, HPZEmerald->masterColors[c + 5]);
    }

    if (self->solid) {
        RSDK.SetActivePalette(6, 0, ScreenInfo->size.y);
        RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);
        if (self->overlayOnly) {
            self->alpha     = 0;
            self->inkEffect = INK_NONE;
            RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 1, &self->emeraldAnimator, true, 1);
            RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);
            self->alpha     = self->overlayTimer;
            self->inkEffect = INK_ADD;
            RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 3, &self->overlayAnimator, true, self->emeraldID);
            RSDK.DrawSprite(&self->overlayAnimator, NULL, false);
        }
        else {
            if (self->superEmeraldObtained || self->forceActive) {
                if (!self->alpha) {
                    self->alpha = abs(RSDK.Sin256(self->timer * 1.25) / 3);
                    self->alpha >>= 1;
                    self->inkEffect = INK_NONE;
                    if (self->forceActive)
                        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 2, &self->emeraldAnimator, true, self->emeraldID);
                    RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);
                    self->alpha <<= 1;
                    LogHelpers_Print("alpha is %d", self->alpha);
                    self->inkEffect = INK_ADD;
                    if (self->forceActive)
                        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 3, &self->overlayAnimator, true, self->emeraldID);
                    RSDK.DrawSprite(&self->overlayAnimator, NULL, false);
                    self->alpha = 0;
                    if (pauseMenu->classID != PauseMenu->classID)
                        ++self->timer;
                }
            }
        }
        RSDK.SetActivePalette(0, 0, ScreenInfo->size.y);
    }
    else {
        if (addendumData->collectedSuperEmeralds == 0b01111111 && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
            RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);

            if (!self->alpha) {
                self->alpha = abs(RSDK.Sin256(self->timer * 1.25) / 3);
                self->alpha >>= 1;
                self->inkEffect = INK_NONE;
                RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);
                self->alpha <<= 1;
                self->inkEffect = INK_ADD;
                RSDK.DrawSprite(&self->overlayAnimator, NULL, false);
                self->alpha = 0;
                if (pauseMenu->classID != PauseMenu->classID)
                    ++self->timer;
            }
        }
        else {
            self->inkEffect = INK_NONE;
            RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);

            self->inkEffect = INK_ADD;
            RSDK.DrawSprite(&self->overlayAnimator, NULL, false);
        }
    }
}

void HPZEmerald_Create(void *data)
{
    RSDK_THIS(HPZEmerald);

    if (!SceneInfo->inEditor) {
        AddendumData *addendumData       = Addendum_GetSaveRAM();
        AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
        self->visible = true;

        RSDK.SetPaletteEntry(6, 41, 0xFFFFFF);

        for (int32 c = 0; c < 56; ++c)
            RSDK.SetPaletteEntry(6, 128 + c, HPZEmerald->superEmeraldColors[c + (addendumOptions->emeraldPalette * 56)]);

        for (int32 c = 0; c < 8; ++c)
            RSDK.SetPaletteEntry(6, 208 + c, HPZEmerald->relicColors[c]);

        switch (self->type) {
            default:
            case HPZEMERALD_MASTER: self->drawGroup = 1; break;
                    
            case HPZEMERALD_EMERALD_LOW:
                self->solid     = true;
                self->drawGroup = Zone->objectDrawGroup[0];
                break;

            case HPZEMERALD_EMERALD_HIGH:
                self->solid     = true;
                self->drawGroup = Zone->objectDrawGroup[1];
                break;
        }

        self->startPos      = self->position;
        self->active        = ACTIVE_BOUNDS;
        self->updateRange.x = 0x800000;
        self->updateRange.y = 0x800000;
        self->onGround      = true;

        if (self->type != HPZEMERALD_MASTER) {
            if (addendumData->emeraldsTransferred && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                if ((addendumData->collectedSuperEmeralds & (1 << self->emeraldID)) != 0)
                    self->superEmeraldObtained = true;

                if (self->superEmeraldObtained || self->forceActive) {
                    RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 2, &self->emeraldAnimator, true, self->emeraldID);
                    RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 3, &self->overlayAnimator, true, self->emeraldID);
                }
                else
                    RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 1, &self->emeraldAnimator, true, 1);
            }
            else
                RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 1, &self->emeraldAnimator, true, 0);
        }
        else {
            RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 0, &self->emeraldAnimator, true, 0);
            RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 0, &self->overlayAnimator, true, 1);
        }

        self->hitbox = RSDK.GetHitbox(&self->emeraldAnimator, 0);

        if (SceneInfo->activeCategory == 9) {
            if (addendumVar->doHPZResults) {
                SpecialClear->SortedSuperEmeralds[self->emeraldID] = self;
                LogHelpers_Print("emerald %d inserted into slot %d", self->emeraldID, self->linearID);
            }
            else {
                HPZIntro->SortedSuperEmeralds[self->linearID] = self;
                LogHelpers_Print("emerald %d inserted into slot %d", self->emeraldID, self->linearID);
            }
        }
    }
}

void HPZEmerald_StageLoad(void)
{
    HPZEmerald->aniFrames = RSDK.LoadSpriteAnimation("LRZ3/Emerald.bin", SCOPE_STAGE);
    HPZEmerald->sfxSpecialWarp = RSDK.GetSfx("Global/SpecialWarp.wav");
}

#if GAME_INCLUDE_EDITOR
void HPZEmerald_EditorDraw(void)
{
    RSDK_THIS(HPZEmerald);

    self->solid = false;
    switch (self->type) {
        default:
        case HPZEMERALD_MASTER:
        case HPZEMERALD_EMERALD_LOW: self->solid = true; break;

        case HPZEMERALD_EMERALD_HIGH: self->solid = true; break;
    }

    if (self->type) {
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 1, &self->emeraldAnimator, true, 0);
    }
    else {
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 0, &self->emeraldAnimator, true, 0);
        RSDK.SetSpriteAnimation(HPZEmerald->aniFrames, 0, &self->overlayAnimator, true, 1);
    }

    self->inkEffect = INK_NONE;
    RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);
}

void HPZEmerald_EditorLoad(void)
{
    HPZEmerald->aniFrames = RSDK.LoadSpriteAnimation("LRZ3/Emerald.bin", SCOPE_STAGE);

    RSDK_ACTIVE_VAR(HPZEmerald, type);
    RSDK_ENUM_VAR("Master Emerald", HPZEMERALD_MASTER);
    RSDK_ENUM_VAR("Stone Emerald (Low Group)", HPZEMERALD_EMERALD_LOW);
    RSDK_ENUM_VAR("Stone Emerald (High Group)", HPZEMERALD_EMERALD_HIGH);
}
#endif

void HPZEmerald_Serialize(void)
{
    RSDK_EDITABLE_VAR(HPZEmerald, VAR_UINT8, type);
    RSDK_EDITABLE_VAR(HPZEmerald, VAR_UINT8, emeraldID);
    RSDK_EDITABLE_VAR(HPZEmerald, VAR_UINT8, linearID);
}
