// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: Player Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectPlayer *Player;

Hitbox Player_FallbackHitbox = { -10, -20, 10, 20 };

color hyperPalette_Sonic[6][6] = {
    { 0x21E247, 0x60ED88, 0x83F1AA, 0xA8F8CA, 0xC5FCDF, 0xE3FFF4 }, // green
    { 0x4ED9FA, 0x6CE9FC, 0x88F4FA, 0xA4FAFA, 0xC1FAFA, 0xDEFAFA }, // cyan
    { 0x0A44FF, 0x546FFF, 0x7984FF, 0xA09DFF, 0xBFBAFF, 0xDDD6FF }, // blue
    { 0xDE2CFF, 0xE665FF, 0xE987FF, 0xF3A7FF, 0xFBC2FF, 0xFFDDFE }, // purple
    { 0xFF3436, 0xFF6B75, 0xFF8C98, 0xFFAAB8, 0xFDC4CE, 0xFDDEE6 }, // red
    { 0xFFC527, 0xFFDC61, 0xFEE883, 0xFEF3A4, 0xF8F2BF, 0xFBFADC }  // yellow
};

color hyperPalette_Sonic_HCZ[6][6] = {
    { 0x5BEAA8, 0x74ECC1, 0x83EDCF, 0x91EEDA, 0x9DEDE1, 0xA9EFE8 },
    { 0xB0BD92, 0xB2CFAC, 0xB3D9BB, 0xB4E1C9, 0xB3E6D4, 0xB5ECE1 },
    { 0x9295E7, 0x9CAFE9, 0xA1BDEA, 0xA9CCEB, 0xA0D7EA, 0xB4E4EC },
    { 0x5B9AE7, 0x74AFE9, 0x85BEEA, 0x95CCEB, 0xA0D7EA, 0xACE4EC },
    { 0xB09599, 0xB2AFB4, 0xB3BEC3, 0xB4CCD1, 0xB3D7DA, 0xB5E4E4 },
    { 0x67DEEF, 0x73E4EF, 0x80E9EF, 0x8DEEEF, 0x9AF0EF, 0xA6F2EF }
};

color hyperPalette_Sonic_CPZ[6][6] = {
    { 0x9988B5, 0xB38ACE, 0xC28BDC, 0xD08CE7, 0xDB8BEE, 0xE88DF6 },
    { 0xEE5B9F, 0xF06CB9, 0xF176C8, 0xF27FD6, 0xF183E1, 0xF38AEE },
    { 0xD033F4, 0xDB4CF7, 0xE05BF7, 0xE869F8, 0xED75F7, 0xF281FA },
    { 0x9938F4, 0xB34DF7, 0xC45BF7, 0xD369F8, 0xDE75F7, 0xEA81FA },
    { 0xEE33A6, 0xF04CC1, 0xF15BD0, 0xF269DE, 0xF175E7, 0xF381F2 },
    { 0xA57BFC, 0xB282FC, 0xBF87FC, 0xCB8CFC, 0xD88EFC, 0xE590FC }
};

/* Original colors
color hyperPalette_Sonic[6][6] = {
    { 0x44EE70, 0x77F3A1, 0x95F4BD, 0xB1F6D4, 0xC8F4E2, 0xE1F9F1 },
    { 0xEE9444, 0xF3B777, 0xF4CB95, 0xF6DCB1, 0xF4E5C8, 0xF9F2E1 },
    { 0xB244EE, 0xC777F3, 0xD194F4, 0xE1B1F6, 0xECC8F4, 0xF7E1F9 },
    { 0x444EEE, 0x7778F3, 0x9995F4, 0xB8B1F6, 0xCEC8F4, 0xE6E1F9 },
    { 0xEE4452, 0xF37788, 0xF495A6, 0xF6B1C1, 0xF4C8D4, 0xF9E1E9 },
    { 0x5CD5FF, 0x75E2FF, 0x8FEDFF, 0xA8F6FF, 0xC2FBFF, 0xDBFFFF }
};

color hyperPalette_Sonic_HCZ[6][6] = {
    { 0x5BEAA8, 0x74ECC1, 0x83EDCF, 0x91EEDA, 0x9DEDE1, 0xA9EFE8 },
    { 0xB0BD92, 0xB2CFAC, 0xB3D9BB, 0xB4E1C9, 0xB3E6D4, 0xB5ECE1 },
    { 0x9295E7, 0x9CAFE9, 0xA1BDEA, 0xA9CCEB, 0xA0D7EA, 0xB4E4EC },
    { 0x5B9AE7, 0x74AFE9, 0x85BEEA, 0x95CCEB, 0xA0D7EA, 0xACE4EC },
    { 0xB09599, 0xB2AFB4, 0xB3BEC3, 0xB4CCD1, 0xB3D7DA, 0xB5E4E4 },
    { 0x67DEEF, 0x73E4EF, 0x80E9EF, 0x8DEEEF, 0x9AF0EF, 0xA6F2EF }
};

color hyperPalette_Sonic_CPZ[6][6] = {
    { 0x9988B5, 0xB38ACE, 0xC28BDC, 0xD08CE7, 0xDB8BEE, 0xE88DF6 },
    { 0xEE5B9F, 0xF06CB9, 0xF176C8, 0xF27FD6, 0xF183E1, 0xF38AEE },
    { 0xD033F4, 0xDB4CF7, 0xE05BF7, 0xE869F8, 0xED75F7, 0xF281FA },
    { 0x9938F4, 0xB34DF7, 0xC45BF7, 0xD369F8, 0xDE75F7, 0xEA81FA },
    { 0xEE33A6, 0xF04CC1, 0xF15BD0, 0xF269DE, 0xF175E7, 0xF381F2 },
    { 0xA57BFC, 0xB282FC, 0xBF87FC, 0xCB8CFC, 0xD88EFC, 0xE590FC }
};
*/

color hyperPaletteWhite[3][6] = {
    { 0xDCDCDC, 0xE3E3E3, 0xEAEAEA, 0xF1F1F1, 0xF8F8F8, 0xFFFFFF },
    { 0xA7E1DE, 0xAAE5E1, 0xAEE8E5, 0xB1EBE8, 0xB5EFEC, 0xB8F2EF },
    { 0xE57FEB, 0xE982EF, 0xEC86F2, 0xEF89F6, 0xF38DF9, 0xF690FC }
};

color hyperPaletteWhite_Ray[3][7] = {
    { 0xD5D5D5, 0xDCDCDC, 0xE3E3E3, 0xEAEAEA, 0xF1F1F1, 0xF8F8F8, 0xFFFFFF },
    { 0x97D7CF, 0xA7E1DE, 0xAAE5E1, 0xAEE8E5, 0xB1EBE8, 0xB5EFEC, 0xB8F2EF },
    { 0xD66FE1, 0xE57FEB, 0xE982EF, 0xEC86F2, 0xEF89F6, 0xF38DF9, 0xF690FC }
};

void Player_Update(void)
{
    RSDK_THIS(Player);
    EntityPlayer *leader             = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *sidekick           = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    SaveRAM *saveRAM                 = SaveGame_GetSaveRAM();
    AddendumData *addendumData       = Addendum_GetSaveRAM();
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    EntitySuperSparkle *superSparkle = RSDK_GET_ENTITY(self->playerID + Player->playerCount, SuperSparkle);

#if MANIA_USE_PLUS
    // Cheat prevention, you can't play as mighty, ray, or amy if you don't have plus installed & active
    if (!API.CheckDLC(DLC_PLUS) && self->characterID > ID_KNUCKLES)
        Player_ChangeCharacter(self, ID_SONIC);

    StateMachine_Run(self->stateInputReplay);
#endif

    StateMachine_Run(self->stateInput);

    if (self->classID == Player->classID) {
        if (self->camera) {
            if (self->scrollDelay > 0) {
                self->scrollDelay--;
                if (!self->scrollDelay)
                    self->camera->state = Camera_State_FollowXY;
            }
            else if (self->state != Player_State_LookUp && self->state != Player_State_Crouch) {
                if (self->camera->lookPos.y > 0)
                    self->camera->lookPos.y -= 2;
                else if (self->camera->lookPos.y < 0)
                    self->camera->lookPos.y += 2;
            }
        }

        if (self->invincibleTimer) {
            if (self->invincibleTimer <= 0) {
                self->invincibleTimer++;
            }
            else {
                self->invincibleTimer--;
                if (!self->invincibleTimer) {
                    Player_ApplyShield(self);

#if MANIA_USE_PLUS
                    if (globals->gameMode != MODE_ENCORE || !self->sidekick) {
#else
                    if (!self->sidekick) {
#endif
                        bool32 stopPlaying = true;
                        foreach_active(Player, player)
                        {
                            if (player->invincibleTimer > 0)
                                stopPlaying = false;
                        }

                        if (stopPlaying)
                            Music_JingleFadeOut(TRACK_INVINCIBLE, true);
                    }
                }
            }
        }

        if (self->speedShoesTimer > 0) {
            self->speedShoesTimer--;
            if (!self->speedShoesTimer) {
                Player_UpdatePhysicsState(self);

                bool32 stopPlaying = true;
                foreach_active(Player, player)
                {
                    if (player->speedShoesTimer > 0)
                        stopPlaying = false;
                }

                if (stopPlaying)
                    Music_JingleFadeOut(TRACK_SNEAKERS, true);
            }
        }

        if (self->state != Player_State_Hurt) {
            if (self->blinkTimer > 0) {
                self->blinkTimer--;
                self->visible = !(self->blinkTimer & 4);
            }
        }

#if MANIA_USE_PLUS
        if (self->characterID == ID_RAY && self->state != Player_State_RayGlide && !self->isGhost) {
            Player->raySwoopTimer = 0;
            Player->rayDiveTimer  = 0;
        }

        if (self->uncurlTimer > 0)
            self->uncurlTimer--;
#endif
        Player_HandleSuperForm();

        if (self->characterID == ID_TAILS && self->state != Player_State_TailsFlight && self->abilitySpeed)
            self->abilitySpeed = 0;

        // Hurt Player if we're touching T/B or L/R sides at same time
        if (self->collisionFlagH == (1 | 2) || self->collisionFlagV == (1 | 2))
            self->deathType = PLAYER_DEATH_DIE_USESFX;

        self->collisionFlagH = 0;
        self->collisionFlagV = 0;
        if (self->collisionLayers & Zone->moveLayerMask) {
            TileLayer *move  = RSDK.GetTileLayer(Zone->moveLayer);
            move->position.x = -self->moveLayerPosition.x >> 16;
            move->position.y = -self->moveLayerPosition.y >> 16;
        }

        if (self->forceRespawn)
            self->state = Player_State_HoldRespawn;

#if GAME_VERSION != VER_100
        if (self->isTransforming)
            self->state = Player_State_Transform;
#endif

        StateMachine_Run(self->state);

        if (self->classID == Player->classID) {
            self->flailing      = false;
            self->invertGravity = false;

            if (self->outerbox) {
                self->groundedStore = self->onGround;
                RSDK.ProcessObjectMovement(self, self->outerbox, self->innerbox);
            }
            else {
                self->outerbox      = RSDK.GetHitbox(&self->animator, 0);
                self->innerbox      = RSDK.GetHitbox(&self->animator, 1);
                self->groundedStore = self->onGround;
                RSDK.ProcessObjectMovement(self, self->outerbox, self->innerbox);
                self->outerbox = NULL;
            }

            self->collisionLayers &= ~Zone->moveLayerMask;
            if (self->onGround && !self->collisionMode)
                self->collisionFlagV |= 1;
        }
    }

    if (globals->gameMode != MODE_COMPETITION) {
        if (addendumOptions->coopStyle < COOPSTYLE_APART) {
            for (int32 p = 1; p < addendumVar->playerCount; ++p) {
                EntityPlayer* player = RSDK_GET_ENTITY(p, Player);
                if (leader->superState > SUPERSTATE_NONE) {
                    player->superState = leader->superState;
                    if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                        Player_TryTransform(player, 0x7F, addendumData->collectedSuperEmeralds, 0x00);
                    else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                        Player_TryTransform(player, 0x7F, 0x00, addendumData->collectedTimeStones);
                    else
                        Player_TryTransform(player, 0x7F, 0x00, 0x00);
                }
            }
        }
    }

    Hitbox *playerHitbox = Player_GetHitbox(self);
    EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(self), Shield);
    Hitbox tempHitbox;
    if (shield->classID == Shield->classID && shield->state == Shield_State_Insta) {
        tempHitbox.left   = -24;
        tempHitbox.top    = -24;
        tempHitbox.right  = 24;
        tempHitbox.bottom = 24;
        playerHitbox      = &tempHitbox;
    }

    // extended debug features
    RSDKControllerState *controller = &ControllerInfo[self->controllerID];
    RSDKTriggerState *lBumper       = &TriggerInfoL[self->controllerID];

    if (SceneInfo->debugMode) {
        if (controller->keyZ.press || lBumper->keyBumper.press) {
            if (self->state == Player_State_Ground) {
                switch (self->characterID) {
                    default:
                    case ID_SONIC: Player_ChangeCharacter(self, ID_TAILS); break;
                    case ID_TAILS: Player_ChangeCharacter(self, ID_KNUCKLES); break;
                    case ID_KNUCKLES: Player_ChangeCharacter(self, ID_MIGHTY); break;
                    case ID_MIGHTY: Player_ChangeCharacter(self, ID_RAY); break;
                    case ID_RAY: Player_ChangeCharacter(self, ID_AMY); break;
                    case ID_AMY: Player_ChangeCharacter(self, ID_SONIC); break;
                }
            }

            if (self->state == Player_State_LookUp) {
                if (self->rings < 9999) {
                    Player_GiveRings(self, 50, true);
                }
            }

            if (self->state == Player_State_Crouch) {
                if (addendumOptions->lifeSystem == LIFESYSTEM_MANIA) {
                    if (saveRAM->lives < 999)
                        saveRAM->lives += 1;
                    if (self->lives < 999)
                        self->lives += 1;
                }
                else if (addendumOptions->lifeSystem == LIFESYSTEM_UNCAPPED) {
                    saveRAM->lives += 1;
                    self->lives += 1;
                }
            }

            if (self->state == Player_State_Spindash) {
                if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones == 0b01111111) {
                    saveRAM->collectedEmeralds        = 0b00000000;
                    addendumData->collectedTimeStones = 0b00000000;
                }
                else if (saveRAM->collectedEmeralds == 0b01111111 && addendumData->collectedTimeStones != 0b01111111) {
                    saveRAM->collectedEmeralds        = 0b01111111;
                    addendumData->collectedTimeStones = 0b01111111;
                }
                else if (saveRAM->collectedEmeralds != 0b01111111) {
                    saveRAM->collectedEmeralds        = 0b01111111;
                    addendumData->collectedTimeStones = 0b00000000;
                }
            }

            if (self->state == Player_State_Spindash_CD) {
                if (saveRAM->continues < 99)
                    saveRAM->continues += 1;
            }

            if (self->state == Player_State_Peelout) {
                if (!addendumData->emeraldsTransferred)
                    addendumData->emeraldsTransferred = true;
                else {
                    switch (addendumData->collectedSuperEmeralds) {
                        case 0b00000000: addendumData->collectedSuperEmeralds = 0b00000001; break;
                        case 0b00000001: addendumData->collectedSuperEmeralds = 0b00000011; break;
                        case 0b00000011: addendumData->collectedSuperEmeralds = 0b00000111; break;
                        case 0b00000111: addendumData->collectedSuperEmeralds = 0b00001111; break;
                        case 0b00001111: addendumData->collectedSuperEmeralds = 0b00011111; break;
                        case 0b00011111: addendumData->collectedSuperEmeralds = 0b00111111; break;
                        case 0b00111111: addendumData->collectedSuperEmeralds = 0b01111111; break;
                        case 0b01111111:
                            addendumData->collectedSuperEmeralds = 0b00000000;
                            addendumData->emeraldsTransferred = false;
                            break;
                    }
                }
            }
        }
    }

    if (globals->gameMode != MODE_COMPETITION) {
        RSDKControllerState *leadercontroller = &ControllerInfo[leader->controllerID];
        if (leader->superState == SUPERSTATE_SUPER && leadercontroller->keyY.press && leader->animator.animationID == ANI_JUMP
            && (!RSDK.CheckSceneFolder("ERZ"))) {
            leader->superState = SUPERSTATE_FADEOUT;
            if (sidekick->classID == Player->classID)
                sidekick->superState = SUPERSTATE_FADEOUT;
        }
    }

    if (self->classID == Player->classID) { // give players their small Super sparkles back if they lose them for whatever reason
        if (self->superState == SUPERSTATE_SUPER && superSparkle->classID != SuperSparkle->classID)
            RSDK.ResetEntity(superSparkle, SuperSparkle->classID, self);
    }
}

void Player_LateUpdate(void)
{
    RSDK_THIS(Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (self->state == Player_State_FlyCarried) {
        self->flyCarryLeaderPos.x = self->position.x & 0xFFFF0000;
        self->flyCarryLeaderPos.y = self->position.y & 0xFFFF0000;
    }

    if (self->deathType) {
        self->abilityValues[0] = 0;

#if MANIA_USE_PLUS
        if (!self->sidekick)
            RSDK.CopyEntity(&Zone->entityStorage[1], self, false);
#endif

        bool32 stopInvincibility = self->sidekick || globals->gameMode == MODE_COMPETITION;
#if MANIA_USE_PLUS
        stopInvincibility |= globals->gameMode == MODE_ENCORE;
#endif

        if (stopInvincibility) {
            if (self->invincibleTimer > 1)
                self->invincibleTimer = 1;
            if (self->speedShoesTimer > 1)
                self->speedShoesTimer = 1;
        }
        else {
            self->invincibleTimer = 0;
            self->speedShoesTimer = 0;
        }

        if (self->gravityStrength <= 1)
            self->direction |= FLIP_Y;
        else
            self->direction &= ~FLIP_Y;

        self->visible         = true;
        self->onGround        = false;
        self->groundVel       = 0;
        self->velocity.x      = 0;
        self->nextGroundState = StateMachine_None;
        self->nextAirState    = StateMachine_None;
        self->interaction     = false;
        self->tileCollisions  = TILECOLLISION_NONE;

        if (globals->gameMode != MODE_COMPETITION)
            self->active = ACTIVE_ALWAYS;

        self->shield         = SHIELD_NONE;
        self->collisionFlagH = 0;
        self->collisionFlagV = 0;
        self->underwater     = false;
        Player_UpdatePhysicsState(self);

        destroyEntity(RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(self), Shield));

        switch (self->deathType) {
            default: break;

            case PLAYER_DEATH_DIE_USESFX:
                RSDK.PlaySfx(Player->sfxHurt, false, 255);
                // [Fallthrough]
            case PLAYER_DEATH_DIE_NOSFX:
                self->deathType  = PLAYER_DEATH_NONE;
                self->velocity.y = -0x68000;
                self->state      = Player_State_Death;

                if (!(self->drawFX & FX_SCALE) || self->scale.x == 0x200)
                    self->drawGroup = Zone->playerDrawGroup[1];

                if (self->sidekick || globals->gameMode == MODE_COMPETITION) {
                    if (self->camera) {
                        self->scrollDelay   = 2;
                        self->camera->state = StateMachine_None;
                    }
                }
#if MANIA_USE_PLUS
                else if (globals->gameMode == MODE_ENCORE) {
                    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
                    if (globals->stock == ID_NONE && !sidekick->classID) {
                        RSDK.SetEngineState(ENGINESTATE_FROZEN);
                        SceneInfo->timeEnabled = false;
                    }

                    if (self->camera) {
                        self->scrollDelay   = 2;
                        self->camera->state = StateMachine_None;
                    }
                }
#endif
                else {
                    if (!(globals->gameMode == MODE_MANIA && addendumOptions->coopStyle > COOPSTYLE_MANIA && addendumVar->playerCount > 1)) {
                        RSDK.SetEngineState(ENGINESTATE_FROZEN);
                        SceneInfo->timeEnabled = false;
                    }

                    if (self->camera) {
                        self->scrollDelay   = 2;
                        self->camera->state = StateMachine_None;
                    }
                }
                break;

            case PLAYER_DEATH_DROWN:
                self->deathType = PLAYER_DEATH_NONE;
                // Bug Details:
                // setting this actually causes a slight bug, as when you die the underwater flag is cleared but your gravity strength isn't updated
                // so if you debug out, you'll have regular speed with a moon jump
                // (yes I know this is super minor but its neat to know anyways)
                self->gravityStrength = 0x1000;
                self->velocity.y      = 0;
                RSDK.PlaySfx(Water->sfxDrown, false, 255);
                self->state = Player_State_Drown;

                if (!self->sidekick) {
                    if (globals->gameMode == MODE_COMPETITION) {
                        Music_JingleFadeOut(TRACK_DROWNING, false);
                    }
#if MANIA_USE_PLUS
                    else if (globals->gameMode == MODE_ENCORE) {
                        EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
                        if (globals->stock == ID_NONE && !sidekick->classID) {
                            SceneInfo->timeEnabled = false;
                        }
                    }
#endif
                    else {
                        SceneInfo->timeEnabled = false;
                    }
                }

                if (self->camera) {
                    self->scrollDelay   = 2;
                    self->camera->state = StateMachine_None;
                }
                break;
        }
    }

    if (self->onGround) {
        if (self->nextGroundState) {
            self->state           = self->nextGroundState;
            self->nextGroundState = StateMachine_None;
            if (self->sidekick)
                RSDK_GET_ENTITY(SLOT_PLAYER1, Player)->scoreBonus = 0;
            else
                self->scoreBonus = 0;
        }

        if (self->camera) {
            if (self->animator.animationID == ANI_JUMP)
                self->camera->adjustY = self->jumpOffset;
            else
                self->camera->adjustY = 0;
        }
    }
    else if (self->nextAirState) {
        self->state        = self->nextAirState;
        self->nextAirState = StateMachine_None;
    }

    if (self->tailFrames != (uint16)-1) {
        switch (self->animator.animationID) {
            case ANI_IDLE:
            case ANI_BORED_1:
            case ANI_LOOK_UP:
            case ANI_CROUCH:
                RSDK.SetSpriteAnimation(self->tailFrames, 0, &self->tailAnimator, false, 0);
                self->tailDirection = self->direction;
                self->tailRotation  = self->rotation;
                break;

            case ANI_JUMP:
                RSDK.SetSpriteAnimation(self->tailFrames, 1, &self->tailAnimator, false, 0);
                if (self->onGround) {
                    self->tailRotation  = self->rotation;
                    self->tailDirection = self->groundVel <= 0;
                }
                else {
                    self->tailRotation = RSDK.ATan2(self->velocity.x, self->velocity.y) << 1;
                    if (self->direction == FLIP_X)
                        self->tailRotation = (self->tailRotation - 256) & 0x1FF;
                    self->tailDirection = self->direction;
                }
                break;

            case ANI_SKID:
            case ANI_PUSH:
            case ANI_HANG:
                RSDK.SetSpriteAnimation(self->tailFrames, 3, &self->tailAnimator, false, 0);
                self->tailDirection = self->direction;
                break;

            case ANI_SPINDASH:
                RSDK.SetSpriteAnimation(self->tailFrames, 2, &self->tailAnimator, false, 0);
                self->tailDirection = self->direction;
                break;

            case ANI_CDSPINDASH:
                RSDK.SetSpriteAnimation(self->tailFrames, 1, &self->tailAnimator, false, 0);
                if (self->direction == FLIP_X)
                    self->tailDirection = FLIP_X;
                else
                    self->tailDirection = -self->direction;
                break;

            case ANI_HANG_MOVE:
                RSDK.SetSpriteAnimation(self->tailFrames, 4, &self->tailAnimator, false, 0);
                self->tailDirection = self->direction;
                break;

            case ANI_PULLEY_HOLD:
                RSDK.SetSpriteAnimation(self->tailFrames, 5, &self->tailAnimator, false, 0);
                self->tailDirection = self->direction;
                if (self->tailDirection)
                    self->tailRotation = self->rotation + 32;
                else
                    self->tailRotation = self->rotation - 32;
                break;

            default: RSDK.SetSpriteAnimation(-1, 0, &self->tailAnimator, false, 0); break;
        }

        RSDK.ProcessAnimation(&self->tailAnimator);
    }

    RSDK.ProcessAnimation(&self->animator);
}

void Player_StaticUpdate(void)
{
    RSDK_THIS(Player);
#if MANIA_USE_PLUS
    // Moved here from ERZ start since flying can now be done in any stage, not just ERZ
    if (Player->superDashCooldown > 0) {
        RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        HUD_EnableRingFlash();
        --Player->superDashCooldown;
    }
#endif

    bool32 flying = false;
    bool32 tired  = false;
    if (SceneInfo->state == ENGINESTATE_REGULAR) {
        foreach_active(Player, player)
        {
            if (player->characterID == ID_TAILS) {
                int32 anim = player->animator.animationID;
                if (anim == ANI_FLY || anim == ANI_FLY_LIFT)
                    flying = true;
                if (anim == ANI_FLY_TIRED || anim == ANI_FLY_LIFT_TIRED)
                    tired = true;
            }
        }

        if (flying) {
            if (!Player->playingFlySfx) {
                RSDK.PlaySfx(Player->sfxFlying, true, 255);
                Player->playingFlySfx = true;
            }
        }

        if (tired) {
            if (!Player->playingTiredSfx) {
                RSDK.PlaySfx(Player->sfxTired, true, 255);
                Player->playingTiredSfx = true;
            }
        }
    }

    if (!flying && Player->playingFlySfx) {
        RSDK.StopSfx(Player->sfxFlying);
        Player->playingFlySfx = false;
    }

    if (!tired && Player->playingTiredSfx) {
        RSDK.StopSfx(Player->sfxTired);
        Player->playingTiredSfx = false;
    }

#if MANIA_USE_PLUS
    Player->raySwoopTimer -= 8;
    if (Player->raySwoopTimer < 0)
        Player->raySwoopTimer = 0;

    Player->rayDiveTimer -= 16;
    if (Player->rayDiveTimer < 0)
        Player->rayDiveTimer = 0;
#endif

    SaveRAM *saveRAM                 = SaveGame_GetSaveRAM();
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (addendumOptions->lifeSystem == LIFESYSTEM_MANIA) {
        if (self->lives > 99 || saveRAM->lives > 99) {
            self->lives    = 99;
            saveRAM->lives = 99;
        }
    }
}

void Player_Draw(void)
{
    RSDK_THIS(Player);

#if MANIA_USE_PLUS
    if (self->isGhost) {
        self->inkEffect = INK_BLEND;
        self->alpha     = 0x7F; // redundant since the ink effect is INK_BLEND, which is basically 50% alpha anyways
    }
#endif

    Entity *parent   = self->abilityPtrs[0];
    Vector2 posStore = self->position;
    if (self->state == Player_State_FlyToPlayer && parent) {
        self->position.x = parent->position.x;
        self->position.y = parent->position.y;
    }

    if (self->tailFrames != (uint16)-1) {
        int32 rotStore  = self->rotation;
        int32 dirStore  = self->direction;
        self->rotation  = self->tailRotation;
        self->direction = self->tailDirection;
        RSDK.DrawSprite(&self->tailAnimator, NULL, false);

        self->rotation  = rotStore;
        self->direction = dirStore;
    }

    // Copy the colours for any other players so stuff like super forms or etc don't effect the other players aside from P1
    // Used for sidekicks, competition players with the same player or etc
    /* Addendum shouldn't even use this anymore, seeing as P2 Super in Mania Mode and Super Run in Competition are now base-game features.
    if (self->playerID == 1 && GET_CHARACTER_ID(1) == GET_CHARACTER_ID(2) && globals->gameMode == MODE_COMPETITION) {
        uint32 colorStore[PLAYER_PRIMARY_COLOR_COUNT + 1];

        switch (self->characterID) {
            case ID_SONIC:
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    colorStore[c] = RSDK.GetPaletteEntry(0, PLAYER_PALETTE_INDEX_SONIC + c);
                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[c]);
                }

                RSDK.DrawSprite(&self->animator, NULL, false);

                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_SONIC + c, colorStore[c]);
                break;

            case ID_TAILS:
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    colorStore[c] = RSDK.GetPaletteEntry(0, PLAYER_PALETTE_INDEX_TAILS + c);
                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[c]);
                }

                RSDK.DrawSprite(&self->animator, NULL, false);

                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_TAILS + c, colorStore[c]);
                break;

            case ID_KNUCKLES:
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    colorStore[c] = RSDK.GetPaletteEntry(0, PLAYER_PALETTE_INDEX_KNUX + c);
                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[c]);
                }

                RSDK.DrawSprite(&self->animator, NULL, false);

                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_KNUX + c, colorStore[c]);
                break;

#if MANIA_USE_PLUS
            case ID_MIGHTY:
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    colorStore[c] = RSDK.GetPaletteEntry(0, PLAYER_PALETTE_INDEX_MIGHTY + c);
                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[c]);
                }

                RSDK.DrawSprite(&self->animator, NULL, false);

                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_MIGHTY + c, colorStore[c]);
                break;

            case ID_RAY:
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                    colorStore[c] = RSDK.GetPaletteEntry(0, PLAYER_PALETTE_INDEX_RAY + c);
                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[c]);
                }

                RSDK.DrawSprite(&self->animator, NULL, false);

                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_RAY + c, colorStore[c]);
                break;

            case ID_AMY:
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    colorStore[c] = RSDK.GetPaletteEntry(0, PLAYER_PALETTE_INDEX_AMY + c);
                    RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[c]);
                }

                RSDK.DrawSprite(&self->animator, NULL, false);

                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_AMY + c, colorStore[c]);
                break;
#endif
        }
    }
    else { */
        // Draw the Player, with some fancy stuff
        Player_State_DrawMiracle();
    // }

    if (self->state == Player_State_FlyToPlayer && parent) {
        self->position.x = posStore.x;
        self->position.y = posStore.y;
    }
}

void Player_Create(void *data)
{
    RSDK_THIS(Player);

    if (SceneInfo->inEditor) {
        RSDK.SetSpriteAnimation(Player->sonicFrames, ANI_IDLE, &self->animator, true, 0);
        self->characterID = ID_SONIC;
    }
    else {
        EntityPlayer *leader             = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        EntityPlayer *sidekick           = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
        AddendumData *addendumData       = Addendum_GetSaveRAM();
        AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
        self->playerID = RSDK.GetEntitySlot(self);

        // Handle character specific stuff
        switch (self->characterID) {
            default:
            case ID_SONIC:
                self->aniFrames     = Player->sonicFrames;
                self->tailFrames    = -1;
                self->jumpOffset    = TO_FIXED(5);
                self->stateAbility  = Player_JumpAbility_Sonic;
                self->stateTallJump = StateMachine_None;
                self->sensorY       = TO_FIXED(20);

                if (addendumOptions->peeloutAbility != PEELOUTABILITY_NONE) {
                    self->statePeelout = Player_Action_Peelout;

                    if (addendumOptions->sonicMoveset == SONICMOVESET_ADDENDUM || SONICMOVESET_CD) {
                        for (int32 f = 0; f < 4; ++f) {
                            SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_DASH, f + 1);
                            SpriteFrame *src = RSDK.GetFrame(self->aniFrames, ANI_PEELOUT, f);

                            *dst = *src;
                        }
                    }
                }
                else
                    self->statePeelout = StateMachine_None;

                if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                    for (int32 s = 0; s < 16; ++s) {
                        SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_SPINDASH, s);
                        SpriteFrame *src = RSDK.GetFrame(self->aniFrames, 55, s);

                        *dst = *src;
                    }
                }
                break;

            case ID_TAILS:
                self->aniFrames     = Player->tailsFrames;
                self->tailFrames    = Player->tailsTailsFrames;
                self->jumpOffset    = TO_FIXED(0);
                self->stateAbility  = Player_JumpAbility_Tails;
                if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY || addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
                    self->statePeelout = Player_Action_Peelout;
                else
                    self->statePeelout = StateMachine_None;
                self->stateTallJump = StateMachine_None;
                self->sensorY       = TO_FIXED(16);
                break;

            case ID_KNUCKLES:
                self->aniFrames     = Player->knuxFrames;
                self->tailFrames    = -1;
                self->jumpOffset    = TO_FIXED(5);
                self->stateAbility  = Player_JumpAbility_Knux;
                if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY || addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
                    self->statePeelout = Player_Action_Peelout;
                else
                    self->statePeelout = StateMachine_None;
                self->stateTallJump = StateMachine_None;
                self->sensorY       = TO_FIXED(20);
                
                if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                    for (int32 s = 0; s < 16; ++s) {
                        SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_SPINDASH, s);
                        SpriteFrame *src = RSDK.GetFrame(self->aniFrames, 55, s);

                        *dst = *src;
                    }
                }
                break;

#if MANIA_USE_PLUS
            case ID_MIGHTY:
                self->aniFrames     = Player->mightyFrames;
                self->tailFrames    = -1;
                self->jumpOffset    = TO_FIXED(5);
                self->stateAbility  = Player_JumpAbility_Mighty;
                if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY || addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
                    self->statePeelout = Player_Action_Peelout;
                else
                    self->statePeelout = StateMachine_None;
                self->stateTallJump = StateMachine_None;
                self->sensorY       = TO_FIXED(20);

                if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                    for (int32 s = 0; s < 16; ++s) {
                        SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_SPINDASH, s);
                        SpriteFrame *src = RSDK.GetFrame(self->aniFrames, 55, s);

                        *dst = *src;
                    }
                }
                break;

            case ID_RAY:
                self->aniFrames     = Player->rayFrames;
                self->tailFrames    = -1;
                self->jumpOffset    = TO_FIXED(5);
                self->stateAbility  = Player_JumpAbility_Ray;
                if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY || addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
                    self->statePeelout = Player_Action_Peelout;
                else
                    self->statePeelout = StateMachine_None;
                self->stateTallJump = StateMachine_None;
                self->sensorY       = TO_FIXED(20);

                if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                    for (int32 s = 0; s < 16; ++s) {
                        SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_SPINDASH, s);
                        SpriteFrame *src = RSDK.GetFrame(self->aniFrames, 55, s);

                        *dst = *src;
                    }
                }
                break;

            case ID_AMY:
                self->aniFrames     = Player->amyFrames;
                self->tailFrames    = -1;
                self->jumpOffset    = TO_FIXED(5);
                self->stateAbility  = Player_JumpAbility_Amy;
                if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALL) {
                    self->statePeelout = Player_Action_Peelout;
                    self->stateTallJump = StateMachine_None;
                }
                else {
                    self->statePeelout = StateMachine_None;
                    self->stateTallJump = Player_Action_TallJump;
                }
                self->sensorY       = TO_FIXED(20);

                if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                    for (int32 s = 0; s < 16; ++s) {
                        SpriteFrame *dst = RSDK.GetFrame(self->aniFrames, ANI_SPINDASH, s);
                        SpriteFrame *src = RSDK.GetFrame(self->aniFrames, 55, s);

                        *dst = *src;
                    }
                }
                break;
#endif
        }

        // Handle Sensor setup
        self->sensorX[0] = TO_FIXED(10);
        self->sensorX[1] = TO_FIXED(5);
        self->sensorX[2] = TO_FIXED(0);
        self->sensorX[3] = -TO_FIXED(5);
        self->sensorX[4] = -TO_FIXED(10);

        self->active         = ACTIVE_NORMAL;
        self->tileCollisions = TILECOLLISION_DOWN;
        self->visible        = true;
        self->drawGroup      = Zone->playerDrawGroup[0];
        self->scale.x        = 0x200;
        self->scale.y        = 0x200;
        self->controllerID   = self->playerID + 1;
        self->state          = Player_State_Ground;

        // Handle Input Setup
        if (!SceneInfo->entitySlot || globals->gameMode == MODE_COMPETITION) {
            self->stateInput = Player_Input_P1;
        }
#if MANIA_USE_PLUS
        else if (SceneInfo->entitySlot == 1 && globals->gameMode == MODE_TIMEATTACK) {
            StateMachine_Run(Player->configureGhostCB);
        }
#endif
        else {
            API_AssignInputSlotToDevice(self->controllerID, INPUT_AUTOASSIGN);
            self->stateInput = Player_Input_P2_AI;
            self->sidekick   = true;
        }

        AnalogStickInfoL[self->controllerID].deadzone = 0.3f;

        // Handle Powerups
        self->ringExtraLife       = Player->ringExtraLife;
        Player->ringExtraLife     = 100;

        if (SceneInfo->activeCategory != 9) {
            if (!Player->restartRingsApplied) {
                for (int32 p = 0; p < addendumVar->playerCount; ++p) {
                    EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
                    if (player->classID == Player->classID) {
                        int32 rings                  = globals->storedRings[p];
                        bool32 hyperRing             = globals->storedHyperRings[p];
                        player->rings                = rings;
                        globals->storedRings[p]      = 0;
                        player->hyperRing            = hyperRing;
                        globals->storedHyperRings[p] = 0;
                    }
                }
                Player->restartRingsApplied = true;
            }
        }

        if (globals->startSuper) {
            if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD && addendumData->collectedSuperEmeralds == 0b01111111)
                self->hyperState = true;
            else
                self->hyperState = false;
            if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE && addendumData->collectedTimeStones == 0b01111111)
                self->miracleState = true;
            else
                self->miracleState = false;
            self->state = Player_State_StartSuper;
        }

        if (addendumOptions->shieldTransfer && SceneInfo->activeCategory != 9) {  
            if (!Player->restartShieldApplied) {
                for (int32 p = 0; p < addendumVar->playerCount; ++p) {
                    EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
                    if (player->classID == Player->classID) {
                        player->shield   = globals->storedShields[p];
                        Player_ApplyShield(player);
                        globals->storedShields[p] = 0;
                    }
                }
                Player->restartShieldApplied = true;
            }
        }

        if (globals->gameMode == MODE_COMPETITION) {
            if (addendumOpt->competitonMods & COMP_SUPERRUN) {
                self->rings = 55;
                Player_TryTransform(self, 0xFF, 0x00, 0x00);
            }
            else if (addendumOpt->competitonMods & COMP_HYPERRUN) {
                self->rings = 55;
                Player_TryTransform(self, 0xFF, 0xFF, 0x00);
            }
            else if (addendumOpt->competitonMods & COMP_MIRACLERUN) {
                self->rings = 55;
                Player_TryTransform(self, 0xFF, 0x00, 0xFF);
            }
        }

        // Handle Lives/Score setup
        EntityCompetitionSession *session = CompetitionSession_GetSession();
        if (globals->gameMode == MODE_COMPETITION) {
            self->lives    = session->lives[self->playerID];
            self->score    = 0;
            self->score1UP = 50000;
        }
        else if (globals->gameMode == MODE_TIMEATTACK) {
            self->lives    = 1;
            self->score    = 0;
            self->score1UP = 50000;
        }
        else {
            self->lives    = Player->savedLives;
            self->score    = Player->savedScore;
            self->score1UP = Player->savedScore1UP;
        }

        // Setup the target score
        while (self->score1UP <= self->score) self->score1UP += 50000;

        self->collisionLayers = Zone->collisionLayers;
        self->drawFX          = FX_ROTATE | FX_FLIP;
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_IDLE, &self->animator, true, 0);

        Player_UpdatePhysicsState(self);
        self->minJogVelocity  = 0x40000;
        self->minRunVelocity  = 0x60000;
        self->minDashVelocity = 0xC0000;
    }
}

void Player_StageLoad(void)
{
    RSDK_THIS(Player);
    SaveRAM* saveRAM = SaveGame_GetSaveRAM();
    AddendumData* addendumData = Addendum_GetSaveRAM();
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();

    if (!globals->playerID)
        globals->playerID = RSDK.CheckSceneFolder("MSZCutscene") ? ID_KNUCKLES : ID_DEFAULT_PLAYER;

    SceneInfo->debugMode = addendumOptions->debugMode;
#if MANIA_USE_PLUS
    RSDK.AddViewableVariable("Debug Mode", &SceneInfo->debugMode, VIEWVAR_BOOL, false, true);
#endif

    if (globals->gameMode == MODE_MANIA) {
        globals->playerID = ID_NONE;
        globals->playerID |= 1 << (saveRAM->characterID);
        globals->playerID |= addendumData->player2ID < 6 ? ((1 << (addendumData->player2ID)) << 8) : ID_NONE << 8;
        globals->playerID |= addendumData->player3ID < 6 ? ((1 << (addendumData->player3ID)) << 16) : ID_NONE << 16;
        globals->playerID |= addendumData->player4ID < 6 ? ((1 << (addendumData->player4ID)) << 24) : ID_NONE << 24;
    }

    Player->playerCount = 0;
    Player->active      = ACTIVE_ALWAYS;

    // Sprite loading & characterID management
    if (globals->gameMode == MODE_COMPETITION)
        Player_LoadSpritesVS();
    else if (addendumOptions->coopStyle > COOPSTYLE_MANIA && addendumVar->playerCount > 1 && globals->gameMode == MODE_MANIA) {
        RSDK.SetVideoSetting(VIDEOSETTING_SCREENCOUNT, addendumVar->playerCount);
        Player_LoadSpritesCoop();
    }
    else
        Player_LoadSprites();

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_ENCORE) {
        Player->playerCount    = 2;
        EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
        sidekick->playerID     = 1;
    }
    else {
        Player->playerCount = RSDK.GetEntityCount(Player->classID, false);
    }
#else
    Player->playerCount = RSDK.GetEntityCount(Player->classID, false);
#endif

    for (int32 p = 0; p < 4; ++p) {
        // Handle Sidekick stuff setup
        Player->nextLeaderPosID[p] = 1;
        Player->lastLeaderPosID[p] = 0;
        Player->upState[p]         = false;
        Player->downState[p]       = false;
        Player->leftState[p]       = false;
        Player->rightState[p]      = false;
        Player->jumpHoldState[p]   = false;
        Player->jumpPressState[p]  = false;
    }

#if GAME_VERSION != VER_100
    Player->disableP2KeyCheck = false;
#endif

    // Sfx Loading
    Player->sfxJump        = RSDK.GetSfx("Global/Jump.wav");
    Player->sfxLoseRings   = RSDK.GetSfx("Global/LoseRings.wav");
    Player->sfxHurt        = RSDK.GetSfx("Global/Hurt.wav");
    Player->sfxRoll        = RSDK.GetSfx("Global/Roll.wav");
    Player->sfxCharge      = RSDK.GetSfx("Global/Charge.wav");
    Player->sfxRelease     = RSDK.GetSfx("Global/Release.wav");
    Player->sfxPeelCharge  = RSDK.GetSfx("Global/PeelCharge.wav");
    Player->sfxPeelRelease = RSDK.GetSfx("Global/PeelRelease.wav");
    Player->sfxDropdash    = RSDK.GetSfx("Global/DropDash.wav");
    Player->sfxSkidding    = RSDK.GetSfx("Global/Skidding.wav");
    Player->sfxGrab        = RSDK.GetSfx("Global/Grab.wav");
    Player->sfxFlying      = RSDK.GetSfx("Global/Flying.wav");
    Player->sfxTired       = RSDK.GetSfx("Global/Tired.wav");
    Player->sfxLand        = RSDK.GetSfx("Global/Land.wav");
    Player->sfxSlide       = RSDK.GetSfx("Global/Slide.wav");
    Player->sfxOuttahere   = RSDK.GetSfx("Global/OuttaHere.wav");
    Player->sfxTransform   = RSDK.GetSfx("Stage/Transform.wav");
    Player->sfxTransform2  = RSDK.GetSfx("Stage/Transform2.wav");
#if MANIA_USE_PLUS
    Player->sfxPimPom        = RSDK.GetSfx("Stage/PimPom.wav");
    Player->sfxSwap          = RSDK.GetSfx("Global/Swap.wav");
    Player->sfxSwapFail      = RSDK.GetSfx("Global/SwapFail.wav");
    Player->sfxMightyDeflect = RSDK.GetSfx("Global/MightyDeflect.wav");
    Player->sfxMightyDrill   = RSDK.GetSfx("Global/MightyDrill.wav");
    Player->sfxMightyLand    = RSDK.GetSfx("Global/MightyLand.wav");
    Player->sfxMightyUnspin  = RSDK.GetSfx("Global/MightyUnspin.wav");
    Player->sfxAmyHammer     = RSDK.GetSfx("Amy/AmyHammerHit.wav");
    Player->sfxAmyHammerFly  = RSDK.GetSfx("Amy/AmyHammerFly.wav");
    Player->sfx1up           = RSDK.GetSfx("Global/1up.wav");
    Player->sfxTwinkle       = RSDK.GetSfx("Global/Twinkle.wav");
    Player->sfxSparkleAnticipation = RSDK.GetSfx("Global/SparkleAnticipation.wav");
    Player->sfxWallRumble    = RSDK.GetSfx("Global/WallRumble.wav");

    Soundboard_LoadSfx("Global/RaySwoop.wav", 41417, Player_SfxCheck_RaySwoop, Player_SfxUpdate_RaySwoop);
    Soundboard_LoadSfx("Global/RayDive.wav", 72323, Player_SfxCheck_RayDive, Player_SfxUpdate_RayDive);
#endif

    // Handle gotHit values (used for TMZ1 achievement)
    for (int32 p = 0; p < PLAYER_COUNT; ++p) Player->gotHit[p] = false;
}

// Extra Entity Functions
void Player_LoadSprites(void)
{
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    foreach_all(Player, spawn)
    {
        int32 playerID = GET_CHARACTER_ID(1);
#if MANIA_USE_PLUS
        if (playerID == ID_MIGHTY || playerID == ID_RAY || playerID == ID_AMY)
            playerID = ID_SONIC;
#endif
        if (spawn->characterID & playerID) {
            spawn->characterID = GET_CHARACTER_ID(1);
            switch (spawn->characterID) {
                default:
                case ID_SONIC:
                    if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                        Player->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/Sonic.bin", SCOPE_STAGE);
                        Player->superFrames   = RSDK.LoadSpriteAnimation("CE+/SuperSonic.bin", SCOPE_STAGE);
                        Player->miracleFrames = RSDK.LoadSpriteAnimation("CE+/MiracleSonic.bin", SCOPE_STAGE);
                    }
                    else {
                        Player->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
                        Player->superFrames   = RSDK.LoadSpriteAnimation("Players/SuperSonic.bin", SCOPE_STAGE);
                        Player->miracleFrames = RSDK.LoadSpriteAnimation("Players/MiracleSonic.bin", SCOPE_STAGE);
                    }
                    break;

                case ID_TAILS:
                    if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                        Player->tailsFrames             = RSDK.LoadSpriteAnimation("CE+/Tails.bin", SCOPE_STAGE);
                        Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("CE+/TailSprite.bin", SCOPE_STAGE);
                        Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("CE+/MiracleTails.bin", SCOPE_STAGE);
                        Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("CE+/MiracleTailSprite.bin", SCOPE_STAGE);
                    }
                    else {
                        Player->tailsFrames             = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
                        Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("Players/TailSprite.bin", SCOPE_STAGE);
                        Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("Players/MiracleTails.bin", SCOPE_STAGE);
                        Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("Players/MiracleTailSprite.bin", SCOPE_STAGE);
                    }
                    break;

                case ID_KNUCKLES:
                    if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                        Player->knuxFrames        = RSDK.LoadSpriteAnimation("CE+/Knux.bin", SCOPE_STAGE);
                        Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("CE+/MiracleKnux.bin", SCOPE_STAGE);
                    }
                    else {
                        Player->knuxFrames        = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
                        Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("Players/MiracleKnux.bin", SCOPE_STAGE);
                    }
                    break;
#if MANIA_USE_PLUS
                case ID_MIGHTY:
                    if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                        Player->mightyFrames        = RSDK.LoadSpriteAnimation("CE+/Mighty.bin", SCOPE_STAGE);
                        Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("CE+/MiracleMighty.bin", SCOPE_STAGE);
                    }
                    else {
                        Player->mightyFrames        = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
                        Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("Players/MiracleMighty.bin", SCOPE_STAGE);
                    }
                    break;

                case ID_RAY:
                    if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                        Player->rayFrames        = RSDK.LoadSpriteAnimation("CE+/Ray.bin", SCOPE_STAGE);
                        Player->miracleRayFrames = RSDK.LoadSpriteAnimation("CE+/MiracleRay.bin", SCOPE_STAGE);
                    }
                    else {
                        Player->rayFrames        = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
                        Player->miracleRayFrames = RSDK.LoadSpriteAnimation("Players/MiracleRay.bin", SCOPE_STAGE);
                    }
                    break;

                case ID_AMY:
                    Player->amyFrames        = RSDK.LoadSpriteAnimation("Players/Amy.bin", SCOPE_STAGE);
                    Player->miracleAmyFrames = RSDK.LoadSpriteAnimation("Players/MiracleAmy.bin", SCOPE_STAGE);
                    break;
#endif
            }

            EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
            RSDK.CopyEntity(player1, spawn, true);
            player1->camera = Camera_SetTargetEntity(0, player1);
            RSDK.AddCamera(&player1->position, ScreenInfo->center.x << 16, ScreenInfo->center.y << 16, true);
        }
        else {
            destroyEntity(spawn);
        }
    }

    if (GET_CHARACTER_ID(2) > 0) {
        EntityPlayer *leader   = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

        for (int32 i = 0; i < 0x10; ++i) Player->leaderPositionBuffer[1][i] = leader->position;

        sidekick->classID    = Player->classID;
        sidekick->position.x = leader->position.x;
        sidekick->position.y = leader->position.y;
        sidekick->position.x -= 0x100000;

        sidekick->characterID = GET_CHARACTER_ID(2);
        switch (sidekick->characterID) {
            default:
            case ID_SONIC:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/Sonic.bin", SCOPE_STAGE);
                    Player->superFrames   = RSDK.LoadSpriteAnimation("CE+/SuperSonic.bin", SCOPE_STAGE);
                    Player->miracleFrames = RSDK.LoadSpriteAnimation("CE+/MiracleSonic.bin", SCOPE_STAGE);
                }
                else {
                    Player->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
                    Player->superFrames   = RSDK.LoadSpriteAnimation("Players/SuperSonic.bin", SCOPE_STAGE);
                    Player->miracleFrames = RSDK.LoadSpriteAnimation("Players/MiracleSonic.bin", SCOPE_STAGE);
                }
                break;

            case ID_TAILS:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->tailsFrames             = RSDK.LoadSpriteAnimation("CE+/Tails.bin", SCOPE_STAGE);
                    Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("CE+/TailSprite.bin", SCOPE_STAGE);
                    Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("CE+/MiracleTails.bin", SCOPE_STAGE);
                    Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("CE+/MiracleTailSprite.bin", SCOPE_STAGE);
                }
                else {
                    Player->tailsFrames             = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
                    Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("Players/TailSprite.bin", SCOPE_STAGE);
                    Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("Players/MiracleTails.bin", SCOPE_STAGE);
                    Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("Players/MiracleTailSprite.bin", SCOPE_STAGE);
                }
                break;

            case ID_KNUCKLES:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->knuxFrames        = RSDK.LoadSpriteAnimation("CE+/Knux.bin", SCOPE_STAGE);
                    Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("CE+/MiracleKnux.bin", SCOPE_STAGE);
                }
                else {
                    Player->knuxFrames        = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
                    Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("Players/MiracleKnux.bin", SCOPE_STAGE);
                }
                break;
#if MANIA_USE_PLUS
            case ID_MIGHTY:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->mightyFrames        = RSDK.LoadSpriteAnimation("CE+/Mighty.bin", SCOPE_STAGE);
                    Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("CE+/MiracleMighty.bin", SCOPE_STAGE);
                }
                else {
                    Player->mightyFrames        = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
                    Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("Players/MiracleMighty.bin", SCOPE_STAGE);
                }
                break;

            case ID_RAY:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->rayFrames        = RSDK.LoadSpriteAnimation("CE+/Ray.bin", SCOPE_STAGE);
                    Player->miracleRayFrames = RSDK.LoadSpriteAnimation("CE+/MiracleRay.bin", SCOPE_STAGE);
                }
                else {
                    Player->rayFrames        = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
                    Player->miracleRayFrames = RSDK.LoadSpriteAnimation("Players/MiracleRay.bin", SCOPE_STAGE);
                }
                break;

            case ID_AMY:
                Player->amyFrames        = RSDK.LoadSpriteAnimation("Players/Amy.bin", SCOPE_STAGE);
                Player->miracleAmyFrames = RSDK.LoadSpriteAnimation("Players/MiracleAmy.bin", SCOPE_STAGE);
                break;
#endif
        }
    }

    if (GET_CHARACTER_ID(3) > 0) {
        EntityPlayer *leader   = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER3, Player);

        for (int32 i = 0; i < 0x10; ++i) Player->leaderPositionBuffer[2][i] = leader->position;

        sidekick->classID    = Player->classID;
        sidekick->position.x = leader->position.x;
        sidekick->position.y = leader->position.y;
        sidekick->position.x -= 0x200000;

        sidekick->characterID = GET_CHARACTER_ID(3);
        switch (sidekick->characterID) {
            default:
            case ID_SONIC:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/Sonic.bin", SCOPE_STAGE);
                    Player->superFrames   = RSDK.LoadSpriteAnimation("CE+/SuperSonic.bin", SCOPE_STAGE);
                    Player->miracleFrames = RSDK.LoadSpriteAnimation("CE+/MiracleSonic.bin", SCOPE_STAGE);
                }
                else {
                    Player->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
                    Player->superFrames   = RSDK.LoadSpriteAnimation("Players/SuperSonic.bin", SCOPE_STAGE);
                    Player->miracleFrames = RSDK.LoadSpriteAnimation("Players/MiracleSonic.bin", SCOPE_STAGE);
                }
                break;

            case ID_TAILS:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->tailsFrames             = RSDK.LoadSpriteAnimation("CE+/Tails.bin", SCOPE_STAGE);
                    Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("CE+/TailSprite.bin", SCOPE_STAGE);
                    Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("CE+/MiracleTails.bin", SCOPE_STAGE);
                    Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("CE+/MiracleTailSprite.bin", SCOPE_STAGE);
                }
                else {
                    Player->tailsFrames             = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
                    Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("Players/TailSprite.bin", SCOPE_STAGE);
                    Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("Players/MiracleTails.bin", SCOPE_STAGE);
                    Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("Players/MiracleTailSprite.bin", SCOPE_STAGE);
                }
                break;

            case ID_KNUCKLES:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->knuxFrames        = RSDK.LoadSpriteAnimation("CE+/Knux.bin", SCOPE_STAGE);
                    Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("CE+/MiracleKnux.bin", SCOPE_STAGE);
                }
                else {
                    Player->knuxFrames        = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
                    Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("Players/MiracleKnux.bin", SCOPE_STAGE);
                }
                break;
#if MANIA_USE_PLUS
            case ID_MIGHTY:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->mightyFrames        = RSDK.LoadSpriteAnimation("CE+/Mighty.bin", SCOPE_STAGE);
                    Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("CE+/MiracleMighty.bin", SCOPE_STAGE);
                }
                else {
                    Player->mightyFrames        = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
                    Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("Players/MiracleMighty.bin", SCOPE_STAGE);
                }
                break;

            case ID_RAY:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->rayFrames        = RSDK.LoadSpriteAnimation("CE+/Ray.bin", SCOPE_STAGE);
                    Player->miracleRayFrames = RSDK.LoadSpriteAnimation("CE+/MiracleRay.bin", SCOPE_STAGE);
                }
                else {
                    Player->rayFrames        = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
                    Player->miracleRayFrames = RSDK.LoadSpriteAnimation("Players/MiracleRay.bin", SCOPE_STAGE);
                }
                break;

            case ID_AMY:
                Player->amyFrames        = RSDK.LoadSpriteAnimation("Players/Amy.bin", SCOPE_STAGE);
                Player->miracleAmyFrames = RSDK.LoadSpriteAnimation("Players/MiracleAmy.bin", SCOPE_STAGE);
                break;
#endif
        }
    }

    if (GET_CHARACTER_ID(4) > 0) {
        EntityPlayer *leader   = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER4, Player);

        for (int32 i = 0; i < 0x10; ++i) Player->leaderPositionBuffer[3][i] = leader->position;

        sidekick->classID    = Player->classID;
        sidekick->position.x = leader->position.x;
        sidekick->position.y = leader->position.y;
        sidekick->position.x -= 0x300000;

        sidekick->characterID = GET_CHARACTER_ID(4);
        switch (sidekick->characterID) {
            default:
            case ID_SONIC:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/Sonic.bin", SCOPE_STAGE);
                    Player->superFrames   = RSDK.LoadSpriteAnimation("CE+/SuperSonic.bin", SCOPE_STAGE);
                    Player->miracleFrames = RSDK.LoadSpriteAnimation("CE+/MiracleSonic.bin", SCOPE_STAGE);
                }
                else {
                    Player->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
                    Player->superFrames   = RSDK.LoadSpriteAnimation("Players/SuperSonic.bin", SCOPE_STAGE);
                    Player->miracleFrames = RSDK.LoadSpriteAnimation("Players/MiracleSonic.bin", SCOPE_STAGE);
                }
                break;

            case ID_TAILS:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->tailsFrames             = RSDK.LoadSpriteAnimation("CE+/Tails.bin", SCOPE_STAGE);
                    Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("CE+/TailSprite.bin", SCOPE_STAGE);
                    Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("CE+/MiracleTails.bin", SCOPE_STAGE);
                    Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("CE+/MiracleTailSprite.bin", SCOPE_STAGE);
                }
                else {
                    Player->tailsFrames             = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
                    Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("Players/TailSprite.bin", SCOPE_STAGE);
                    Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("Players/MiracleTails.bin", SCOPE_STAGE);
                    Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("Players/MiracleTailSprite.bin", SCOPE_STAGE);
                }
                break;

            case ID_KNUCKLES:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->knuxFrames        = RSDK.LoadSpriteAnimation("CE+/Knux.bin", SCOPE_STAGE);
                    Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("CE+/MiracleKnux.bin", SCOPE_STAGE);
                }
                else {
                    Player->knuxFrames        = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
                    Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("Players/MiracleKnux.bin", SCOPE_STAGE);
                }
                break;
#if MANIA_USE_PLUS
            case ID_MIGHTY:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->mightyFrames        = RSDK.LoadSpriteAnimation("CE+/Mighty.bin", SCOPE_STAGE);
                    Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("CE+/MiracleMighty.bin", SCOPE_STAGE);
                }
                else {
                    Player->mightyFrames        = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
                    Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("Players/MiracleMighty.bin", SCOPE_STAGE);
                }
                break;

            case ID_RAY:
                if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                    Player->rayFrames        = RSDK.LoadSpriteAnimation("CE+/Ray.bin", SCOPE_STAGE);
                    Player->miracleRayFrames = RSDK.LoadSpriteAnimation("CE+/MiracleRay.bin", SCOPE_STAGE);
                }
                else {
                    Player->rayFrames        = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
                    Player->miracleRayFrames = RSDK.LoadSpriteAnimation("Players/MiracleRay.bin", SCOPE_STAGE);
                }
                break;

            case ID_AMY:
                Player->amyFrames        = RSDK.LoadSpriteAnimation("Players/Amy.bin", SCOPE_STAGE);
                Player->miracleAmyFrames = RSDK.LoadSpriteAnimation("Players/MiracleAmy.bin", SCOPE_STAGE);
                break;
#endif
        }
    }
}
void Player_LoadSpritesVS(void)
{
    EntityCompetitionSession *session = CompetitionSession_GetSession();
    AddendumOptions *addendumOptions  = Addendum_GetOptionsRAM();

    foreach_all(Player, spawn)
    {
        if (spawn->characterID & ID_SONIC) {
            int32 slotID = 0;
            for (int32 i = 0; i < session->playerCount; ++i, ++slotID) {
                EntityPlayer *player = RSDK_GET_ENTITY(slotID, Player);
                RSDK.CopyEntity(player, spawn, false);
                player->characterID = GET_CHARACTER_ID(1 + i);
                switch (player->characterID) {
                    default:
                    case ID_SONIC:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/Sonic.bin", SCOPE_STAGE);
                            Player->superFrames   = RSDK.LoadSpriteAnimation("CE+/SuperSonic.bin", SCOPE_STAGE);
                            Player->miracleFrames = RSDK.LoadSpriteAnimation("CE+/MiracleSonic.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
                            Player->superFrames   = RSDK.LoadSpriteAnimation("Players/SuperSonic.bin", SCOPE_STAGE);
                            Player->miracleFrames = RSDK.LoadSpriteAnimation("Players/MiracleSonic.bin", SCOPE_STAGE);
                        }
                        break;

                    case ID_TAILS:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->tailsFrames             = RSDK.LoadSpriteAnimation("CE+/Tails.bin", SCOPE_STAGE);
                            Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("CE+/TailSprite.bin", SCOPE_STAGE);
                            Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("CE+/MiracleTails.bin", SCOPE_STAGE);
                            Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("CE+/MiracleTailSprite.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->tailsFrames             = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
                            Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("Players/TailSprite.bin", SCOPE_STAGE);
                            Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("Players/MiracleTails.bin", SCOPE_STAGE);
                            Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("Players/MiracleTailSprite.bin", SCOPE_STAGE);
                        }
                        break;

                    case ID_KNUCKLES:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->knuxFrames        = RSDK.LoadSpriteAnimation("CE+/Knux.bin", SCOPE_STAGE);
                            Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("CE+/MiracleKnux.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->knuxFrames        = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
                            Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("Players/MiracleKnux.bin", SCOPE_STAGE);
                        }
                        break;
#if MANIA_USE_PLUS
                    case ID_MIGHTY:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->mightyFrames        = RSDK.LoadSpriteAnimation("CE+/Mighty.bin", SCOPE_STAGE);
                            Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("CE+/MiracleMighty.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->mightyFrames        = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
                            Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("Players/MiracleMighty.bin", SCOPE_STAGE);
                        }
                        break;

                    case ID_RAY:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->rayFrames        = RSDK.LoadSpriteAnimation("CE+/Ray.bin", SCOPE_STAGE);
                            Player->miracleRayFrames = RSDK.LoadSpriteAnimation("CE+/MiracleRay.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->rayFrames        = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
                            Player->miracleRayFrames = RSDK.LoadSpriteAnimation("Players/MiracleRay.bin", SCOPE_STAGE);
                        }
                        break;

                    case ID_AMY:
                        Player->amyFrames        = RSDK.LoadSpriteAnimation("Players/Amy.bin", SCOPE_STAGE);
                        Player->miracleAmyFrames = RSDK.LoadSpriteAnimation("Players/MiracleAmy.bin", SCOPE_STAGE);
                        break;
#endif
                }

                player->controllerID = i + 1;
                player->camera       = Camera_SetTargetEntity(i, player);
            }
        }

        destroyEntity(spawn);
    }
}
void Player_LoadSpritesCoop(void)
{
    AddendumOptions *addendumOptions  = Addendum_GetOptionsRAM();
    EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    foreach_all(Player, spawn)
    {
        int32 playerID = GET_CHARACTER_ID(1);
#if MANIA_USE_PLUS
        if (playerID == ID_MIGHTY || playerID == ID_RAY || playerID == ID_AMY)
            playerID = ID_SONIC;
#endif
        if (spawn->characterID & playerID) {
            for (int32 p = 0; p < 4; ++p) {
                EntityPlayer *player = RSDK_GET_ENTITY(p, Player);

                RSDK.CopyEntity(player, spawn, false);
                player->characterID = GET_CHARACTER_ID(p + 1);

                for (int32 i = 0; i < 0x10; ++i) Player->leaderPositionBuffer[p][i] = leader->position;

                player->classID    = Player->classID;
                player->position.x = leader->position.x;
                player->position.y = leader->position.y;
                player->position.x -= 0x100000 * p;

                if (player->characterID == ID_NONE)
                    destroyEntity(player);

                switch (player->characterID) {
                    default:
                    case ID_SONIC:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/Sonic.bin", SCOPE_STAGE);
                            Player->superFrames   = RSDK.LoadSpriteAnimation("CE+/SuperSonic.bin", SCOPE_STAGE);
                            Player->miracleFrames = RSDK.LoadSpriteAnimation("CE+/MiracleSonic.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
                            Player->superFrames   = RSDK.LoadSpriteAnimation("Players/SuperSonic.bin", SCOPE_STAGE);
                            Player->miracleFrames = RSDK.LoadSpriteAnimation("Players/MiracleSonic.bin", SCOPE_STAGE);
                        }
                        break;

                    case ID_TAILS:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->tailsFrames             = RSDK.LoadSpriteAnimation("CE+/Tails.bin", SCOPE_STAGE);
                            Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("CE+/TailSprite.bin", SCOPE_STAGE);
                            Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("CE+/MiracleTails.bin", SCOPE_STAGE);
                            Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("CE+/MiracleTailSprite.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->tailsFrames             = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
                            Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("Players/TailSprite.bin", SCOPE_STAGE);
                            Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("Players/MiracleTails.bin", SCOPE_STAGE);
                            Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("Players/MiracleTailSprite.bin", SCOPE_STAGE);
                        }
                        break;

                    case ID_KNUCKLES:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->knuxFrames        = RSDK.LoadSpriteAnimation("CE+/Knux.bin", SCOPE_STAGE);
                            Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("CE+/MiracleKnux.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->knuxFrames        = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
                            Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("Players/MiracleKnux.bin", SCOPE_STAGE);
                        }
                        break;
#if MANIA_USE_PLUS
                    case ID_MIGHTY:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->mightyFrames        = RSDK.LoadSpriteAnimation("CE+/Mighty.bin", SCOPE_STAGE);
                            Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("CE+/MiracleMighty.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->mightyFrames        = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
                            Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("Players/MiracleMighty.bin", SCOPE_STAGE);
                        }
                        break;

                    case ID_RAY:
                        if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                            Player->rayFrames        = RSDK.LoadSpriteAnimation("CE+/Ray.bin", SCOPE_STAGE);
                            Player->miracleRayFrames = RSDK.LoadSpriteAnimation("CE+/MiracleRay.bin", SCOPE_STAGE);
                        }
                        else {
                            Player->rayFrames        = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
                            Player->miracleRayFrames = RSDK.LoadSpriteAnimation("Players/MiracleRay.bin", SCOPE_STAGE);
                        }
                        break;

                    case ID_AMY:
                        Player->amyFrames        = RSDK.LoadSpriteAnimation("Players/Amy.bin", SCOPE_STAGE);
                        Player->miracleAmyFrames = RSDK.LoadSpriteAnimation("Players/MiracleAmy.bin", SCOPE_STAGE);
                        break;
#endif
                }

                player->controllerID = p + 1;
                player->camera       = Camera_SetTargetEntity(p, player);
                RSDK.AddCamera(&player->position, ScreenInfo->center.x << 16, ScreenInfo->center.y << 16, true);
            }
        }

        destroyEntity(spawn);
    }
}
void Player_SaveValues(void)
{
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *player2 = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    globals->restartLives[0] = Player->savedLives = player1->lives;
    globals->restartScore    = Player->savedScore = player1->score;
    globals->restartScore1UP = Player->savedScore1UP = player1->score1UP;
    if (addendumOptions->shieldTransfer) {
        for (int32 p = 0; p < 4; ++p) {
            EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
            if (player->classID == Player->classID) {
                globals->restartShield[p]    = player->shield;
                globals->restartHyperRing[p] = player->hyperRing;
            }
        }
    }
}
void Player_GiveScore(EntityPlayer *player, int32 score)
{
    if (player->sidekick)
        player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    player->score += score;
    if (player->score > 9999999)
        player->score = 9999999;

    if (player->score >= player->score1UP) {
        Player_GiveLife(player);
        while (player->score1UP <= player->score) player->score1UP += 50000;
    }
}
void Player_GiveRings(EntityPlayer *player, int32 amount, bool32 playSfx)
{
    EntityCompetitionSession *session = CompetitionSession_GetSession();
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();

    if (globals->gameMode == MODE_COMPETITION)
        session->totalRings[player->playerID] += amount;

    player->rings = CLAMP(player->rings + amount, 0, 9999);
    if (player->rings >= player->ringExtraLife) {
        Player_GiveLife(player);
        player->ringExtraLife += 100;
    }

    if (playSfx) {
        if (Ring->pan) {
            if (amount >= 0) {
                int32 channel = RSDK.PlaySfx(Ring->sfxRing, false, 255);
                RSDK.SetChannelAttributes(channel, 1.0, -1.0, 1.0);
            }
            else {
                int32 channel = RSDK.PlaySfx(Ring->sfxAntiRing, false, 255);
                RSDK.SetChannelAttributes(channel, 1.0, -1.0, 1.0);
            }
            Ring->pan = 0;
        }
        else {
            if (amount >= 0) {
                int32 channel = RSDK.PlaySfx(Ring->sfxRing, false, 255);
                RSDK.SetChannelAttributes(channel, 1.0, 1.0, 1.0);
            }
            else {
                int32 channel = RSDK.PlaySfx(Ring->sfxAntiRing, false, 255);
                RSDK.SetChannelAttributes(channel, 1.0, 1.0, 1.0);
            }
            Ring->pan = 1;
        }
    }
}
void Player_GiveLife(EntityPlayer *entity)
{
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

#if MANIA_USE_PLUS
    if (globals->gameMode != MODE_TIMEATTACK && globals->gameMode != MODE_ENCORE) {
#else
    if (globals->gameMode != MODE_TIMEATTACK) {
#endif
        if (addendumOptions->lifeSystem != LIFESYSTEM_INFINITE) {
            if (addendumOptions->lifeSystem == LIFESYSTEM_MANIA) {
                if (entity->lives < 99) {
                    entity->lives++;
                    RSDK.PlaySfx(Player->sfx1up, false, 255);
                }
            }
            else {
                entity->lives++;
                RSDK.PlaySfx(Player->sfx1up, false, 255);
            }
        }
    }
}
void Player_ApplyShield(EntityPlayer *player)
{
    if (player->shield && player->superState != SUPERSTATE_SUPER && player->invincibleTimer <= 0) {
        EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(player), Shield);
        RSDK.ResetEntity(shield, Shield->classID, player);  
    }
}
void Player_ChangeCharacter(EntityPlayer *entity, int32 character)
{
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    uint16 playerID     = entity->playerID;
    entity->characterID = character;
    globals->playerID &= ~(255 << 8 * playerID);
    globals->playerID |= character << 8 * entity->playerID;

    switch (entity->characterID) {
        default:
        case ID_SONIC:
            if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                Player->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/Sonic.bin", SCOPE_STAGE);
                Player->superFrames   = RSDK.LoadSpriteAnimation("CE+/SuperSonic.bin", SCOPE_STAGE);
                Player->miracleFrames = RSDK.LoadSpriteAnimation("CE+/MiracleSonic.bin", SCOPE_STAGE);
                if (SizeLaser) {
                    SizeLaser->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/ChibiSonic.bin", SCOPE_STAGE);
                    SizeLaser->superFrames   = RSDK.LoadSpriteAnimation("CE+/ChibiSuperSonic.bin", SCOPE_STAGE);
                    SizeLaser->miracleFrames = RSDK.LoadSpriteAnimation("CE+/ChibiMiracleSonic.bin", SCOPE_STAGE);
                }
            }
            else {
                Player->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
                Player->superFrames   = RSDK.LoadSpriteAnimation("Players/SuperSonic.bin", SCOPE_STAGE);
                Player->miracleFrames = RSDK.LoadSpriteAnimation("Players/MiracleSonic.bin", SCOPE_STAGE);
                if (SizeLaser) {
                    SizeLaser->sonicFrames   = RSDK.LoadSpriteAnimation("Players/ChibiSonic.bin", SCOPE_STAGE);
                    SizeLaser->superFrames   = RSDK.LoadSpriteAnimation("Players/ChibiSuperSonic.bin", SCOPE_STAGE);
                    SizeLaser->miracleFrames = RSDK.LoadSpriteAnimation("Players/ChibiMiracleSonic.bin", SCOPE_STAGE);
                }
            }

            if (entity->isChibi) {
                if (entity->superState == SUPERSTATE_SUPER) {
                    if (entity->miracleState)
                        entity->aniFrames = SizeLaser->miracleFrames;
                    else
                        entity->aniFrames = SizeLaser->superFrames;
                }
                else
                    entity->aniFrames = SizeLaser->sonicFrames;
                entity->jumpOffset = TO_FIXED(4);
            }
            else {
                if (entity->superState == SUPERSTATE_SUPER) {
                    if (entity->miracleState)
                        entity->aniFrames = Player->miracleFrames;
                    else
                        entity->aniFrames = Player->superFrames;
                }
                else
                    entity->aniFrames = Player->sonicFrames;
                entity->jumpOffset = TO_FIXED(5);
            }

            entity->tailFrames       = -1;
            entity->stateAbility     = Player_JumpAbility_Sonic;
            entity->stateTallJump    = StateMachine_None;
            entity->sensorY          = TO_FIXED(20);
            entity->hyperBlendAmount = 64;
            entity->hyperBlendState  = 0;

            if (addendumOptions->peeloutAbility != PEELOUTABILITY_NONE) {
                entity->statePeelout = Player_Action_Peelout;

                if (addendumOptions->sonicMoveset == SONICMOVESET_ADDENDUM || SONICMOVESET_CD) {
                    for (int32 f = 0; f < 4; ++f) {
                        SpriteFrame *dst = RSDK.GetFrame(entity->aniFrames, ANI_DASH, f + 1);
                        SpriteFrame *src = RSDK.GetFrame(entity->aniFrames, ANI_PEELOUT, f);

                        *dst = *src;
                    }
                }
            }
            else
                entity->statePeelout = StateMachine_None;

            if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                for (int32 s = 0; s < 16; ++s) {
                    SpriteFrame *dst = RSDK.GetFrame(entity->aniFrames, ANI_SPINDASH, s);
                    SpriteFrame *src = RSDK.GetFrame(entity->aniFrames, 55, s);

                    *dst = *src;
                }
            }
            break;

        case ID_TAILS:
            if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                Player->tailsFrames             = RSDK.LoadSpriteAnimation("CE+/Tails.bin", SCOPE_STAGE);
                Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("CE+/TailSprite.bin", SCOPE_STAGE);
                Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("CE+/MiracleTails.bin", SCOPE_STAGE);
                Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("CE+/MiracleTailSprite.bin", SCOPE_STAGE);

                if (SizeLaser) {
                    SizeLaser->tailsFrames        = RSDK.LoadSpriteAnimation("CE+/ChibiTails.bin", SCOPE_STAGE);
                    SizeLaser->tailFrames         = RSDK.LoadSpriteAnimation("CE+/CTailSprite.bin", SCOPE_STAGE);
                    SizeLaser->miracleTailsFrames = RSDK.LoadSpriteAnimation("CE+/ChibiMiracleTails.bin", SCOPE_STAGE);
                    SizeLaser->miracleTailFrames  = RSDK.LoadSpriteAnimation("CE+/MiracleCTailSprite.bin", SCOPE_STAGE);
                }
            }
            else {
                Player->tailsFrames             = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
                Player->tailsTailsFrames        = RSDK.LoadSpriteAnimation("Players/TailSprite.bin", SCOPE_STAGE);
                Player->miracleTailsFrames      = RSDK.LoadSpriteAnimation("Players/MiracleTails.bin", SCOPE_STAGE);
                Player->miracleTailsTailsFrames = RSDK.LoadSpriteAnimation("Players/MiracleTailSprite.bin", SCOPE_STAGE);

                if (SizeLaser) {
                    SizeLaser->tailsFrames        = RSDK.LoadSpriteAnimation("Players/ChibiTails.bin", SCOPE_STAGE);
                    SizeLaser->tailFrames         = RSDK.LoadSpriteAnimation("Players/CTailSprite.bin", SCOPE_STAGE);
                    SizeLaser->miracleTailsFrames = RSDK.LoadSpriteAnimation("Player/ChibiMiracleTails.bin", SCOPE_STAGE);
                    SizeLaser->miracleTailFrames  = RSDK.LoadSpriteAnimation("Player/MiracleCTailSprite.bin", SCOPE_STAGE);
                }
            }

            if (entity->isChibi) {
                if (entity->superState == SUPERSTATE_SUPER && entity->miracleState) {
                    entity->aniFrames  = SizeLaser->miracleTailsFrames;
                    entity->tailFrames = SizeLaser->miracleTailFrames;
                }
                else {
                    entity->aniFrames  = SizeLaser->tailsFrames;
                    entity->tailFrames = SizeLaser->tailFrames;
                }
                entity->jumpOffset = TO_FIXED(4);
            }
            else {
                if (entity->superState == SUPERSTATE_SUPER && entity->miracleState) {
                    entity->aniFrames  = Player->miracleTailsFrames;
                    entity->tailFrames = Player->miracleTailsTailsFrames;
                }
                else {
                    entity->aniFrames  = Player->tailsFrames;
                    entity->tailFrames = Player->tailsTailsFrames;
                }
                entity->jumpOffset = TO_FIXED(0);
            }

            entity->stateAbility  = Player_JumpAbility_Tails;
            if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY || addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
                entity->statePeelout = Player_Action_Peelout;
            else
                entity->statePeelout  = StateMachine_None;
            entity->stateTallJump = StateMachine_None;
            entity->sensorY       = TO_FIXED(16);
            break;

        case ID_KNUCKLES:
            if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                Player->knuxFrames        = RSDK.LoadSpriteAnimation("CE+/Knux.bin", SCOPE_STAGE);
                Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("CE+/MiracleKnux.bin", SCOPE_STAGE);

                if (SizeLaser) {
                    SizeLaser->knuxFrames        = RSDK.LoadSpriteAnimation("CE+/ChibiKnux.bin", SCOPE_STAGE);
                    SizeLaser->miracleKnuxFrames = RSDK.LoadSpriteAnimation("CE+/ChibiMiracleKnux.bin", SCOPE_STAGE);
                }
            }
            else {
                Player->knuxFrames        = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
                Player->miracleKnuxFrames = RSDK.LoadSpriteAnimation("Players/MiracleKnux.bin", SCOPE_STAGE);

                if (SizeLaser) {
                    SizeLaser->knuxFrames        = RSDK.LoadSpriteAnimation("Players/ChibiKnux.bin", SCOPE_STAGE);
                    SizeLaser->miracleKnuxFrames = RSDK.LoadSpriteAnimation("Players/ChibiMiracleKnux.bin", SCOPE_STAGE);
                }
            }

            if (entity->isChibi) {
                if (entity->superState == SUPERSTATE_SUPER && entity->miracleState)
                    entity->aniFrames = SizeLaser->miracleKnuxFrames;
                else
                entity->aniFrames = SizeLaser->knuxFrames;
                entity->jumpOffset = TO_FIXED(4);
            }
            else {
                if (entity->superState == SUPERSTATE_SUPER && entity->miracleState) {
                    entity->aniFrames = Player->miracleKnuxFrames;
                }
                else {
                entity->aniFrames = Player->knuxFrames;
                }
                entity->jumpOffset = TO_FIXED(5);
            }

            entity->tailFrames    = -1;
            entity->stateAbility  = Player_JumpAbility_Knux;
            if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY || addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
                entity->statePeelout = Player_Action_Peelout;
            else
                entity->statePeelout  = StateMachine_None;
            entity->stateTallJump = StateMachine_None;
            entity->sensorY       = TO_FIXED(20);

            if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                for (int32 s = 0; s < 16; ++s) {
                    SpriteFrame *dst = RSDK.GetFrame(entity->aniFrames, ANI_SPINDASH, s);
                    SpriteFrame *src = RSDK.GetFrame(entity->aniFrames, 55, s);

                    *dst = *src;
                }
            }
            break;

#if MANIA_USE_PLUS
        case ID_MIGHTY:
            if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                Player->mightyFrames        = RSDK.LoadSpriteAnimation("CE+/Mighty.bin", SCOPE_STAGE);
                Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("CE+/MiracleMighty.bin", SCOPE_STAGE);

                if (SizeLaser) {
                    SizeLaser->mightyFrames        = RSDK.LoadSpriteAnimation("CE+/ChibiMighty.bin", SCOPE_STAGE);
                    SizeLaser->miracleMightyFrames = RSDK.LoadSpriteAnimation("CE+/ChibiMiracleMighty.bin", SCOPE_STAGE);
                }
            }
            else {
                Player->mightyFrames        = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
                Player->miracleMightyFrames = RSDK.LoadSpriteAnimation("Players/MiracleMighty.bin", SCOPE_STAGE);

                if (SizeLaser) {
                    SizeLaser->mightyFrames        = RSDK.LoadSpriteAnimation("Players/ChibiMighty.bin", SCOPE_STAGE);
                    SizeLaser->miracleMightyFrames = RSDK.LoadSpriteAnimation("Players/ChibiMiracleMighty.bin", SCOPE_STAGE);
                }
            }

            if (entity->isChibi) {
                if (entity->superState == SUPERSTATE_SUPER && entity->miracleState)
                    entity->aniFrames = SizeLaser->miracleMightyFrames;
                else
                    entity->aniFrames = SizeLaser->mightyFrames;
                entity->jumpOffset = TO_FIXED(4);
            }
            else {
                if (entity->superState == SUPERSTATE_SUPER && entity->miracleState)
                    entity->aniFrames = Player->miracleMightyFrames;
                else
                    entity->aniFrames = Player->mightyFrames;
                entity->jumpOffset = TO_FIXED(5);
            }

            entity->tailFrames    = -1;
            entity->stateAbility  = Player_JumpAbility_Mighty;
            if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY || addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
                entity->statePeelout = Player_Action_Peelout;
            else
                entity->statePeelout  = StateMachine_None;
            entity->stateTallJump = StateMachine_None;
            entity->sensorY       = TO_FIXED(20);

            if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                for (int32 s = 0; s < 16; ++s) {
                    SpriteFrame *dst = RSDK.GetFrame(entity->aniFrames, ANI_SPINDASH, s);
                    SpriteFrame *src = RSDK.GetFrame(entity->aniFrames, 55, s);

                    *dst = *src;
                }
            }
            break;

        case ID_RAY:
            if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
                Player->rayFrames        = RSDK.LoadSpriteAnimation("CE+/Ray.bin", SCOPE_STAGE);
                Player->miracleRayFrames = RSDK.LoadSpriteAnimation("CE+/MiracleRay.bin", SCOPE_STAGE);

                if (SizeLaser) {
                    SizeLaser->rayFrames        = RSDK.LoadSpriteAnimation("CE+/ChibiRay.bin", SCOPE_STAGE);
                    SizeLaser->miracleRayFrames = RSDK.LoadSpriteAnimation("CE+/ChibiMiracleRay.bin", SCOPE_STAGE);
                }
            }
            else {
                Player->rayFrames        = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
                Player->miracleRayFrames = RSDK.LoadSpriteAnimation("Players/MiracleRay.bin", SCOPE_STAGE);

                if (SizeLaser) {
                    SizeLaser->rayFrames        = RSDK.LoadSpriteAnimation("Players/ChibiRay.bin", SCOPE_STAGE);
                    SizeLaser->miracleRayFrames = RSDK.LoadSpriteAnimation("Players/ChibiMiracleRay.bin", SCOPE_STAGE);
                }
            }

            if (entity->isChibi) {
                if (entity->superState == SUPERSTATE_SUPER && entity->miracleState)
                    entity->aniFrames = SizeLaser->miracleRayFrames;
                else
                    entity->aniFrames = SizeLaser->rayFrames;
                entity->jumpOffset = TO_FIXED(4);
            }
            else {
                if (entity->superState == SUPERSTATE_SUPER && entity->miracleState)
                    entity->aniFrames = Player->miracleRayFrames;
                else
                    entity->aniFrames = Player->rayFrames;
                entity->jumpOffset = TO_FIXED(5);
            }

            entity->tailFrames    = -1;
            entity->stateAbility  = Player_JumpAbility_Ray;
            if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY || addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
                entity->statePeelout = Player_Action_Peelout;
            else
                entity->statePeelout  = StateMachine_None;
            entity->stateTallJump = StateMachine_None;
            entity->sensorY       = TO_FIXED(20);

            if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                for (int32 s = 0; s < 16; ++s) {
                    SpriteFrame *dst = RSDK.GetFrame(entity->aniFrames, ANI_SPINDASH, s);
                    SpriteFrame *src = RSDK.GetFrame(entity->aniFrames, 55, s);

                    *dst = *src;
                }
            }
            break;

        case ID_AMY:
            Player->amyFrames = RSDK.LoadSpriteAnimation("Players/Amy.bin", SCOPE_STAGE);
            Player->miracleAmyFrames = RSDK.LoadSpriteAnimation("Players/MiracleAmy.bin", SCOPE_STAGE);
            if (SizeLaser) {
                SizeLaser->amyFrames = RSDK.LoadSpriteAnimation("Players/ChibiAmy.bin", SCOPE_STAGE);
                SizeLaser->miracleAmyFrames = RSDK.LoadSpriteAnimation("Players/ChibiMiracleAmy.bin", SCOPE_STAGE);
            }

            if (entity->isChibi) {
                if (entity->miracleState)
                    entity->aniFrames = SizeLaser->miracleAmyFrames;
                else
                    entity->aniFrames = SizeLaser->amyFrames;
                entity->jumpOffset = TO_FIXED(4);
            }
            else {
                if (entity->miracleState)
                    entity->aniFrames = Player->miracleAmyFrames;
                else
                    entity->aniFrames = Player->amyFrames;
                entity->jumpOffset = TO_FIXED(5);
            }

            entity->tailFrames   = -1;
            entity->stateAbility = Player_JumpAbility_Amy;
            entity->statePeelout = StateMachine_None;
            entity->sensorY      = TO_FIXED(20);
            if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALL) {
                entity->statePeelout = Player_Action_Peelout;
                entity->stateTallJump = StateMachine_None;
            }
            else {
                entity->statePeelout = StateMachine_None;
                entity->stateTallJump = Player_Action_TallJump;
            }

            if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
                for (int32 s = 0; s < 16; ++s) {
                    SpriteFrame *dst = RSDK.GetFrame(entity->aniFrames, ANI_SPINDASH, s);
                    SpriteFrame *src = RSDK.GetFrame(entity->aniFrames, 55, s);

                    *dst = *src;
                }
            }
            break;
#endif
    }

    entity->sensorX[0] = TO_FIXED(10);
    entity->sensorX[1] = TO_FIXED(5);
    entity->sensorX[2] = TO_FIXED(0);
    entity->sensorX[3] = -TO_FIXED(5);
    entity->sensorX[4] = -TO_FIXED(10);

    if (entity->state == Player_State_KnuxWallClimb || entity->state == Player_State_DropDash || entity->state == Player_State_TailsFlight
        || entity->state == Player_State_KnuxGlideDrop || entity->state == Player_State_KnuxGlideLeft || entity->state == Player_State_KnuxGlideRight
        || entity->state == Player_State_KnuxGlideSlide || entity->state == Player_State_KnuxLedgePullUp
#if MANIA_USE_PLUS
        || entity->state == Player_State_MightyHammerDrop || entity->state == Player_State_RayGlide || entity->state == Player_State_MightyUnspin
        || entity->state == Player_Action_TallJump || entity->state == Player_State_AmyHeliHammer_Left || entity->state == Player_State_AmyHeliHammer_Right
#endif
    ) {
        entity->state = Player_State_Air;
        RSDK.SetSpriteAnimation(entity->aniFrames, ANI_JUMP, &entity->animator, false, 0);
    }
    else {
        RSDK.SetSpriteAnimation(entity->aniFrames, entity->animator.animationID, &entity->animator, false, 0);
    }

    int32 hyperColor = entity->hyperBlendState;
    if (entity->superState != SUPERSTATE_NONE) {
        if (entity->hyperState) {
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[hyperColor][c]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[0][c]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[c + 12]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, hyperPaletteWhite[0][c]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[c + 12]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, hyperPaletteWhite[0][c]);
#if MANIA_USE_PLUS
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[c + 12]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, hyperPaletteWhite[0][c]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[c + 12]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, hyperPaletteWhite[0][c]);
#endif

                if (HCZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_HCZ[hyperColor][c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[1][c]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, hyperPaletteWhite[1][c]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, hyperPaletteWhite[1][c]);
#if MANIA_USE_PLUS
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, hyperPaletteWhite[1][c]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, hyperPaletteWhite[1][c]);
#endif
                }
                else if (CPZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_CPZ[hyperColor][c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[2][c]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, hyperPaletteWhite[2][c]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, hyperPaletteWhite[2][c]);
#if MANIA_USE_PLUS
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, hyperPaletteWhite[2][c]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, hyperPaletteWhite[2][c]);
#endif
                }
            }

#if MANIA_USE_PLUS
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[c + 14]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, hyperPaletteWhite_Ray[0][c]);

                if (HCZSetup) {
                    RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_HCZ[c + 14]);
                    RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_RAY + c, hyperPaletteWhite_Ray[1][c]);
                }

                if (CPZSetup) {
                    RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_CPZ[c + 14]);
                    RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_RAY + c, hyperPaletteWhite_Ray[2][c]);
                }
            }
#endif
        }
        else if (entity->miracleState) {
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[c + 12]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[c + 12]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[c + 12]);
#if MANIA_USE_PLUS
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[c + 12]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[c + 12]);
#endif

                if (HCZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_HCZ[c + 12]);
#if MANIA_USE_PLUS
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_HCZ[c + 12]);
#endif
                }
                else if (CPZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_CPZ[c + 12]);
#if MANIA_USE_PLUS
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_CPZ[c + 12]);
#endif
                }
            }

#if MANIA_USE_PLUS
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[c + 7]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[c + 14]);

                if (HCZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_HCZ[c + 7]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_HCZ[c + 14]);
                }

                if (CPZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_CPZ[c + 7]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_CPZ[c + 14]);
                }
            }
#endif
        }
        else {
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[c + 12]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[c + 12]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[c + 12]);
#if MANIA_USE_PLUS
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[c + 12]);
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[c + 6]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[c + 12]);
#endif

                if (HCZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_HCZ[c + 12]);
#if MANIA_USE_PLUS
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_HCZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[c + 12]);
#endif
                }
                else if (CPZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_CPZ[c + 12]);
#if MANIA_USE_PLUS
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_CPZ[c + 12]);
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[c + 6]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[c + 12]);
#endif
                }
            }

#if MANIA_USE_PLUS
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[c + 7]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[c + 14]);

                if (HCZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_HCZ[c + 7]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_HCZ[c + 14]);
                }

                if (CPZSetup) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_CPZ[c + 7]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_CPZ[c + 14]);
                }
            }
#endif
        }

        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
            RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[c]);
            RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[c]);
            RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[c]);
#if MANIA_USE_PLUS
            RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[c]);
            RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[c]);
#endif

            if (HCZSetup) {
                RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_HCZ[c]);
                RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_HCZ[c]);
                RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_HCZ[c]);
#if MANIA_USE_PLUS
                RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_HCZ[c]);
                RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[c]);
#endif
            }
            else if (CPZSetup) {
                RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_CPZ[c]);
                RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_CPZ[c]);
                RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_CPZ[c]);
#if MANIA_USE_PLUS
                RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_CPZ[c]);
                RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[c]);
#endif
            }
        }

#if MANIA_USE_PLUS
        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
            RSDK.SetPaletteEntry(0, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[c]);

            if (HCZSetup) {
                RSDK.SetPaletteEntry(1, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_HCZ[c]);
            }

            if (CPZSetup) {
                RSDK.SetPaletteEntry(2, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_CPZ[c]);
            }
        }
#endif

        if (FarPlane) {
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_SONIC, 3, PLAYER_PALETTE_INDEX_SONIC, PLAYER_PRIMARY_COLOR_COUNT);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 3, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 3, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
#if MANIA_USE_PLUS
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 3, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 3, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_AMY, 3, PLAYER_PALETTE_INDEX_AMY, PLAYER_PRIMARY_COLOR_COUNT);
#endif
        }
        else if (OOZSetup) {
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_SONIC, 1, PLAYER_PALETTE_INDEX_SONIC, PLAYER_PRIMARY_COLOR_COUNT);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_SONIC, 2, PLAYER_PALETTE_INDEX_SONIC, PLAYER_PRIMARY_COLOR_COUNT);

            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 1, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 2, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);

            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 1, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 2, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);

#if MANIA_USE_PLUS
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 1, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 2, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);

            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 1, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 2, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);

            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_AMY, 1, PLAYER_PALETTE_INDEX_AMY, PLAYER_PRIMARY_COLOR_COUNT);
            RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_AMY, 2, PLAYER_PALETTE_INDEX_AMY, PLAYER_PRIMARY_COLOR_COUNT);
#endif
        }

        if (entity->superState == SUPERSTATE_SUPER) {
            if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                Player_TryTransform(entity, 0xFF, Addendum_GetSaveRAM()->collectedSuperEmeralds, 0x00);
            else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                Player_TryTransform(entity, 0xFF, 0x00, Addendum_GetSaveRAM()->collectedTimeStones);
            else
                Player_TryTransform(entity, 0xFF, 0x00, 0x00);
        }
    }

    Player_UpdatePhysicsState(entity);
}
bool32 Player_TryTransform(EntityPlayer *player, uint8 emeraldMasks, uint8 superEmeraldMasks, uint8 timeStoneMasks)
{
    RSDK_THIS(Player);
    AddendumData *addendumData       = Addendum_GetSaveRAM();
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    
    if (!MSZCutsceneK && globals->gameMode != MODE_COMPETITION) {
        if (!SceneInfo->timeEnabled && !ERZStart && (!PhantomEgg || PhantomEgg->disableSuperForm))
            return false;
    }

    uint8 emeralds = emeraldMasks;
    uint8 timeStones = timeStoneMasks;
    uint8 superEmeralds = superEmeraldMasks;
#if MANIA_USE_PLUS
    if (emeraldMasks == 0xFF || emeraldMasks == 127) { // 0xFF seems to be the "force transform" flag
        emeralds             = 0b01111111;
        player->miracleState = false;
        player->hyperState   = false;
    }
    if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
        if (superEmeraldMasks == 0xFF || superEmeraldMasks == 127) {
            superEmeralds      = 0b01111111;
            player->hyperState = true;
        }
    }
    if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
        if (timeStoneMasks == 0xFF || timeStoneMasks == 127) {
            timeStones           = 0b01111111;
            player->miracleState = true;
        }
    }

    if (Player->canSuperCB) {
        if (!Player->canSuperCB(false))
            return false;
    }
#endif

#if MANIA_USE_PLUS
    if ((player->superState >= SUPERSTATE_SUPER || ((emeralds != 0b01111111 && timeStones != 0b01111111) || (emeralds != 0b01111111 && superEmeralds != 0b01111111)) 
        || (emeralds == 0b01111111 && addendumData->emeraldsTransferred && addendumData->collectedSuperEmeralds != 0b01111111) || player->rings < 50))
        return false;

    if (player->superState != SUPERSTATE_SUPER) {
        if (emeralds == 0b01111111 && superEmeralds == 0b01111111 && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
            if (!player->sidekick) {
                int32 angle = 0;
                for (int32 p = 0; p < 16; ++p) {
                    EntityDebris *masterSparkles = CREATE_ENTITY(Debris, NULL, player->position.x, player->position.y);
                    masterSparkles->state        = Debris_State_Rotate;
                    masterSparkles->drawGroup    = Zone->objectDrawGroup[1];
                    masterSparkles->active       = ACTIVE_NORMAL;
                    masterSparkles->originPos.x  = player->position.x;
                    masterSparkles->originPos.y  = player->position.y;
                    masterSparkles->angle        = angle;
                    masterSparkles->radius       = 0x10000;
                    masterSparkles->groundVel    = 0x600;

                    angle += 0x1000; // how far out each sparkle is spaced out from each other

                    RSDK.SetSpriteAnimation(Debris->emeraldFrames, 1, &masterSparkles->emeraldsAnimator, true, p);
                }

                player->hyperState = true;
            }
        }
        else if (emeralds == 0b01111111 && timeStones == 0b1111111 && addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
            if (!player->sidekick) {
                int32 angle = 0;
                for (int32 p = 0; p < 14; ++p) {
                    EntityDebris *powerStone = CREATE_ENTITY(Debris, NULL, player->position.x, player->position.y);
                    powerStone->state        = Debris_State_Rotate;
                    powerStone->drawGroup    = Zone->objectDrawGroup[1];
                    powerStone->active       = ACTIVE_NORMAL;
                    powerStone->originPos.x  = player->position.x;
                    powerStone->originPos.y  = player->position.y;
                    powerStone->angle        = angle;
                    powerStone->radius       = 0x10000;
                    powerStone->groundVel    = 1024;

                    angle += 0x1249; // how far out each emerald/time stone is spaced out from each other

                    RSDK.SetSpriteAnimation(Debris->emeraldFrames, 0, &powerStone->emeraldsAnimator, true, p);
                }

                player->miracleState = true;
            }
        }
        else {
            if (emeralds == 0b01111111 && ((superEmeralds != 0b01111111 && addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD && !addendumData->emeraldsTransferred) || 
                (timeStones != 0b01111111 && addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) || addendumOptions->secondaryGems == SECONDGEMS_NONE)) {
                if (!player->sidekick) {
                    int32 angle = 0;
                    for (int32 i = 0; i < 7; ++i) {
                        EntityDebris *emerald = CREATE_ENTITY(Debris, NULL, player->position.x, player->position.y);
                        emerald->state        = Debris_State_Rotate;
                        emerald->drawGroup    = Zone->objectDrawGroup[1];
                        emerald->active       = ACTIVE_NORMAL;
                        emerald->originPos.x  = player->position.x;
                        emerald->originPos.y  = player->position.y;
                        emerald->angle        = angle;
                        emerald->radius       = 0x10000;
                        emerald->groundVel    = 1024;

                        angle += 0x2492;

                        RSDK.SetSpriteAnimation(Debris->emeraldFrames, 0, &emerald->emeraldsAnimator, true, i);
                    }

                    player->miracleState = false;
                    player->hyperState   = false;
                }
            }
        }
    }

    RSDK.StopSfx(Player->sfxSwapFail);
    if (globals->secrets & SECRET_SUPERDASH)
        player->stateAbility = ERZStart_Player_StartSuperFly;
#else
    if (player->superState >= SUPERSTATE_SUPER || emeralds != 0b01111111 || player->rings < 50)
        return false;
#endif

    int32 hyperColor = player->hyperBlendState;
    switch (player->characterID) {
        case ID_SONIC:
            if (player->hyperState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(6, 109, 0x000000);
                    RSDK.SetPaletteEntry(7, 109, Player->superExtras[7]);
                }
            }
            else if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(6, 109, 0x000000);
                    RSDK.SetPaletteEntry(7, 109, Player->superExtras[13]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(6, 109, 0x000000);
                    RSDK.SetPaletteEntry(7, 109, Player->superExtras[0]);
                }
            }
            break;

        case ID_TAILS:
            if (player->hyperState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            break;

        case ID_KNUCKLES:
            if (player->hyperState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            break;

#if MANIA_USE_PLUS
        case ID_MIGHTY:
            if (player->hyperState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            break;

        case ID_RAY:
            if (player->hyperState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                }
            }
            else if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                }
            }
            break;

        case ID_AMY:
            if (player->hyperState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
#endif

        default: break;
    }

    if (player->characterID == ID_SONIC) {
        if (player->isChibi) {
            if (player->miracleState)
                player->aniFrames = SizeLaser->miracleFrames;
            else
                player->aniFrames = SizeLaser->superFrames;
        }
        else {
            if (player->miracleState)
                player->aniFrames = Player->miracleFrames;
            else
                player->aniFrames = Player->superFrames;
        }
    }

    if (player->characterID == ID_TAILS && player->miracleState) {
        if (player->isChibi) {
            player->aniFrames  = SizeLaser->miracleTailsFrames;
            player->tailFrames = SizeLaser->miracleTailFrames;
        }
        else {
            player->aniFrames  = Player->miracleTailsFrames;
            player->tailFrames = Player->miracleTailsTailsFrames;
        }
    }

    if (player->characterID == ID_KNUCKLES && player->miracleState) {
        if (player->isChibi)
            player->aniFrames = SizeLaser->miracleKnuxFrames;
        else
            player->aniFrames = Player->miracleKnuxFrames;
    }

    if (player->characterID == ID_MIGHTY && player->miracleState) {
        if (player->isChibi)
            player->aniFrames = SizeLaser->miracleMightyFrames;
        else
            player->aniFrames = Player->miracleMightyFrames;
    }

    if (player->characterID == ID_RAY && player->miracleState) {
        if (player->isChibi)
            player->aniFrames = SizeLaser->miracleRayFrames;
        else
            player->aniFrames = Player->miracleRayFrames;
    }

    if (player->characterID == ID_AMY && player->miracleState) {
        if (player->isChibi)
            player->aniFrames = SizeLaser->miracleAmyFrames;
        else
            player->aniFrames = Player->miracleAmyFrames;
    }

    if (player->characterID != ID_TAILS) {
        if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
            for (int32 s = 0; s < 16; ++s) {
                SpriteFrame *dst = RSDK.GetFrame(player->aniFrames, ANI_SPINDASH, s);
                SpriteFrame *src = RSDK.GetFrame(player->aniFrames, 55, s);

                *dst = *src;
            }
        }
    }

#if MANIA_USE_PLUS
    if (emeraldMasks == 0xFF) {
        player->superState = SUPERSTATE_SUPER;
        Player_UpdatePhysicsState(player);
    }
    else {
#endif
        if (player->isChibi)
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_JUMP, &player->animator, true, 0);
        else
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_TRANSFORM, &player->animator, true, 0);

#if GAME_VERSION != VER_100
        player->superInvulnTimer = 60;
        player->invincibleTimer  = 1;
#endif
        player->velocity.x      = 0;
        player->velocity.y      = 0;
        player->groundVel       = 0;
        player->onGround        = false;
        player->nextAirState    = StateMachine_None;
        player->nextGroundState = StateMachine_None;
        player->interaction     = false;
        if (player->animator.frameID == 9)
            player->state = Player_State_Transform;
#if GAME_VERSION != VER_100
        player->isTransforming  = true;
#endif
#if MANIA_USE_PLUS
        if (!ERZStart && globals->superMusicEnabled)
            Music_FadeOut(0.8);
#else
        if (!ERZStart)
            Music_TransitionTrack(TRACK_SUPER, 0.04);
#endif
        player->jumpAbilityState = 0;
        player->superState       = SUPERSTATE_FADEIN;

#if MANIA_USE_PLUS
    }
#endif

    player->superBlendAmount   = 0;
    player->superBlendState    = 0;
    player->superRingLossTimer = player->miracleState ? 90 : 60;
    player->timer              = 0;
    return true;
}
bool32 Player_TryTransform_ERZ(EntityPlayer *player, uint8 emeraldMasks, uint8 superEmeraldMasks, uint8 timeStoneMasks)
{
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (!SceneInfo->timeEnabled && !ERZStart && (!PhantomEgg || PhantomEgg->disableSuperForm))
        return false;

    if (Addendum_GetSaveRAM()->emeraldsTransferred && Addendum_GetSaveRAM()->collectedSuperEmeralds != 0b01111111)
        return false;

    uint8 emeralds      = emeraldMasks;
    uint8 timeStones    = timeStoneMasks;
    uint8 superEmeralds = superEmeraldMasks;
#if MANIA_USE_PLUS
    if (emeraldMasks == 0xFF) // 0xFF seems to be the "force transform" flag
        emeralds = 0b01111111;
    if (superEmeraldMasks == 0xFF)
        superEmeralds = 0b01111111;
    if (timeStoneMasks == 0xFF)
        timeStones = 0b01111111;

    if (Player->canSuperCB) {
        if (!Player->canSuperCB(false))
            return false;
    }
#endif

#if MANIA_USE_PLUS
    if ((player->superState >= SUPERSTATE_SUPER || ((emeralds != 0b01111111 && timeStones != 0b01111111) || (emeralds != 0b01111111 && superEmeralds != 0b01111111)) 
        || player->rings < 50))
        return false;

    RSDK.StopSfx(Player->sfxSwapFail);
    if (globals->secrets & SECRET_SUPERDASH)
        player->stateAbility = ERZStart_Player_StartSuperFly;
#else
    if (player->superState >= SUPERSTATE_SUPER || emeralds != 0b01111111 || player->rings < 50)
            return false;
#endif

    if (emeralds == 0x7F) {
        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
            if (superEmeralds == 0b01111111)
                player->hyperState = true;
        }
        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
            player->miracleState = true;
        }
        else
            player->miracleState = false;
    }

    switch (player->characterID) {
        case ID_SONIC:
            if (player->hyperState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(6, 109, 0x000000);
                    RSDK.SetPaletteEntry(7, 109, Player->superExtras[7]);
                }
            }
            else if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(6, 109, 0x000000);
                    RSDK.SetPaletteEntry(7, 109, Player->superExtras[13]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(6, 109, 0x000000);
                    RSDK.SetPaletteEntry(7, 109, Player->superExtras[0]);
                }
            }
            break;

        case ID_TAILS:
            if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            break;

        case ID_KNUCKLES:
            if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            break;

#if MANIA_USE_PLUS
        case ID_MIGHTY:
            if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            break;

        case ID_RAY:
            if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                }
            }
            break;

        case ID_AMY:
            if (player->miracleState) {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
            else {
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                }
            }
#endif

        default: break;
    }

    if (player->characterID == ID_SONIC) {
        if (player->isChibi) {
            if (player->miracleState)
                player->aniFrames = SizeLaser->miracleFrames;
            else
                player->aniFrames = SizeLaser->superFrames;
        }
        else {
            if (player->miracleState)
                player->aniFrames = Player->miracleFrames;
            else
                player->aniFrames = Player->superFrames;
        }
    }

    if (player->characterID == ID_TAILS && player->miracleState) {
        if (player->isChibi) {
            player->aniFrames  = SizeLaser->miracleTailsFrames;
            player->tailFrames = SizeLaser->miracleTailFrames;
        }
        else {
            player->aniFrames  = Player->miracleTailsFrames;
            player->tailFrames = Player->miracleTailsTailsFrames;
        }
    }

    if (player->characterID == ID_KNUCKLES && player->miracleState) {
        if (player->isChibi)
            player->aniFrames = SizeLaser->miracleKnuxFrames;
        else
            player->aniFrames = Player->miracleKnuxFrames;
    }

    if (player->characterID == ID_MIGHTY && player->miracleState) {
        if (player->isChibi)
            player->aniFrames = SizeLaser->miracleMightyFrames;
        else
            player->aniFrames = Player->miracleMightyFrames;
    }

    if (player->characterID == ID_RAY && player->miracleState) {
        if (player->isChibi)
            player->aniFrames = SizeLaser->miracleRayFrames;
        else
            player->aniFrames = Player->miracleRayFrames;
    }

    if (player->characterID == ID_AMY && player->miracleState) {
        if (player->isChibi)
            player->aniFrames = SizeLaser->miracleAmyFrames;
        else
            player->aniFrames = Player->miracleAmyFrames;
    }

    if (player->characterID != ID_TAILS) {
        if (addendumOptions->spindashType == SPINDASHTYPE_CD) {
            for (int32 s = 0; s < 16; ++s) {
                SpriteFrame *dst = RSDK.GetFrame(player->aniFrames, ANI_SPINDASH, s);
                SpriteFrame *src = RSDK.GetFrame(player->aniFrames, 55, s);

                *dst = *src;
            }
        }
    }

#if MANIA_USE_PLUS
    if (emeraldMasks == 0xFF) {
        player->superState = SUPERSTATE_SUPER;
        Player_UpdatePhysicsState(player);
    }
    else {
#endif
        if (player->isChibi)
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_JUMP, &player->animator, true, 0);
        else
            RSDK.SetSpriteAnimation(player->aniFrames, 56, &player->animator, true, 0);

#if GAME_VERSION != VER_100
        player->superInvulnTimer = 60;
        player->invincibleTimer  = 1;
#endif
        player->velocity.x      = 0;
        player->velocity.y      = 0;
        player->groundVel       = 0;
        player->onGround        = false;
        player->nextAirState    = StateMachine_None;
        player->nextGroundState = StateMachine_None;
        player->interaction     = false;
        if (player->animator.frameID == 9)
            player->state = Player_State_Transform;
#if GAME_VERSION != VER_100
        player->isTransforming = true;
#endif
#if MANIA_USE_PLUS
        if (!ERZStart && globals->superMusicEnabled)
            Music_FadeOut(0.8);
#else
        if (!ERZStart)
            Music_TransitionTrack(TRACK_SUPER, 0.04);
#endif
        player->jumpAbilityState = 0;
        player->superState       = SUPERSTATE_FADEIN;

#if MANIA_USE_PLUS
    }
#endif

    player->superBlendAmount   = 0;
    player->superBlendState    = 0;
    player->superRingLossTimer = player->miracleState ? 80 : 60;
    player->timer              = 0;
    return true;
}
void Player_BlendSuperSonicColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 2;
                else
                    self->superBlendAmount -= 4;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->superBlendState & 1) {
                if (self->superBlendAmount <= 0)
                    self->superBlendState &= ~1;
                else {
                    if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                        self->superBlendAmount -= 2;
                    else
                        self->superBlendAmount -= 4;
                }
            }
            else {
                if (self->superBlendAmount >= 256) {
                    self->superBlendState |= 1;

                    if (self->superBlendState == 1) {
                        if (self->miracleState) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[13]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[14]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[0]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[1]);
                            }
                        }
                        self->superBlendState  = 2;
                        self->superBlendAmount = 0;
                    }
                }
                else {
                    if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                        self->superBlendAmount += 2;
                    else
                        self->superBlendAmount += 4;
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_SONIC, (PLAYER_PALETTE_INDEX_SONIC + PLAYER_PRIMARY_COLOR_COUNT) - 1);
    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, 109, 110);
}
void Player_BlendSuperTailsColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 2;
                else
                    self->superBlendAmount -= 4;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->miracleState) {
                if (self->superBlendState & 1) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState &= ~1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 2;
                        else
                            self->superBlendAmount -= 4;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256) {
                        self->superBlendState |= 1;

                        if (self->superBlendState == 1) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            self->superBlendState  = 2;
                            self->superBlendAmount = 0;
                        }
                    }
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 2;
                        else
                            self->superBlendAmount += 4;
                    }
                }
            }
            else {
                if (self->superBlendState) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState = 0;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 2;
                        else
                            self->superBlendAmount -= 4;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256)
                        self->superBlendState = 1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 2;
                        else
                            self->superBlendAmount += 4;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_TAILS, (PLAYER_PALETTE_INDEX_TAILS + PLAYER_PRIMARY_COLOR_COUNT) - 1);
}
void Player_BlendSuperKnuxColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 2;
                else
                    self->superBlendAmount -= 4;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->miracleState) {
                if (self->superBlendState & 1) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState &= ~1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 2;
                        else
                            self->superBlendAmount -= 4;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256) {
                        self->superBlendState |= 1;

                        if (self->superBlendState == 1) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            self->superBlendState  = 2;
                            self->superBlendAmount = 0;
                        }
                    }
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 2;
                        else
                            self->superBlendAmount += 4;
                    }
                }
            }
            else {
                if (self->superBlendState) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState = 0;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 2;
                        else
                            self->superBlendAmount -= 4;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256)
                        self->superBlendState = 1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 2;
                        else
                            self->superBlendAmount += 4;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_KNUX, (PLAYER_PALETTE_INDEX_KNUX + PLAYER_PRIMARY_COLOR_COUNT) - 1);
}
#if MANIA_USE_PLUS
void Player_BlendSuperMightyColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 2;
                else
                    self->superBlendAmount -= 4;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->miracleState) {
                if (self->superBlendState & 1) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState &= ~1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 2;
                        else
                            self->superBlendAmount -= 4;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256) {
                        self->superBlendState |= 1;

                        if (self->superBlendState == 1) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            self->superBlendState  = 2;
                            self->superBlendAmount = 0;
                        }
                    }
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 2;
                        else
                            self->superBlendAmount += 4;
                    }
                }
            }
            else {
                if (self->superBlendState) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState = 0;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 2;
                        else
                            self->superBlendAmount -= 4;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256)
                        self->superBlendState = 1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 2;
                        else
                            self->superBlendAmount += 4;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_MIGHTY, (PLAYER_PALETTE_INDEX_MIGHTY + PLAYER_PRIMARY_COLOR_COUNT) - 1);
}
void Player_BlendSuperRayColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 2;
                else
                    self->superBlendAmount -= 4;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->miracleState) {
                if (self->superBlendState & 1) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState &= ~1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 2;
                        else
                            self->superBlendAmount -= 4;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256) {
                        self->superBlendState |= 1;

                        if (self->superBlendState == 1) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                            self->superBlendState  = 2;
                            self->superBlendAmount = 0;
                        }
                    }
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 2;
                        else
                            self->superBlendAmount += 4;
                    }
                }
            }
            else {
                if (self->superBlendState) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState = 0;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 2;
                        else
                            self->superBlendAmount -= 4;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256)
                        self->superBlendState = 1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 2;
                        else
                            self->superBlendAmount += 4;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_RAY, (PLAYER_PALETTE_INDEX_RAY + (PLAYER_PRIMARY_COLOR_COUNT + 1)));
}
void Player_BlendSuperAmyColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 2;
                else
                    self->superBlendAmount -= 4;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->superBlendState & 1) {
                if (self->superBlendAmount <= 0)
                    self->superBlendState &= ~1;
                else
                    self->superBlendAmount -= 4;
            }
            else {
                if (self->superBlendAmount >= 256) {
                    self->superBlendState |= 1;

                    if (self->superBlendState == 1) {
                        if (self->miracleState) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        self->superBlendState  = 2;
                        self->superBlendAmount = 0;
                    }
                }
                else {
                    if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                        self->superBlendAmount += 2;
                    else
                        self->superBlendAmount += 4;
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_AMY, (PLAYER_PALETTE_INDEX_AMY + PLAYER_PRIMARY_COLOR_COUNT) - 1);
}
#endif
void Player_HandleSuperForm(void)
{
    RSDK_THIS(Player);
    int32 hyperColor = self->hyperBlendState;

    if (self->superState != SUPERSTATE_NONE) {
        switch (self->characterID) {
            case ID_SONIC:
                if (self->hyperState)
                    Player_BlendHyperSonicColors(0);
                else
                    Player_BlendSuperSonicColors(0);

                if (FarPlane) {
                    RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_SONIC, 3, PLAYER_PALETTE_INDEX_SONIC, PLAYER_PRIMARY_COLOR_COUNT);
                }
                else if (OOZSetup) {
                    RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_SONIC, 1, PLAYER_PALETTE_INDEX_SONIC, PLAYER_PRIMARY_COLOR_COUNT);
                    RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_SONIC, 2, PLAYER_PALETTE_INDEX_SONIC, PLAYER_PRIMARY_COLOR_COUNT);
                }
                else if (HCZSetup) {
                    if (self->superBlendState >= 2) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_HCZ[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[1][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[13]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[14]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[2]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[3]);
                            }
                        }
                    }
                    else {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_HCZ[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[7 + hyperColor]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[13]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[2]);
                            }
                        }
                    }

                    if (self->hyperState)
                        Player_BlendHyperSonicColors(1);
                    else
                        Player_BlendSuperSonicColors(1);

                    if (self->superBlendState >= 2) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[7 + hyperColor]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[6]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[13]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[14]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[0]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[1]);
                            }
                        }
                    }
                    else {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[7 + hyperColor]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[13]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[0]);
                            }
                        }
                    }
                }
                else if (CPZSetup) {
                    if (self->superBlendState >= 2) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_CPZ[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[2][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[13]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[14]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[4]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[5]);
                            }
                        }
                    }
                    else {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_CPZ[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[13]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[4]);
                            }
                        }
                    }

                    if (self->hyperState)
                        Player_BlendHyperSonicColors(2);
                    else
                        Player_BlendSuperSonicColors(2);

                    if (self->superBlendState >= 2) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[7 + hyperColor]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[6]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[13]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[14]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, Player->superExtras[0]);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[1]);
                            }
                        }
                    }
                    else {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[7 + hyperColor]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(6, 109, 0x000000);
                                RSDK.SetPaletteEntry(7, 109, Player->superExtras[0]);
                            }
                        }
                    }
                }
                break;

            case ID_TAILS:
                if (self->hyperState)
                    Player_BlendHyperTailsColors(0);
                else
                    Player_BlendSuperTailsColors(0);

                if (self->hyperState) {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 3, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 1, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 2, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, hyperPaletteWhite[1][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendHyperTailsColors(1);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                    else if (CPZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, hyperPaletteWhite[2][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendHyperTailsColors(2);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                }
                else if (self->miracleState) {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 3, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 1, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 2, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }

                        Player_BlendSuperTailsColors(1);

                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                    else if (CPZSetup) {
                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }

                        Player_BlendSuperTailsColors(2);

                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                }
                else {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 3, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 1, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_TAILS, 2, PLAYER_PALETTE_INDEX_TAILS, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendSuperTailsColors(1);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                    else if (CPZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendSuperTailsColors(2);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                }
                break;

            case ID_KNUCKLES:
                if (self->hyperState)
                    Player_BlendHyperKnuxColors(0);
                else
                    Player_BlendSuperKnuxColors(0);

                if (self->hyperState) {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 3, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 1, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 2, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, hyperPaletteWhite[1][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendHyperKnuxColors(1);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                    else if (CPZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, hyperPaletteWhite[2][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendHyperKnuxColors(2);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                }
                else if (self->miracleState) {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 3, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 1, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 2, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }

                        Player_BlendSuperKnuxColors(1);

                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                    else if (CPZSetup) {
                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }

                        Player_BlendSuperKnuxColors(2);

                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                }
                else {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 3, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 1, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_KNUX, 2, PLAYER_PALETTE_INDEX_KNUX, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendSuperKnuxColors(1);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                    else if (CPZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendSuperKnuxColors(2);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                }
                break;

#if MANIA_USE_PLUS
            case ID_MIGHTY:
                if (self->hyperState)
                    Player_BlendHyperMightyColors(0);
                else
                    Player_BlendSuperMightyColors(0);

                if (self->hyperState) {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 3, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 1, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 2, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, hyperPaletteWhite[1][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendHyperMightyColors(1);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                    else if (CPZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, hyperPaletteWhite[2][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendHyperMightyColors(2);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                }
                else if (self->miracleState) {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 3, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 1, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 2, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }

                        Player_BlendSuperMightyColors(1);

                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                    else if (CPZSetup) {
                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }

                        Player_BlendSuperMightyColors(2);

                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                }
                else {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 3, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 1, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_MIGHTY, 2, PLAYER_PALETTE_INDEX_MIGHTY, PLAYER_PRIMARY_COLOR_COUNT);
                    }
                    else if (HCZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendSuperMightyColors(1);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                    else if (CPZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }

                        Player_BlendSuperMightyColors(2);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                    }
                }
                break;

            case ID_RAY:
                if (self->hyperState)
                    Player_BlendHyperRayColors(0);
                else
                    Player_BlendSuperRayColors(0);

                if (self->hyperState) {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 3, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 1, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 2, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                    }
                    else if (HCZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_HCZ[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, hyperPaletteWhite_Ray[1][(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        }

                        Player_BlendHyperRayColors(1);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, hyperPaletteWhite_Ray[0][(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        }
                    }
                    else if (CPZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_CPZ[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, hyperPaletteWhite_Ray[2][(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        }

                        Player_BlendHyperRayColors(2);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, hyperPaletteWhite_Ray[0][(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        }
                    }
                }
                else if (self->miracleState) {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 3, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 1, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 2, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                    }
                    else if (HCZSetup) {
                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_HCZ[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_HCZ[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_HCZ[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_HCZ[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                        }

                        Player_BlendSuperRayColors(1);

                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                        }
                    }
                    else if (CPZSetup) {
                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_CPZ[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_CPZ[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_CPZ[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray_CPZ[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                        }

                        Player_BlendSuperRayColors(2);

                        if (self->superBlendState >= 2) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                        }
                        else {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                        }
                    }
                }
                else {
                    if (FarPlane) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 3, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                    }
                    else if (OOZSetup) {
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 1, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                        RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_RAY, 2, PLAYER_PALETTE_INDEX_RAY, PLAYER_PRIMARY_COLOR_COUNT + 1);
                    }
                    else if (HCZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_HCZ[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_HCZ[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        }

                        Player_BlendSuperRayColors(1);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        }
                    }
                    else if (CPZSetup) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_CPZ[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray_CPZ[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        }

                        Player_BlendSuperRayColors(2);

                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        }
                    }
                }
                break;

            case ID_AMY:
                if (self->hyperState)
                    Player_BlendHyperAmyColors(0);
                else
                    Player_BlendSuperAmyColors(0);

                if (FarPlane) {
                    RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_AMY, 3, PLAYER_PALETTE_INDEX_AMY, PLAYER_PRIMARY_COLOR_COUNT);
                }
                else if (OOZSetup) {
                    RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_AMY, 1, PLAYER_PALETTE_INDEX_AMY, PLAYER_PRIMARY_COLOR_COUNT);
                    RSDK.CopyPalette(0, PLAYER_PALETTE_INDEX_AMY, 2, PLAYER_PALETTE_INDEX_AMY, PLAYER_PRIMARY_COLOR_COUNT);
                }
                else if (HCZSetup) {
                    if (self->superBlendState >= 2) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, hyperPaletteWhite[1][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                    else {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_HCZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }

                    if (self->hyperState)
                        Player_BlendHyperAmyColors(1);
                    else
                        Player_BlendSuperAmyColors(1);

                    if (self->superBlendState >= 2) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                    else {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                }
                else if (CPZSetup) {
                    if (self->superBlendState >= 2) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, hyperPaletteWhite[2][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                    else {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy_CPZ[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }

                    if (self->hyperState)
                        Player_BlendHyperAmyColors(2);
                    else
                        Player_BlendSuperAmyColors(2);

                    if (self->superBlendState >= 2) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                    else {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            if (self->hyperState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else if (self->miracleState) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            else {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                        }
                    }
                }
                break;
#endif
        }
    }

    if (self->superState == SUPERSTATE_SUPER) {
        bool32 canStopSuper = false;
        if (!canStopSuper) {
            self->superInvulnTimer = 60;
            self->invincibleTimer  = 0;
            if (--self->superRingLossTimer <= 0) {
                self->superRingLossTimer = self->miracleState ? 90 : 60;
                if (--self->rings <= 0) {
                    self->rings      = 0;
                    self->superState = SUPERSTATE_FADEOUT;
                }
            }
        }
    }

    if (self->superState == SUPERSTATE_FADEOUT) {
        switch (self->characterID) {
            case ID_SONIC:
                self->stateAbility = Player_JumpAbility_Sonic;
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    if (self->hyperState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[(hyperColor)][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(6, 109, 0x000000);
                        RSDK.SetPaletteEntry(7, 109, Player->superExtras[7 + hyperColor]);
                    }
                    else if (self->miracleState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->miraclePalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    else {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, Player->superPalette_Sonic[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                }
                self->superBlendAmount = 256;
                self->superBlendState  = 1;
                self->hyperBlendAmount = 64;
                self->hyperBlendState  = 0;
                self->hyperFadeInFinished = false;
                break;

            case ID_TAILS:
                self->stateAbility = Player_JumpAbility_Tails;
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    if (self->hyperState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    else if (self->miracleState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->miraclePalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    else {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                }
                self->superBlendAmount = 256;
                self->superBlendState  = 1;
                break;

            case ID_KNUCKLES:
                self->stateAbility = Player_JumpAbility_Knux;
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    if (self->hyperState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    if (self->miracleState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->miraclePalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    else {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                }
                self->superBlendAmount = 256;
                self->superBlendState  = 1;
                break;
#if MANIA_USE_PLUS
            case ID_MIGHTY:
                self->stateAbility = Player_JumpAbility_Mighty;
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    if (self->hyperState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    if (self->miracleState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->miraclePalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    else {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                }
                self->superBlendAmount = 256;
                self->superBlendState  = 1;
                break;

            case ID_RAY:
                self->stateAbility = Player_JumpAbility_Ray;
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT + 1; ++c) {
                    if (self->hyperState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                    }
                    if (self->miracleState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->miraclePalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                    }
                    else {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(1 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                    }
                }
                self->superBlendAmount = 256;
                self->superBlendState  = 1;
                break;

            case ID_AMY:
                self->stateAbility = Player_JumpAbility_Amy;
                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                    if (self->hyperState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    if (self->miracleState) {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->miraclePalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                    else {
                        RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(1 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                    }
                }
                self->superBlendAmount = 256;
                self->superBlendState  = 1;
                break;
#endif
            default: break;
        }

        if (ERZStart) {
            self->shield   = SHIELD_NONE;
            self->rotation = 0;
            if (self->state == ERZStart_State_PlayerSuperFly || self->state == ERZStart_State_PlayerRebound)
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_HURT, &self->animator, false, 0);
        }
        else {
            bool32 stopPlaying = true;
            foreach_active(Player, player)
            {
                if (player->superState == SUPERSTATE_SUPER)
                    stopPlaying = false;
            }

            if (stopPlaying) {
                Music_JingleFadeOut(TRACK_SUPER, true);
                Player->transformMusicNotPlaying = true;
            }

            if (self->state == ERZStart_State_PlayerSuperFly || self->state == ERZStart_State_PlayerRebound)
                self->state = Player_State_Air;
        }

        if (self->characterID == ID_SONIC) {
            if (self->isChibi)
                self->aniFrames = SizeLaser->sonicFrames;
            else
                self->aniFrames = Player->sonicFrames;
            if (!self->animator.animationID)
                self->animator.frameID = 0;

            RSDK.SetSpriteAnimation(self->aniFrames, self->animator.animationID, &self->animator, true, self->animator.frameID);
        }

        if (self->characterID == ID_TAILS) {
            if (self->isChibi) {
                self->aniFrames  = SizeLaser->tailsFrames;
                self->tailFrames = SizeLaser->tailFrames;
            }
            else {
                self->aniFrames  = Player->tailsFrames;
                self->tailFrames = Player->tailsTailsFrames;
            }
            if (!self->animator.animationID)
                self->animator.frameID = 0;

            RSDK.SetSpriteAnimation(self->aniFrames, self->animator.animationID, &self->animator, true, self->animator.frameID);
            RSDK.SetSpriteAnimation(self->tailFrames, self->animator.animationID, &self->animator, true, self->animator.frameID);
        }

        if (self->characterID == ID_KNUCKLES) {
            if (self->isChibi)
                self->aniFrames = SizeLaser->knuxFrames;
            else
                self->aniFrames = Player->knuxFrames;
            if (!self->animator.animationID)
                self->animator.frameID = 0;

            RSDK.SetSpriteAnimation(self->aniFrames, self->animator.animationID, &self->animator, true, self->animator.frameID);
        }

        if (self->characterID == ID_MIGHTY) {
            if (self->isChibi)
                self->aniFrames = SizeLaser->mightyFrames;
            else
                self->aniFrames = Player->mightyFrames;
            if (!self->animator.animationID)
                self->animator.frameID = 0;

            RSDK.SetSpriteAnimation(self->aniFrames, self->animator.animationID, &self->animator, true, self->animator.frameID);
        }

        if (self->characterID == ID_RAY) {
            if (self->isChibi)
                self->aniFrames = SizeLaser->rayFrames;
            else
                self->aniFrames = Player->rayFrames;
            if (!self->animator.animationID)
                self->animator.frameID = 0;

            RSDK.SetSpriteAnimation(self->aniFrames, self->animator.animationID, &self->animator, true, self->animator.frameID);
        }

        if (self->characterID == ID_AMY) {
            if (self->isChibi)
                self->aniFrames = SizeLaser->amyFrames;
            else
                self->aniFrames = Player->amyFrames;
            if (!self->animator.animationID)
                self->animator.frameID = 0;

            RSDK.SetSpriteAnimation(self->aniFrames, self->animator.animationID, &self->animator, true, self->animator.frameID);
        }

        self->invincibleTimer  = 0;
        self->superInvulnTimer = 0;

        if (self->shield)
            Player_ApplyShield(self);

        self->superState = SUPERSTATE_DONE;
        Player_UpdatePhysicsState(self);
    }
}
bool32 Player_CheckP2KeyPress(void)
{
    RSDK_THIS(Player);

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_ENCORE)
        return false;
#endif

#if GAME_VERSION != VER_100
    if (self->controllerID > CONT_P4 || Player->disableP2KeyCheck)
        return false;
#else
    if (self->controllerID > CONT_P4)
        return false;
#endif

    RSDKControllerState *controller = &ControllerInfo[self->controllerID];

    return controller->keyUp.down || controller->keyDown.down || controller->keyLeft.down || controller->keyRight.down || controller->keyA.down
           || controller->keyB.down || controller->keyC.down || controller->keyX.down;
}
EntityPlayer *Player_GetNearestPlayerX(void)
{
    RSDK_THIS_GEN();

    EntityPlayer *targetPlayer = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    int32 targetDistance       = 0x7FFFFFFF;

    foreach_active(Player, player)
    {
        int32 distX = abs(player->position.x - self->position.x);
        if (distX < targetDistance) {
            targetDistance = distX;
            targetPlayer   = player;
        }
    }

    return targetPlayer;
}
EntityPlayer *Player_GetNearestPlayer(void)
{
    RSDK_THIS_GEN();

    EntityPlayer *targetPlayer = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    int32 targetDistance       = 0x7FFFFFFF;

    foreach_active(Player, player)
    {
        int32 distX = abs(player->position.x - self->position.x);
        int32 distY = abs(player->position.y - self->position.y);
        if (distX + distY < targetDistance) {
            targetDistance = distX + distY;
            targetPlayer   = player;
        }
    }

    return targetPlayer;
}
#if MANIA_USE_PLUS
void Player_RemoveEncoreLeader(void)
{
    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

    if (globals->stock != ID_NONE) {
        int32 newCharacter = GET_STOCK_ID(1);
        Player_ChangeCharacter(sidekick, newCharacter);
        globals->playerID &= 0xFF;
        globals->playerID |= newCharacter << 8;
        globals->stock >>= 8;
    }
    else {
        globals->playerID &= 0xFF;
        destroyEntity(sidekick);
        sidekick->playerID = 1;
    }
}
#endif
void Player_ResetBoundaries(EntityPlayer *player)
{
    Vector2 size;

    int32 screen = RSDK.GetEntitySlot(player);
    RSDK.GetLayerSize(Zone->fgLayer[0], &size, true);

    Zone->cameraBoundsL[screen]      = 0;
    Zone->cameraBoundsR[screen]      = size.x;
    Zone->cameraBoundsT[screen]      = 0;
    Zone->cameraBoundsB[screen]      = size.y;
    Zone->playerBoundsL[screen]      = Zone->cameraBoundsL[screen] << 16;
    Zone->playerBoundsR[screen]      = Zone->cameraBoundsR[screen] << 16;
    Zone->playerBoundsT[screen]      = Zone->cameraBoundsT[screen] << 16;
    Zone->playerBoundsB[screen]      = Zone->cameraBoundsB[screen] << 16;
    Zone->deathBoundary[screen]      = Zone->cameraBoundsB[screen] << 16;
    Zone->playerBoundActiveT[screen] = true;
    Zone->playerBoundActiveT[screen] = false;

    if (player->camera) {
        player->camera->boundsL = Zone->cameraBoundsL[screen];
        player->camera->boundsR = Zone->cameraBoundsR[screen];
        player->camera->boundsT = Zone->cameraBoundsT[screen];
        player->camera->boundsB = Zone->cameraBoundsB[screen];
    }
}
void Player_HandleDeath(EntityPlayer *player)
{
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (player->sidekick) {
        player->respawnTimer = 0;

        EntityDust *dust  = CREATE_ENTITY(Dust, INT_TO_VOID(1), player->position.x, player->position.y);
        dust->visible     = false;
        dust->active      = ACTIVE_NEVER;
        dust->isPermanent = true;
        dust->position.y  = (ScreenInfo->position.y - 128) << 16;

        // Sidekicks just respawn, no biggie
#if MANIA_USE_PLUS
        EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        if (globals->gameMode != MODE_ENCORE || (leader->state != Player_State_Death && leader->state != Player_State_Drown)) {
            if (addendumOptions->coopStyle > COOPSTYLE_MANIA) {
                EntityExplosion *explosion = CREATE_ENTITY(Explosion, INT_TO_VOID(EXPLOSION_ENEMY), leader->position.x, leader->position.y);
                player->angle      = leader->angle;
                player->state      = Player_State_Air;
                player->nextAirState    = StateMachine_None;
                player->nextGroundState = StateMachine_None;
                player->position.x = leader->position.x;
                player->position.y = leader->position.y;
                player->groundVel  = leader->groundVel;
                player->drawGroup  = Zone->playerDrawGroup[0];
                player->drownTimer = 0;
                player->tileCollisions = TILECOLLISION_DOWN;
                player->interaction    = true;
                player->active     = ACTIVE_NORMAL;
                player->camera->position.x = leader->camera->position.x;
                player->camera->position.y = leader->camera->position.y;
            }
            else {
                player->angle            = 0x80;
                player->state            = Player_State_HoldRespawn;
                player->abilityPtrs[0]   = dust;
                player->abilityValues[0] = 0;
                player->nextAirState     = StateMachine_None;
                player->nextGroundState  = StateMachine_None;
                player->stateInput       = Player_Input_P2_Delay;
                player->position.x       = -0x400000;
                player->position.y       = -0x400000;
                player->velocity.x       = 0;
                player->velocity.y       = 0;
                player->groundVel        = 0;
                player->tileCollisions   = TILECOLLISION_NONE;
                player->interaction      = false;
                player->drawGroup        = Zone->playerDrawGroup[1];
                player->drownTimer       = 0;
                player->active           = ACTIVE_NORMAL;
            }
        }
        else {
            player->state      = Player_State_EncoreRespawn;
            player->velocity.x = 0;
            player->velocity.y = 0;
            player->position.x = -0x200000;
            player->position.y = -0x200000;
        }
#else
        player->angle = 0x80;
        player->state = Player_State_HoldRespawn;
        player->abilityPtrs[0] = dust;
        player->abilityValues[0] = 0;
        player->nextAirState = StateMachine_None;
        player->nextGroundState = StateMachine_None;
        player->stateInput = Player_Input_P2_Delay;
        player->position.x = -0x400000;
        player->position.y = -0x400000;
        player->velocity.x = 0;
        player->velocity.y = 0;
        player->groundVel = 0;
        player->tileCollisions = TILECOLLISION_NONE;
        player->interaction = false;
        player->drawGroup = Zone->playerDrawGroup[1];
        player->drownTimer = 0;
        player->active = ACTIVE_NORMAL;
#endif
    }
    else {
#if MANIA_USE_PLUS
        // if we're in encore mode AND can swap to the next player, just do that
        if (globals->gameMode == MODE_ENCORE && Player_SwapMainPlayer(false)) {
            EntityPlayer *player2 = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

            globals->characterFlags &= ~(1 << HUD_CharacterIndexFromID(player2->characterID));

            if (player->state == Player_State_FlyToPlayer || player->state == Player_State_ReturnToPlayer
                || player->state == Player_State_HoldRespawn) {
                if (!EncoreIntro) {
                    Player_HandleQuickRespawn(player);
                    Player_ResetBoundaries(player);
                }

                Player_RemoveEncoreLeader();
            }
            else {
                player->blinkTimer   = 120;
                player->scrollDelay  = 0;
                EntityCamera *camera = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
                player->camera       = camera;
                camera->target       = (Entity *)player;
                camera->state        = Camera_State_FollowXY;
                Player_RemoveEncoreLeader();
            }
        }
        else { // regular death event
#endif
            if (player->lives > 0 && globals->gameMode != MODE_TIMEATTACK && addendumOptions->lifeSystem != LIFESYSTEM_INFINITE)
                player->lives--;
            Player->savedLives                      = player->lives;
            Player->savedScore                      = player->score;
            Player->savedScore1UP                   = player->score1UP;
            globals->restartLives[player->playerID] = player->lives;

#if MANIA_USE_PLUS
            if (globals->gameMode != MODE_ENCORE) {
                player->rings            = 0;
                player->ringExtraLife    = 0;
                globals->restartRings[RSDK.GetEntitySlot(player)] = 0;
                globals->restart1UP      = 100;
            }
#else
        player->rings = 0;
        player->ringExtraLife = 0;
        globals->restartRings = 0;
        globals->restart1UP = 100;
#endif
            globals->coolBonus[player->playerID] = 0;

            EntityCompetitionSession *session = CompetitionSession_GetSession();
            if (globals->gameMode == MODE_COMPETITION)
                session->lives[player->playerID] = player->lives;

#if MANIA_USE_PLUS
            if (globals->gameMode != MODE_ENCORE) {
#endif
                if (player->lives) {
                    if (Zone->gotTimeOver) {
                        // Time Over!!
                        player->classID = TYPE_BLANK;
                        RSDK.ResetEntitySlot(SLOT_GAMEOVER, GameOver->classID, INT_TO_VOID(true));

                        SaveRAM *saveRAM = SaveGame_GetSaveRAM();
                        if (globals->gameMode == MODE_COMPETITION) {
                            int32 playerID                    = RSDK.GetEntitySlot(player);
                            if (!session->finishState[playerID]) {
                                CompSession_DeriveWinner(playerID, FINISHTYPE_GAMEOVER);
                            }
#if MANIA_USE_PLUS
                            foreach_all(HUD, hud) { hud->vsStates[RSDK.GetEntitySlot(player)] = HUD_State_MoveOut; }
#endif
                        }
                        else if (saveRAM) {
                            saveRAM->lives    = player->lives;
                            saveRAM->score    = player->score;
                            saveRAM->score1UP = player->score1UP;
#if MANIA_USE_PLUS
                            saveRAM->continues = globals->continues;
                            if (globals->gameMode == MODE_ENCORE) {
                                globals->playerID &= 0xFF;
                                saveRAM->playerID = globals->playerID;

                                globals->characterFlags &= ~(1 << HUD_CharacterIndexFromID(player->characterID));

                                saveRAM->characterFlags = globals->characterFlags;
                                saveRAM->stock          = globals->stock;
                            }
#endif

                            SaveGame_SaveFile(StateMachine_None);
                        }

                        EntityGameOver *gameOver = RSDK_GET_ENTITY(SLOT_GAMEOVER, GameOver);
                        gameOver->playerID       = RSDK.GetEntitySlot(player);
                        GameOver->activeScreens |= 1 << player->playerID;
                        RSDK.SetEngineState(ENGINESTATE_FROZEN);
                        SceneInfo->timeEnabled = false;
                    }
                    else if (globals->gameMode != MODE_COMPETITION) {
                        // Regular Death, fade out and respawn
                        SaveRAM *saveRAM = SaveGame_GetSaveRAM();
                        if (saveRAM) {
                            saveRAM->lives    = player->lives;
                            saveRAM->score    = player->score;
                            saveRAM->score1UP = player->score1UP;
#if MANIA_USE_PLUS
                            saveRAM->continues = globals->continues;
                            if (globals->gameMode == MODE_ENCORE) {
                                globals->playerID &= 0xFF;
                                saveRAM->playerID = globals->playerID;

                                globals->characterFlags &= ~(1 << HUD_CharacterIndexFromID(player->characterID));

                                saveRAM->characterFlags = globals->characterFlags;
                                saveRAM->stock          = globals->stock;
                            }
#endif
                            SaveGame_SaveFile(StateMachine_None);
                        }

                        if (globals->gameMode == MODE_MANIA && addendumOptions->coopStyle > COOPSTYLE_MANIA && addendumVar->playerCount > 1) {
                            Player_HandleQuickRespawn(player);
                        }
                        else {
                            Music_FadeOut(0.025);
                            Zone_StartFadeOut_MusicFade(10, 0x000000);
                            player->classID = TYPE_BLANK;
                        }
                    }
                    else {
                        // Competition (or encore) death, do a quick respawn
                        Player_HandleQuickRespawn(player);
#if MANIA_USE_PLUS
                        if (!player->playerID && globals->gameMode == MODE_ENCORE)
                            Player_HandleQuickRespawn(RSDK_GET_ENTITY(SLOT_PLAYER2, Player));
#endif
                    }
                }
                else {
                    // GGGGGGGame Over...!
                    int32 screenID  = 0;
                    player->classID = TYPE_BLANK;
                    if (player->camera) {
                        screenID               = player->camera->screenID;
                        player->camera->target = (Entity *)player->camera;
                    }

                    bool32 showGameOver = true;
                    if (globals->gameMode == MODE_COMPETITION) {
                        showGameOver                      = false;
                        int32 playerID                    = RSDK.GetEntitySlot(player);
                        if (!session->finishState[playerID]) {
                            CompSession_DeriveWinner(playerID, FINISHTYPE_GAMEOVER);
                            showGameOver = !MANIA_USE_PLUS;
                        }
#if MANIA_USE_PLUS
                        foreach_all(HUD, hud) { hud->vsStates[RSDK.GetEntitySlot(player)] = HUD_State_MoveOut; }
#endif
                    }

                    if (showGameOver) {
                        EntityGameOver *gameOver = RSDK_GET_ENTITY(SLOT_GAMEOVER, GameOver);
                        RSDK.ResetEntity(gameOver, GameOver->classID, INT_TO_VOID(false));
                        gameOver->playerID = RSDK.GetEntitySlot(player);
                        GameOver->activeScreens |= 1 << screenID;
                        if (!(globals->gameMode == MODE_MANIA && addendumOptions->coopStyle > COOPSTYLE_MANIA && addendumVar->playerCount > 1)) {
                            RSDK.SetEngineState(ENGINESTATE_FROZEN);
                            SceneInfo->timeEnabled = false;
                        }
                    }
                }

                if (player->classID == Player->classID) {
                    player->abilityValues[0] = 0;
                    Player_ResetBoundaries(player);

                    if (BoundsMarker)
                        BoundsMarker_ApplyAllBounds(player, true);
                }
#if MANIA_USE_PLUS
            }
            else {
                // Encore death, lets switch to the next character and be on our way if possible
                globals->characterFlags &= ~(1 << HUD_CharacterIndexFromID(player->characterID));

                if (!globals->characterFlags) {
                    int32 screenID  = 0;
                    player->classID = TYPE_BLANK;
                    if (player->camera) {
                        screenID               = player->camera->screenID;
                        player->camera->target = (Entity *)player->camera;
                    }

                    EntityGameOver *gameOver = RSDK_GET_ENTITY(SLOT_GAMEOVER, GameOver);
                    RSDK.ResetEntity(gameOver, GameOver->classID, INT_TO_VOID(false));
                    gameOver->playerID = RSDK.GetEntitySlot(player);
                    GameOver->activeScreens |= 1 << screenID;
                    RSDK.SetEngineState(ENGINESTATE_FROZEN);
                    SceneInfo->timeEnabled = false;

                    if (player->classID == Player->classID) {
                        player->abilityValues[0] = 0;
                        Player_ResetBoundaries(player);
                        if (BoundsMarker)
                            BoundsMarker_ApplyAllBounds(player, true);
                    }
                }
                else {
                    EntityPlayer *player2 = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
                    player2->respawnTimer = 0;
                    Player_SwapMainPlayer(true);

                    if (globals->stock) {
                        Player_ChangeCharacter(player2, GET_STOCK_ID(1));
                        globals->stock >>= 8;
                    }
                    else {
                        globals->playerID &= 0xFF;
                        player2->classID = TYPE_BLANK;
                    }

                    // Bug Details
                    // if you somehow die (drowing is the easiest way) after getting a buddy in AIZ Encore
                    // the game will lock up since it cant do this behaviour
                    // Fix:
                    // remove this check for EncoreIntro and add a xboundary
                    // or maybe check for this and respawn both players anyways
                    // alternatively remove the water
                    if (!EncoreIntro) {
                        // Encore death, do a quick respawn
                        Player_HandleQuickRespawn(player);
                        if (!player->playerID && globals->gameMode == MODE_ENCORE)
                            Player_HandleQuickRespawn(RSDK_GET_ENTITY(SLOT_PLAYER2, Player));

                        if (player->classID == Player->classID) {
                            player->abilityValues[0] = 0;
                            Player_ResetBoundaries(player);
                            if (BoundsMarker)
                                BoundsMarker_ApplyAllBounds(player, true);
                        }
                    }
                }
            }
#endif
#if MANIA_USE_PLUS
        }
#endif
    }
}
void Player_HandleQuickRespawn(EntityPlayer *player)
{
    player->drawGroup      = Zone->playerDrawGroup[0];
    player->stateInput     = player->sidekick ? Player_Input_P2_AI : Player_Input_P1;
    player->tileCollisions = TILECOLLISION_DOWN;
    player->interaction    = true;
    player->collisionPlane = 0;
    player->onGround       = false;
    player->active         = ACTIVE_NORMAL;
    player->ringExtraLife  = 100;
    RSDK.SetSpriteAnimation(player->aniFrames, ANI_HURT, &player->animator, false, 0);
    int32 screen = RSDK.GetEntitySlot(player);

    player->position.x  = StarPost->playerPositions[screen].x;
    player->position.y  = StarPost->playerPositions[screen].y;
    player->direction   = StarPost->playerDirections[screen];
    player->scrollDelay = 0;
    if (player->camera) {
        player->camera->position.x = player->position.x;
        player->camera->position.y = player->position.y;
        player->camera->state      = Camera_State_FollowXY;
        Zone_ReloadScene(screen);
    }
    player->underwater = 0;

    Player_UpdatePhysicsState(player);
    player->drawFX &= ~FX_SCALE;
    player->scale.x = 0x200;
    player->scale.y = 0x200;
    player->state   = Player_State_Air;
}

// Collision
Hitbox *Player_GetHitbox(EntityPlayer *player)
{
    Hitbox *playerHitbox = RSDK.GetHitbox(&player->animator, 0);
    return playerHitbox ? playerHitbox : &Player_FallbackHitbox;
}
Hitbox *Player_GetAltHitbox(EntityPlayer *player)
{
    Hitbox *playerHitbox = RSDK.GetHitbox(&player->animator, 1);
    return playerHitbox ? playerHitbox : &Player_FallbackHitbox;
}

bool32 Player_CheckCollisionTouch(EntityPlayer *player, void *e, Hitbox *entityHitbox)
{
#if MANIA_USE_PLUS
    if (player->isGhost)
        return false;
#endif

    Hitbox *playerHitbox = player->outerbox ? player->outerbox : Player_GetHitbox(player);
    Entity *entity       = (Entity *)e;

    return RSDK.CheckObjectCollisionTouchBox(entity, entityHitbox, player, playerHitbox);
}
bool32 Player_CheckCollisionBox(EntityPlayer *player, void *e, Hitbox *entityHitbox)
{
#if MANIA_USE_PLUS
    if (player->isGhost)
        return C_NONE;
#endif

    Entity *entity       = (Entity *)e;
    Hitbox *playerHitbox = player->outerbox ? player->outerbox : Player_GetHitbox(player);

    switch (RSDK.CheckObjectCollisionBox(entity, entityHitbox, player, playerHitbox, true)) {
        default:
        case C_NONE: return C_NONE;

        case C_TOP: {
            player->controlLock   = 0;
            player->collisionMode = CMODE_FLOOR;

            int32 colPos[2];
            if (entity->direction & FLIP_X) {
                colPos[0] = entity->position.x - (entityHitbox->right << 16);
                colPos[1] = entity->position.x - (entityHitbox->left << 16);
            }
            else {
                colPos[0] = entity->position.x + (entityHitbox->left << 16);
                colPos[1] = entity->position.x + (entityHitbox->right << 16);
            }

            int32 sensorX1 = player->position.x + player->sensorX[0];
            int32 sensorX3 = player->position.x + player->sensorX[2];
            int32 sensorX2 = player->position.x + player->sensorX[1];
            int32 sensorX4 = player->position.x + player->sensorX[3];
            int32 sensorX5 = player->position.x + player->sensorX[4];

            if (sensorX1 >= colPos[0] && sensorX1 <= colPos[1])
                player->flailing |= 1;
            if (sensorX2 >= colPos[0] && sensorX2 <= colPos[1])
                player->flailing |= 2;
            if (sensorX3 >= colPos[0] && sensorX3 <= colPos[1])
                player->flailing |= 4;
            if (sensorX4 >= colPos[0] && sensorX4 <= colPos[1])
                player->flailing |= 8;
            if (sensorX5 >= colPos[0] && sensorX5 <= colPos[1])
                player->flailing |= 0x10;

            if (entity->velocity.y <= 0)
                player->collisionFlagV |= 1;
            return C_TOP;
        }

        case C_LEFT:
            player->controlLock = 0;
            if (player->left && player->onGround) {
                if (!(player->state == Player_State_Spindash || player->state == Player_State_Spindash_CD)) {
                    player->groundVel = -0x8000;
                    player->position.x &= 0xFFFF0000;
                }
            }
            return C_LEFT;

        case C_RIGHT:
            player->controlLock = 0;
            if (player->right && player->onGround)
                player->groundVel = 0x8000;
            return C_RIGHT;

        case C_BOTTOM: return C_BOTTOM;
    }
}
bool32 Player_CheckCollisionPlatform(EntityPlayer *player, void *e, Hitbox *entityHitbox)
{
#if MANIA_USE_PLUS
    if (player->isGhost)
        return false;
#endif

    Hitbox *playerHitbox = player->outerbox ? player->outerbox : Player_GetHitbox(player);
    Entity *entity       = (Entity *)e;

    if (RSDK.CheckObjectCollisionPlatform(entity, entityHitbox, player, playerHitbox, true)) {
        player->controlLock   = 0;
        player->collisionMode = CMODE_FLOOR;

        int32 colPos[2];
        if (entity->direction & FLIP_X) {
            colPos[0] = entity->position.x - (entityHitbox->right << 16);
            colPos[1] = entity->position.x - (entityHitbox->left << 16);
        }
        else {
            colPos[0] = entity->position.x + (entityHitbox->left << 16);
            colPos[1] = entity->position.x + (entityHitbox->right << 16);
        }

        int32 sensorX1 = player->position.x + player->sensorX[0];
        int32 sensorX3 = player->position.x + player->sensorX[2];
        int32 sensorX2 = player->position.x + player->sensorX[1];
        int32 sensorX4 = player->position.x + player->sensorX[3];
        int32 sensorX5 = player->position.x + player->sensorX[4];

        if (sensorX1 >= colPos[0] && sensorX1 <= colPos[1])
            player->flailing |= 0x01;
        if (sensorX2 >= colPos[0] && sensorX2 <= colPos[1])
            player->flailing |= 0x02;
        if (sensorX3 >= colPos[0] && sensorX3 <= colPos[1])
            player->flailing |= 0x04;
        if (sensorX4 >= colPos[0] && sensorX4 <= colPos[1])
            player->flailing |= 0x08;
        if (sensorX5 >= colPos[0] && sensorX5 <= colPos[1])
            player->flailing |= 0x10;

        if (entity->velocity.y <= 0)
            player->collisionFlagV |= 1;

        return true;
    }

    return false;
}

bool32 Player_Hurt(EntityPlayer *player, void *e)
{
    Entity *entity = (Entity *)e;

    if (player->state == Player_State_Hurt || player->state == Player_State_Death || player->state == Player_State_Drown || player->invincibleTimer
        || player->superInvulnTimer || player->blinkTimer > 0) {
        return false;
    }

    player->velocity.x = player->position.x > entity->position.x ? 0x20000 : -0x20000;
    Player_Hit(player);

    return true;
}
bool32 Player_HurtFlip(EntityPlayer *player)
{
    if (player->state == Player_State_Hurt || player->state == Player_State_Death || player->state == Player_State_Drown || player->invincibleTimer
        || player->superInvulnTimer || player->blinkTimer > 0) {
        return false;
    }

    player->velocity.x = player->direction != FLIP_NONE ? 0x20000 : -0x20000;
    Player_Hit(player);

    return true;
}
// Hits the player if not invulnerable and the player's shield doesn't match shield, returns true if player was hit
bool32 Player_ElementHurt(EntityPlayer *player, void *entity, int32 shield) { return player->shield != shield ? Player_Hurt(player, entity) : false; }
bool32 Player_CheckAttacking(EntityPlayer *player, void *e)
{
    Entity *entity   = (Entity *)e;
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();
    int32 anim       = player->animator.animationID;
    bool32 attacking = player->invincibleTimer != 0 || player->superInvulnTimer != 0 || anim == ANI_JUMP || anim == ANI_SPINDASH || anim == ANI_CDSPINDASH;
    switch (player->characterID) {
        case ID_SONIC: attacking |= anim == ANI_DROPDASH; break;
        case ID_TAILS:
            if (!attacking && entity) {
                attacking = anim == ANI_FLY || anim == ANI_FLY_TIRED || anim == ANI_FLY_LIFT;
                if (player->position.y <= entity->position.y)
                    return false;
            }
            break;
        case ID_KNUCKLES: attacking |= anim == ANI_GLIDE || anim == ANI_GLIDE_SLIDE; break;
#if MANIA_USE_PLUS
        case ID_MIGHTY: attacking |= anim == ANI_HAMMERDROP; break;
        case ID_RAY:
            if (addendumOptions->rayMoveset == RAYMOVESET_ADDENDUM)
                attacking |= (anim == ANI_FLY_UP && (abs(player->velocity.x) >= 0x80000 || abs(player->velocity.y) >= 0x80000)) || (anim == ANI_FLY_DOWN && (abs(player->velocity.x) >= 0x80000 || abs(player->velocity.y) >= 0x80000));
            break;
        case ID_AMY: attacking |= anim == ANI_HAMMER_HIT || anim == ANI_SPIN_JUMP || anim == ANI_HELI_HAMMER; break;
#endif
        default: break;
    }

    return attacking;
}
// This is identical to Player_CheckAttacking, except it's not checking for the player invincible timer.
bool32 Player_CheckAttackingNoInvTimer(EntityPlayer *player, void *e)
{
    Entity *entity   = (Entity *)e;
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();
    int32 anim       = player->animator.animationID;
    bool32 attacking = anim == ANI_JUMP || anim == ANI_SPINDASH || anim == ANI_CDSPINDASH;
    switch (player->characterID) {
        case ID_SONIC: attacking |= anim == ANI_DROPDASH; break;
        case ID_TAILS:
            if (!attacking && entity) {
                attacking = anim == ANI_FLY || anim == ANI_FLY_TIRED || anim == ANI_FLY_LIFT;
                if (player->position.y <= entity->position.y)
                    return false;
            }
            break;
        case ID_KNUCKLES: attacking |= anim == ANI_GLIDE || anim == ANI_GLIDE_SLIDE; break;
#if MANIA_USE_PLUS
        case ID_MIGHTY: attacking |= anim == ANI_HAMMERDROP; break;
        case ID_RAY:
            if (addendumOptions->rayMoveset == RAYMOVESET_ADDENDUM)
                attacking |= (anim == ANI_FLY_UP && (abs(player->velocity.x) >= 0x80000 || abs(player->velocity.y) >= 0x80000)) || (anim == ANI_FLY_DOWN && (abs(player->velocity.x) >= 0x80000 || abs(player->velocity.y) >= 0x80000));
            break;
        case ID_AMY: attacking |= anim == ANI_HAMMER_HIT || anim == ANI_SPIN_JUMP || anim == ANI_HELI_HAMMER; break;
#endif
        default: break;
    }

    return attacking;
}
bool32 Player_CheckBadnikTouch(EntityPlayer *player, void *e, Hitbox *entityHitbox)
{
    Entity *entity = (Entity *)e;
#if MANIA_USE_PLUS
    if (player->isGhost)
        return false;
#endif

    Hitbox *playerHitbox = Player_GetHitbox(player);
#if MANIA_USE_PLUS
    if (player->characterID == ID_MIGHTY && player->jumpAbilityState > 1) {
        Hitbox tempHitbox;

        if (player->isChibi) {
            tempHitbox.left  = -32;
            tempHitbox.right = 32;
        }
        else {
            tempHitbox.left  = -48;
            tempHitbox.right = 48;
        }

        tempHitbox.top    = 0;
        tempHitbox.bottom = playerHitbox->bottom + 16;
        if (RSDK.CheckObjectCollisionTouchBox(entity, entityHitbox, player, &tempHitbox))
            return true;
    }
#endif

    EntityShield *instaShield = RSDK_GET_ENTITY(13 + RSDK.GetEntitySlot(player), Shield);
    Hitbox tempHitbox;
    if (instaShield->classID == Shield->classID && instaShield->state == Shield_State_Insta) {
        tempHitbox.left   = -24;
        tempHitbox.top    = -24;
        tempHitbox.right  = 24;
        tempHitbox.bottom = 24;
        playerHitbox      = &tempHitbox;
    }

    if (player->hyperAttacking) {
        int32 attackType;
        switch (player->characterID) {
            case ID_SONIC: attackType = 0; break;
            case ID_TAILS: attackType = 1; break;
            case ID_KNUCKLES: attackType = 2; break;
            case ID_MIGHTY: attackType = 3; break;
            case ID_RAY: attackType = 4; break;
            case ID_AMY: attackType = 5; break;
        }

        if (entity->onScreen) {
            for (int32 i = 0; i < 0x80; ++i) {
                if (entity->classID == Zone->hyperAttackList[i].classID) {
                    switch (attackType) {
                        case 0:
                            if (Zone->hyperAttackList[i].hyperDashTarget)
                                return true;
                            break;

                        case 1: break;

                        case 2:
                            if (Zone->hyperAttackList[i].hyperQuakeTarget)
                                return true;
                            break;

                        case 3:
                            if (Zone->hyperAttackList[i].hyperSlamTarget)
                                return true;
                            break;

                        case 4:
                            if (Zone->hyperAttackList[i].hyperLandTarget)
                                return true;
                            break;

                        case 5:
                            if (Zone->hyperAttackList[i].hyperHammerTarget)
                                return true;
                            break;
                    }
                }
            }
        }
    }

    return RSDK.CheckObjectCollisionTouchBox(entity, entityHitbox, player, playerHitbox);
}
bool32 Player_CheckBadnikBreak(EntityPlayer *player, void *e, bool32 destroy)
{
    Entity *badnik = (Entity *)e;

    if (Player_CheckAttacking(player, badnik)) {
        BadnikHelpers_BadnikBreakUnseeded(badnik, false, true);

        if (Zone_GetZoneID() > ZONE_INVALID) {
            int32 characterID = 0;
            switch (player->characterID) {
                default: characterID = 0;
                case ID_SONIC: characterID = 1; break;
                case ID_TAILS: characterID = 2; break;
                case ID_KNUCKLES: characterID = 3; break;
#if MANIA_USE_PLUS
                case ID_MIGHTY: characterID = 4; break;
                case ID_RAY: characterID = 5; break;
                case ID_AMY: characterID = 6; break;
#endif
            }

#if MANIA_USE_PLUS
            StatInfo info;
            TimeAttackData_TrackEnemyDefeat(&info, Zone_GetZoneID(), Zone->actID, characterID, SceneInfo->filter == (FILTER_BOTH | FILTER_ENCORE),
                                            FROM_FIXED(badnik->position.x), FROM_FIXED(badnik->position.y));
            API.TryTrackStat(&info);
#else
            APICallback_TrackEnemyDefeat(Zone_GetZoneID(), Zone->actID, characterID, FROM_FIXED(badnik->position.x), FROM_FIXED(badnik->position.y));
#endif
        }

        int32 yVel = 0;
        if (player->velocity.y <= 0) {
            yVel = player->velocity.y + 0x10000;
        }
        else if (player->position.y >= badnik->position.y
#if MANIA_USE_PLUS
                 || (player->characterID == ID_MIGHTY && player->animator.animationID == ANI_HAMMERDROP)
#endif
        ) {
            yVel = player->velocity.y - 0x10000;
        }
        else {
            yVel = -(player->velocity.y + 2 * player->gravityStrength);
        }
        player->velocity.y = yVel;

        if (globals->gameMode != MODE_COMPETITION)
            player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

        EntityScoreBonus *scoreBonus = CREATE_ENTITY(ScoreBonus, NULL, badnik->position.x, badnik->position.y);
        scoreBonus->drawGroup        = Zone->objectDrawGroup[1];
        scoreBonus->animator.frameID = player->scoreBonus;

        switch (player->scoreBonus) {
            case 0: Player_GiveScore(player, 100); break;
            case 1: Player_GiveScore(player, 200); break;
            case 2: Player_GiveScore(player, 500); break;

            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14: Player_GiveScore(player, 1000); break;

            case 15: Player_GiveScore(player, 10000); break;

            default: break;
        }

        if (player->scoreBonus < 15)
            player->scoreBonus++;

        if (destroy) {
            destroyEntity(badnik);
            badnik->active = ACTIVE_DISABLED;
        }

        player->jumpAbilityState = 1;

        return true;
    }
#if MANIA_USE_PLUS
    else if (player->characterID == ID_MIGHTY && player->animator.animationID == ANI_CROUCH) {
        if (player->uncurlTimer)
            return false;

        RSDK.PlaySfx(Player->sfxPimPom, false, 255);

        player->uncurlTimer = 30;
        player->groundVel   = badnik->position.x > player->position.x ? -0x10000 : 0x10000;
    }
#endif
    else {
#if MANIA_USE_PLUS
        if (!player->uncurlTimer) {
#endif
            Player_Hurt(player, badnik);
#if MANIA_USE_PLUS
        }
#endif
    }

    return false;
}
bool32 Player_CheckBossHit(EntityPlayer *player, void *e)
{
    Entity *entity = (Entity *)e;

    if (player->hyperAttacking) {
        int32 attackType;
        switch (player->characterID) {
            case ID_SONIC: attackType = 0; break;
            case ID_TAILS: attackType = 1; break;
            case ID_KNUCKLES: attackType = 2; break;
            case ID_MIGHTY: attackType = 3; break;
            case ID_RAY: attackType = 4; break;
            case ID_AMY: attackType = 5; break;
        }

        for (int32 i = 0; i < 0x80; ++i) {
            if (entity->classID == Zone->hyperAttackList[i].classID) {
                switch (attackType) {
                    case 0:
                        if (Zone->hyperAttackList[i].hyperDashTarget)
                            return true;
                        break;

                    case 1: break;

                    case 2:
                        if (Zone->hyperAttackList[i].hyperQuakeTarget)
                            return true;
                        break;

                    case 3:
                        if (Zone->hyperAttackList[i].hyperSlamTarget)
                            return true;
                        break;

                    case 4:
                        if (Zone->hyperAttackList[i].hyperLandTarget)
                            return true;
                        break;

                    case 5:
                        if (Zone->hyperAttackList[i].hyperHammerTarget)
                            return true;
                        break;
                }
            }

            player->hyperAttacking = false;
        }
    }

    if (Player_CheckAttacking(player, entity)) {
        player->groundVel  = -player->groundVel;
        player->velocity.x = -player->velocity.x;
        player->velocity.y = -(player->velocity.y + 2 * player->gravityStrength);

        if (player->characterID == ID_KNUCKLES && player->animator.animationID == ANI_GLIDE) {
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_GLIDE_DROP, &player->animator, false, 0);
            player->state = Player_State_KnuxGlideDrop;
        }
        else {
#if MANIA_USE_PLUS
            if (player->state == Player_State_MightyHammerDrop || player->state == Player_State_RayGlide) {
                player->state = Player_State_Air;
                RSDK.SetSpriteAnimation(player->aniFrames, ANI_JUMP, &player->animator, false, 0);
                if (player->velocity.y < -0x40000)
                    player->velocity.y = -0x40000;
            }

            if (player->state == Player_State_AmyHeliHammer_Left || player->state == Player_State_AmyHeliHammer_Right) {
                player->state = Player_State_Air;
                RSDK.SetSpriteAnimation(player->aniFrames, ANI_FREE_FALL, &player->animator, false, 0);
                if (player->velocity.y < -0x40000)
                    player->velocity.y = -0x40000;
            }

            if (player->characterID == ID_AMY && player->animator.animationID == ANI_SPIN_JUMP) {
                player->state = Player_State_Air;
                RSDK.SetSpriteAnimation(player->aniFrames, ANI_FREE_FALL, &player->animator, false, 0);
                if (player->velocity.y < -0x40000)
                    player->velocity.y = -0x40000;
            }
#endif
        }

        return true;
    }
    else {
        Player_Hurt(player, entity);
    }

    return false;
}
bool32 Player_ProjectileHurt(EntityPlayer *player, void *p)
{
    Entity *projectile = (Entity *)p;

    bool32 deflected = false;
#if MANIA_USE_PLUS
    if (player->characterID == ID_MIGHTY) {
        int32 anim = player->animator.animationID;
        if (anim == ANI_CROUCH || anim == ANI_JUMP || anim == ANI_SPINDASH || anim == ANI_HAMMERDROP)
            deflected = true;
    }
#endif

    if (player->shield > SHIELD_BLUE || deflected) {
#if MANIA_USE_PLUS
        if (deflected)
            RSDK.PlaySfx(Player->sfxMightyDeflect, false, 0xFE);
#endif

        int32 angle             = RSDK.ATan2(player->position.x - projectile->position.x, player->position.y - projectile->position.y);
        projectile->velocity.x  = -0x800 * RSDK.Cos256(angle);
        projectile->velocity.y  = -0x800 * RSDK.Sin256(angle);
        projectile->interaction = false;
        return true;
    }

    Player_Hurt(player, projectile);

    return false;
}
#if MANIA_USE_PLUS
bool32 Player_CheckMightyShellHit(EntityPlayer *player, void *e, int32 velX, int32 velY)
{
    Entity *entity = (Entity *)e;

    if (player->characterID == ID_MIGHTY
        && (player->animator.animationID == ANI_CROUCH || player->animator.animationID == ANI_JUMP || player->animator.animationID == ANI_SPINDASH
            || player->animator.animationID == ANI_HAMMERDROP)) {
        if (!player->uncurlTimer) {
            RSDK.PlaySfx(Player->sfxPimPom, false, 255);
            player->uncurlTimer = 30;
        }

        int32 angle        = RSDK.ATan2(player->position.x - entity->position.x, player->position.y - entity->position.y);
        entity->velocity.x = velX * RSDK.Cos256(angle);
        entity->velocity.y = velY * RSDK.Sin256(angle);
        return true;
    }

    return false;
}
#endif
bool32 Player_CheckItemBreak(EntityPlayer *player, void *e, bool32 hitIfNotAttacking)
{
    Entity *entity = (Entity *)e;
#if MANIA_USE_PLUS
    int32 anim      = player->animator.animationID;
    int32 character = player->characterID;
#endif

    if (Player_CheckAttacking(player, entity)) {
        if (player->velocity.y <= 0) {
            player->velocity.y += 0x10000;
            return true;
        }
        else if (player->position.y >= entity->position.y
#if MANIA_USE_PLUS
                 || (character == ID_MIGHTY && anim == ANI_HAMMERDROP)
#endif
        ) {
            player->velocity.y -= 0x10000;
            return true;
        }
        else {
            player->velocity.y = -(player->velocity.y + 2 * player->gravityStrength);
            return true;
        }
    }
    else {
        if (hitIfNotAttacking) {
#if MANIA_USE_PLUS
            if (!(character == ID_MIGHTY && anim == ANI_CROUCH)) {
#endif
                Player_Hurt(player, entity);
#if MANIA_USE_PLUS
            }
#endif
        }
        return false;
    }
}

// Player State Helpers
void Player_UpdatePhysicsState(EntityPlayer *entity)
{
    int32 *tablePtr = NULL;
    switch (entity->characterID) {
        default:
        case ID_SONIC:
            if (entity->hyperState)
                tablePtr = Player->hyperPhysicsTable;
            else
                tablePtr = Player->sonicPhysicsTable;
            break;
        case ID_TAILS:
            if (entity->hyperState)
                tablePtr = Player->hyperPhysicsTable;
            else
                tablePtr = Player->tailsPhysicsTable;
            break;
        case ID_KNUCKLES:
            if (entity->hyperState)
                tablePtr = Player->hyperKnuxPhysicsTable;
            else
                tablePtr = Player->knuxPhysicsTable;
            break;
#if MANIA_USE_PLUS
        case ID_MIGHTY:
            if (entity->hyperState)
                tablePtr = Player->hyperPhysicsTable;
            else
                tablePtr = Player->mightyPhysicsTable;
            break;
        case ID_RAY:
            if (entity->hyperState)
                tablePtr = Player->hyperPhysicsTable;
            else
                tablePtr = Player->rayPhysicsTable;
            break;
        case ID_AMY:
            if (entity->hyperState)
                tablePtr = Player->hyperPhysicsTable;
            else
                tablePtr = Player->mightyPhysicsTable;
            break;
#endif
    }

    int32 tablePos = 0;
    if (entity->underwater) {
        entity->gravityStrength = 0x2000;
        tablePos                = 1;
        if (entity->speedShoesTimer >= 0)
            entity->gravityStrength = 0x1000;
    }
    else {
        entity->gravityStrength = 0x5800;
        if (entity->speedShoesTimer >= 0)
            entity->gravityStrength = 0x3800;
    }

    int32 decelShift = 0;
    if (entity->superState == SUPERSTATE_SUPER) {
        tablePos |= 2;
        decelShift = 2;
    }

    if (entity->speedShoesTimer > 0) {
        tablePos |= 4;
        decelShift = 1;
    }

    int32 tableID               = 8 * tablePos;
    entity->topSpeed            = tablePtr[tableID];
    entity->acceleration        = tablePtr[tableID + 1];
    entity->deceleration        = tablePtr[tableID + 1] >> decelShift;
    entity->airAcceleration     = tablePtr[tableID + 2];
    entity->airDeceleration     = tablePtr[tableID + 3];
    entity->skidSpeed           = tablePtr[tableID + 4];
    entity->rollingFriction     = tablePtr[tableID + 5];
    entity->jumpStrength        = tablePtr[tableID + 6];
    entity->jumpCap             = tablePtr[tableID + 7];
    entity->rollingDeceleration = 0x2000;

    if (entity->speedShoesTimer < 0) {
        entity->topSpeed >>= 1;
        entity->acceleration >>= 1;
        entity->airAcceleration >>= 1;
        entity->skidSpeed >>= 1;
        entity->rollingFriction >>= 1;
        entity->airDeceleration >>= 1;
    }

    if (entity->isChibi) {
        entity->topSpeed -= entity->topSpeed >> 3;
        entity->acceleration -= entity->acceleration >> 4;
        entity->airAcceleration -= entity->airAcceleration >> 4;
        entity->jumpStrength -= entity->jumpStrength >> 3;
        entity->jumpCap -= entity->jumpCap >> 3;
    }
}

void Player_HandleIdleAnimation(void)
{
    RSDK_THIS(Player);

    switch (self->characterID) {
        case ID_SONIC:
#if !MANIA_USE_PLUS
            // pre-1.05 super sonic didn't have a "bored" anim
            if (self->superState != SUPERSTATE_SUPER) {
#endif
                if (self->timer != 720 || self->isChibi || self->superState == SUPERSTATE_SUPER) {
                    if (self->timer < 240) {
                        self->timer++;
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_IDLE, &self->animator, false, 0);
                    }
                    else {
                        self->timer++;
                        if (self->animator.animationID == ANI_BORED_1) {
                            if (self->animator.frameID == 41)
                                self->timer = 0;
                        }
                        else
                            RSDK.SetSpriteAnimation(self->aniFrames, ANI_BORED_1, &self->animator, false, 0);
                    }
                }
                else {
                    if (self->animator.animationID == ANI_BORED_2) {
                        if (self->animator.frameID == 67)
                            self->timer = 0;
                    }
                    else
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_BORED_2, &self->animator, false, 0);
                }
#if !MANIA_USE_PLUS
            }
            else {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_IDLE, &self->animator, false, 0);
            }
#endif
            break;

        case ID_TAILS:
            if (self->timer < 240) {
                self->timer++;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_IDLE, &self->animator, false, 0);
            }
            else if (self->animator.animationID == ANI_BORED_1) {
                if (self->animator.frameID == 45)
                    self->timer = 0;
            }
            else {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_BORED_1, &self->animator, false, 0);
            }
            break;

        case ID_KNUCKLES:
            if (self->timer < 240) {
                self->timer++;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_IDLE, &self->animator, false, 0);
            }
            else if (self->animator.animationID == ANI_BORED_1) {
                if (self->animator.frameID == 69)
                    self->timer = 0;
            }
            else {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_BORED_1, &self->animator, false, 0);
            }
            break;

#if MANIA_USE_PLUS
        case ID_MIGHTY:
            if (self->timer < 240) {
                self->timer++;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_IDLE, &self->animator, false, 0);
            }
            else if (self->animator.animationID == ANI_BORED_1) {
                if (self->animator.frameID == 35)
                    self->timer = 0;
            }
            else {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_BORED_1, &self->animator, false, 0);
            }
            break;

        case ID_RAY:
            if (self->timer < 240) {
                self->timer++;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_IDLE, &self->animator, false, 0);
            }
            else if (self->animator.animationID == ANI_BORED_1) {
                if (self->animator.frameID == 55)
                    self->timer = 0;
            }
            else {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_BORED_1, &self->animator, false, 0);
            }
            break;

        case ID_AMY:
            if (self->timer < 240) {
                self->timer++;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_IDLE, &self->animator, false, 0);
            }
            else if (self->animator.animationID == ANI_BORED_1) {
                if (self->animator.frameID == 35)
                    self->timer = 0;
            }
            else {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_BORED_1, &self->animator, false, 0);
            }
            break;
#endif
        default: break;
    }
}

void Player_HandleGroundAnimation(void)
{
    RSDK_THIS(Player);

    if (self->skidding > 0) {
        if (self->animator.animationID != ANI_SKID) {
            if (self->animator.animationID == ANI_SKID_TURN) {
                if (self->animator.frameID == self->animator.frameCount - 1) {
                    self->direction ^= FLIP_X;
                    self->skidding = 1;
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, 0);
                }
            }
            else {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_SKID, &self->animator, false, 0);
                if (abs(self->groundVel) >= 0x60000) {
                    if (abs(self->groundVel) >= 0xA0000)
                        self->animator.speed = 64;
                    else
                        self->animator.speed = 144;
                }
                else {
                    self->skidding -= 8;
                }

                RSDK.PlaySfx(Player->sfxSkidding, false, 255);
                EntityDust *dust = CREATE_ENTITY(Dust, self, self->position.x, self->position.y);
                dust->state      = Dust_State_DustTrail;
            }
        }
        else {
            int32 spd = self->animator.speed;
            if (self->direction) {
                if (self->groundVel >= 0) {
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_SKID_TURN, &self->animator, false, 0);
                }
            }
            else if (self->groundVel <= 0) {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_SKID_TURN, &self->animator, false, 0);
            }

            self->animator.speed = spd;
        }

        --self->skidding;
    }
    else {
        if (self->pushing > -3 && self->pushing < 3) {
            if (self->groundVel || (self->angle >= 0x20 && self->angle <= 0xE0 && !self->invertGravity)) {
                self->timer          = 0;
                self->outtaHereTimer = 0;

                int32 velocity = abs(self->groundVel);
                if (velocity < self->minJogVelocity) {
                    if (self->animator.animationID == ANI_JOG) {
                        if (self->animator.frameID == 9)
                            RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, 9);
                    }
                    else if (self->animator.animationID == ANI_AIR_WALK) {
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, self->animator.frameID);
                    }
                    else {
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, 0);
                    }
                    self->animator.speed = (velocity >> 12) + 48;
                    self->minJogVelocity = 0x40000;
                }
                else if (velocity < self->minRunVelocity) {
                    if (self->animator.animationID != ANI_WALK || self->animator.frameID == 3)
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JOG, &self->animator, false, 0);
                    self->animator.speed = (velocity >> 12) + 0x40;
                    self->minJogVelocity = 0x38000;
                    self->minRunVelocity = 0x60000;
                }
                else if (velocity < self->minDashVelocity) {
                    if (self->animator.animationID == ANI_DASH || self->animator.animationID == ANI_RUN)
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_RUN, &self->animator, false, 0);
                    else
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_RUN, &self->animator, false, 1);

                    self->animator.speed  = MIN((velocity >> 12) + 0x60, 0x200);
                    self->minRunVelocity  = 0x58000;
                    self->minDashVelocity = 0xC0000;
                }
                else {
                    if (self->animator.animationID == ANI_DASH || self->animator.animationID == ANI_RUN)
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_DASH, &self->animator, false, 0);
                    else
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_DASH, &self->animator, false, 1);
                    self->minDashVelocity = 0xB8000;
                }
            }
            else {
                self->minJogVelocity  = 0x40000;
                self->minRunVelocity  = 0x60000;
                self->minDashVelocity = 0xC0000;

                Vector2 posStore = self->position;

                self->flailing |=
                    RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_FLOOR, self->collisionPlane, self->sensorX[0], self->sensorY, 10) << 0;
                self->flailing |=
                    RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_FLOOR, self->collisionPlane, self->sensorX[1], self->sensorY, 10) << 1;
                self->flailing |=
                    RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_FLOOR, self->collisionPlane, self->sensorX[2], self->sensorY, 10) << 2;
                self->flailing |=
                    RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_FLOOR, self->collisionPlane, self->sensorX[3], self->sensorY, 10) << 3;
                self->flailing |=
                    RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_FLOOR, self->collisionPlane, self->sensorX[4], self->sensorY, 10) << 4;

                self->position = posStore;
                switch (self->flailing) {
                    case 0b00000001:
                    case 0b00000011:
                        if (self->direction == FLIP_X || self->isChibi) {
                            self->direction = FLIP_X;
                            RSDK.SetSpriteAnimation(self->aniFrames, ANI_BALANCE_1, &self->animator, false, 0);
                        }
                        else {
                            RSDK.SetSpriteAnimation(self->aniFrames, ANI_BALANCE_2, &self->animator, false, 0);
                        }
                        break;

                    case 0b00010000:
                    case 0b00011000:
                        if (self->direction && !self->isChibi) {
                            RSDK.SetSpriteAnimation(self->aniFrames, ANI_BALANCE_2, &self->animator, false, 0);
                        }
                        else {
                            self->direction = FLIP_NONE;
                            RSDK.SetSpriteAnimation(self->aniFrames, ANI_BALANCE_1, &self->animator, false, 0);
                        }
                        break;

                    // bit 5 & 6 are never set, this code cannot be reached
                    // in theory, bit 5 & 6 would be set using sensorLC & sensorLR equivalents from v4/S2/S3
                    case 0b01101111:
                    case 0b01110100: RSDK.SetSpriteAnimation(self->aniFrames, ANI_BALANCE_1, &self->animator, false, 0); break;

                    // Not balancing
                    case 0b00000000:
                    default: Player_HandleIdleAnimation(); break;
                }

                // Wait for ~333 hours to do outta here (sonic is has gotten surprisingly patient since CD...)
                if (++self->outtaHereTimer >= 72000000) {
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_OUTTA_HERE, &self->animator, false, 0);
                    self->state           = Player_State_OuttaHere;
                    self->tileCollisions  = TILECOLLISION_NONE;
                    self->interaction     = false;
                    self->nextAirState    = StateMachine_None;
                    self->nextGroundState = StateMachine_None;
                    self->velocity.x      = 0;
                    self->velocity.y      = 0;
                    RSDK.PlaySfx(Player->sfxOuttahere, false, 255);
                }
            }
        }
        else {
            self->pushing = CLAMP(self->pushing, -3, 3);
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_PUSH, &self->animator, false, 0);
        }
    }
}
void Player_HandleGroundMovement(void)
{
    RSDK_THIS(Player);

    if (self->controlLock > 0) {
        self->controlLock--;

        if (!self->invertGravity)
            self->groundVel += RSDK.Sin256(self->angle) << 13 >> 8;
    }
    else {
        bool32 left  = false;
        bool32 right = false;

        if (self->invertGravity) {
            right = self->left;
            left  = self->right;
        }
        else {
            left  = self->left;
            right = self->right;
        }

        if (left) {
            if (self->groundVel > -self->topSpeed) {
                if (self->groundVel <= 0) {
                    self->groundVel -= self->acceleration;
                }
                else {
                    if (!self->collisionMode && self->groundVel > 0x40000 && !Zone->autoScrollSpeed) {
                        self->direction = FLIP_NONE;
                        self->skidding  = 24;
                    }

                    if (self->groundVel < self->skidSpeed)
                        self->groundVel = -abs(self->skidSpeed);
                    else
                        self->groundVel -= self->skidSpeed;
                }
            }

            if (self->groundVel <= 0 && self->skidding < 1)
                self->direction = FLIP_X;
        }

        if (right) {
            if (self->groundVel < self->topSpeed) {
                if (self->groundVel >= 0) {
                    self->groundVel += self->acceleration;
                }
                else {
                    if (!self->collisionMode && self->groundVel < -0x40000 && !Zone->autoScrollSpeed) {
                        self->direction = FLIP_X;
                        self->skidding  = 24;
                    }

                    if (self->groundVel > -self->skidSpeed)
                        self->groundVel = abs(self->skidSpeed);
                    else
                        self->groundVel += self->skidSpeed;
                }
            }

            if (self->groundVel >= 0 && self->skidding < 1)
                self->direction = FLIP_NONE;
        }

        if (self->left || self->right) {
            if (!self->invertGravity) {
                self->groundVel += RSDK.Sin256(self->angle) << 13 >> 8;

                if (self->right) {
                    if (!self->left) {
                        if (self->angle > 0xC0 && self->angle < 0xE4 && self->groundVel > -0x20000 && self->groundVel < 0x28000) {
                            self->controlLock = 30;
                        }
                    }
                }
                else if (self->left) {
                    if (self->angle > 0x1C && self->angle < 0x40 && self->groundVel > -0x28000 && self->groundVel < 0x20000) {
                        self->controlLock = 30;
                    }
                }
            }
        }
        else {
            if (self->groundVel <= 0) {
                self->groundVel += self->deceleration;

                if (self->groundVel > 0)
                    self->groundVel = 0;
            }
            else {
                self->groundVel -= self->deceleration;

                if (self->groundVel < 0)
                    self->groundVel = 0;
            }

            if (!self->invertGravity) {
                if (self->groundVel > 0x2000 || self->groundVel < -0x2000)
                    self->groundVel += RSDK.Sin256(self->angle) << 13 >> 8;

                if (self->angle > 0xC0 && self->angle < 0xE4) {
                    if (abs(self->groundVel) < 0x10000)
                        self->controlLock = 30;
                }

                if (self->angle > 0x1C && self->angle < 0x40) {
                    if (abs(self->groundVel) < 0x10000)
                        self->controlLock = 30;
                }
            }
        }
    }

    if (!self->invertGravity && self->collisionMode != CMODE_FLOOR && self->collisionMode <= CMODE_RWALL) {
        if (self->angle >= 0x40 && self->angle <= 0xC0 && abs(self->groundVel) < 0x20000) {
            self->velocity.x    = self->groundVel * RSDK.Cos256(self->angle) >> 8;
            self->velocity.y    = self->groundVel * RSDK.Sin256(self->angle) >> 8;
            self->onGround      = false;
            self->angle         = 0;
            self->collisionMode = CMODE_FLOOR;
        }
    }
}
void Player_HandleGroundRotation(void)
{
    RSDK_THIS(Player);

    if (self->angle <= 0x04 || self->angle >= 0xFC) {
        self->rotation = 0;
    }
    else {
        int32 targetRotation = 0;
        if (self->angle > 0x10 && self->angle < 0xE8)
            targetRotation = self->angle << 1;

        int32 rotate = targetRotation - self->rotation;
        int32 shift  = (abs(self->groundVel) <= 0x60000) + 1;

        if (abs(rotate) >= abs(rotate - 0x200)) {
            if (abs(rotate - 0x200) < abs(rotate + 0x200))
                self->rotation += (rotate - 0x200) >> shift;
            else
                self->rotation += (rotate + 0x200) >> shift;
        }
        else {
            if (abs(rotate) < abs(rotate + 0x200))
                self->rotation += rotate >> shift;
            else
                self->rotation += (rotate + 0x200) >> shift;
        }

        self->rotation &= 0x1FF;
    }
}
void Player_HandleAirRotation(void)
{
    RSDK_THIS(Player);

    if (self->rotation >= 0x100) {
        if (self->rotation < 0x200)
            self->rotation += 4;
        else
            self->rotation = 0;
    }
    else {
        if (self->rotation > 0)
            self->rotation -= 4;
        else
            self->rotation = 0;
    }
}
void Player_HandleAirMovement(void)
{
    RSDK_THIS(Player);

    Player_Gravity_True();

    self->velocity.y += self->gravityStrength;

    if (self->velocity.y < self->jumpCap && self->animator.animationID == ANI_JUMP && !self->jumpHold && self->applyJumpCap) {
        self->velocity.x -= self->velocity.x >> 5;
        self->velocity.y = self->jumpCap;
    }

    self->collisionMode = CMODE_FLOOR;
    self->pushing       = 0;

    Player_HandleAirRotation();
}
void Player_HandleAirFriction(void)
{
    RSDK_THIS(Player);

    if (self->velocity.y > -0x40000 && self->velocity.y < 0)
        self->velocity.x -= self->velocity.x >> 5;

    if (self->left) {
        if (self->velocity.x > -self->topSpeed)
            self->velocity.x -= self->airAcceleration;

        self->direction = FLIP_X;
    }

    if (self->right) {
        if (self->velocity.x < self->topSpeed)
            self->velocity.x += self->airAcceleration;

        self->direction = FLIP_NONE;
    }
}

void Player_Action_Jump(EntityPlayer *entity)
{
    entity->controlLock = 0;
    entity->onGround    = false;

    if (entity->collisionMode == CMODE_FLOOR && entity->state != Player_State_Roll)
        entity->position.y += entity->jumpOffset;

    int32 jumpForce    = entity->gravityStrength + entity->jumpStrength;
    entity->velocity.x = (entity->groundVel * RSDK.Cos256(entity->angle) + jumpForce * RSDK.Sin256(entity->angle)) >> 8;
    entity->velocity.y = (entity->groundVel * RSDK.Sin256(entity->angle) - jumpForce * RSDK.Cos256(entity->angle)) >> 8;

    if (entity->camera) {
        entity->camera->disableYOffset = true;
        entity->camera->offset.y       = 0x200000;
    }

    RSDK.SetSpriteAnimation(entity->aniFrames, ANI_JUMP, &entity->animator, false, 0);
    if (entity->characterID == ID_TAILS)
        entity->animator.speed = 120;
    else
        entity->animator.speed = ((abs(entity->groundVel) * 0xF0) / 0x60000) + 0x30;

    if (entity->animator.speed > 0xF0)
        entity->animator.speed = 0xF0;

    entity->angle            = 0;
    entity->collisionMode    = CMODE_FLOOR;
    entity->skidding         = 0;
    entity->applyJumpCap     = true;
    entity->jumpAbilityState = 1;

    RSDK.PlaySfx(Player->sfxJump, false, 255);
    entity->state = Player_State_Air;
}
void Player_Action_Roll(void)
{
    RSDK_THIS(Player);

    RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);

    self->pushing = 0;
    self->state   = Player_State_Roll;
    if (self->collisionMode == CMODE_FLOOR)
        self->position.y += self->jumpOffset;
}
void Player_Action_Spindash(void)
{
    RSDK_THIS(Player);

    EntityDust *dust = CREATE_ENTITY(Dust, self, self->position.x, self->position.y);
    RSDK.SetSpriteAnimation(Dust->aniFrames, 1, &dust->animator, true, 0);
    dust->state     = Dust_State_SpinDash;
    dust->drawGroup = self->drawGroup;

    RSDK.SetSpriteAnimation(self->aniFrames, ANI_SPINDASH, &self->animator, true, 0);
    self->state          = Player_State_Spindash;
    self->abilityTimer   = 0;
    self->spindashCharge = 0;
    RSDK.PlaySfx(Player->sfxCharge, false, 255);
}
void Player_Action_Spindash_CD(void)
{
    RSDK_THIS(Player);
    if (self->characterID == ID_TAILS)
        RSDK.SetSpriteAnimation(self->aniFrames, 55, &self->animator, true, 0);
    else
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_SPINDASH, &self->animator, true, 0);

    self->state          = Player_State_Spindash_CD;
    self->abilityTimer   = 0;
    self->spindashCharge = 0;
    RSDK.PlaySfx(Player->sfxCharge, false, 255);
}
void Player_Action_Peelout(void)
{
    RSDK_THIS(Player);

    RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, true, 0);

    self->state          = Player_State_Peelout;
    self->abilityTimer   = 0;
    self->spindashCharge = 0;
    RSDK.PlaySfx(Player->sfxPeelCharge, false, 255);
}
#if MANIA_USE_PLUS
void Player_Action_TallJump(void)
{
    RSDK_THIS(Player);

    self->controlLock     = 0;
    self->onGround        = true;
    self->nextAirState    = 0x0;
    int32 hammeranimation = self->animator.animationID;
    int32 hammerframe     = self->animator.frameID;
    int32 spinning        = false;

    if (hammeranimation == 48) {
        if (self->isChibi ? hammerframe == 4 : hammerframe == 6) {
            self->onGround = false;
            spinning       = true;
            if (self->collisionMode == CMODE_FLOOR)
                self->position.y += self->jumpOffset;

            int32 jumpForce  = self->gravityStrength + self->jumpStrength;
            self->velocity.x = (self->groundVel * RSDK.Cos256(self->angle) + jumpForce * RSDK.Sin256(self->angle)) >> 8;
            self->velocity.y = ((self->groundVel * RSDK.Sin256(self->angle) - jumpForce * RSDK.Cos256(self->angle)) >> 8) * 1.6;
            RSDK.PlaySfx(Player->sfxAmyHammer, false, 255);

            if (self->camera) {
                self->camera->disableYOffset = true;
                self->camera->offset.y       = 0x200000;
            }

            RSDK.SetSpriteAnimation(self->aniFrames, 49, &self->animator, false, 0);
            self->animator.speed   = 100;
            self->applyJumpCap     = true;
            self->jumpAbilityState = 1;

            if (self->superState == SUPERSTATE_SUPER && self->hyperState) {
                self->hyperAttacking  = true;
                self->hyperFlashTimer = 128;
                HUD_HandleHyperFlash(self);
                RSDK.PlaySfx(Player->sfxWallRumble, false, 0xFF);
            }

            self->nextAirState     = Player_State_TallJump;
            self->state            = Player_State_TallJump;
        }
    }
}
bool32 Player_SwapMainPlayer(bool32 forceSwap)
{
    RSDK_THIS(Player);

    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    if (!sidekick->classID)
        return false;

    if (!forceSwap) {
        if (Player->cantSwap || self->drawGroup == 2 || !SceneInfo->timeEnabled)
            return false;

        if (sidekick->respawnTimer) {
            sidekick->respawnTimer = 240;
            return false;
        }

        if (self->state == Player_State_Death || self->state == Player_State_Drown) {
            if (sidekick->state == Player_State_Death || sidekick->state == Player_State_Drown || sidekick->state == Player_State_EncoreRespawn
                || sidekick->state == Player_State_Static) {
                return false;
            }
        }
        else {
            if (self->state != Player_State_Ground && self->state != Player_State_Roll)
                return false;
            if (sidekick->state != Player_State_Ground && sidekick->state != Player_State_Roll)
                return false;
        }
    }

    EntityPlayer *leader             = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityCamera *sidekickCam        = sidekick->camera;
    int32 sidekickController         = sidekick->controllerID;
    void (*sidekickInputState)(void) = sidekick->stateInput;
    if (sidekick->state == Ice_PlayerState_Frozen) {
        Ice_BreakPlayerBlock(sidekick);
        Ice->playerTimers[0] = 30;
        Ice->playerTimers[1] = 0;
        foreach_all(Ice, ice)
        {
            if (ice->state == Ice_State_PlayerBlock)
                destroyEntity(ice);
        }
    }
    RSDK.CopyEntity(&Zone->entityStorage[0], leader, false);
    RSDK.CopyEntity(leader, sidekick, false);
    RSDK.CopyEntity(sidekick, &Zone->entityStorage[0], false);

    sidekick->state        = Player_State_Air;
    self->controllerID     = sidekick->controllerID;
    self->stateInput       = sidekick->stateInput;
    self->sidekick         = false;
    self->score            = sidekick->score;
    self->score1UP         = sidekick->score1UP;
    self->rings            = sidekick->rings;
    self->ringExtraLife    = sidekick->ringExtraLife;
    self->shield           = sidekick->shield;
    self->camera           = sidekick->camera;
    self->invincibleTimer  = sidekick->invincibleTimer;
    self->superInvulnTimer = sidekick->superInvulnTimer;
    self->speedShoesTimer  = sidekick->speedShoesTimer;
    self->hyperRing        = sidekick->hyperRing;
    self->playerID         = sidekick->playerID;
    self->scrollDelay      = 0;
    self->camera->state    = Camera_State_FollowXY;
    Player_UpdatePhysicsState(self);

    sidekick->controllerID     = sidekickController;
    sidekick->stateInput       = sidekickInputState;
    sidekick->sidekick         = true;
    sidekick->score            = 0;
    sidekick->score1UP         = 0;
    sidekick->rings            = 0;
    sidekick->ringExtraLife    = 0;
    sidekick->shield           = SHIELD_NONE;
    sidekick->invincibleTimer  = 0;
    sidekick->superInvulnTimer = 0;
    sidekick->speedShoesTimer  = 0;
    sidekick->camera           = sidekickCam;
    sidekick->hyperRing        = false;
    sidekick->playerID         = RSDK.GetEntitySlot(sidekick);
    Player_UpdatePhysicsState(sidekick);

    if (sidekick->superState == SUPERSTATE_SUPER)
        self->superState = SUPERSTATE_SUPER;

    globals->playerID = self->characterID + (sidekick->characterID << 8);
    RSDK.PlaySfx(Player->sfxSwap, false, 255);
    HUD->swapCooldown = 60;

    return true;
}
#endif

void Player_HandleRollDeceleration(void)
{
    RSDK_THIS(Player);

    int32 initialVel = self->groundVel;
    if (self->right && self->groundVel < 0)
        self->groundVel += self->rollingDeceleration;

    if (self->left && self->groundVel > 0)
        self->groundVel -= self->rollingDeceleration;

    if (self->groundVel) {
        if (self->groundVel < 0) {
            self->groundVel += self->rollingFriction;

            if (RSDK.Sin256(self->angle) >= 0)
                self->groundVel += 0x1400 * RSDK.Sin256(self->angle) >> 8;
            else
                self->groundVel += 0x5000 * RSDK.Sin256(self->angle) >> 8;

            if (self->groundVel < -0x120000)
                self->groundVel = -0x120000;
        }
        else {
            self->groundVel -= self->rollingFriction;

            if (RSDK.Sin256(self->angle) <= 0)
                self->groundVel += 0x1400 * RSDK.Sin256(self->angle) >> 8;
            else
                self->groundVel += 0x5000 * RSDK.Sin256(self->angle) >> 8;

            if (self->groundVel > 0x120000)
                self->groundVel = 0x120000;
        }
    }
    else {
        self->groundVel += 0x5000 * RSDK.Sin256(self->angle) >> 8;
    }

    switch (self->collisionMode) {
        case CMODE_FLOOR:
            if (self->state == Player_State_TubeRoll) {
                if (abs(self->groundVel) < 0x10000) {
                    if (self->direction & FLIP_Y)
                        self->groundVel = -0x40000;
                    else
                        self->groundVel = 0x40000;
                }
            }
            else {
                if ((self->groundVel >= 0 && initialVel <= 0) || (self->groundVel <= 0 && initialVel >= 0)) {
                    self->groundVel = 0;
                    self->state     = Player_State_Ground;
                }
            }
            break;

        case CMODE_LWALL:
        case CMODE_RWALL:
            if (self->angle >= 0x40 && self->angle <= 0xC0) {
                if (abs(self->groundVel) < 0x20000) {
                    self->velocity.x    = self->groundVel * RSDK.Cos256(self->angle) >> 8;
                    self->velocity.y    = self->groundVel * RSDK.Sin256(self->angle) >> 8;
                    self->onGround      = false;
                    self->angle         = 0;
                    self->collisionMode = CMODE_FLOOR;
                }
            }
            break;

        case CMODE_ROOF:
            if (self->invertGravity) {
                if ((self->groundVel >= 0 && initialVel <= 0) || (self->groundVel <= 0 && initialVel >= 0)) {
                    self->groundVel = 0;
                    self->state     = Player_State_Ground;
                }
            }
            else {
                if (self->angle >= 0x40 && self->angle <= 0xC0) {
                    if (abs(self->groundVel) < 0x20000) {
                        self->velocity.x    = self->groundVel * RSDK.Cos256(self->angle) >> 8;
                        self->velocity.y    = self->groundVel * RSDK.Sin256(self->angle) >> 8;
                        self->onGround      = false;
                        self->angle         = 0;
                        self->collisionMode = CMODE_FLOOR;
                    }
                }
            }
            break;
    }
}
void Player_Hit(EntityPlayer *player)
{
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();
    uint8 hurtType = PLAYER_HURT_NONE;
    if (player->sidekick) {
        hurtType = PLAYER_HURT_HASSHIELD;
    }
    else {
        int32 entityID       = RSDK.GetEntitySlot(player);
        EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + entityID, Shield);
        if (shield->classID == Shield->classID) {
            player->shield = SHIELD_NONE;
            destroyEntity(shield);
            hurtType = PLAYER_HURT_HASSHIELD;
        }
        else {
            hurtType = (player->rings <= 0) + PLAYER_HURT_RINGLOSS;
        }

        if (!Player->gotHit[player->playerID])
            Player->gotHit[player->playerID] = true;
    }

    player->nextAirState    = StateMachine_None;
    player->nextGroundState = StateMachine_None;
    if (globals->coolBonus[player->playerID] > 0)
        globals->coolBonus[player->playerID] -= 1000;

    switch (hurtType) {
        default: break;

        case PLAYER_HURT_HASSHIELD: // Hurt, no rings (shield/P2 AI/etc)
            player->state = Player_State_Hurt;
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_HURT, &player->animator, false, 0);
            player->velocity.y     = -0x40000;
            player->onGround       = false;
            player->tileCollisions = TILECOLLISION_DOWN;
            player->blinkTimer     = 120;
            if (player->underwater) {
                player->velocity.x >>= 1;
                player->velocity.y = -0x20000;
            }
            RSDK.PlaySfx(Player->sfxHurt, false, 0xFF);
            break;

        case PLAYER_HURT_RINGLOSS: // Hurt, lost rings
            player->state = Player_State_Hurt;
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_HURT, &player->animator, false, 0);
            player->velocity.y     = -0x40000;
            player->onGround       = false;
            player->tileCollisions = TILECOLLISION_DOWN;
            player->blinkTimer     = 120;
            if (player->underwater) {
                player->velocity.x >>= 1;
                player->velocity.y = -0x20000;
            }

            if (player->hyperRing) {
                if (addendumOptions->coopStyle == COOPSTYLE_TOGETHER) {
                    Ring_LoseHyperRings(player, player->rings / addendumVar->playerCount, player->collisionPlane);
                }
                else
                    Ring_LoseHyperRings(player, player->rings, player->collisionPlane);
            }
            else {
                if (addendumOptions->coopStyle == COOPSTYLE_TOGETHER)
                    Ring_LoseRings(player, player->rings / addendumVar->playerCount, player->collisionPlane);
                else
                    Ring_LoseRings(player, player->rings, player->collisionPlane);
            }

            player->hyperRing     = false;
            if (addendumOptions->coopStyle == COOPSTYLE_TOGETHER) {
                for (int32 p = 0; p < addendumVar->playerCount; ++p) {
                    EntityPlayer* players = RSDK_GET_ENTITY(p, Player);
                    int32 subRings = players->rings / addendumVar->playerCount;
                    if (players->rings > 3)
                        players->rings -= subRings;
                    else
                        players->rings = 0;
                }
            }
            else
                player->rings = 0;
            player->ringExtraLife = 100;
            RSDK.PlaySfx(Player->sfxLoseRings, false, 0xFF);
            break;

        case PLAYER_HURT_DIE: // Hurt, dies.
            if (SceneInfo->debugMode) {
                player->state = Player_State_Hurt;
                RSDK.SetSpriteAnimation(player->aniFrames, ANI_HURT, &player->animator, false, 0);
                player->velocity.y     = -0x40000;
                player->onGround       = false;
                player->tileCollisions = TILECOLLISION_DOWN;
                player->blinkTimer     = 120;
                if (player->underwater) {
                    player->velocity.x >>= 1;
                    player->velocity.y = -0x20000;
                }
                RSDK.PlaySfx(Player->sfxHurt, false, 0xFF);
            }
            else
                player->deathType = PLAYER_DEATH_DIE_USESFX;
            break;
    }
}
bool32 Player_CheckValidState(EntityPlayer *player)
{
    if (player->classID == Player->classID && !player->deathType) {
        if (player->state != Player_State_Death && player->state != Player_State_Drown &&
#if MANIA_USE_PLUS
            player->state != Player_State_EncoreRespawn && player->state != Player_State_ReturnToPlayer &&
#endif
            player->state != Player_State_HoldRespawn && player->state != Player_State_FlyToPlayer && player->state != Player_State_Transform) {
            return true;
        }
    }

    return false;
}
void Player_HandleFlyCarry(EntityPlayer *leader)
{
    RSDK_THIS(Player);

    if (self->flyCarryTimer > 0)
        self->flyCarryTimer--;

    int32 off;
    if (leader->animator.animationID == ANI_JUMP)
        off = self->position.y + TO_FIXED(33);
    else
        off = self->position.y + TO_FIXED(28);

    if (leader->state != Player_State_FlyCarried && (!leader->onGround || self->velocity.y < 0)) {
        bool32 canFlyCarry = (leader->state == Player_State_Roll || leader->state == Player_State_LookUp || leader->state == Player_State_Crouch
                              || leader->state == Player_State_Air || leader->state == Player_State_Ground);
        if (LottoMachine)
            canFlyCarry = canFlyCarry && (!((1 << RSDK.GetEntitySlot(leader)) & LottoMachine->activePlayers));

        if (canFlyCarry && (leader->animator.animationID != ANI_FAN)) {
            if (abs(self->position.x - leader->position.x) < TO_FIXED(12) && abs(off - leader->position.y) < TO_FIXED(12) && !self->flyCarryTimer
                && !leader->down && !leader->onGround) {
                RSDK.SetSpriteAnimation(leader->aniFrames, ANI_HANG, &leader->animator, false, 0);
                leader->state           = Player_State_FlyCarried;
                leader->nextAirState    = StateMachine_None;
                leader->nextGroundState = StateMachine_None;
                RSDK.PlaySfx(Player->sfxGrab, false, 255);
            }
        }
    }

    if (leader->state == Player_State_FlyCarried) {
        int32 entityXPos = self->position.x;
        int32 entityYPos = self->position.y;
        int32 entityXVel = self->velocity.x;
        int32 entityYVel = self->velocity.y;

        Hitbox *sidekickOuterBox = RSDK.GetHitbox(&self->animator, 0);
        Hitbox *sidekickInnerBox = RSDK.GetHitbox(&self->animator, 1);
        if (self->collisionLayers & Zone->moveLayerMask) {
            TileLayer *move  = RSDK.GetTileLayer(Zone->moveLayer);
            move->position.x = -self->moveLayerPosition.x >> 16;
            move->position.y = -self->moveLayerPosition.y >> 16;
        }

        RSDK.ProcessObjectMovement(self, sidekickOuterBox, sidekickInnerBox);

        if (self->onGround && !self->collisionMode)
            self->collisionFlagV |= 1;

        leader->flyCarrySidekickPos.x = self->position.x & 0xFFFF0000;
        leader->flyCarrySidekickPos.y = self->position.y & 0xFFFF0000;

        self->position.x = entityXPos;
        self->position.y = entityYPos;
        self->velocity.x = entityXVel;
        self->velocity.y = entityYVel;

        leader->position.x = entityXPos;
        leader->position.y = entityYPos + TO_FIXED(28);
        leader->velocity.x = entityXVel;
        leader->velocity.y = entityYVel;

        Hitbox *leaderOuterBox = Player_GetHitbox(leader);
        Hitbox *leaderInnerBox = Player_GetAltHitbox(leader);
        if (leader->collisionLayers & Zone->moveLayerMask) {
            TileLayer *move  = RSDK.GetTileLayer(Zone->moveLayer);
            move->position.x = -leader->moveLayerPosition.x >> 16;
            move->position.y = -leader->moveLayerPosition.y >> 16;
        }

        RSDK.ProcessObjectMovement(leader, leaderOuterBox, leaderInnerBox);

        if (leader->onGround)
            leader->collisionFlagV |= 1;

        leader->collisionPlane = self->collisionPlane;
        leader->direction      = self->direction;
        leader->velocity.x     = 0;
        leader->velocity.y     = 0;
    }
}
void Player_HandleSidekickRespawn(void)
{
    RSDK_THIS(Player);
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();

    EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    if (leader->classID == Player->classID && (leader->drawGroup != 2 || self->drawGroup != 2)) {
        int32 rx = abs(FROM_FIXED(self->position.x) - ScreenInfo->position.x - ScreenInfo->center.x);
        int32 ry = abs(FROM_FIXED(self->position.y) - ScreenInfo->position.y - ScreenInfo->center.y);

        if (rx >= ScreenInfo->center.x + 96 || ry >= ScreenInfo->center.y + 96) {
            if (addendumOptions->coopStyle == COOPSTYLE_MANIA)
                ++self->respawnTimer;
        }
        else
            self->respawnTimer = 0;

        if (self->respawnTimer >= 240) {
            self->respawnTimer = 0;
            self->state            = Player_State_HoldRespawn;
            self->forceRespawn     = true;
            self->position.x       = -0x400000;
            self->position.y       = -0x400000;
            self->abilityValues[0] = 0;
            self->drawFX &= ~FX_SCALE;
            self->nextAirState    = StateMachine_None;
            self->nextGroundState = StateMachine_None;
            self->stateInput      = Player_Input_P2_Delay;
            self->scale.x         = 0x200;
            self->scale.y         = 0x200;
            self->velocity.x      = 0;
            self->velocity.y      = 0;
            self->groundVel       = 0;
            self->tileCollisions  = TILECOLLISION_NONE;
            self->interaction     = false;
            self->blinkTimer      = 0;
            self->visible         = true;

            if (leader->underwater && leader->position.y < Water->waterLevel) {
                self->drawGroup  = leader->drawGroup;
                self->drownTimer = 0;
            }
            else {
                self->drawGroup  = Zone->playerDrawGroup[1];
                self->drownTimer = 0;
            }
        }
    }
}
void Player_State_StartSuper(void)
{
    RSDK_THIS(Player);

    if (self->characterID == ID_SONIC) {
        if (self->miracleState)
            self->aniFrames = Player->miracleFrames;
        else
            self->aniFrames = Player->superFrames;
    }

    if (self->characterID == ID_TAILS && self->miracleState) {
        self->aniFrames = Player->miracleTailsFrames;
        self->tailFrames = Player->miracleTailsTailsFrames;
    }

    if (self->characterID == ID_KNUCKLES && self->miracleState) {
        self->aniFrames = Player->miracleKnuxFrames;
    }

    if (self->characterID == ID_MIGHTY && self->miracleState)
        self->aniFrames = Player->miracleMightyFrames;

    if (self->characterID == ID_RAY && self->miracleState)
        self->aniFrames = Player->miracleRayFrames;

    if (self->characterID == ID_AMY && self->miracleState)
        self->aniFrames = Player->miracleAmyFrames;

    destroyEntity(RSDK_GET_ENTITY(self->playerID + Player->playerCount, Shield));
    self->superInvulnTimer = 60;
    self->invincibleTimer  = 0;
    self->superState       = SUPERSTATE_SUPER;
    Player_UpdatePhysicsState(self);

    RSDK.ResetEntity(RSDK_GET_ENTITY(self->playerID + 2 * Player->playerCount, ImageTrail), ImageTrail->classID, self);
#if MANIA_USE_PLUS
    RSDK.ResetEntity(RSDK_GET_ENTITY(self->playerID + Player->playerCount, SuperSparkle), SuperSparkle->classID, self);
#endif

    self->state = Player_State_Ground;
#if GAME_VERSION != VER_100
    Player_State_Ground();
#endif
}

// Player States
void Player_State_Static(void)
{
    // No code. Do nothing. Just vibe.
}
void Player_State_Ground(void)
{
    RSDK_THIS(Player);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (!self->onGround) {
        self->state = Player_State_Air;
        Player_HandleAirMovement();
    }
    else {
        if (!self->groundVel) {
            if (self->left)
                --self->pushing;
            else if (self->right)
                ++self->pushing;
            else
                self->pushing = 0;
        }
        else {
            if (!self->left && !self->right) {
                self->pushing = 0;
            }
            else {
                if (abs(self->groundVel) > 0x10000)
                    self->pushing = 0;
            }
        }

        if (self->invertGravity) {
            if (self->collisionMode != CMODE_ROOF)
                self->pushing = 0;
        }
        else if (self->collisionMode != CMODE_FLOOR) {
            self->pushing = 0;
        }

        Player_HandleGroundRotation();
        Player_HandleGroundMovement();

        Player_Gravity_False();

        self->nextAirState = Player_State_Air;

        Player_HandleGroundAnimation();

        if (TriggerInfoR[self->controllerID].keyBumper.press) {
            if (self->stateTallJump) {
                RSDK.SetSpriteAnimation(self->aniFrames, 48, &self->animator, true, 0);
                self->state = Player_Action_TallJump;
            }
        }

        if (self->jumpPress) {
            if (self->characterID == ID_AMY && self->stateTallJump && ControllerInfo[self->controllerID].keyUp.down) {
                RSDK.SetSpriteAnimation(self->aniFrames, 48, &self->animator, true, 0);
                self->state = Player_Action_TallJump;
            }
            else {
                Player_Action_Jump(self);
                self->timer = 0;
            }
        }
        else {
            if (self->groundVel) {
                int32 minRollVel = self->state == Player_State_Crouch ? 0x11000 : 0x8800;
                if (touchControls) { // makes rolling easier to perform while running with the new 8-way d-pad touch input system
                    if (abs(self->groundVel) >= minRollVel && self->down) {
                        Player_Action_Roll();
                        RSDK.PlaySfx(Player->sfxRoll, false, 255);
                    }
                }
                else {
                    if (abs(self->groundVel) >= minRollVel && !self->left && !self->right && self->down) {
                        Player_Action_Roll();
                        RSDK.PlaySfx(Player->sfxRoll, false, 255);
                    }
                }
            }
            else if (((self->angle < 0x20 || self->angle > 0xE0) && !self->collisionMode) || (self->invertGravity && self->angle == 0x80)) {
                if (self->up) {
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_LOOK_UP, &self->animator, true, 1);
                    self->timer = 0;
                    self->state = Player_State_LookUp;
                }
                else if (self->down) {
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_CROUCH, &self->animator, true, 1);
                    self->timer = 0;
                    self->state = Player_State_Crouch;
                }
            }
        }
    }
}
void Player_State_Air(void)
{
    RSDK_THIS(Player);
    self->hyperAttacking = false;

#if GAME_VERSION != VER_100
    self->tileCollisions = TILECOLLISION_DOWN;
#endif
    Player_HandleAirFriction();

    if (self->onGround) {
        self->state = Player_State_Ground;

        Player_Gravity_False();
    }
    else {
        Player_HandleAirMovement();
        self->nextGroundState = Player_State_Ground;

        if (self->velocity.y > 0) {
            if (self->animator.animationID >= ANI_SPRING_TWIRL) {
                if (self->animator.animationID <= ANI_SPRING_DIAGONAL) {
                    RSDK.SetSpriteAnimation(self->aniFrames, self->animationReserve, &self->animator, false, 0);
                }
                else if (self->animator.animationID == ANI_SPRING_CS && !self->animator.frameID) {
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_AIR_WALK, &self->animator, false, 0);
                }
            }
        }

        switch (self->animator.animationID) {
            case ANI_IDLE:
            case ANI_WALK:
                if (self->animator.speed < 64)
                    self->animator.speed = 64;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_AIR_WALK, &self->animator, false, self->animator.frameID);
                break;

            case ANI_LOOK_UP:
            case ANI_CROUCH:
            case ANI_SKID_TURN: RSDK.SetSpriteAnimation(self->aniFrames, ANI_AIR_WALK, &self->animator, false, 0); break;

            case ANI_JOG: RSDK.SetSpriteAnimation(self->aniFrames, ANI_AIR_WALK, &self->animator, false, 0); break;

            case ANI_JUMP:
                if (self->velocity.y >= self->jumpCap)
                    StateMachine_Run(self->stateAbility);
                break;

            case ANI_SKID:
                if (self->skidding <= 0)
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_AIR_WALK, &self->animator, false, self->animator.frameID);
                else
                    self->skidding--;
                break;

            case ANI_SPINDASH: RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0); break;

            default: break;
        }
    }

    if (!(self->state == Player_State_KnuxWallClimb || self->state == Player_State_DropDash || self->state == Player_State_TailsFlight
        || self->state == Player_State_KnuxGlideDrop || self->state == Player_State_KnuxGlideLeft || self->state == Player_State_KnuxGlideRight
        || self->state == Player_State_KnuxGlideSlide || self->state == Player_State_KnuxLedgePullUp
#if MANIA_USE_PLUS
        || self->state == Player_State_MightyHammerDrop || self->state == Player_State_MightyWallStick || self->state == Player_State_RayGlide || self->state == Player_State_MightyUnspin
        || self->state == Player_Action_TallJump || self->state == Player_State_AmyHeliHammer_Left || self->state == Player_State_AmyHeliHammer_Right || self->state == Player_HandleHyperSonicDash
#endif
    )) {
        if (self->animator.animationID != ANI_JUMP) {
            RSDKControllerState *controller = &ControllerInfo[self->controllerID];
            RSDKAnalogState *analog         = &AnalogStickInfoL[self->controllerID];
            if (controller->keyDown.down && self->jumpPress || analog->keyDown.down && self->jumpPress) {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->jumpHold = true;
            }
        }
    }
}
void Player_State_Roll(void)
{
    RSDK_THIS(Player);

    Player_HandleGroundRotation();
    Player_HandleRollDeceleration();

    self->applyJumpCap = false;
    if (!self->onGround) {
        self->state = Player_State_Air;
        Player_HandleAirMovement();
    }
    else {
        if (self->characterID == ID_TAILS)
            self->animator.speed = 120;
        else
            self->animator.speed = ((abs(self->groundVel) * 0xF0) / 0x60000) + 0x30;

        if (self->animator.speed > 0xF0)
            self->animator.speed = 0xF0;

        Player_Gravity_False();

        if (self->jumpPress)
            Player_Action_Jump(self);
    }
}
void Player_State_TubeRoll(void)
{
    RSDK_THIS(Player);

    Player_HandleGroundRotation();

    bool32 left  = self->left;
    bool32 right = self->right;
    if (self->controlLock > 0) {
        self->left  = false;
        self->right = false;
        self->controlLock--;
    }

    Player_HandleRollDeceleration();

    self->left         = left;
    self->right        = right;
    self->applyJumpCap = false;

    if (!self->onGround) {
        self->state = Player_State_TubeAirRoll;
        Player_HandleAirMovement();
    }
    else {
        if (self->characterID == ID_TAILS)
            self->animator.speed = 120;
        else
            self->animator.speed = ((abs(self->groundVel) * 0xF0) / 0x60000) + 0x30;

        if (self->animator.speed > 0xF0)
            self->animator.speed = 0xF0;

        Player_Gravity_False();
    }
}
void Player_State_TubeAirRoll(void)
{
    RSDK_THIS(Player);

    Player_HandleGroundRotation();

    bool32 left  = self->left;
    bool32 right = self->right;
    if (self->controlLock > 0) {
        self->left  = false;
        self->right = false;
        self->controlLock--;
    }

    Player_HandleAirFriction();

    self->left         = left;
    self->right        = right;
    self->applyJumpCap = false;

    self->nextGroundState = Player_State_TubeRoll;

    if (!self->onGround) {
        Player_HandleAirMovement();
    }
    else {
        self->state = Player_State_TubeRoll;

        Player_Gravity_False();
    }
}
void Player_State_LookUp(void)
{
    RSDK_THIS(Player);

    if (self->invertGravity)
        self->rotation = 0x80;

    Player_Gravity_False();

    self->nextAirState = Player_State_Air;

    if (self->up) {
        self->left  = false;
        self->right = false;

        Player_HandleGroundMovement();

        RSDK.SetSpriteAnimation(self->aniFrames, ANI_LOOK_UP, &self->animator, false, 1);
        if (self->animator.frameID == 5)
            self->animator.speed = 0;

        if (self->timer < 60) {
            self->timer++;
        }
        else if (self->camera) {
            if (self->invertGravity) {
                if (self->camera->lookPos.y < 96)
                    self->camera->lookPos.y += 2;
            }
            else {
                if (self->camera->lookPos.y > -96)
                    self->camera->lookPos.y -= 2;
            }
        }

        if (self->jumpPress) {
            if (self->stateTallJump) {
                RSDK.SetSpriteAnimation(self->aniFrames, 48, &self->animator, true, 0);
                self->state = Player_Action_TallJump;
            }
            else if (self->statePeelout) {
                StateMachine_Run(self->statePeelout);
            }
            else {
                Player_Action_Jump(self);
            }
        }
    }
    else {
        self->animator.speed = 64;

        if (self->animator.frameID == 0 || self->left || self->right)
            self->state = Player_State_Ground;

        if (self->jumpPress)
            Player_Action_Jump(self);
    }
}
void Player_State_Crouch(void)
{
    RSDK_THIS(Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (self->invertGravity)
        self->rotation = 0x80;

    self->left  = false;
    self->right = false;

    Player_HandleGroundMovement();

    Player_Gravity_False();

    self->nextAirState = Player_State_Air;

    if (self->down) {
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_CROUCH, &self->animator, false, 1);
        if (self->animator.frameID == 4)
            self->animator.speed = 0;

        if (self->timer < 60) {
            self->timer++;
        }
        else if (self->camera) {
            if (self->invertGravity) {
                if (self->camera->lookPos.y > -96)
                    self->camera->lookPos.y -= 2;
            }
            else {
                if (self->camera->lookPos.y < 96)
                    self->camera->lookPos.y += 2;
            }
        }

        if (self->jumpPress) {
            if (addendumOptions->spindashType == SPINDASHTYPE_CD)
                Player_Action_Spindash_CD();
            else if (addendumOptions->spindashType == SPINDASHTYPE_NONE)
                Player_Action_Jump(self);
            else
                Player_Action_Spindash();
        }
    }
    else {
        self->animator.speed = 128;

        if (self->animator.frameID == 0 || self->left || self->right)
            self->state = Player_State_Ground;

        if (self->jumpPress)
            Player_Action_Jump(self);
    }
}
void Player_State_Spindash(void)
{
    RSDK_THIS(Player);

    float chargeSpeeds[13] = { 1.0f,       1.0614005f, 1.125531f,  1.1926451f, 1.2630343f, 1.3370349f, 1.4150375f,
                               1.4974997f, 1.5849625f, 1.6780719f, 1.7776076f, 1.8845228f, 2.00000000f };

    if (self->jumpPress) {
        self->abilityTimer += 0x20000;

        if (self->abilityTimer > 0x90000)
            self->abilityTimer = 0x90000;

        if (self->spindashCharge < 12)
            self->spindashCharge++;

        if (self->spindashCharge < 0)
            self->spindashCharge = 0;

        RSDK.SetSpriteAnimation(self->aniFrames, ANI_SPINDASH, &self->animator, true, 0);
        int32 channel = RSDK.PlaySfx(Player->sfxCharge, false, 255);
        RSDK.SetChannelAttributes(channel, 1.0, 0.0, chargeSpeeds[self->spindashCharge]);
    }
    else {
        self->abilityTimer -= self->abilityTimer >> 5;
    }

    if (!self->down) {
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);

        if (self->camera && !Zone->autoScrollSpeed) {
            self->scrollDelay   = 15;
            self->camera->state = Camera_State_FollowY;
        }

        int32 vel = 0;
        if (self->superState == SUPERSTATE_SUPER)
            vel = (((uint32)self->abilityTimer >> 1) & 0x7FFF8000) + 0xB0000;
        else
            vel = (((uint32)self->abilityTimer >> 1) & 0x7FFF8000) + 0x80000;

        if (self->direction != FLIP_NONE)
            self->groundVel = -vel;
        else
            self->groundVel = vel;

        RSDK.StopSfx(Player->sfxCharge);
        RSDK.PlaySfx(Player->sfxRelease, false, 0xFF);

        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);

        if (!self->collisionMode)
            self->position.y += self->jumpOffset;

        self->pushing = 0;
        self->state   = Player_State_Roll;
    }
}
void Player_State_Spindash_CD(void)
{
    RSDK_THIS(Player);

    float chargeTimes[13]       = { 2.46f, 4.92f, 7.38f, 9.84f, 12.30f, 14.76f, 17.22f, 19.68f, 22.14f, 24.60f, 27.06f, 29.52f, 31.98f };
    int32 averageSpeedperCharge = 0x7943;
    int32 frameToSpeedRatio     = 0x2813;
    // ^^ written-down calculations. does nothing; exists only for future reference ^^

    self->timer = 0;

    if (self->abilityTimer < 0x112520)
        self->abilityTimer += 0x8929; // 1.599715606114469

    if (self->spindashCharge < 32)
        self->spindashCharge += 1;

    if (self->characterID == ID_TAILS)
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_CDSPINDASH, &self->animator, false, 0);
    else
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_SPINDASH, &self->animator, false, 0);
    self->animator.speed = 120;

    if (self->spindashCharge == 32) {
        self->spindashCharge = 33;
        EntityDust *dust     = CREATE_ENTITY(Dust, self, self->position.x, self->position.y);
        RSDK.SetSpriteAnimation(Dust->aniFrames, 1, &dust->animator, true, 0);
        dust->state     = Dust_State_SpinDash;
        dust->drawGroup = self->drawGroup;
    }

    if (self->spindashCharge < 0) // this probably isn't needed, but keeping it here just to be safe
        self->spindashCharge = 0;

    if (!self->down) {
        if (self->camera && !Zone->autoScrollSpeed) {
            self->scrollDelay   = 15;
            self->camera->state = Camera_State_FollowY;
        }

        int32 vel = 0;
        if (self->superState == SUPERSTATE_SUPER)
            vel = (((uint32)self->abilityTimer >> 1) & 0x7FFF8000) + 0x6E050;
        else
            vel = (((uint32)self->abilityTimer >> 1) & 0x7FFF8000) + 0x31994;

        if (self->direction != FLIP_NONE)
            self->groundVel = -vel;
        else
            self->groundVel = vel;

        RSDK.StopSfx(Player->sfxCharge);
        RSDK.PlaySfx(Player->sfxRelease, false, 0xFF);

        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);

        self->pushing = 0;
        self->state   = Player_State_Roll;
    }
}
void Player_State_Peelout(void)
{
    RSDK_THIS(Player);

    if (self->gravityStrength == 0x1000) {
        if (self->superState == SUPERSTATE_SUPER) {
            self->abilityTimer += 0xA000;
            if (self->abilityTimer > 0x70000)
                self->abilityTimer = 0x70000;
        }
        else {
            self->abilityTimer += 0x6000;
            if (self->abilityTimer > 0x60000)
                self->abilityTimer = 0x60000;
        }
    }
    else if (self->superState == SUPERSTATE_SUPER) {
        self->abilityTimer += 0xC000;
        if (self->abilityTimer > 0xD0000)
            self->abilityTimer = 0xD0000;
    }
    else {
        self->abilityTimer += 0x8000;
        if (self->abilityTimer > 0xC0000)
            self->abilityTimer = 0xC0000;
    }

    if (self->abilityTimer < self->minJogVelocity) {
        if (self->animator.animationID == ANI_JOG) {
            if (self->animator.frameID == 9)
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, 9);
        }
        else if (self->animator.animationID == ANI_AIR_WALK) {
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, self->animator.frameID);
        }
        else {
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, 0);
        }

        self->animator.speed = (self->abilityTimer >> 12) + 48;
        self->minJogVelocity = 0x40000;
    }
    else if (self->abilityTimer < self->minRunVelocity) {
        if (self->animator.animationID != ANI_WALK || self->animator.frameID == 3)
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JOG, &self->animator, false, 0);
        self->animator.speed = (self->abilityTimer >> 12) + 64;
        self->minJogVelocity = 0x38000;
        self->minRunVelocity = 0x60000;
    }
    else if (self->abilityTimer < self->minDashVelocity) {
        if (self->animator.animationID == ANI_DASH || self->animator.animationID == ANI_RUN)
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_RUN, &self->animator, false, 0);
        else
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_RUN, &self->animator, false, 1);

        self->animator.speed = (self->abilityTimer >> 12) + 96;
        if (self->animator.speed > 0x200)
            self->animator.speed = 512;
        self->minDashVelocity = 0xC0000;
        self->minRunVelocity  = 0x58000;
    }
    else {
        if (self->animator.animationID == ANI_DASH || self->animator.animationID == ANI_RUN)
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_DASH, &self->animator, false, 0);
        else
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_DASH, &self->animator, false, 1);

        self->minDashVelocity = 0xB8000;
    }

    if (!self->up) {
        RSDK.StopSfx(Player->sfxPeelCharge);

        if (self->abilityTimer >= 0x60000) {
            if (self->camera && !Zone->autoScrollSpeed) {
                self->scrollDelay   = 15;
                self->camera->state = Camera_State_FollowY;
            }

            if (self->direction)
                self->groundVel = -self->abilityTimer;
            else
                self->groundVel = self->abilityTimer;

            RSDK.PlaySfx(Player->sfxPeelRelease, false, 0xFF);
        }

        self->state = Player_State_Ground;
    }
}
void Player_State_TallJump(void)
{
    RSDK_THIS(Player);
    Player_State_Air();
    if (self->velocity.y > 0) {
        if (self->animator.animationID != ANI_JUMP) {
            RSDK.SetSpriteAnimation(self->aniFrames, 50, &self->animator, false, 0);
            self->animator.speed = 64;
        }
        self->state          = Player_State_Air;
    }
}
void Player_State_OuttaHere(void)
{
    RSDK_THIS(Player);

    if (self->onGround) {
        if (self->animator.frameID == 14) {
            self->applyJumpCap = false;

            if (self->direction == FLIP_X)
                self->velocity.x = -0x10000;
            else
                self->velocity.x = 0x10000;
            self->velocity.y = -0x58000;

            self->onGround   = false;
            self->stateInput = StateMachine_None;

            if (self->camera)
                self->camera->state = StateMachine_None;
        }
    }
    else {
        Player_HandleAirMovement();
        if (self->velocity.y > 0x100000) {
            RSDK.ResetEntitySlot(SLOT_GAMEOVER, GameOver->classID, INT_TO_VOID(false));
            destroyEntity(self);
        }
    }
}
void Player_State_Transform(void)
{
    RSDK_THIS(Player);

    EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    AddendumData *addendumData = Addendum_GetSaveRAM();
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    self->position.x += Zone->autoScrollSpeed;

#if GAME_VERSION != VER_100
    self->superInvulnTimer = 60;
    self->invincibleTimer  = 1;
#endif

    RSDK.ObjectTileCollision(self, Zone->collisionLayers, CMODE_FLOOR, 0, 0, TO_FIXED(20), true);

    if (ERZStart) {
        if (++self->timer == 36) {
            EntityImageTrail *trail = RSDK_GET_ENTITY(2 * Player->playerCount + self->playerID, ImageTrail);
            RSDK.ResetEntity(trail, ImageTrail->classID, self);

            if (ERZStart)
                self->shield = SHIELD_LIGHTNING;

            RSDK.PlaySfx(Player->sfxTransform2, false, 255);
            if (self->hyperState) {
                RSDK.PlaySfx(Player->sfxTransform, false, 255);
                self->hyperFlashTimer = 128;
                HUD_HandleHyperFlash(self);
            }

            EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + self->playerID, Shield);
            RSDK.ResetEntity(shield, SuperSparkle->classID, self);
            self->superState = SUPERSTATE_SUPER;
#if GAME_VERSION == VER_100
            self->invincibleTimer = 60;
#endif
            Player_UpdatePhysicsState(self);

            if (self->isChibi) {
#if GAME_VERSION != VER_100
                self->isTransforming = false;
#endif
                self->interaction = true;
                self->state       = Player_State_Air;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, 3);
#if MANIA_USE_PLUS
                if (!self->sidekick)
                    Music_PlayJingle(TRACK_SUPER);
#endif
            }
        }
    }
    else {
        if (++self->timer == 67) {
            EntityImageTrail *trail = RSDK_GET_ENTITY(2 * Player->playerCount + self->playerID, ImageTrail);
            RSDK.ResetEntity(trail, ImageTrail->classID, self);

            if (ERZStart)
                self->shield = SHIELD_LIGHTNING;

            RSDK.PlaySfx(Player->sfxTransform2, false, 255);
            if (self->hyperState) {
                RSDK.PlaySfx(Player->sfxTransform, false, 255);
                self->hyperFlashTimer = 128;
                HUD_HandleHyperFlash(self);
            }

            EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + self->playerID, Shield);
            RSDK.ResetEntity(shield, SuperSparkle->classID, self);
            self->superState = SUPERSTATE_SUPER;
#if GAME_VERSION == VER_100
            self->invincibleTimer = 60;
#endif
            Player_UpdatePhysicsState(self);

            if (self->isChibi) {
#if GAME_VERSION != VER_100
                self->isTransforming = false;
#endif
                self->interaction = true;
                self->state       = Player_State_Air;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, 3);
            }
#if MANIA_USE_PLUS
            if (globals->superMusicEnabled)
                if (!self->sidekick)
                    Music_PlayJingle(TRACK_SUPER);
#endif
        }
    }

    if (!self->isChibi && self->animator.frameID == self->animator.frameCount - 1) {
#if GAME_VERSION != VER_100
        self->isTransforming = false;
#endif
        self->interaction = true;
        self->state       = Player_State_Air;
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_WALK, &self->animator, false, 3);
    }
}
void Player_State_Hurt(void)
{
    RSDK_THIS(Player);

    if (self->onGround) {
        self->state = Player_State_Ground;

        if (self->velocity.x >= -0x20000) {
            if (self->velocity.x <= 0x20000)
                self->groundVel = 0;
            else
                self->groundVel -= 0x20000;
        }
        else {
            self->groundVel += 0x20000;
        }

        self->pushing     = false;
        self->controlLock = false;

        Player_Gravity_False();

        self->skidding = false;
    }
    else {
        Player_Gravity_True();

        self->skidding = 0;

        if (!self->underwater)
            self->velocity.y += 0x3000;
        else
            self->velocity.y += 0xF00;
    }
}
void Player_State_Death(void)
{
    RSDK_THIS(Player);

    if (self->blinkTimer) {
        self->blinkTimer = 0;
        self->visible    = true;
    }

    self->velocity.x = 0;
    self->velocity.y += self->gravityStrength;

    RSDK.SetSpriteAnimation(self->aniFrames, ANI_DIE, &self->animator, false, 0);

    if (!self->sidekick) {
        if (self->camera) {
            if (self->position.y > self->camera->position.y - self->camera->targetMoveVel.y + 0x1800000)
                self->position.y = self->camera->position.y - self->camera->targetMoveVel.y + 0x1800000;

            self->scrollDelay = 2;
        }
    }

    if (self->velocity.y > 0x100000)
        Player_HandleDeath(self);
}
void Player_State_Drown(void)
{
    RSDK_THIS(Player);

    if (self->blinkTimer) {
        self->blinkTimer = 0;
        self->visible    = true;
    }

    self->velocity.x = 0;
    self->velocity.y += self->gravityStrength;

    RSDK.SetSpriteAnimation(self->aniFrames, ANI_DROWN, &self->animator, false, 0);

    if (!self->sidekick) {
        if (self->camera) {
            if (self->position.y > self->camera->position.y + 0x1000000)
                self->position.y = self->camera->position.y + 0x1000000;
            self->scrollDelay = 2;
        }
    }

    if (self->velocity.y > 0x100000)
        Player_HandleDeath(self);
}
void Player_State_DropDash(void)
{
    RSDK_THIS(Player);
    RSDKControllerState *controller = &ControllerInfo[self->controllerID];
    RSDKTriggerState *bumperR       = &TriggerInfoR[self->controllerID];

    if (self->onGround) {
        Player_Gravity_False();

        if (self->right)
            self->direction = FLIP_NONE;
        if (self->left)
            self->direction = FLIP_X;

        int32 vel = 0x80000;
        int32 cap = 0xC0000;
        if (self->superState == SUPERSTATE_SUPER) {
            vel = 0xC0000;
            cap = 0xD0000;

            if (self->camera)
                Camera_ShakeScreen(self->camera->screenID, 6, 6);
        }

        if (self->direction) {
            if (self->velocity.x <= 0) {
                self->groundVel = (self->groundVel >> 2) - vel;

                if (self->groundVel < -cap)
                    self->groundVel = -cap;
            }
            else if (self->angle) {
                self->groundVel = (self->groundVel >> 1) - vel;
            }
            else {
                self->groundVel = -vel;
            }
        }
        else {
            if (self->velocity.x >= 0) {
                self->groundVel = vel + (self->groundVel >> 2);

                if (self->groundVel > cap)
                    self->groundVel = cap;
            }
            else if (self->angle) {
                self->groundVel = vel + (self->groundVel >> 1);
            }
            else {
                self->groundVel = vel;
            }
        }

        if (self->camera && !Zone->autoScrollSpeed) {
            self->scrollDelay   = 8;
            self->camera->state = Camera_State_FollowY;
        }

        EntityDust *dust = CREATE_ENTITY(Dust, self, self->position.x, self->position.y);
        RSDK.SetSpriteAnimation(Dust->aniFrames, 2, &dust->animator, true, 0);
        dust->state = Dust_State_DustPuff;
        dust->position.y += RSDK.GetHitbox(&self->animator, 0)->bottom << 16;
        dust->direction = self->direction;
        dust->drawGroup = self->drawGroup;

        RSDK.StopSfx(Player->sfxDropdash);
        if (self->superState == SUPERSTATE_SUPER)
            RSDK.PlaySfx(Player->sfxPeelRelease, false, 255);
        else
            RSDK.PlaySfx(Player->sfxRelease, false, 255);

        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
        if (!self->collisionMode)
            self->position.y += self->jumpOffset;
        self->pushing = 0;
        self->state   = Player_State_Roll;
    }
    else if (self->jumpHold || (controller->keyUp.down && self->jumpHold || bumperR->keyBumper.down)) {
        Player_HandleAirFriction();
        Player_HandleAirMovement();

        self->animator.speed += 8;
        if (self->animator.speed > 0x100)
            self->animator.speed = 0x100;
    }
    else {
        self->jumpAbilityState = 0;
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
        self->state = Player_State_Air;
    }
}
void Player_State_BubbleBounce(void)
    {
    RSDK_THIS(Player);

    if (self->shield == SHIELD_BUBBLE) {
        if (!self->onGround) {
            Player_HandleAirFriction();
            Player_HandleAirMovement();
        }
        else {
            self->controlLock = 0;

            int32 vel = 0;
            if (self->underwater != 1) // only apply lower velocity if in water level types, pools use regular vel
                vel = self->gravityStrength + 0x78000;
            else
                vel = self->gravityStrength + 0x40000;
            self->onGround = false;

            self->velocity.x = (self->groundVel * RSDK.Cos256(self->angle) + vel * RSDK.Sin256(self->angle)) >> 8;
            if (self->superState == SUPERSTATE_SUPER)
                self->velocity.y = ((self->groundVel * RSDK.Sin256(self->angle) - vel * RSDK.Cos256(self->angle)) >> 8) * 1.25;
            else
                self->velocity.y = (self->groundVel * RSDK.Sin256(self->angle) - vel * RSDK.Cos256(self->angle)) >> 8;

            Player_Gravity_True();

            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
            self->animator.speed = (abs(self->groundVel) >> 12) + 0x30;

            EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(self), Shield);
            RSDK.SetSpriteAnimation(Shield->aniFrames, 9, &shield->fxAnimator, true, 0);
            RSDK.SetSpriteAnimation(-1, 0, &shield->shieldAnimator, true, 0);
            shield->state = Shield_State_BubbleBounced;
            if (self->animator.speed > 0xF0)
                self->animator.speed = 0xF0;

            self->angle            = 0;
            self->collisionMode    = CMODE_FLOOR;
            self->applyJumpCap     = false;
            if (self->superState == SUPERSTATE_SUPER)
                self->jumpAbilityState = 22;
            else
                self->jumpAbilityState = 1;
            RSDK.PlaySfx(Shield->sfxBubbleBounce, false, 255);

            self->state = Player_State_Air;
        }
    }
    else {
        self->state = Player_State_Air;
    }
}
void Player_State_TailsFlight(void)
{
    RSDK_THIS(Player);

    Player_HandleAirFriction();

    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();
    RSDKControllerState *controller = &ControllerInfo[self->controllerID];
    RSDKAnalogState *analog         = &AnalogStickInfoL[self->controllerID];
    RSDKTriggerState *bumperR       = &TriggerInfoR[self->controllerID];

    if (addendumOptions->tailsMoveset == TAILSMOVESET_ADDENDUM) {
        if (((controller->keyDown.down || analog->keyDown.down) && self->jumpPress) || bumperR->keyBumper.press)
            self->state = Player_State_FlightCancel;
    }

    if (self->onGround) {
        self->state = Player_State_Ground;
        Player_HandleAirMovement();
    }
    else {
        if (self->velocity.y < -0x10000)
            self->abilitySpeed = 0x800;

        if (self->velocity.y <= 0) {
            if (self->abilityValue >= 60)
                self->abilitySpeed = 0x800;
            else
                self->abilityValue++;
        }

        if (addendumOptions->tailsMoveset == TAILSMOVESET_ADDENDUM) {
            if (self->superState == SUPERSTATE_SUPER)
                self->velocity.y += (self->abilitySpeed / 2);
            else
                self->velocity.y += self->abilitySpeed;
        }
        else
            self->velocity.y += self->abilitySpeed;

        uint16 slot = 0;
        if (!self->sidekick)
            slot = SceneInfo->entitySlot;

        if (self->position.y < Zone->playerBoundsT[slot] + 0x100000 && self->velocity.y < 0)
            self->velocity.y = 0;

        EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        if (globals->gameMode != MODE_COMPETITION && !self->isChibi && !leader->isChibi)
            Player_HandleFlyCarry(leader);

        bool32 notSuper = true;
        if (addendumOptions->tailsMoveset == TAILSMOVESET_ADDENDUM) {
            if (self->superState == SUPERSTATE_SUPER)
                notSuper = false;
            else
                notSuper = true;
        }

        if (self->timer >= 480 && notSuper) {
            if (!self->underwater) {
                if (leader->state == Player_State_FlyCarried)
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_LIFT_TIRED, &self->animator, false, 0);
                else
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_TIRED, &self->animator, false, 0);
            }
            else {
                if (leader->state == Player_State_FlyCarried)
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_SWIM_LIFT, &self->animator, false, 0);
                else
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_SWIM_TIRED, &self->animator, false, 0);
            }
        }
        else {
            if (self->underwater) {
                if (leader->state == Player_State_FlyCarried) {
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_SWIM_LIFT, &self->animator, false, 0);
                }
                else {
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_SWIM, &self->animator, false, 0);
                    self->animator.speed = 128;
                    if (self->velocity.y >= 0)
                        self->animator.speed = 64;
                }
            }
            else {
                if (leader->state != Player_State_FlyCarried || self->velocity.y >= 0)
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY, &self->animator, false, 0);
                else
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_LIFT, &self->animator, false, 0);

                if (self->velocity.y >= 0)
                    self->animator.speed = 128;
                else
                    self->animator.speed = 256;
            }

            if (++self->timer == 480 && notSuper) {
                if (!self->underwater) {
                    if (leader->state == Player_State_FlyCarried)
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_LIFT_TIRED, &self->animator, false, 0);
                    else
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_TIRED, &self->animator, false, 0);
                }
                else {
                    if (leader->state == Player_State_FlyCarried)
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_SWIM_LIFT, &self->animator, false, 0);
                    else
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_SWIM_TIRED, &self->animator, false, 0);
                }
            }
            else if (self->jumpPress && (!self->underwater || leader->state != Player_State_FlyCarried)) {
                self->abilitySpeed = -0x2000;
                self->abilityValue = 0;
            }
        }
    }
}
void Player_State_FlyCarried(void)
{
    RSDK_THIS(Player);

    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();
    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    if (sidekick->state != Player_State_TailsFlight)
        self->state = Player_State_Air;

    if (self->flyCarrySidekickPos.x != self->flyCarryLeaderPos.x)
        self->state = Player_State_Air;

    if (self->onGround && self->velocity.y >= 0)
        self->state = Player_State_Ground;

    if (addendumOptions->tailsMoveset == TAILSMOVESET_ADDENDUM) {
        if (self->jumpPress && self->down) {
            self->state = Player_State_Air;

            if (!self->underwater)
                self->velocity.y = -0x40000;
            else
                self->velocity.y = -0x20000;

            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
        }
    }
    
    sidekick->flyCarryTimer = 30;
}
void Player_State_FlightCancel(void)
{
    RSDK_THIS(Player);
    self->state = Player_State_Air;
    RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
}
void Player_State_KnuxGlideLeft(void)
{
    RSDK_THIS(Player);

    if (!self->onGround) {
        if (!self->jumpHold) {
            self->timer        = 0;
            self->abilitySpeed = 0;
            self->velocity.x >>= 2;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_DROP, &self->animator, false, 0);
            self->state = Player_State_KnuxGlideDrop;
        }
        else {
            if (self->timer == 256) {
                if (self->abilitySpeed < 0x180000)
                    self->abilitySpeed += 0x400;
            }
            else if (self->abilitySpeed < 0x40000) {
                self->abilitySpeed += 0x1000;
            }

            if (self->velocity.y <= 0x8000)
                self->velocity.y += 0x2000;
            else
                self->velocity.y -= 0x2000;

            if (self->timer < 256)
                self->timer += 4;
            int32 storeX = self->position.x;

            int32 highY = 0, lowY = 0;
            if (self->isChibi) {
                highY = -0x10000;
                lowY  = 0x30000;
            }
            else {
                highY = -0x20000;
                lowY  = 0xB0000;
            }

            bool32 collidedHigh = false, collidedLow = false;
            int32 highPos = 0, lowPos = 0;
            if (self->timer >= 128) {
                self->position.x += self->velocity.x;
                int32 startPos = self->position.x;

                collidedHigh = RSDK.ObjectTileCollision(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, -0xC0000, highY, true);
                highPos      = self->position.x;

                self->position.x = startPos;
                collidedLow      = RSDK.ObjectTileCollision(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, -0xC0000, lowY, true);
                lowPos           = self->position.x;
            }

            int32 prevVelX   = self->velocity.x;
            bool32 isMoving  = self->velocity.x;
            if (self->velocity.x > -0x40000) {
                self->velocity.x = self->abilitySpeed * RSDK.Cos512(self->timer) >> 9;
            }
            if (!prevVelX && self->velocity.x) {
                isMoving           = false;
                if (self->position.y > Zone->playerBoundsT[SceneInfo->entitySlot])
                    self->abilitySpeed = 0x40000;
                else
                    self->abilitySpeed = 0;
                self->velocity.x   = self->abilitySpeed * RSDK.Cos512(self->timer) >> 9;
            }

            self->position.x = storeX;
            if (self->right) {
                self->state            = Player_State_KnuxGlideRight;
                self->direction        = FLIP_NONE;
                self->animator.frameID = 0;
                self->animator.timer   = 0;
            }
            else if (!isMoving && self->timer == 256) {
                if (collidedHigh || collidedLow) {
                    self->abilitySpeed = 0;
                    self->timer        = 0;
                    if (highPos == lowPos) {
                        RSDK.PlaySfx(Player->sfxGrab, false, 255);

                        if (self->hyperState) {
                            if (abs(self->prevVelocity.x) >= 0x90000) {
                                self->hyperAttacking = true;
                                Camera_ShakeScreen(RSDK.GetEntitySlot(self), 10, 0);
                                RSDK.StopSfx(Player->sfxGrab);
                                RSDK.PlaySfx(Player->sfxWallRumble, false, 0xFF);
                            }
                        }

                        self->state = Player_State_KnuxWallClimb;
                        self->velocity.x = 0;
                        self->velocity.y = 0;
                    }
                    else {
                        self->velocity.x >>= 2;
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_DROP, &self->animator, false, 0);
                        self->state = Player_State_KnuxGlideDrop;
                    }
                }
                else if (collidedHigh) {
                    self->timer        = 0;
                    self->abilitySpeed = 0;
                    self->velocity.x >>= 2;
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_DROP, &self->animator, false, 0);
                    self->state = Player_State_KnuxGlideDrop;
                }
            }

            if (self->position.y < Zone->playerBoundsT[SceneInfo->entitySlot] + 0x100000) {
                self->velocity.x   = 0;
                self->abilitySpeed = 0;
                prevVelX           = 0;
            }
        }
    }
    else if (self->collisionMode == CMODE_FLOOR) {
        self->timer = 0;
        self->state = Player_State_KnuxGlideSlide;
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_SLIDE, &self->animator, false, 0);
        self->groundVel = self->velocity.x;

        EntityDust *dust = CREATE_ENTITY(Dust, self, self->position.x, self->position.y);
        dust->state      = Dust_State_GlideTrail;
    }
    else {
        self->state = Player_State_Ground;

        Player_Gravity_False();

        self->skidding = 0;
    }

    if (self->position.y < Zone->playerBoundsT[SceneInfo->entitySlot] + 0x100000) {
        self->velocity.x   = 0;
        self->abilitySpeed = 0;
    }
}
void Player_State_KnuxGlideRight(void)
{
    RSDK_THIS(Player);

    if (!self->onGround) {
        if (!self->jumpHold) {
            self->timer        = 0;
            self->abilitySpeed = 0;
            self->velocity.x >>= 2;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_DROP, &self->animator, false, 0);
            self->state = Player_State_KnuxGlideDrop;
        }
        else {
            if (!self->timer) {
                if (self->abilitySpeed < 0x180000)
                    self->abilitySpeed += 0x400;
            }
            else if (self->abilitySpeed < 0x40000) {
                self->abilitySpeed += 0x1000;
            }

            if (self->velocity.y <= 0x8000)
                self->velocity.y += 0x2000;
            else
                self->velocity.y -= 0x2000;

            if (self->timer > 0)
                self->timer -= 4;
            int32 storeX = self->position.x;

            int32 highY = 0, lowY = 0;
            if (self->isChibi) {
                highY = -0x10000;
                lowY  = 0x30000;
            }
            else {
                highY = -0x20000;
                lowY  = 0xB0000;
            }

            bool32 collidedHigh = false, collidedLow = false;
            int32 highPos = 0, lowPos = 0;
            if (self->timer < 128) {
                self->position.x += self->velocity.x;
                int32 startPos = self->position.x;

                collidedHigh = RSDK.ObjectTileCollision(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, 0xC0000, highY, true);
                highPos      = self->position.x;

                self->position.x = startPos;
                collidedLow      = RSDK.ObjectTileCollision(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, 0xC0000, lowY, true);
                lowPos           = self->position.x;
            }

            int32 prevVelX   = self->velocity.x;
            bool32 isMoving  = self->velocity.x;
            if (self->velocity.x < 0x40000) {
                self->velocity.x = self->abilitySpeed * RSDK.Cos512(self->timer) >> 9;
            }
            if (!prevVelX && self->velocity.x) {
                isMoving           = false;
                self->abilitySpeed = 0x40000;
                self->velocity.x   = self->abilitySpeed * RSDK.Cos512(self->timer) >> 9;
            }

            self->position.x = storeX;
            if (self->left) {
                self->state            = Player_State_KnuxGlideLeft;
                self->direction        = FLIP_X;
                self->animator.frameID = 0;
                self->animator.timer   = 0;
            }
            else if (!isMoving && !self->timer) {
                if (collidedHigh || collidedLow) {
                    self->abilitySpeed = 0;
                    self->timer        = 0;
                    if (highPos == lowPos) {
                        RSDK.PlaySfx(Player->sfxGrab, false, 255);

                        if (self->hyperState) {
                            if (abs(self->prevVelocity.x) >= 0x90000) {
                                self->hyperAttacking = true;
                                Camera_ShakeScreen(RSDK.GetEntitySlot(self), 10, 0);
                                RSDK.StopSfx(Player->sfxGrab);
                                RSDK.PlaySfx(Player->sfxWallRumble, false, 0xFF);
                            }
                        }

                        self->state      = Player_State_KnuxWallClimb;
                        self->velocity.x = 0;
                        self->velocity.y = 0;
                    }
                    else {
                        self->velocity.x >>= 2;
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_DROP, &self->animator, false, 0);
                        self->state = Player_State_KnuxGlideDrop;
                    }
                }
                else if (collidedHigh) {
                    self->timer        = 0;
                    self->abilitySpeed = 0;
                    self->velocity.x >>= 2;
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_DROP, &self->animator, false, 0);
                    self->state = Player_State_KnuxGlideDrop;
                }
            }
        }
    }
    else if (self->collisionMode) {
        self->state = Player_State_Ground;

        Player_Gravity_False();

        self->skidding = 0;
    }
    else {
        self->timer = 0;
        self->state = Player_State_KnuxGlideSlide;
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_SLIDE, &self->animator, false, 0);
        self->groundVel = self->velocity.x;

        EntityDust *dust = CREATE_ENTITY(Dust, self, self->position.x, self->position.y);
        dust->state      = Dust_State_GlideTrail;
    }

    if (self->position.y < Zone->playerBoundsT[SceneInfo->entitySlot] + 0x100000) {
        self->velocity.x   = 0;
        self->abilitySpeed = 0;
    }
}
void Player_State_KnuxGlideDrop(void)
{
    RSDK_THIS(Player);
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();
    RSDKControllerState *controller  = &ControllerInfo[self->controllerID];
    RSDKAnalogState *analog          = &AnalogStickInfoL[self->controllerID];

    if (self->onGround && self->animator.animationID != ANI_JUMP) {
        if (!self->timer)
            RSDK.PlaySfx(Player->sfxLand, false, 255);

        Player_Gravity_False();

        if (abs(Zone->autoScrollSpeed) > 0x20000) {
            if (Zone->autoScrollSpeed <= 0) {
                self->groundVel  = Zone->autoScrollSpeed + 0x20000;
                self->velocity.x = Zone->autoScrollSpeed + 0x20000;
            }
            else {
                self->groundVel  = Zone->autoScrollSpeed - 0x20000;
                self->velocity.x = Zone->autoScrollSpeed - 0x20000;
            }
            self->timer = 16;
        }
        else {
            self->groundVel  = 0;
            self->velocity.x = 0;
            if (controller->keyDown.down)
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_CROUCH, &self->animator, false, 2);
            else
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_LAND, &self->animator, false, 0);
        }

        if (self->jumpPress) {
            Player_Action_Jump(self);
            self->timer = 0;
        }

        if (controller->keyDown.down || analog->keyDown.down) {
            self->state    = Player_State_Crouch;
            self->skidding = 0;
            self->timer    = 0;
        }
        else {
            if (self->timer >= 16) {
                self->state    = Player_State_Ground;
                self->skidding = 0;
                self->timer    = 0;
            }
            else {
                self->timer++;
            }
        }
    }
    else {
        Player_HandleAirFriction();
        Player_HandleAirMovement();
        
        if (addendumOptions->knuxMoveset == KNUXMOVESET_ADDENDUM) {
            if (controller->keyDown.down && self->jumpPress || analog->keyDown.down && self->jumpPress) {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->jumpAbilityState = 0;
                self->state = Player_State_Air;
            }
        }
    }
}
void Player_State_KnuxGlideSlide(void)
{
    RSDK_THIS(Player);
    RSDKControllerState *controller = &ControllerInfo[self->controllerID];
    RSDKAnalogState *analog         = &AnalogStickInfoL[self->controllerID];

    if (!self->onGround) {
        self->timer = 0;
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_DROP, &self->animator, false, 0);
        self->state = Player_State_KnuxGlideDrop;
    }
    else {
        if (self->groundVel && !Zone->autoScrollSpeed) {
            if (!self->timer)
                RSDK.PlaySfx(Player->sfxSlide, false, 255);

            self->timer = (self->timer + 1) & 7;
            if (self->animator.frameID == 2) {
                self->animator.speed = 0;
                self->animator.timer = 0;
            }

            bool32 canGetUp = true;
            if (self->groundVel <= 0) {
                self->groundVel += 0x2000;
                if (self->groundVel < 0)
                    canGetUp = false;
            }
            else {
                self->groundVel -= 0x2000;
                if (self->groundVel > 0)
                    canGetUp = false;
            }

            if (canGetUp || !self->jumpHold) {
                self->animator.frameID = 3;
                self->timer            = 0;
                self->groundVel        = 0;
            }
        }
        else {
            Player_Gravity_False();

            self->animator.speed = 1;

            if (controller->keyDown.down || analog->keyDown.down) {
                self->state    = Player_State_Crouch;
                self->skidding = 0;
                self->timer    = 0;
            }
            else {
                if (self->timer >= 16) {
                    self->state    = Player_State_Ground;
                    self->skidding = 0;
                    self->timer    = 0;
                }
                else {
                    self->timer++;
                }
            }
        }
    }
}
void Player_State_KnuxWallClimb(void)
{
    RSDK_THIS(Player);

    if (self->onGround) {
        self->state = Player_State_Ground;

        Player_Gravity_False();
    }
    else {
        if (self->up) {
            if (self->superState == SUPERSTATE_SUPER)
                self->velocity.y = -0x20000;
            else
                self->velocity.y = -0x10000;

            int32 boundary = Zone->playerBoundsT[SceneInfo->entitySlot] + 0x140000;
            if (self->position.y < boundary)
                self->position.y = boundary;
        }
        else if (self->down) {
            if (self->superState == SUPERSTATE_SUPER)
                self->velocity.y = 0x20000;
            else
                self->velocity.y = 0x10000;
        }
        else {
            self->velocity.y = 0;
        }

        if (self->jumpPress) {
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
            self->state            = Player_State_Air;
            self->applyJumpCap     = false;
            self->jumpAbilityState = 1;

            RSDK.PlaySfx(Player->sfxJump, false, 255);
            if (self->direction == FLIP_X) {
                self->velocity.x = 0x40000;
                self->groundVel  = 0x40000;
                self->direction  = FLIP_NONE;
            }
            else {
                self->velocity.x = -0x40000;
                self->groundVel  = -0x40000;
                self->direction  = FLIP_X;
            }

            self->velocity.y = -0x38000;
            if (self->underwater) {
                self->velocity.x >>= 1;
                self->velocity.y >>= 1;
                self->groundVel >>= 1;
            }
        }
        else {
            Hitbox *hitbox = Player_GetHitbox(self);
            int32 storeX   = self->position.x;

            int32 highY = 0;
            int32 lowY  = 0;

            int32 roofX = 0;
            int32 roofY = 0;
            if (self->isChibi) {
                highY = -0x40000;
                lowY  = 0x40000;
                roofY = -0xC0000;
            }
            else {
                highY = -0xA0000;
                lowY  = 0xB0000;
                roofY = -0x140000;
            }

            bool32 collidedHigh = false, collidedLow = false;
            if (self->direction) {
                collidedHigh = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, hitbox->left << 16, highY, 8);
                int32 targetX  = self->position.x;

                self->position.x = storeX;
                collidedLow      = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, hitbox->left << 16, lowY, 8);
                if (self->velocity.y < 0 && self->position.x < targetX)
                    self->velocity.y = 0;
                roofX = -0x40000;
            }
            else {
                collidedHigh = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, hitbox->right << 16, highY, 8);
                int32 targetX  = self->position.x;

                self->position.x = storeX;
                collidedLow      = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, hitbox->right << 16, lowY, 8);
                if (self->velocity.y < 0 && self->position.x > targetX)
                    self->velocity.y = 0;
                roofX = 0x40000;
            }
            self->position.y += self->velocity.y;

            if (RSDK.ObjectTileCollision(self, self->collisionLayers, CMODE_ROOF, self->collisionPlane, roofX, roofY, true))
                self->velocity.y = 0;

            if (!collidedHigh) {
                self->position.y &= 0xFFF00000;
                if (self->isChibi)
                    self->position.y -= 0x10000;
                else
                    self->position.y += 0xA0000;
                self->velocity.y     = 0;
                self->position.x     = storeX;
                self->state          = Player_State_KnuxLedgePullUp;
                self->timer          = 1;
                self->tileCollisions = TILECOLLISION_NONE;
                self->velocity.y     = 0;
            }
            else if (!collidedLow) {
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_DROP, &self->animator, false, 2);
                self->velocity.y = 0;
                self->state      = Player_State_KnuxGlideDrop;
            }
            else {
                if (!self->velocity.y)
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_CLIMB_IDLE, &self->animator, false, 0);
                else if (self->velocity.y > 0)
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_CLIMB_DOWN, &self->animator, false, 0);
                else if (self->velocity.y < 0) {
                    if (self->superState == SUPERSTATE_SUPER)
                        self->animator.speed = 2;
                    else
                        self->animator.speed = 1;
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_CLIMB_UP, &self->animator, false, 0);
                }

                self->velocity.y = 0;
            }
        }

        self->hyperAttacking = false;
    }
}
void Player_State_KnuxLedgePullUp(void)
{
    RSDK_THIS(Player);

    self->left  = false;
    self->right = false;
    RSDK.SetSpriteAnimation(self->aniFrames, ANI_LEDGE_PULL_UP, &self->animator, false, 1);

    Animator backup;
    memcpy(&backup, &self->animator, sizeof(backup));

    RSDK.ProcessAnimation(&self->animator);
    if (self->timer != self->animator.frameID && self->animator.frameID < 6) {
        self->timer = self->animator.frameID;

        if (!self->isChibi) {
            if (self->direction == FLIP_X)
                self->position.x -= 0x50000;
            else
                self->position.x += 0x50000;

            self->position.y -= 0x80000;
        }
        else {
            if (self->direction == FLIP_X)
                self->position.x -= 0x40000;
            else
                self->position.x += 0x40000;

            self->position.y -= 0x40000;
        }
    }

    if (self->animator.frameID == 6) {
        self->onGround       = true;
        self->tileCollisions = TILECOLLISION_DOWN;
    }

    if (self->animator.frameID == self->animator.frameCount - 1) {
        self->timer = 0;
        self->state = Player_State_Ground;
    }

    memcpy(&self->animator, &backup, sizeof(backup));
}
#if MANIA_USE_PLUS
void Player_State_MightyHammerDrop(void)
{
    RSDK_THIS(Player);
    RSDKControllerState* controller = &ControllerInfo[self->controllerID];

    if (self->onGround) {
        self->controlLock = 0;
        self->onGround    = false;

        int32 dropForce = self->gravityStrength + (self->underwater == 1 ? 0x10000 : 0x20000);
        int32 groundVel = self->groundVel - (self->groundVel >> 2);

        self->velocity.x = (groundVel * RSDK.Cos256(self->angle) + dropForce * RSDK.Sin256(self->angle)) >> 8;
        if (controller->keyDown.down && (self->angle > 10 && self->angle < 502))
            self->velocity.y = self->velocity.y;
        else
            self->velocity.y = (groundVel * RSDK.Sin256(self->angle) - dropForce * RSDK.Cos256(self->angle)) >> 8;

        Player_Gravity_True();

        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);

        self->animator.speed = MIN((abs(self->groundVel) >> 12) + 0x30, 0xF0);

        RSDK.StopSfx(Player->sfxMightyDrill);
        RSDK.PlaySfx(Player->sfxMightyLand, false, 0xFF);
        if (self->superState == SUPERSTATE_SUPER) {
            if (self->hyperState) {
                self->hyperFlashTimer = 128;
                HUD_HandleHyperFlash(self);
                self->hyperAttacking = true;
                Camera_ShakeScreen(RSDK.GetEntitySlot(self), 0, 8);
            }
            else if (self->miracleState)
                Camera_ShakeScreen(RSDK.GetEntitySlot(self), 0, 8);
            else
                Camera_ShakeScreen(RSDK.GetEntitySlot(self), 0, 6);
        }
        else
            Camera_ShakeScreen(RSDK.GetEntitySlot(self), 0, 4);

        Hitbox *hitbox = RSDK.GetHitbox(&self->animator, 0);
        Player_SpawnMightyHammerdropDust(0x10000, hitbox);
        Player_SpawnMightyHammerdropDust(-0x10000, hitbox);
        Player_SpawnMightyHammerdropDust(0x18000, hitbox);
        Player_SpawnMightyHammerdropDust(-0x18000, hitbox);
        Player_SpawnMightyHammerdropDust(0x20000, hitbox);
        Player_SpawnMightyHammerdropDust(-0x20000, hitbox);

        self->angle            = 0;
        self->collisionMode    = CMODE_FLOOR;
        self->applyJumpCap     = false;
        self->jumpAbilityState = 3;

        if (self->invincibleTimer > 0) {
            if (self->invincibleTimer < 8)
                self->invincibleTimer = 8;
            if (controller->keyDown.down)
                self->state = Player_State_Ground;
            else
                self->state = Player_State_Air;
        }
        else {
            self->invincibleTimer = -8;
            if (controller->keyDown.down)
                self->state = Player_State_Ground;
            else
                self->state = Player_State_Air;
        }
    }
    else {
        Player_HandleAirFriction();
        Player_HandleAirMovement();

        if (self->velocity.y <= 0x10000) {
            self->state = Player_State_Air;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
        }
    }
}
void Player_State_MightyUnspin(void)
{
    RSDK_THIS(Player);

    Player_HandleAirFriction();

    if (self->onGround) {
        self->state = Player_State_Ground;

        Player_Gravity_False();
    }
    else {
        ++self->blinkTimer;

        Player_Gravity_True();

        Player_HandleAirMovement();
        self->nextGroundState = Player_State_Ground;
    }
}
void Player_State_MightyWallStick(void)
{
    RSDK_THIS(Player);
    RSDKTriggerState *bumperR = &TriggerInfoR[self->controllerID];
    Hitbox *hitbox = Player_GetHitbox(self);
    int32 storeX   = self->position.x;

    int32 highY = 0;
    int32 lowY  = 0;

    int32 roofX = 0;
    int32 roofY = 0;
    if (self->isChibi) {
        highY = -0x10000;
        lowY  = 0x30000;
    }
    else {
        highY = -0x20000;
        lowY  = 0xB0000;
    }

    bool32 collidedHigh = false, collidedLow = false;
    if (!self->direction && !self->isChibi || self->direction && self->isChibi) {
        collidedHigh = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, hitbox->left << 16, highY, 8);
        int32 highX  = self->position.x;

        self->position.x = storeX;
        collidedLow      = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, hitbox->left << 16, lowY, 8);
    }
    else {
        collidedHigh = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, hitbox->right << 16, highY, 8);
        int32 highY  = self->position.x;

        self->position.x = storeX;
        collidedLow      = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, hitbox->right << 16, lowY, 8);
    }
    self->velocity.y = 0x3000;
    if (self->onGround) {
        self->state = Player_State_Ground;
    }
    if (self->timer >= 64 || !collidedHigh) {
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
        self->applyJumpCap     = true;
        self->jumpAbilityState = 0;
        self->direction        = self->direction != FLIP_NONE;
        self->state            = Player_State_Air;
    }
    if (self->jumpPress || bumperR->keyBumper.down) { /// HERE WE GO
        if (self->direction == FLIP_NONE && !self->isChibi || self->direction == FLIP_X && self->isChibi) {
            if (self->down & !self->left & !self->right) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.y       = 0x80000;
                self->velocity.x       = 0;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
            if (self->down && self->right) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.x       = 0x70000;
                self->velocity.y       = 0x50000;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
            if (!self->left && !self->down) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.x       = 0x70000;
                self->velocity.y       = -0x5000;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
            if (self->left || self->up && self->right) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.x       = 0x70000;
                self->velocity.y       = -0x80000;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
            if (self->up && !self->right) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->timer            = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.y       = -0x80000;
                self->velocity.x       = 0;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
        }
        if (self->direction == FLIP_X && !self->isChibi || self->direction == FLIP_NONE && self->isChibi) {
            if (self->down & !self->left & !self->right) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.y       = 0x80000;
                self->velocity.x       = 0;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
            if (self->down && self->left) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.x       = -0x70000;
                self->velocity.y       = 0x50000;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
            if (!self->right && !self->down) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.x       = -0x70000;
                self->velocity.y       = -0x5000;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
            if (self->right || self->up && self->left) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.x       = -0x70000;
                self->velocity.y       = -0x80000;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
            if (self->up && !self->left) {
                RSDK.PlaySfx(Player->sfxJump, false, 255);
                self->applyJumpCap     = false;
                self->jumpAbilityState = 1;
                self->timer            = 1;
                self->direction        = self->direction != FLIP_NONE;
                self->velocity.y       = -0x80000;
                self->velocity.x       = 0;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
                self->state = Player_State_Air;
            }
        }
    }
    self->timer++;
}
void Player_SpawnMightyHammerdropDust(int32 speed, Hitbox *hitbox)
{
    RSDK_THIS(Player);

    EntityDust *dust = CREATE_ENTITY(Dust, self, self->position.x, self->position.y);
    dust->state      = Dust_State_DustPuff_Collide;
    dust->position.y += hitbox->bottom << 16;
    dust->drawGroup       = self->drawGroup;
    dust->collisionPlane  = self->collisionPlane;
    dust->collisionMode   = 0;
    dust->collisionLayers = self->collisionLayers;
    dust->tileCollisions  = TILECOLLISION_DOWN;
    dust->animator.frameDuration += 4 * (4 - (abs(speed) >> 15));
    dust->velocity.x = dust->groundVel = self->velocity.x * (Zone->autoScrollSpeed != 0) + (speed >> self->isChibi);
    if (self->isChibi) {
        dust->drawFX |= FX_SCALE;
        dust->scale.x = 256;
        dust->scale.y = 256;
    }

    if (!self->angle) {
        RSDK.ObjectTileGrip(dust, dust->collisionLayers, CMODE_FLOOR, dust->collisionPlane, 0, 0, 4);
    }
    else {
        for (int32 i = 0; i < 0x10; ++i) {
            if (RSDK.ObjectTileGrip(dust, dust->collisionLayers, CMODE_FLOOR, dust->collisionPlane, 0, 0, 8))
                break;

            dust->position.y += 0x80000;
        }
    }
}
bool32 Player_CheckMightyUnspin(EntityPlayer *player, int32 bounceDistance, bool32 checkHammerDrop, int32 *uncurlTimer)
{
    RSDK_THIS_GEN();

    if (player->characterID != ID_MIGHTY)
        return false;

    if (player->superState == SUPERSTATE_SUPER)
        return false;

    if (player->state == Player_State_Hurt || player->state == Player_State_Death || player->state == Player_State_Drown || player->invincibleTimer
        || player->blinkTimer > 0) {
        return false;
    }

    int32 anim = player->animator.animationID;
    if (anim == ANI_JUMP || anim == ANI_SPINDASH || anim == ANI_HAMMERDROP) {
        int32 angle = RSDK.ATan2(player->position.x - self->position.x, player->position.y - self->position.y);
        if (player->animator.animationID != ANI_UNSPIN) {
            player->velocity.x = bounceDistance * RSDK.Cos256(angle);
            player->groundVel  = player->velocity.x;
        }

        player->velocity.y = bounceDistance * RSDK.Sin256(angle);

        if (checkHammerDrop) {
            if (player->state == Player_State_MightyHammerDrop) {
                player->state = Player_State_Air;
                RSDK.SetSpriteAnimation(player->aniFrames, ANI_JUMP, &player->animator, false, 0);
            }

            if (player->animator.animationID == ANI_SPINDASH) {
                RSDK.SetSpriteAnimation(player->aniFrames, ANI_JUMP, &player->animator, false, 0);
                if (player->state == Player_State_Spindash) {
                    if (player->onGround)
                        player->state = Player_State_Roll;
                    else
                        player->state = Player_State_Air;
                }
            }
        }
        else {
            player->velocity.y = -0x48000;

            if (!(player->direction & FLIP_X))
                player->velocity.x = -0x28000;
            else
                player->velocity.x = 0x28000;

            if (player->underwater) {
                player->velocity.x >>= 1;
                player->velocity.y = -0x24000;
            }

            player->blinkTimer = 121;
            player->visible    = true;
            RSDK.SetSpriteAnimation(player->aniFrames, ANI_UNSPIN, &player->animator, false, 0);
            RSDK.PlaySfx(Player->sfxMightyUnspin, false, 255);
            player->onGround         = 0;
            player->applyJumpCap     = false;
            player->jumpAbilityState = 0;
            player->state            = Player_State_MightyUnspin;
        }

        player->applyJumpCap = false;
        if (uncurlTimer && !*uncurlTimer) {
            if (player->animator.animationID != ANI_UNSPIN)
                RSDK.PlaySfx(Player->sfxPimPom, false, 255);
            *uncurlTimer = 8;
        }

        return true;
    }

    if (checkHammerDrop == 2 && anim == ANI_CROUCH) {
        if (!player->uncurlTimer) {
            RSDK.PlaySfx(Player->sfxPimPom, false, 255);
            player->uncurlTimer = 30;
            if (self->position.x > player->position.x)
                player->groundVel = -0x10000;
            else
                player->groundVel = 0x10000;
        }

        return true;
    }

    return false;
}
void Player_State_RayGlide(void)
{
    RSDK_THIS(Player);
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();
    EntityImageTrail *trail = RSDK_GET_ENTITY(2 * Player->playerCount + RSDK.GetEntitySlot(self), ImageTrail);

    if (addendumOptions->rayMoveset == RAYMOVESET_ADDENDUM) {
        if (self->superState != SUPERSTATE_SUPER || self->speedShoesTimer <= 0) {
            if ((abs(self->velocity.x) >= 0x80000) || (abs(self->velocity.y >= 0x80000))) {
                trail->baseAlpha = 0x100;
            }
            else {
                trail->baseAlpha = 0;
            }
        }
    }

    if (self->rotation) {
        if (self->abilityValue < 0x70)
            self->abilityValue += 8;
    }
    else {
        if (self->abilityValue > 0x10)
            self->abilityValue -= 8;
    }

    if (self->abilitySpeed) {
        self->velocity.y += self->abilitySpeed >> (2 - (self->underwater != false));
        if (self->velocity.y < self->abilitySpeed) {
            self->velocity.y   = self->abilitySpeed;
            self->abilitySpeed = 0;
        }
    }
    else {
        self->velocity.y += (self->gravityStrength * RSDK.Cos512(self->abilityValue)) >> 9;
    }

    if (self->velocity.y < -0x60000)
        self->velocity.y = -0x60000;

    if (self->rotation == true) {
        if (self->velocity.y > 0x10000)
            self->velocity.y -= self->velocity.y >> 2;
    }

    if (self->velocity.y <= 0) {
        self->abilityValues[0] -= 22 * RSDK.Sin256(0x50 - self->abilityValue);
        if (self->abilityValues[0] < 0x40000)
            self->abilityValues[0] = 0x40000;
    }
    else if (self->velocity.y > self->abilityValues[0]) {
        self->abilityValues[0] = self->velocity.y - (self->velocity.y >> 6);
    }

    if (self->velocity.x) {
        if (self->direction) {
            self->velocity.x -= (22 * RSDK.Sin256(0x50 - self->abilityValue)) >> (uint8)(self->underwater != false);

            if (self->velocity.x > -0x10000)
                self->velocity.x = -0x10000;

            if (self->velocity.x < -self->abilityValues[0])
                self->velocity.x = -self->abilityValues[0];
        }
        else {
            self->velocity.x += (22 * RSDK.Sin256(0x50 - self->abilityValue)) >> (uint8)(self->underwater != false);

            if (self->velocity.x < 0x10000)
                self->velocity.x = 0x10000;

            if (self->velocity.x > self->abilityValues[0]) 
                self->velocity.x = self->abilityValues[0];
        }
    }

    if (self->controlLock) {
        self->controlLock--;
    }
    else if (self->direction == FLIP_X && (!self->right || self->abilityValue != 0x10)) {
        if (self->left && self->abilityValue == 0x70 && self->rotation == true) {
            self->abilitySpeed = 0;
            self->rotation     = false;

            if (self->superState == SUPERSTATE_SUPER && self->hyperState) {
                self->hyperAttacking  = true;
                self->hyperFlashTimer = 128;
                HUD_HandleHyperFlash(self);
            }

            RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_DOWN, &self->animator, false, 0);
        }
    }
    else if (self->direction == FLIP_NONE && (!self->left || self->abilityValue != 0x10)) {
        if (self->right && self->abilityValue == 0x70 && self->rotation == true) {
            self->abilitySpeed = 0;
            self->rotation     = false;

            if (self->superState == SUPERSTATE_SUPER && self->hyperState) {
                self->hyperAttacking  = true;
                self->hyperFlashTimer = 128;
                HUD_HandleHyperFlash(self);
            }

            RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_DOWN, &self->animator, false, 0);
        }
    }
    else if (!self->rotation) {
        self->rotation = true;

        if (self->velocity.y > 0x28000 || self->abilityTimer == 256 || (self->underwater && self->velocity.y > 0x18000)) {
            int32 xVel = abs(self->velocity.x);

            self->abilitySpeed = -((self->abilityTimer * ((xVel >> 1) + (xVel >> 2) + (xVel >> 4))) >> 8);
            if (self->underwater)
                self->abilitySpeed = (self->abilitySpeed >> 1) + (self->abilitySpeed >> 3);

            if (self->abilityTimer > 16)
                self->abilityTimer -= 32;

            if (self->abilitySpeed < -0x60000)
                self->abilitySpeed = -0x60000;
        }

        if (self->superState == SUPERSTATE_SUPER && self->hyperState) {
            self->hyperAttacking = true;
            self->hyperFlashTimer = 128;
            HUD_HandleHyperFlash(self);
        }

        RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_UP, &self->animator, false, 0);
    }

    if (!self->isGhost && !self->underwater) {
        if (self->animator.animationID == ANI_FLY_DOWN)
            Player->rayDiveTimer = 256;
        else if (self->animator.animationID == ANI_FLY_UP)
            Player->raySwoopTimer = 256;
    }

    if (self->onGround) {
        if (abs(self->groundVel) < 0x20000)
            self->groundVel <<= 1;

        if (self->superState == SUPERSTATE_SUPER && self->hyperState) {
            self->hyperAttacking = true;
            Camera_ShakeScreen(SceneInfo->currentScreenID, 0, 4);
            RSDK.PlaySfx(Player->sfxMightyLand, false, 0xFF);
        }

        self->state = Player_State_Ground;

        Player_Gravity_False();

        self->skidding     = 0;
        self->abilityValue = 0;

        if (addendumOptions->rayMoveset == RAYMOVESET_ADDENDUM) {
            if (self->superState != SUPERSTATE_SUPER || self->speedShoesTimer > 0)
                destroyEntity(trail);
        }
    }
    else {
        if (!self->jumpHold || self->position.y < Zone->playerBoundsT[self->playerID] + 0x100000) {
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
            self->state = Player_State_Air;
        }
        else if (abs(self->velocity.x) < 0x10000) {
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
            self->state = Player_State_Air;
        }
    }

    if (RSDK.ObjectTileCollision(self, self->collisionLayers, CMODE_ROOF, self->collisionPlane, 0, -TO_FIXED(16), false))
        self->abilitySpeed = 0;
}
void Player_State_AmyHeliHammer_Left(void)
{
    RSDK_THIS(Player);
    Player_HandleAirFriction();

    if (self->onGround) {
        self->state = Player_State_Ground;
    }
    else {
        if (self->jumpHold) {
            if (self->velocity.x < -0x10000)
                self->abilitySpeed = 0x1300;
            if (self->velocity.x <= 0) {
                if (self->abilityValue >= 60)
                    self->abilitySpeed = 0x1300;
                else
                    self->abilityValue++;
            }

            if (!RSDK.IsSfxPlaying(Player->sfxAmyHammerFly)) {
                RSDK.PlaySfx(Player->sfxAmyHammerFly, false, 0xFF);
            }
        }
        else {
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
            RSDK.StopSfx(Player->sfxAmyHammerFly);
            self->state = Player_State_Air;
        }
    }

    self->velocity.y += self->abilitySpeed;
}
void Player_State_AmyHeliHammer_Right(void)
{
    RSDK_THIS(Player);
    Player_HandleAirFriction();

    if (self->onGround) {
        self->state = Player_State_Ground;
    }
    else {
        if (self->jumpHold) {
            if (self->velocity.x > -0x10000)
                self->abilitySpeed = 0x1300;
            if (self->velocity.x <= 0) {
                if (self->abilityValue >= 60)
                    self->abilitySpeed = 0x1300;
                else
                    self->abilityValue++;
            }

            if (!RSDK.IsSfxPlaying(Player->sfxAmyHammerFly)) {
                RSDK.PlaySfx(Player->sfxAmyHammerFly, false, 0xFF);
            }
        }
        else {
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
            RSDK.StopSfx(Player->sfxAmyHammerFly);
            self->state = Player_State_Air;
        }
    }
    self->velocity.y += self->abilitySpeed;
}
#endif
void Player_State_FlyToPlayer(void)
{
    RSDK_THIS(Player);

    EntityPlayer *leader = NULL;
    if (self->playerID)
        leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
#if MANIA_USE_PLUS
    else
        leader = (EntityPlayer *)&Zone->entityStorage[1];
#endif

    self->respawnTimer = 0;
    self->tileCollisions = TILECOLLISION_NONE;
    self->interaction    = false;

#if GAME_VERSION != VER_100
    if (SizeLaser) {
        if (leader->isChibi != self->isChibi)
            SizeLaser_SetPlayerSize(self, leader->isChibi);
    }
#endif

    switch (self->characterID) {
        default:
        case ID_SONIC:
#if MANIA_USE_PLUS
        case ID_MIGHTY:
        case ID_RAY:
#endif
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
            break;

        case ID_TAILS:
            if (self->underwater)
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_SWIM, &self->animator, false, 0);
            else
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY, &self->animator, false, 0);

            self->scale.x = 0x200;
            self->scale.y = 0x200;
            self->drawFX &= ~FX_SCALE;
            break;

        case ID_KNUCKLES:
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE, &self->animator, false, 0);
            self->scale.x = 0x200;
            self->scale.y = 0x200;
            self->drawFX &= ~FX_SCALE;
            break;

        case ID_AMY:
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_HELI_HAMMER, &self->animator, false, 0);
            self->scale.x = 0x200;
            self->scale.y = 0x200;
            self->drawFX &= ~FX_SCALE;
            break;
    }

    if (leader->underwater && leader->position.y < Water->waterLevel)
        self->drawGroup = leader->drawGroup;
    else
        self->drawGroup = Zone->playerDrawGroup[1];

    Entity *parent = self->abilityPtrs[0];
    int32 screenX  = (ScreenInfo->size.x + ScreenInfo->center.x) << 16;
    int32 screenY  = (ScreenInfo->size.y + ScreenInfo->center.y) << 16;
    if (parent->position.x < leader->position.x - screenX || parent->position.x > screenX + leader->position.x
        || parent->position.y < leader->position.y - screenY || parent->position.y > leader->position.y + screenY) {
        parent->position   = leader->position;
        parent->position.y = (ScreenInfo->position.y - 128) << 16;
    }

    if (self->camera && self->camera->target != parent) {
#if MANIA_USE_PLUS
        if (globals->gameMode != MODE_ENCORE) {
#endif
            self->camera->position.x = parent->position.x;
            self->camera->position.y = parent->position.y;
            Camera_SetTargetEntity(self->camera->screenID, parent);
#if MANIA_USE_PLUS
        }
#endif
    }

    int32 maxDistance = 0;
    if (self->abilityValues[0] || self->characterID == ID_TAILS || self->characterID == ID_KNUCKLES) {
        maxDistance    = Player->targetLeaderPosition[1].x - parent->position.x;
        int32 distance = maxDistance >> 4;

        if (self->characterID != ID_TAILS && self->characterID != ID_KNUCKLES) {
            distance = ((Player->targetLeaderPosition[1].x - parent->position.x) >> 5) + ((Player->targetLeaderPosition[1].x - parent->position.x) >> 4);
        }

        if (parent->position.x >= Player->targetLeaderPosition[1].x + 0x40000) {
            self->direction = FLIP_X;

            if (distance < -0xC0000)
                distance = -0xC0000;

            if (leader->velocity.x < 0)
                distance += leader->velocity.x;

            distance -= 0x10000;
            if (distance < maxDistance) {
                distance    = maxDistance;
                maxDistance = 0;
            }
        }
        else if (parent->position.x <= Player->targetLeaderPosition[1].x - 0x40000) {
            self->direction = FLIP_NONE;

            if (distance > 0xC0000)
                distance = 0xC0000;

            if (leader->velocity.x > 0)
                distance += leader->velocity.x;

            distance += 0x10000;
            if (distance > maxDistance) {
                distance    = maxDistance;
                maxDistance = 0;
            }
        }
        parent->position.x += distance;

        int32 yVel = 0;
        if (self->characterID == ID_TAILS || self->characterID == ID_KNUCKLES) {
            yVel = 0x10000;
#if MANIA_USE_PLUS
            if (globals->gameMode == MODE_ENCORE)
                yVel = 0x20000;
#endif
        }
        else {
            yVel = 0x30000;
        }

        if (parent->position.y > Player->targetLeaderPosition[1].y)
            parent->position.y -= yVel;
        else if (parent->position.y < Player->targetLeaderPosition[1].y)
            parent->position.y += yVel;

        parent->position.x &= 0xFFFF0000;
        parent->position.y &= 0xFFFF0000;
    }
    else {
        self->drawGroup    = Zone->playerDrawGroup[1];
        parent->position.x = Player->targetLeaderPosition[1].x;
        parent->position.y = (ScreenInfo->position.y + ScreenInfo->center.y + 32) << 16;
        parent->position.y += (ScreenInfo->center.y - 32) * RSDK.Sin512(self->angle) << 8;
        self->drawFX |= FX_SCALE;
        self->scale.x = 0x2000 - 16 * self->angle - 8 * self->angle;
        self->scale.y = 0x2000 - 16 * self->angle - 8 * self->angle;
        if (self->scale.x < 0x200) {
            self->scale.x = 0x200;
            self->scale.y = 0x200;
        }

        self->angle += 3;
        if (self->angle >= 512 || (self->angle >= 368 && parent->position.y >= leader->position.y)) {
            self->abilityValues[0] = 1;
            self->drawFX &= ~FX_SCALE;
            self->scale.x    = 0x200;
            self->scale.y    = 0x200;
            self->position.x = parent->position.x;
        }
    }

    if (leader->classID == Player->classID) {
        if (leader->state != Player_State_Death && leader->state != Player_State_Drown && leader->state != Player_State_TubeRoll) {
            if (abs(maxDistance) <= 0x40000 && abs(Player->targetLeaderPosition[1].y - parent->position.y) < 0x20000)
                Player_FinishedReturnToPlayer(self, leader);
        }
    }
}
void Player_State_ReturnToPlayer(void)
{
    RSDK_THIS(Player);

    EntityPlayer *leader = NULL;
    if (self->playerID)
        leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
#if MANIA_USE_PLUS
    else
        leader = (EntityPlayer *)&Zone->entityStorage[1];
#endif

    RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
    Entity *parent = self->abilityPtrs[0];
    if (Player_CheckValidState(leader)) {
        parent->position.x = leader->position.x;
        parent->position.y = leader->position.y;
        parent->position.y -= 0x180000;
    }

    self->velocity.y += 0x4800;
    self->onGround   = false;
    self->velocity.x = 0;
    self->abilityValues[0] += self->velocity.y;
    self->position.x = parent->position.x;
    self->position.y = parent->position.y + self->abilityValues[0];

    if (self->scale.x > 512) {
        self->scale.x -= 10;
        if (self->scale.x <= 0x200) {
            self->drawFX &= ~FX_SCALE;
            self->scale.x = 0x200;
        }
        self->scale.y = self->scale.x;
    }

    if (self->velocity.y >= 0) {
        if (self->position.y >= parent->position.y) {
            self->drawFX &= ~FX_SCALE;
            self->scale.x = 0x200;
            self->scale.y = 0x200;
            Player_FinishedReturnToPlayer(self, leader);
        }
    }
}
void Player_State_HoldRespawn(void)
{
    RSDK_THIS(Player);

    if (++self->abilityValues[0] == 2) {
        EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

        if (leader->classID == Player->classID) {
            EntityDust *dust  = CREATE_ENTITY(Dust, INT_TO_VOID(1), leader->position.x, leader->position.y);
            dust->visible     = false;
            dust->active      = ACTIVE_NEVER;
            dust->isPermanent = true;
            dust->position.y  = (ScreenInfo->position.y - 128) << 16;
#if MANIA_USE_PLUS
            self->tileCollisions = TILECOLLISION_NONE;
            self->interaction    = false;
            self->forceRespawn   = false;
            self->drawGroup      = Zone->playerDrawGroup[1] + 1;
            self->angle          = 128;

            if ((self->characterID != ID_TAILS && self->characterID != ID_KNUCKLES) || globals->gameMode == MODE_ENCORE) {
                self->state = Player_State_ReturnToPlayer;
                self->drawFX |= FX_SCALE;
                self->scale.x = 0x400;
                self->scale.y = 0x400;

                self->abilityValues[0] = 0x100000 - leader->position.y + ((ScreenInfo->size.y + ScreenInfo->position.y) << 16);
                if (self->abilityValues[0] < 0xA80000) {
                    self->velocity.y = self->abilityValues[0] / -12;
                }
                else
                    self->velocity.y = -0xE0000;
            }
            else {
                self->state            = Player_State_FlyToPlayer;
                self->abilityValues[0] = 0;
            }
#else
            self->forceRespawn = false;
            self->state = Player_State_FlyToPlayer;
#endif
            self->abilityPtrs[0] = dust;
        }
    }
}
void Player_FinishedReturnToPlayer(EntityPlayer *player, EntityPlayer *leader)
{
    RSDK_THIS(Player);

    Entity *parent         = player->abilityPtrs[0];
    player->abilityPtrs[0] = NULL;

    if (!SizeLaser || player->state == Player_State_FlyToPlayer) {
        player->state = Player_State_Air;
    }
#if MANIA_USE_PLUS
    else if (globals->gameMode != MODE_ENCORE) {
        player->state = Player_State_Air;
    }
#endif
    else if (!player->isChibi && (leader->isChibi || leader->state == SizeLaser_PlayerState_ShrinkChibi)) {
        player->drawFX |= FX_SCALE;
        player->scale.x          = 0x200;
        player->scale.y          = 0x200;
        player->velocity.x       = 0;
        player->velocity.y       = 0;
        player->groundVel        = 0;
        player->nextAirState     = StateMachine_None;
        player->nextGroundState  = StateMachine_None;
        player->interaction      = false;
        player->abilityPtrs[0]   = SizeLaser_PlayerState_Resize;
        player->abilityValues[0] = parent->position.x - player->position.x;
        player->abilityValues[1] = parent->position.y - player->position.y;
        player->state            = SizeLaser_PlayerState_ShrinkChibi;
    }
    else if (!player->isChibi || (leader->isChibi || leader->state == SizeLaser_PlayerState_GrowNormal)) {
        player->state = Player_State_Air;
    }
    else {
        player->drawFX |= FX_SCALE;
        player->scale.x         = 0x140;
        player->scale.y         = 0x140;
        player->velocity.x      = 0;
        player->velocity.y      = 0;
        player->groundVel       = 0;
        player->nextAirState    = StateMachine_None;
        player->nextGroundState = StateMachine_None;

        player->tailFrames = -1;
        switch (player->characterID) {
            default:
            case ID_SONIC:
                if (self->superState == SUPERSTATE_SUPER) {
                    if (player->miracleState)
                        player->aniFrames = Player->miracleFrames;
                    else
                        player->aniFrames = Player->superFrames;
                }
                else
                    player->aniFrames = Player->sonicFrames;
                break;

            case ID_TAILS:
                if (self->superState == SUPERSTATE_SUPER && self->miracleState) {
                    player->aniFrames  = Player->miracleTailsFrames;
                    player->tailFrames = Player->miracleTailsTailsFrames;
                }
                else {
                    player->aniFrames  = Player->tailsFrames;
                    player->tailFrames = Player->tailsTailsFrames;
                }
                break;
                
            case ID_KNUCKLES:
                if (self->superState == SUPERSTATE_SUPER && player->miracleState) {
                    player->aniFrames = Player->miracleKnuxFrames;
                }
                else
                    player->aniFrames = Player->knuxFrames;
                break;
#if MANIA_USE_PLUS
            case ID_MIGHTY:
                if (self->superState == SUPERSTATE_SUPER && self->miracleState)
                    player->aniFrames = Player->miracleMightyFrames;
                else
                    player->aniFrames = Player->mightyFrames;
                break;

            case ID_RAY:
                if (self->superState == SUPERSTATE_SUPER && self->miracleState)
                    player->aniFrames = Player->miracleRayFrames;
                else
                    player->aniFrames = Player->rayFrames;
                break;

            case ID_AMY:
                if (player->miracleState)
                    player->aniFrames = Player->miracleAmyFrames;
                else
                    player->aniFrames = Player->amyFrames;
                break;
#endif
        }

        player->interaction      = false;
        player->abilityPtrs[0]   = SizeLaser_PlayerState_Resize;
        player->abilityValues[0] = parent->position.x - player->position.x;
        player->abilityValues[1] = parent->position.y - player->position.y;
        player->state            = SizeLaser_PlayerState_GrowNormal;
    }

    RSDK.SetSpriteAnimation(player->aniFrames, ANI_JUMP, &player->animator, false, 0);
    player->onGround       = false;
    player->tileCollisions = TILECOLLISION_DOWN;
    player->interaction    = true;
    player->controlLock    = 0;
    player->angle          = 0;

    if (!player->sidekick) {
        player->stateInput = Player_Input_P1;
    }
    else {
        player->stateInput     = Player_Input_P2_AI;
        EntityPlayer *plr1     = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        player->velocity.x     = plr1->velocity.x;
        player->groundVel      = plr1->groundVel;
        for (int32 p = 0; p < 4; ++p) {
            Player->upState[p]        = 0;
            Player->downState[p]      = 0;
            Player->leftState[p]      = 0;
            Player->rightState[p]     = 0;
            Player->jumpHoldState[p]  = 0;
            Player->jumpPressState[p] = 0;
        }
    }

    player->collisionPlane = leader->collisionPlane;
    player->drawGroup      = leader->drawGroup;
    player->active         = ACTIVE_NORMAL;
    player->position.x     = parent->position.x;
    player->position.y     = parent->position.y;
    if (player->playerID == 0)
        player->blinkTimer = 120;

    if (player->camera) {
        Camera_SetTargetEntity(player->camera->screenID, (Entity *)player);
        player->camera->state = Camera_State_FollowXY;
    }
    destroyEntity(parent);

    for (int32 p = 0; p < 4; ++p) {
        Player->upState[p]        = false;
        Player->downState[p]      = 0;
        Player->leftState[p]      = 0;
        Player->rightState[p]     = 0;
        Player->jumpPressState[p] = 0;
        Player->jumpHoldState[p]  = 0;
    }

    if (BoundsMarker)
        BoundsMarker_ApplyAllBounds(player, false);
}
void Player_State_EncoreRespawn(void)
{
    EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    if (leader->state != Player_State_Death && leader->state != Player_State_Drown) {
#if MANIA_USE_PLUS
        RSDK_THIS(Player);

        if (globals->stock) {
            Player_ChangeCharacter(self, GET_STOCK_ID(1));
            globals->stock >>= 8;
            EntityDust *dust       = CREATE_ENTITY(Dust, INT_TO_VOID(1), leader->position.x, leader->position.y);
            dust->visible          = false;
            dust->active           = ACTIVE_NEVER;
            dust->isPermanent      = true;
            dust->position.y       = (ScreenInfo->position.y - 128) << 16;
            leader->angle          = 128;
            self->state            = Player_State_FlyToPlayer;
            self->abilityPtrs[0]   = dust;
            self->abilityValues[0] = 0;
            self->nextAirState     = StateMachine_None;
            self->nextGroundState  = StateMachine_None;
            self->stateInput       = Player_Input_P2_Delay;
            self->position.x       = -0x400000;
            self->position.y       = -0x400000;
            self->velocity.x       = 0;
            self->velocity.y       = 0;
            self->groundVel        = 0;
            self->tileCollisions   = TILECOLLISION_NONE;
            self->interaction      = false;
            self->drawGroup        = Zone->playerDrawGroup[1];
            self->drownTimer       = 0;
            self->active           = ACTIVE_NORMAL;
        }
        else {
#endif
            leader->state   = StateMachine_None;
            leader->classID = TYPE_BLANK;
#if MANIA_USE_PLUS
        }
#endif
    }
}
void Player_State_Victory(void)
{
    RSDK_THIS(Player);

    self->applyJumpCap = false;
    self->drownTimer   = 0;

    if (!self->onGround) {
        Player_HandleAirMovement();
    }
    else {
        switch (self->characterID) {
            case ID_SONIC:
                if (self->animator.animationID == ANI_VICTORY) {
                    if (self->animator.frameID != 3) {
                        self->groundVel = 0;
                    }
                    else {
                        self->velocity.y = -0x32000;
                        if (self->direction == FLIP_X)
                            self->velocity.x = -0xE000;
                        else
                            self->velocity.x = 0xE000;
                        self->onGround = false;
                    }
                }
                break;

            default:
#if MANIA_USE_PLUS
            case ID_AMY:
#endif
            case ID_TAILS: self->groundVel = 0; break;

            case ID_KNUCKLES:
                if (self->animator.frameID != 2 || self->animator.timer != 3) {
                    self->groundVel = 0;
                }
                else {
                    self->velocity.y = -0x30000;
                    if (self->direction == FLIP_X)
                        self->velocity.x = -0xE000;
                    else
                        self->velocity.x = 0xE000;
                    self->onGround = false;
                }
                break;

#if MANIA_USE_PLUS
            case ID_MIGHTY:
            case ID_RAY:
                self->nextAirState    = StateMachine_None;
                self->nextGroundState = StateMachine_None;
                self->groundVel       = 0;
                self->velocity.x      = 0;
                self->velocity.y      = 0;
                if (self->animator.animationID == ANI_VICTORY) {
                    if (self->animator.timer != 1) {
                        self->velocity.x = 0;
                        self->groundVel  = 0;
                    }
                    else {
                        int32 vel = RSDK.GetFrameID(&self->animator) - '0';
                        if (self->onGround) {
                            if (!self->direction)
                                self->groundVel = -(vel << 16);
                            else
                                self->groundVel = (vel << 16);
                        }
                    }
                }
                break;
#endif
        }

        Player_Gravity_False();
    }
}
void Player_State_Bubble(void)
{
    // yep, thats all it is
}
void Player_State_WaterSlide(void)
{
    RSDK_THIS(Player);

    if (!self->onGround) {
        self->state = Player_State_Air;
        Player_HandleAirMovement();
    }
    else {
        Player_Gravity_False();

        if (self->angle) {
            if (self->angle <= 128) {
                if (self->groundVel < 0x80000) {
                    self->groundVel += 0x4000;
                }
            }
            else if (self->groundVel > -0x80000) {
                self->groundVel -= 0x4000;
            }
        }

        int32 vel = RSDK.Sin256(self->angle) << 13 >> 8;
        self->groundVel += vel;
        self->controlLock = 30;
        self->direction   = vel + self->groundVel < 0;
#if MANIA_USE_PLUS
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLUME, &self->animator, false, 0);
#endif
    }

    if (self->jumpPress) {
        Player_Action_Jump(self);

        if ((self->angle < 0x80 && self->velocity.x > 0) || (self->angle <= 0x80 && self->velocity.x < 0))
            self->velocity.x += (self->jumpStrength + (self->jumpStrength >> 1)) * RSDK.Sin256(self->angle) >> 8;
    }
}
void Player_State_TransportTube(void)
{
    // Nothin
}

// Gravity States
void Player_Gravity_True(void)
{
    RSDK_THIS(Player);

    if (self->camera) {
        self->camera->disableYOffset = true;
        self->camera->offset.y       = 0x200000;
    }
}
void Player_Gravity_False(void)
{
    RSDK_THIS(Player);

    if (self->camera)
        self->camera->disableYOffset = false;

    self->jumpAbilityState = 0;
}

// Jump Ability States
void Player_JumpAbility_Sonic(void)
{
    RSDK_THIS(Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    bool32 dropdashDisabled         = self->jumpAbilityState <= 1;
    RSDKControllerState *controller = &ControllerInfo[self->controllerID];
    RSDKTriggerState *bumperR       = &TriggerInfoR[self->controllerID];\

    if (self->superState == SUPERSTATE_SUPER && self->hyperState) {
        if (self->jumpAbilityState == 1) {
            if (self->stateInput != Player_Input_P2_AI || (self->up && globals->gameMode != MODE_ENCORE)) {
                if (self->jumpPress) {
                    self->hyperAttacking  = true;
                    self->state           = Player_HandleHyperSonicDash;
                    self->nextGroundState = StateMachine_None;
                    self->nextAirState    = StateMachine_None;
                }
            }
        }
    }
    else {
        if (self->jumpAbilityState == 1) {
#if MANIA_USE_PLUS
            if (self->stateInput != Player_Input_P2_AI || (self->up && globals->gameMode != MODE_ENCORE)) {
#else
            if (self->stateInput != Player_Input_P2_AI) {
#endif
                if ((controller->keyDown.down && self->jumpHold) || bumperR->keyBumper.down
                    && addendumOptions->sonicMoveset == SONICMOVESET_ADDENDUM || addendumOptions->sonicMoveset == SONICMOVESET_MANIA) {
                    if (++self->jumpAbilityState >= 22) {
                        self->state           = Player_State_DropDash;
                        self->nextGroundState = StateMachine_None;
                        self->nextAirState    = StateMachine_None;
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_DROPDASH, &self->animator, false, 0);
                        RSDK.PlaySfx(Player->sfxDropdash, false, 255);
                    }
                }
                else if (self->jumpPress
#if GAME_VERSION == VER_100
                    && !Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds)
#endif
                ) {
                    EntityShield *shield = RSDK_GET_ENTITY(Player->playerCount + RSDK.GetEntitySlot(self), Shield);
                    EntityShield *instaShield = RSDK_GET_ENTITY(13 + RSDK.GetEntitySlot(self), Shield);
                    if (shield->classID != Shield->classID || shield->shieldAnimator.animationID != SHIELDANI_INSTA) {
                        if (addendumOptions->sonicMoveset == SONICMOVESET_ADDENDUM || addendumOptions->sonicMoveset == SONICMOVESET_MANIA)
                            ++self->jumpAbilityState;
                    }

                    switch (self->shield) {
                        case SHIELD_NONE:
                            if (addendumOptions->sonicMoveset == SONICMOVESET_ADDENDUM || addendumOptions->sonicMoveset == SONICMOVESET_S3K) {
                                self->jumpAbilityState = 0;
                                RSDK.PlaySfx(Shield->sfxInstaShield, false, 255);
                                RSDK.ResetEntity(instaShield, Shield->classID, self);
                                instaShield->inkEffect = INK_ADD;
                                instaShield->alpha     = 0x100;
                                if (self->superState == SUPERSTATE_SUPER)
                                    RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_SUPERINSTA, &instaShield->shieldAnimator, true, 0);
                                else
                                    RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_INSTA, &instaShield->shieldAnimator, true, 0);
                                instaShield->state = Shield_State_Insta;
                            }
                        // [Fallthrough]
                        case SHIELD_BLUE:
                            self->jumpAbilityState = (addendumOptions->sonicMoveset == SONICMOVESET_ADDENDUM || addendumOptions->sonicMoveset == SONICMOVESET_MANIA) ?
                                2 : 0;
                            break;

                        case SHIELD_BUBBLE:
                            self->velocity.x >>= 1;
                            self->velocity.y      = self->superState == SUPERSTATE_SUPER ? 0xC0000 : 0x80000;
                            self->state           = Player_State_BubbleBounce;
                            self->nextGroundState = StateMachine_None;
                            self->nextAirState    = StateMachine_None;
                            RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_BUBBLEATTACKDADD, &shield->fxAnimator, true, 0);
                            RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_BUBBLEATTACKD, &shield->shieldAnimator, true, 0);
                            shield->state = Shield_State_BubbleDrop;
                            RSDK.PlaySfx(Shield->sfxBubbleBounce, false, 255);
                            break;

                        case SHIELD_FIRE:
                            self->jumpAbilityState = 0;
                            self->velocity.x       = self->superState == SUPERSTATE_SUPER ? (self->direction == FLIP_X ? -0xC0000 : 0xC0000)
                                                                                            : (self->direction == FLIP_X ? -0x80000 : 0x80000);
                            self->velocity.y       = 0;
                            RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_FIREATTACK, &shield->shieldAnimator, true, 0);
                            shield->state     = Shield_State_FireDash;
                            shield->direction = self->direction;
                            if (self->camera && !Zone->autoScrollSpeed) {
                                self->scrollDelay   = 15;
                                self->camera->state = Camera_State_FollowY;
                            }
                            RSDK.PlaySfx(Shield->sfxFireDash, false, 255);
                            if (self->superState == SUPERSTATE_SUPER)
                                self->jumpAbilityState = 22;
                            break;

                        case SHIELD_LIGHTNING:
                            self->jumpAbilityState = 0;
                            self->velocity.y       = self->superState == SUPERSTATE_SUPER ? (self->invertGravity ? 0x84000 : -0x84000)
                                                                                            : (self->invertGravity ? 0x58000 : -0x58000);
                            shield->state          = Shield_State_LightningSparks;
                            RSDK.PlaySfx(Shield->sfxLightningJump, false, 255);
                            if (self->superState == SUPERSTATE_SUPER)
                                self->jumpAbilityState = 22;
                            break;

                        default: break;
                    }
                }
#if GAME_VERSION != VER_100
                else {
                    if (ControllerInfo[self->controllerID].keyY.press && self->superState != SUPERSTATE_SUPER) {
                        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, Addendum_GetSaveRAM()->collectedSuperEmeralds, 0x00);
                        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, Addendum_GetSaveRAM()->collectedTimeStones);
                        else
                            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, 0x00);
                    }
                }
#endif
                return;
            }

            dropdashDisabled = true;
        }

        if (!dropdashDisabled && self->jumpHold) {
            if (++self->jumpAbilityState >= 22) {
                self->state           = Player_State_DropDash;
                self->nextGroundState = StateMachine_None;
                self->nextAirState    = StateMachine_None;
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_DROPDASH, &self->animator, false, 0);
                RSDK.PlaySfx(Player->sfxDropdash, false, 255);
            }
        }
    }
}

void Player_JumpAbility_Tails(void)
{
    RSDK_THIS(Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (self->jumpPress && self->jumpAbilityState == 1
        && (self->stateInput != Player_Input_P2_AI
            || (self->up
#if MANIA_USE_PLUS
                && globals->gameMode != MODE_ENCORE
#endif
                ))
#if GAME_VERSION == VER_100
        && !Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds)
#endif
    ) {
        if (!self->invertGravity) {
            self->jumpAbilityState = 0;
            self->timer            = 0;
            self->abilitySpeed     = 0x800;
            if (!self->underwater)
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY, &self->animator, false, 0);
            else
                RSDK.SetSpriteAnimation(self->aniFrames, ANI_SWIM, &self->animator, false, 0);
            self->state           = Player_State_TailsFlight;
            self->nextGroundState = StateMachine_None;
            self->nextAirState    = StateMachine_None;
        }
    }
#if GAME_VERSION != VER_100
    else if (ControllerInfo[self->controllerID].keyY.press && self->superState != SUPERSTATE_SUPER) {
        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, Addendum_GetSaveRAM()->collectedSuperEmeralds, 0x00);
        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, Addendum_GetSaveRAM()->collectedTimeStones);
        else
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, 0x00);
    }
#endif
}
void Player_JumpAbility_Knux(void)
{
    RSDK_THIS(Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (self->jumpPress && self->jumpAbilityState == 1
        && (self->stateInput != Player_Input_P2_AI
            || (self->up
#if MANIA_USE_PLUS
                && globals->gameMode != MODE_ENCORE
#endif
                ))
#if GAME_VERSION == VER_100
        && !Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds)
#endif
    ) {
        if (!self->invertGravity) {
            self->jumpAbilityState = 0;
            self->abilitySpeed     = 0x40000;
            int32 prevVelocity     = self->velocity.x;

            if (self->velocity.y < 0)
                self->velocity.y = 0;

            if (self->direction) {
                self->state = Player_State_KnuxGlideLeft;
                if (addendumOptions->knuxMoveset == KNUXMOVESET_ADDENDUM) {
                    if (prevVelocity < -0x40000) {
                        if (self->superState == SUPERSTATE_SUPER) {
                            if (self->hyperState)
                                self->velocity.x = (prevVelocity * 0.7) - 0x40000;
                            else
                                self->velocity.x = (prevVelocity * 0.5) - 0x40000;
                        }
                        else {
                            self->velocity.x = (prevVelocity * 0.33) - 0x40000;
                        }
                    }
                    else {
                        self->velocity.x = -0x40000;
                    }

                    self->prevVelocity.x = self->velocity.x;
                }
                else
                    self->velocity.x = -0x40000;

                self->timer = 0x100;
            }
            else {
                self->state = Player_State_KnuxGlideRight;
                if (addendumOptions->knuxMoveset == KNUXMOVESET_ADDENDUM) {
                    if (prevVelocity > 0x40000) {
                        if (self->superState == SUPERSTATE_SUPER) {
                            if (self->hyperState)
                                self->velocity.x = (prevVelocity * 0.7) + 0x40000;
                            else
                                self->velocity.x = (prevVelocity * 0.5) + 0x40000;
                        }
                        else {
                            self->velocity.x = (prevVelocity * 0.33) + 0x40000;
                        }
                    }
                    else {
                        self->velocity.x = 0x40000;
                    }

                    self->prevVelocity.x = self->velocity.x;
                }
                else
                    self->velocity.x = 0x40000;

                self->timer = 0;
            }

            self->nextGroundState = StateMachine_None;
            self->nextAirState    = StateMachine_None;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE, &self->animator, false, 6);
        }
    }
#if GAME_VERSION != VER_100
    else if (ControllerInfo[self->controllerID].keyY.press && self->superState != SUPERSTATE_SUPER) {
        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, Addendum_GetSaveRAM()->collectedSuperEmeralds, 0x00);
        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, Addendum_GetSaveRAM()->collectedTimeStones);
        else
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, 0x00);
    }
#endif
}
#if MANIA_USE_PLUS
void Player_JumpAbility_Mighty(void)
{
    RSDK_THIS(Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    RSDKControllerState *controller = &ControllerInfo[self->controllerID];
    RSDKTriggerState *bumperR       = &TriggerInfoR[self->controllerID];
    bool32 touchControls            = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (self->jumpAbilityState <= 1) {
        if (addendumOptions->mightyMoveset == MIGHTYMOVESET_ADDENDUM) {
            if (bumperR->keyBumper.down && self->jumpAbilityState == 1) { // controller method for wall cling
                Hitbox *hitbox = Player_GetHitbox(self);
                int32 highY = 0, lowY = 0;
                if (self->isChibi) {
                    highY = -0x10000;
                    lowY  = 0x30000;
                }
                else {
                    highY = -0x20000;
                    lowY  = 0xB0000;
                }

                bool32 collidedHigh = false, collidedLow = false;
                int32 highPos = 0, lowPos = 0;
                if (self->right) {
                    collidedHigh = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, hitbox->right << 16, highY, 8);
                    highPos      = self->position.x;

                    collidedLow = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, hitbox->right << 16, lowY, 8);
                    lowPos      = self->position.x;
                }
                if (self->left) {
                    collidedHigh = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, hitbox->left << 16, highY, 8);
                    highPos      = self->position.x;

                    collidedLow = RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, hitbox->left << 16, lowY, 8);
                    lowPos      = self->position.x;
                }
                if (bumperR->keyBumper.down && (collidedHigh || collidedLow) && (self->left || self->right)) {
                    RSDK.StopSfx(Player->sfxRelease);
                    RSDK.StopSfx(Player->sfxMightyDrill);
                    RSDK.PlaySfx(Player->sfxGrab, false, 255);
                    self->velocity.x = 0;
                    self->rotation   = 0;
                    self->velocity.y = 0;
                    self->timer      = 0;

                    if (self->isChibi) {
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_SKID, &self->animator, false, 0);
                    }
                    else {
                        self->direction = self->direction != FLIP_X;
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_STICK, &self->animator, false, 0);
                    }
                    self->state = Player_State_MightyWallStick;
                }
            }
        }

        if (self->jumpPress && self->jumpAbilityState == 1
            && (self->stateInput != Player_Input_P2_AI
                || (self->up
#if MANIA_USE_PLUS
                    && globals->gameMode != MODE_ENCORE
#endif
                    ))
#if GAME_VERSION == VER_100
            && !Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds)
#endif
        ) {
            if (!self->invertGravity) {
                if (controller->keyUp.down && !touchControls && addendumOptions->mightyMoveset == MIGHTYMOVESET_ADDENDUM) {
                    Hitbox *hitbox = Player_GetHitbox(self);
                    int32 highY = 0, lowY = 0;
                    if (self->isChibi) {
                        highY = -0x10000;
                        lowY  = 0x30000;
                    }
                    else {
                        highY = -0x20000;
                        lowY  = 0xB0000;
                    }

                    bool32 collidedHigh = false, collidedLow = false;
                    int32 highPos = 0, lowPos = 0;
                    if (self->right) {
                        collidedHigh =
                            RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, hitbox->right << 16, highY, 8);
                        highPos = self->position.x;

                        collidedLow =
                            RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_LWALL, self->collisionPlane, hitbox->right << 16, lowY, 8);
                        lowPos = self->position.x;
                    }
                    if (self->left) {
                        collidedHigh =
                            RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, hitbox->left << 16, highY, 8);
                        highPos = self->position.x;

                        collidedLow =
                            RSDK.ObjectTileGrip(self, self->collisionLayers, CMODE_RWALL, self->collisionPlane, hitbox->left << 16, lowY, 8);
                        lowPos = self->position.x;
                    }
                    if ((controller->keyUp.down && self->jumpHold) && (collidedHigh || collidedLow) && (self->left || self->right)) {
                        RSDK.StopSfx(Player->sfxRelease);
                        RSDK.StopSfx(Player->sfxMightyDrill);
                        RSDK.PlaySfx(Player->sfxGrab, false, 255);
                        self->velocity.x = 0;
                        self->rotation   = 0;
                        self->velocity.y = 0;
                        self->timer      = 0;

                        if (self->isChibi) {
                            RSDK.SetSpriteAnimation(self->aniFrames, ANI_SKID, &self->animator, false, 0);
                        }
                        else {
                            self->direction = self->direction != FLIP_X;
                            RSDK.SetSpriteAnimation(self->aniFrames, ANI_STICK, &self->animator, false, 0);
                        }
                        self->state = Player_State_MightyWallStick;
                    }
                    else {
                        self->velocity.x >>= 1;
                        self->velocity.y       = self->underwater ? 0x80000 : 0xC0000;
                        self->jumpAbilityState = 0;
                        RSDK.SetSpriteAnimation(self->aniFrames, ANI_HAMMERDROP, &self->animator, false, 2);
                        self->nextAirState    = StateMachine_None;
                        self->nextGroundState = StateMachine_None;
                        RSDK.PlaySfx(Player->sfxRelease, false, 0xFF);

                        EntityImageTrail *trail = RSDK_GET_ENTITY(2 * Player->playerCount + RSDK.GetEntitySlot(self), ImageTrail);
                        RSDK.ResetEntity(trail, ImageTrail->classID, self);
                        if (self->camera && !Zone->autoScrollSpeed) {
                            self->scrollDelay   = 8;
                            self->camera->state = Camera_State_FollowX;
                        }

                        RSDK.PlaySfx(Player->sfxMightyDrill, false, 0xFE);
                        self->state = Player_State_MightyHammerDrop;
                    }
                }
                else {
                    self->velocity.x >>= 1;
                    self->velocity.y       = self->underwater ? 0x80000 : 0xC0000;
                    self->jumpAbilityState = 0;
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_HAMMERDROP, &self->animator, false, 2);
                    self->nextAirState    = StateMachine_None;
                    self->nextGroundState = StateMachine_None;
                    RSDK.PlaySfx(Player->sfxRelease, false, 0xFF);

                    EntityImageTrail *trail = RSDK_GET_ENTITY(2 * Player->playerCount + RSDK.GetEntitySlot(self), ImageTrail);
                    RSDK.ResetEntity(trail, ImageTrail->classID, self);
                    if (self->camera && !Zone->autoScrollSpeed) {
                        self->scrollDelay   = 8;
                        self->camera->state = Camera_State_FollowX;
                    }

                    RSDK.PlaySfx(Player->sfxMightyDrill, false, 0xFE);
                    self->state = Player_State_MightyHammerDrop;
                }
            }
        }
        else if (ControllerInfo[self->controllerID].keyY.press && self->superState != SUPERSTATE_SUPER) {
            if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, Addendum_GetSaveRAM()->collectedSuperEmeralds, 0x00);
            else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, Addendum_GetSaveRAM()->collectedTimeStones);
            else
                Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, 0x00);
        }
    }
    else if (--self->jumpAbilityState == 1)
        self->jumpAbilityState = 0;
}
void Player_JumpAbility_Ray(void)
{
    RSDK_THIS(Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();

    if (self->jumpPress && self->jumpAbilityState == 1
        && (self->stateInput != Player_Input_P2_AI
            || (self->up
#if MANIA_USE_PLUS
                && globals->gameMode != MODE_ENCORE
#endif
                ))
#if GAME_VERSION == VER_100
        && !Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds)
#endif
    ) {
        if (!self->invertGravity) {
            self->jumpAbilityState = 0;

            int32 newXVel = self->velocity.x - (self->velocity.x >> 3);
            if (self->direction)
                self->velocity.x = MIN(newXVel, self->underwater ? -0x18000 : -0x30000);
            else
                self->velocity.x = MAX(newXVel, self->underwater ? 0x18000 : 0x30000);

            if ((self->direction == FLIP_NONE && self->right) || (self->direction == FLIP_X && self->left)) {
                if (!self->underwater)
                    Player->rayDiveTimer = 256;

                RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_DOWN, &self->animator, false, 3);
                self->rotation     = false;
                self->abilitySpeed = 0;
            }
            else {
                if (!self->underwater)
                    Player->raySwoopTimer = 256;

                RSDK.SetSpriteAnimation(self->aniFrames, ANI_FLY_UP, &self->animator, false, 3);
                self->rotation = true;

                self->velocity.x >>= 1;
                int32 vel          = abs(self->velocity.x);
                int32 speed        = -((vel >> 1) + (vel >> 2) + (vel >> 4)) >> (uint8)(self->underwater != 0);
                self->abilitySpeed = MIN(speed, 0x40000);
            }

            if (addendumOptions->rayMoveset == RAYMOVESET_ADDENDUM) {
                if (self->superState != SUPERSTATE_SUPER || self->speedShoesTimer <= 0) {
                    EntityImageTrail *trail = RSDK_GET_ENTITY(2 * Player->playerCount + RSDK.GetEntitySlot(self), ImageTrail);
                    RSDK.ResetEntity(trail, ImageTrail->classID, self);
                    trail->baseAlpha = 0x100;
                }
            }

            self->velocity.y >>= 1;
            self->abilityValue     = 0x40;
            self->controlLock      = 0;
            self->abilityValues[0] = abs(self->velocity.x);
            self->state            = Player_State_RayGlide;
            self->abilityTimer     = 256;
            self->nextAirState     = StateMachine_None;
            self->timer            = 0;
        }
    }
    else if (ControllerInfo[self->controllerID].keyY.press && self->superState != SUPERSTATE_SUPER) {
        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, Addendum_GetSaveRAM()->collectedSuperEmeralds, 0x00);
        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, Addendum_GetSaveRAM()->collectedTimeStones);
        else
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, 0x00);
    }
}

bool32 Player_SfxCheck_RayDive(void) { return Player->rayDiveTimer > 0; }
bool32 Player_SfxCheck_RaySwoop(void) { return Player->raySwoopTimer > 0; }

void Player_SfxUpdate_RayDive(int32 sfxID)
{
    RSDK.SetChannelAttributes(Soundboard->sfxChannel[sfxID], (float)Player->rayDiveTimer * (1.0f / 256.0f), 0.0, 1.0);
}
void Player_SfxUpdate_RaySwoop(int32 sfxID)
{
    RSDK.SetChannelAttributes(Soundboard->sfxChannel[sfxID], (Player->raySwoopTimer * 0.8f) * (1.0f / 256.0f), 0.0, 1.0);
}

void Player_JumpAbility_Amy(void)
{
    RSDK_THIS(Player);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    self->timer = 0;

    if (self->jumpPress && self->jumpAbilityState == 1
        && (self->stateInput != Player_Input_P2_AI
            || (self->up
#if MANIA_USE_PLUS
                && globals->gameMode != MODE_ENCORE
#endif
                ))
#if GAME_VERSION == VER_100
        && !Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds)
#endif
    ) {
        if (!self->invertGravity) {
            self->jumpAbilityState = 0;
            self->abilitySpeed     = 0x1300;

            if (self->velocity.y < 0)
                self->velocity.y = 0;

            if (self->direction) {
                self->state      = Player_State_AmyHeliHammer_Left;
                self->velocity.x = (self->velocity.x - 0x15000);
                self->timer      = 0;
            }
            else {
                self->state      = Player_State_AmyHeliHammer_Right;
                self->velocity.x = (self->velocity.x + 0x15000);
                self->timer      = 0;
            }

            self->nextGroundState = StateMachine_None;
            self->nextAirState    = StateMachine_None;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_HELI_HAMMER, &self->animator, false, 0);
        }
    }
#if GAME_VERSION != VER_100
    else if (ControllerInfo[self->controllerID].keyY.press && self->superState != SUPERSTATE_SUPER) {
        if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, Addendum_GetSaveRAM()->collectedSuperEmeralds, 0x00);
        else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, Addendum_GetSaveRAM()->collectedTimeStones);
        else
            Player_TryTransform(self, SaveGame_GetSaveRAM()->collectedEmeralds, 0x00, 0x00);
    }
#endif
}
#endif
bool32 Player_CanTransform(EntityPlayer *player)
{
    if (!SceneInfo->timeEnabled /*&& !ERZStart && (!PhantomEgg || PhantomEgg->disableSuperForm)*/)
        return false;

    if (!ERZSetup && (player->state == Player_State_Transform || player->superState == SUPERSTATE_SUPER))
        return true;

    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    if (!saveRAM)
        return false;

    uint8 emeralds = saveRAM->collectedEmeralds;

#if MANIA_USE_PLUS
    if (Player->canSuperCB && !Player->canSuperCB(false))
        return false;
#endif

    if (player->superState >= SUPERSTATE_SUPER || emeralds != 0x7F || player->rings < 50 || player->sidekick)
        return false;

    return true;
}

bool32 Player_CanSwap(EntityPlayer *player)
{
    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    if (!sidekick->classID)
        return false;

    if (Player->cantSwap || player->drawGroup == 2 || !SceneInfo->timeEnabled)
        return false;

    if (sidekick->respawnTimer) {
        sidekick->respawnTimer = 240;
        return false;
    }

    if (player->state == Player_State_Death || player->state == Player_State_Drown) {
        if (sidekick->state == Player_State_Death || sidekick->state == Player_State_Drown || sidekick->state == Player_State_EncoreRespawn
            || sidekick->state == Player_State_Static) {
            return false;
        }
    }
    else {
        if (player->state != Player_State_Ground && player->state != Player_State_Roll)
            return false;
        if (sidekick->state != Player_State_Ground && sidekick->state != Player_State_Roll)
            return false;
    }

    return true;
}

void Player_Input_P1(void)
{
    RSDK_THIS(Player);
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls) {
        Player_HandleTouchInput();
    }

    if (self->controllerID <= CONT_P4) {
        if (globals->gameMode != MODE_COMPETITION || Announcer->finishedCountdown) {
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
#endif

            if (self->left && self->right) {
                self->left  = false;
                self->right = false;
            }
            self->jumpPress = controller->keyA.press || controller->keyB.press || controller->keyC.press || controller->keyX.press;
            self->jumpHold  = controller->keyA.down || controller->keyB.down || controller->keyC.down || controller->keyX.down;

            if (!LottoMachine || !((1 << self->playerID) & LottoMachine->activePlayers)) {
#if MANIA_USE_PLUS
                if (globals->gameMode == MODE_ENCORE && controller->keyY.press) {
                    if (HUD->swapCooldown || !Player_CheckValidState(self) || !Player_SwapMainPlayer(false)) {
                        RSDK.PlaySfx(Player->sfxSwapFail, false, 0xFF);
                    }
                }
#endif

                if (self->controllerID == CONT_P1 && SceneInfo->debugMode && self->state != Player_State_Transform
                    && ControllerInfo[CONT_P1].keyX.press && globals->gameMode != MODE_TIMEATTACK) {
                    self->classID    = DebugMode->classID;
                    self->velocity.x = 0;
                    self->velocity.y = 0;
                    self->groundVel  = 0;
                    self->drawGroup  = Zone->playerDrawGroup[1];
                    RSDK.SetSpriteAnimation(self->aniFrames, ANI_AIR_WALK, &self->animator, true, 0);
                    RSDK.SetEngineState(ENGINESTATE_REGULAR);
                    self->jumpHold         = false;
                    self->jumpPress        = false;
                    self->visible          = true;
                    self->active           = ACTIVE_NORMAL;
                    DebugMode->debugActive = true;
                }
            }

            if (controller->keyStart.press || Unknown_pausePress) {
                if (SceneInfo->state == ENGINESTATE_REGULAR) {
                    EntityPauseMenu *pauseMenu = RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);
                    bool32 allowPause          = true;
#if MANIA_USE_PLUS
                    if (ActClear && ActClear->actClearActive)
                        allowPause = false;
#endif
                    if (!RSDK.GetEntityCount(TitleCard->classID, false) && !pauseMenu->classID && allowPause) {
                        RSDK.ResetEntitySlot(SLOT_PAUSEMENU, PauseMenu->classID, NULL);
                        pauseMenu->triggerPlayer = self->playerID;
                        if (globals->gameMode == MODE_COMPETITION)
                            pauseMenu->disableRestart = true;
                    }
                }
            }
        }
    }
}
void Player_Input_P2_Delay(void)
{
    RSDK_THIS(Player);

    EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *evil    = leader;

    switch (self->playerID) {
    case SLOT_PLAYER3: evil = RSDK_GET_ENTITY(SLOT_PLAYER2, Player); break;
    case SLOT_PLAYER4: evil = RSDK_GET_ENTITY(SLOT_PLAYER3, Player); break;
    }

    Player->upState[self->playerID] <<= 1;
    Player->upState[self->playerID] |= evil->up;
    Player->upState[self->playerID] &= 0xFFFF;

    Player->downState[self->playerID] <<= 1;
    Player->downState[self->playerID] |= evil->down;
    Player->downState[self->playerID] &= 0xFFFF;

    Player->leftState[self->playerID] <<= 1;
    Player->leftState[self->playerID] |= evil->left;
    Player->leftState[self->playerID] &= 0xFFFF;

    Player->rightState[self->playerID] <<= 1;
    Player->rightState[self->playerID] |= evil->right;
    Player->rightState[self->playerID] &= 0xFFFF;

    Player->jumpPressState[self->playerID] <<= 1;
    Player->jumpPressState[self->playerID] |= evil->jumpPress;
    Player->jumpPressState[self->playerID] &= 0xFFFF;

    Player->jumpHoldState[self->playerID] <<= 1;
    Player->jumpHoldState[self->playerID] |= evil->jumpHold;
    Player->jumpHoldState[self->playerID] &= 0xFFFF;

    if (leader->state == Player_State_FlyCarried) {
        Player->downState[self->playerID] <<= 15;
        Player->leftState[self->playerID] <<= 15;
        Player->rightState[self->playerID] <<= 15;
        Player->jumpPressState[self->playerID] <<= 15;
        Player->jumpHoldState[self->playerID] <<= 15;
    }

    self->up        = Player->upState[self->playerID] >> 15;
    self->down      = Player->downState[self->playerID] >> 15;
    self->left      = Player->leftState[self->playerID] >> 15;
    self->right     = Player->rightState[self->playerID] >> 15;
    self->jumpPress = Player->jumpPressState[self->playerID] >> 15;
    self->jumpHold  = Player->jumpHoldState[self->playerID] >> 15;

    if (Player_CheckValidState(leader)) {
        Player->leaderPositionBuffer[self->playerID][Player->lastLeaderPosID[self->playerID]].x = leader->position.x;
        Player->leaderPositionBuffer[self->playerID][Player->lastLeaderPosID[self->playerID]].y = leader->position.y;
        Player->lastLeaderPosID[self->playerID]                                 = (Player->lastLeaderPosID[self->playerID] + 1) & 0xF;
        Player->nextLeaderPosID[self->playerID]                                 = (Player->nextLeaderPosID[self->playerID] + 1) & 0xF;
        if (!leader->onGround && leader->groundedStore) {
            Player->targetLeaderPosition[self->playerID].x = leader->position.x;
            Player->targetLeaderPosition[self->playerID].y = leader->position.y;
        }
        else {
            Player->targetLeaderPosition[self->playerID].x = Player->leaderPositionBuffer[self->playerID][Player->nextLeaderPosID[self->playerID]].x;
            Player->targetLeaderPosition[self->playerID].y = Player->leaderPositionBuffer[self->playerID][Player->nextLeaderPosID[self->playerID]].y;
        }
    }
    else {
        int32 pos = Player->lastLeaderPosID[self->playerID] - 1;
        if (pos < 0)
            pos += 16;

        Player->targetLeaderPosition[self->playerID].x = Player->leaderPositionBuffer[self->playerID][pos].x;
        Player->targetLeaderPosition[self->playerID].y = Player->leaderPositionBuffer[self->playerID][pos].y;
    }
}
void Player_Input_P2_AI(void)
{
    RSDK_THIS(Player);

    EntityPlayer *leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    self->sidekick = true;
    Player_Input_P2_Delay();

    if (self->state == Player_State_TailsFlight && leader->state == Player_State_FlyCarried) {
        self->up        = leader->up;
        self->down      = leader->down;
        self->left      = leader->left;
        self->right     = leader->right;
        self->jumpHold  = leader->jumpHold;
        self->jumpPress = leader->jumpPress;
    }
    else if (leader->classID == Player->classID && leader->state != Player_State_FlyCarried) {
        int32 leaderPos = Player->targetLeaderPosition[self->playerID].x;
        if (leader->onGround || leader->groundedStore) {
            if (abs(leader->groundVel) < 0x20000) {
                if (!leader->direction)
                    leaderPos -= 0x200000;
                else
                    leaderPos += 0x200000;
            }
        }

        int32 distance = leaderPos - self->position.x;
        if (distance) {
            if (distance >= 0) {
                if (distance >= 0x300000) {
                    self->left  = false;
                    self->right = true;
                }

                if (self->groundVel && self->direction == FLIP_NONE)
                    self->position.x += 0xC0 * RSDK.Cos256(self->angle);
            }
            else {
                if (distance <= -0x300000) {
                    self->right = false;
                    self->left  = true;
                }

                if (self->groundVel && self->direction == FLIP_X) {
                    self->position.x -= 0xC0 * RSDK.Cos256(self->angle);
                }
            }
        }

        uint8 autoJump = 0;
        if (self->animator.animationID == ANI_PUSH) {
            ++Player->autoJumpTimer[self->playerID];
            if (leader->direction == self->direction && leader->animator.animationID == ANI_PUSH)
                Player->autoJumpTimer[self->playerID] = 0;

            autoJump = Player->autoJumpTimer[self->playerID] < 30 ? 1 : 0;
        }
        else {
            if (self->position.y - Player->targetLeaderPosition[self->playerID].y <= 0x200000) {
                Player->autoJumpTimer[self->playerID] = 0;
                autoJump = 2; // Skip autoJump
            }
            else {
                ++Player->autoJumpTimer[self->playerID];
                autoJump = Player->autoJumpTimer[self->playerID] < 64 ? 1 : 0;
            }
        }

        if (autoJump == 1) {
            self->jumpHold = true;
        }
        else if (autoJump == 0) {
            if (self->onGround) {
                if (!self->jumpHold)
                    self->jumpPress = true;

                self->jumpHold = true;
            }

            self->applyJumpCap    = false;
            Player->autoJumpTimer[self->playerID] = 0;
        }

        if (self->controlLock > 0 && abs(self->groundVel) < 0x8000)
            self->stateInput = Player_Input_AI_SpindashPt1;
    }

    if (Player_CheckP2KeyPress())
        self->stateInput = Player_Input_P2_Player;

    Player_HandleSidekickRespawn();
}
void Player_Input_AI_SpindashPt1(void)
{
    RSDK_THIS(Player);

    self->up        = false;
    self->down      = false;
    self->left      = false;
    self->right     = false;
    self->jumpPress = false;
    self->jumpHold  = false;

    if (!self->controlLock && self->onGround && self->groundVel < 0x4000) {
        self->groundVel  = 0;
        self->stateInput = Player_Input_AI_SpindashPt2;

        Player->autoJumpTimer[self->playerID] = 1;
        if (self->animator.animationID != ANI_SPINDASH) {
            self->down      = true;
            self->direction = self->position.x >= Player->targetLeaderPosition[self->playerID].x;
        }
    }

    if (Player_CheckP2KeyPress())
        self->stateInput = Player_Input_P2_Player;

    Player_HandleSidekickRespawn();
}
void Player_Input_AI_SpindashPt2(void)
{
    RSDK_THIS(Player);

    if (Player->autoJumpTimer[self->playerID] >= 64) {
        Player->autoJumpTimer[self->playerID] = 0;
        self->down            = false;
        self->jumpPress       = false;
        self->stateInput      = Player_Input_P2_AI;
    }
    else {
        self->down      = true;
        self->jumpPress = !(Player->autoJumpTimer[self->playerID] & 0xF);
        ++Player->autoJumpTimer[self->playerID];
    }

    if (Player_CheckP2KeyPress())
        self->stateInput = Player_Input_P2_Player;

    Player_HandleSidekickRespawn();
}
void Player_Input_P2_Player(void)
{
    RSDK_THIS(Player);

    if (self->controllerID <= CONT_P4) {
        if (API_IsInputSlotAssigned(self->controllerID)) {
            RSDKControllerState *controller = &ControllerInfo[self->controllerID];
            self->sidekick = false;

            self->up    = controller->keyUp.down;
            self->down  = controller->keyDown.down;
            self->left  = controller->keyLeft.down;
            self->right = controller->keyRight.down;

#if MANIA_USE_PLUS
            self->up |= AnalogStickInfoL[self->controllerID].vDelta > 0.3;
            self->down |= AnalogStickInfoL[self->controllerID].vDelta < -0.3;
            self->left |= AnalogStickInfoL[self->controllerID].hDelta < -0.3;
            self->right |= AnalogStickInfoL[self->controllerID].hDelta > 0.3;
#endif

            if (self->left && self->right) {
                self->left  = false;
                self->right = false;
            }

            self->jumpPress = controller->keyA.press || controller->keyB.press || controller->keyC.press || controller->keyX.press;
            self->jumpHold  = controller->keyA.down || controller->keyB.down || controller->keyC.down || controller->keyX.down;

            if (self->right || self->up || self->down || self->left) {
                Player->aiInputSwapTimer[self->playerID] = 0;
            }
            else if (++Player->aiInputSwapTimer[self->playerID] >= 600) {
                self->stateInput = Player_Input_P2_AI;
                API_AssignInputSlotToDevice(self->controllerID, INPUT_AUTOASSIGN);
            }

            if (controller->keyStart.press && SceneInfo->state == ENGINESTATE_REGULAR) {
                EntityPauseMenu *pauseMenu = RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);
                if (!RSDK.GetEntityCount(TitleCard->classID, false) && !pauseMenu->classID) {
                    RSDK.ResetEntitySlot(SLOT_PAUSEMENU, PauseMenu->classID, NULL);
                    pauseMenu->triggerPlayer = 0;
                }
            }

            Player_HandleSidekickRespawn();
        }
        else {
            self->stateInput = Player_Input_P2_AI;
            API_AssignInputSlotToDevice(self->controllerID, INPUT_AUTOASSIGN);
        }
    }
}

void Player_State_DrawMiracle(void)
{
    RSDK_THIS(Player);

    for (int32 c = 0; c < 32; ++c) {
        Player->colorStorage[c] = RSDK.GetPaletteEntry(0, 223 + c);
        RSDK.SetPaletteEntry(0, 223 + c, Player->miracleColors[c]);
    }

    for (int32 c = 0; c < 32; ++c) {
        Player->colorStorage_HCZ[c] = RSDK.GetPaletteEntry(1, 223 + c);
        RSDK.SetPaletteEntry(1, 223 + c, Player->miracleColors_HCZ[c]);
    }

    for (int32 c = 0; c < 32; ++c) {
        Player->colorStorage_CPZ[c] = RSDK.GetPaletteEntry(2, 223 + c);
        RSDK.SetPaletteEntry(2, 223 + c, Player->miracleColors_CPZ[c]);
    }

    if (self->tailFrames != (uint16)-1) {
        int32 rotStore  = self->rotation;
        int32 dirStore  = self->direction;
        self->rotation  = self->tailRotation;
        self->direction = self->tailDirection;
        RSDK.DrawSprite(&self->tailAnimator, NULL, false);

        self->rotation  = rotStore;
        self->direction = dirStore;
    }

    RSDK.DrawSprite(&self->animator, NULL, false);

    for (int32 c = 0; c < 32; ++c) {
        RSDK.SetPaletteEntry(0, 223 + c, Player->colorStorage[c]);
    }

    for (int32 c = 0; c < 32; ++c) {
        RSDK.SetPaletteEntry(1, 223 + c, Player->colorStorage_HCZ[c]);
    }

    for (int32 c = 0; c < 32; ++c) {
        RSDK.SetPaletteEntry(2, 223 + c, Player->colorStorage_CPZ[c]);
    }
}

void Player_BlendHyperSonicColors(int32 bankID)
{
    RSDK_THIS(Player); 

    if (self->superState == SUPERSTATE_SUPER && self->hyperFadeInFinished) {
        ++self->hyperBlendAmount;

        if (self->hyperBlendState > 5)
            self->hyperBlendState = 0;

        if (self->hyperBlendAmount >= 128) {
            self->hyperBlendAmount = 0;
        }

        int32 hyperColor = self->hyperBlendState;
        if (bankID == 0) {
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[hyperColor][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                RSDK.SetPaletteEntry(6, 109, Player->superExtras[7 + hyperColor]);
                RSDK.SetPaletteEntry(7, 109, Player->superExtras[6]);
            }
        }
        else if (bankID == 1) {
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_HCZ[hyperColor][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[1][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
            }
        }
        else if (bankID == 2) {
            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_CPZ[hyperColor][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[2][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
            }
        }
    }

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else
                self->superBlendAmount -= 4;
            break;

        case SUPERSTATE_SUPER:
            if (self->superBlendState & 1) {
                if (self->superBlendAmount <= 0)
                    self->superBlendState &= ~1;
                else {
                    if (HCZSetup || CPZSetup) { // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                        self->superBlendAmount -= 6;
                        self->hyperBlendAmount--;
                    }
                    else {
                        self->superBlendAmount -= 12;
                        self->hyperBlendAmount -= 3;
                    }
                }
            }
            else {
                if (self->superBlendAmount >= 256) {
                    self->superBlendState |= 1;

                    if (!(self->hyperBlendState > 5))
                        self->hyperBlendState++;
                    else
                        self->hyperBlendState = 0;

                    if (self->superBlendState == 1) {
                        if (!self->hyperFadeInFinished) {
                            self->hyperFadeInFinished = true;
                            self->hyperBlendState = 0;
                            if (bankID == 0) {
                                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                    RSDK.SetPaletteEntry(6, 109, Player->superExtras[7]);
                                    RSDK.SetPaletteEntry(7, 109, Player->superExtras[6]);
                                }
                            }
                            else if (bankID == 1) {
                                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_HCZ[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[1][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                }
                            }
                            else if (bankID == 2) {
                                for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                    RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_SONIC + c, hyperPalette_Sonic_CPZ[0][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                    RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_SONIC + c, hyperPaletteWhite[2][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                }
                            }
                        }
                        self->superBlendState  = 2;
                        self->superBlendAmount = 0;
                    }
                }
                else {
                    if (HCZSetup || CPZSetup) { // here to counteract HCZ and CPZ running this function twice, and blending the palette at 2x speed
                        self->superBlendAmount += 6;
                        self->hyperBlendAmount++;
                    }
                    else {
                        self->superBlendAmount += 12;
                        self->hyperBlendAmount += 3;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_SONIC, (PLAYER_PALETTE_INDEX_SONIC + PLAYER_PRIMARY_COLOR_COUNT) - 1);
    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, 109, 110);
}
void Player_BlendHyperTailsColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 4;
                else
                    self->superBlendAmount -= 8;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->hyperState) {
                if (self->superBlendState & 1) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState &= ~1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 4;
                        else
                            self->superBlendAmount -= 8;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256) {
                        self->superBlendState |= 1;

                        if (self->superBlendState == 1) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_TAILS + c, Player->superPalette_Tails[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_TAILS + c, hyperPaletteWhite[bankID][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            self->superBlendState  = 2;
                            self->superBlendAmount = 0;
                        }
                    }
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 4;
                        else
                            self->superBlendAmount += 8;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_TAILS, (PLAYER_PALETTE_INDEX_TAILS + PLAYER_PRIMARY_COLOR_COUNT) - 1);
}
void Player_BlendHyperKnuxColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 4;
                else
                    self->superBlendAmount -= 8;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->hyperState) {
                if (self->superBlendState & 1) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState &= ~1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 4;
                        else
                            self->superBlendAmount -= 8;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256) {
                        self->superBlendState |= 1;

                        if (self->superBlendState == 1) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_KNUX + c, Player->superPalette_Knux[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_KNUX + c, hyperPaletteWhite[bankID][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            self->superBlendState  = 2;
                            self->superBlendAmount = 0;
                        }
                    }
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 4;
                        else
                            self->superBlendAmount += 8;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_KNUX, (PLAYER_PALETTE_INDEX_KNUX + PLAYER_PRIMARY_COLOR_COUNT) - 1);
}
#if MANIA_USE_PLUS
void Player_BlendHyperMightyColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 4;
                else
                    self->superBlendAmount -= 8;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->hyperState) {
                if (self->superBlendState & 1) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState &= ~1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 4;
                        else
                            self->superBlendAmount -= 8;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256) {
                        self->superBlendState |= 1;

                        if (self->superBlendState == 1) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_MIGHTY + c, Player->superPalette_Mighty[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_MIGHTY + c, hyperPaletteWhite[bankID][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            }
                            self->superBlendState  = 2;
                            self->superBlendAmount = 0;
                        }
                    }
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 4;
                        else
                            self->superBlendAmount += 8;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_MIGHTY, (PLAYER_PALETTE_INDEX_MIGHTY + PLAYER_PRIMARY_COLOR_COUNT) - 1);
}
void Player_BlendHyperRayColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else {
                if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                    self->superBlendAmount -= 4;
                else
                    self->superBlendAmount -= 8;
            }
            break;

        case SUPERSTATE_SUPER:
            if (self->hyperState) {
                if (self->superBlendState & 1) {
                    if (self->superBlendAmount <= 0)
                        self->superBlendState &= ~1;
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount -= 4;
                        else
                            self->superBlendAmount -= 8;
                    }
                }
                else {
                    if (self->superBlendAmount >= 256) {
                        self->superBlendState |= 1;

                        if (self->superBlendState == 1) {
                            for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                                RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_RAY + c, Player->superPalette_Ray[(2 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                                RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_RAY + c, hyperPaletteWhite_Ray[bankID][(0 * (PLAYER_PRIMARY_COLOR_COUNT + 1)) + c]);
                            }
                            self->superBlendState  = 2;
                            self->superBlendAmount = 0;
                        }
                    }
                    else {
                        if (HCZSetup || CPZSetup) // here to counteract HCZ and CPZ running this function twice and blending the palette at 2x speed
                            self->superBlendAmount += 4;
                        else
                            self->superBlendAmount += 8;
                    }
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_RAY, (PLAYER_PALETTE_INDEX_RAY + (PLAYER_PRIMARY_COLOR_COUNT + 1)));
}
void Player_BlendHyperAmyColors(int32 bankID)
{
    RSDK_THIS(Player);

    switch (self->superState) {
        case SUPERSTATE_NONE:
        case SUPERSTATE_FADEIN:
        case SUPERSTATE_FADEOUT:
        case SUPERSTATE_DONE:
        default:
            if (self->superBlendAmount <= 0)
                self->superState = SUPERSTATE_NONE;
            else
                self->superBlendAmount -= 4;
            break;

        case SUPERSTATE_SUPER:
            if (self->superBlendState & 1) {
                if (self->superBlendAmount <= 0)
                    self->superBlendState &= ~1;
                else {
                    if (HCZSetup || CPZSetup)
                        self->superBlendAmount -= 4;
                    else
                        self->superBlendAmount -= 8;
                }
            }
            else {
                if (self->superBlendAmount >= 256) {
                    self->superBlendState |= 1;

                    if (self->superBlendState == 1) {
                        for (int32 c = 0; c < PLAYER_PRIMARY_COLOR_COUNT; ++c) {
                            RSDK.SetPaletteEntry(6, PLAYER_PALETTE_INDEX_AMY + c, Player->superPalette_Amy[(2 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                            RSDK.SetPaletteEntry(7, PLAYER_PALETTE_INDEX_AMY + c, hyperPaletteWhite[bankID][(0 * PLAYER_PRIMARY_COLOR_COUNT) + c]);
                        }
                        self->superBlendState  = 2;
                        self->superBlendAmount = 0;
                    }
                }
                else {
                    if (HCZSetup || CPZSetup)
                        self->superBlendAmount += 4;
                    else
                        self->superBlendAmount += 8;
                }
            }
            break;
    }

    RSDK.SetLimitedFade(bankID, 6, 7, self->superBlendAmount, PLAYER_PALETTE_INDEX_AMY, (PLAYER_PALETTE_INDEX_AMY + PLAYER_PRIMARY_COLOR_COUNT) - 1);
}
#endif

void Player_HandleTouchInput(void) {
    RSDK_THIS(Player);

    if (self->controllerID < PLAYER_COUNT) {
        RSDKControllerState *controller = &ControllerInfo[self->controllerID];
        RSDKTriggerState *rBumper       = &TriggerInfoR[self->controllerID];

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

#if GAME_VERSION != VER_100
        bool32 canSuper = Player_CanTransform(self) && !self->onGround;
#endif
#if MANIA_USE_PLUS
        bool32 canSwap = Player_CanSwap(self) && globals->gameMode == MODE_ENCORE;
#endif
        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (HUD_CheckTouchRect(ScreenInfo->size.x - 88, 156, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedJump           = true;
        }

        bool32 touchedPause = false;
        if (HUD_CheckTouchRect(ScreenInfo->size.x - 0x80, 0, ScreenInfo->size.x, 0x40, NULL, NULL) >= 0) {
            ControllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        bool32 touchedDebug = false;
        if (SceneInfo->debugMode) {
            if (HUD_CheckTouchRect(0, 0, 112, 56, NULL, NULL) >= 0) {
#if GAME_VERSION != VER_100
                ControllerInfo->keyX.down |= true;
                controller->keyX.down = true;
#else
                ControllerInfo->keyY.down |= true;
                controller->keyY.down = true;
#endif
                touchedDebug = true;
            }
        }

#if GAME_VERSION != VER_100
        bool32 touchedSuper = false;
        if (canSuper) {
            if (HUD_CheckTouchRect(ScreenInfo->size.x - 144, 96, ScreenInfo->size.x - 80, 160, NULL, NULL) >= 0) {
                ControllerInfo->keyY.down |= true;
                controller->keyY.down = true;
                touchedSuper          = true;
            }

            if (!Player->touchSuper && touchedSuper) {
                ControllerInfo->keyY.press |= ControllerInfo->keyY.down;
                controller->keyY.press |= controller->keyY.down;
            }
            Player->touchSuper = controller->keyY.down;
        }
        else {
            Player->touchSuper = 0;
        }
#endif

#if MANIA_USE_PLUS
        bool32 touchedSwap = false;
        if (canSwap) {
            if (HUD_CheckTouchRect(ScreenInfo->size.x - 144, 160, ScreenInfo->size.x - 80, 216, NULL, NULL) >= 0) {
                ControllerInfo->keyY.down |= true;
                controller->keyY.down = true;
                touchedSwap           = true;
            }

            if (!Player->touchSwap && touchedSwap) {
                ControllerInfo->keyY.press |= ControllerInfo->keyY.down;
                controller->keyY.press |= controller->keyY.down;
            }
            Player->touchSwap = controller->keyY.down;
        }
        else {
            Player->touchSwap = 0;
        }

        bool32 touchedAux = false;
        if (HUD_CheckTouchRect(ScreenInfo->size.x - 80, 96, ScreenInfo->size.x, 156, NULL, NULL) >= 0) {
            TriggerInfoR->keyBumper.down |= true;
            rBumper->keyBumper.down = true;
            touchedAux              = true;
        }
#endif

        if (!Player->touchJump && touchedJump) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        Player->touchJump = controller->keyA.down;

        if (!Player->touchDebug && touchedDebug) {
            ControllerInfo->keyX.press |= ControllerInfo->keyX.down;
            controller->keyX.press |= controller->keyX.down;
        }
        Player->touchDebug = controller->keyX.down;

        if (!Player->touchPause && touchedPause) {
            ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        Player->touchPause = controller->keyStart.down;

        if (!Player->touchAux && touchedAux) {
            TriggerInfoR->keyBumper.press |= TriggerInfoR->keyBumper.down;
            rBumper->keyBumper.press |= rBumper->keyBumper.down;
        }
        Player->touchAux = rBumper->keyBumper.down;
    }
}

void Player_HandleHyperSonicDash(void)
{
    RSDK_THIS(Player);
    RSDKControllerState *controller = &ControllerInfo[self->controllerID];
    bool32 dropdashDisabled         = self->jumpAbilityState <= 1;

    int32 prevVelocityX = self->velocity.x;
    int32 prevVelocityY = self->velocity.y;

    self->applyJumpCap = false;

    if (self->jumpAbilityState == 1) {
        self->hyperFlashTimer = 128;
        HUD_HandleHyperFlash(self);
        RSDK.PlaySfx(Player->sfxRelease, false, 0xFF);

        EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
        debris->timer        = 22;
        debris->velocity.x   = -TO_FIXED(2);
        debris->velocity.y   = -TO_FIXED(2);
        debris->drawGroup    = Zone->playerDrawGroup[1];
        RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 3, &debris->animator, true, 0);
        if (self->drawFX & FX_SCALE) {
            debris->drawFX |= FX_SCALE;
            debris->scale.x = self->scale.x;
            debris->scale.y = self->scale.y;
        }

        debris             = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
        debris->timer      = 22;
        debris->velocity.x = TO_FIXED(2);
        debris->velocity.y = -TO_FIXED(2);
        debris->drawGroup  = Zone->playerDrawGroup[1];
        RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 3, &debris->animator, true, 0);
        if (self->drawFX & FX_SCALE) {
            debris->drawFX |= FX_SCALE;
            debris->scale.x = self->scale.x;
            debris->scale.y = self->scale.y;
        }

        debris             = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
        debris->timer      = 22;
        debris->velocity.x = -TO_FIXED(2);
        debris->velocity.y = TO_FIXED(2);
        debris->drawGroup  = Zone->playerDrawGroup[1];
        RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 3, &debris->animator, true, 0);
        if (self->drawFX & FX_SCALE) {
            debris->drawFX |= FX_SCALE;
            debris->scale.x = self->scale.x;
            debris->scale.y = self->scale.y;
        }

        debris             = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
        debris->timer      = 22;
        debris->velocity.x = TO_FIXED(2);
        debris->velocity.y = TO_FIXED(2);
        debris->drawGroup  = Zone->playerDrawGroup[1];
        RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 3, &debris->animator, true, 0);
        if (self->drawFX & FX_SCALE) {
            debris->drawFX |= FX_SCALE;
            debris->scale.x = self->scale.x;
            debris->scale.y = self->scale.y;
        }

        if (self->up && !(self->left || self->right || self->down)) {
            if (prevVelocityX != 0)
                self->velocity.x = 0;

            if (prevVelocityY > 0)
                self->velocity.y = 0;

            if (abs(prevVelocityY) < 0x80000)
                self->velocity.y = -0x80000;
            else
                self->velocity.y -= 0x10000;
        }
        else if (self->up && self->left && !self->down) {
            if (prevVelocityX > 0)
                self->velocity.x = 0;

            if (abs(prevVelocityX) < 0x60000)
                self->velocity.x = -0x60000;
            else
                self->velocity.x -= 0x10000;

            if (prevVelocityY > 0)
                self->velocity.y = 0;

            if (abs(prevVelocityY) < 0x80000)
                self->velocity.y = -0x80000;
            else
                self->velocity.y -= 0x10000;
        }
        else if (self->up && self->right && !self->down) {
            if (prevVelocityX < 0)
                self->velocity.x = 0;

            if (abs(prevVelocityX) < 0x80000)
                self->velocity.x = 0x80000;
            else
                self->velocity.x += 0x10000;

            if (prevVelocityY != 0)
                self->velocity.y = 0;

            if (prevVelocityY > 0)
                self->velocity.y = 0;

            if (abs(prevVelocityY) < 0x80000)
                self->velocity.y = -0x80000;
            else
                self->velocity.y -= 0x10000;
        }

        if (self->down && !(self->left || self->right || self->up)) {
            if (prevVelocityX != 0)
                self->velocity.x = 0;

            if (prevVelocityY < 0)
                self->velocity.y = 0;

            if (abs(prevVelocityY) < 0x80000)
                self->velocity.y = 0x80000;
            else
                self->velocity.y += 0x10000;
        }
        else if (self->down && self->left && !self->up) {
            if (prevVelocityX > 0)
                self->velocity.x = 0;

            if (abs(prevVelocityX) < 0x60000)
                self->velocity.x = -0x60000;
            else
                self->velocity.x -= 0x10000;

            if (prevVelocityY < 0)
                self->velocity.y = 0;

            if (abs(prevVelocityY) < 0x80000)
                self->velocity.y = 0x80000;
            else
                self->velocity.y += 0x10000;
        }
        else if (self->down && self->right && !self->up) {
            if (prevVelocityX < 0)
                self->velocity.x = 0;

            if (abs(prevVelocityX) < 0x80000)
                self->velocity.x = 0x80000;
            else
                self->velocity.x += 0x10000;

            if (prevVelocityY != 0)
                self->velocity.y = 0;

            if (prevVelocityY < 0)
                self->velocity.y = 0;

            if (abs(prevVelocityY) < 0x80000)
                self->velocity.y = 0x80000;
            else
                self->velocity.y += 0x10000;
        }

        if (self->left && !(self->right || self->up || self->down)) {
            if (prevVelocityX > 0)
                self->velocity.x = 0;

            if (abs(prevVelocityX) < 0x80000)
                self->velocity.x = -0x80000;
            else
                self->velocity.x -= 0x10000;

            if (prevVelocityY != 0)
                self->velocity.y = 0;
        }

        if (self->right && !(self->left || self->up || self->down)) {
            if (prevVelocityX < 0)
                self->velocity.x = 0;

            if (abs(prevVelocityX) < 0x80000)
                self->velocity.x = 0x80000;
            else
                self->velocity.x += 0x10000;

            if (prevVelocityY != 0)
                self->velocity.y = 0;
        }

        if (!(self->up || self->down || self->left || self->right)) {
            if (self->direction) {
                if (prevVelocityX > 0)
                    self->velocity.x = 0;

                if (abs(prevVelocityX) < 0x80000)
                    self->velocity.x = -0x80000;
                else
                    self->velocity.x -= 0x10000;

                if (prevVelocityY != 0)
                    self->velocity.y = 0;
            }
            else {
                if (prevVelocityX < 0)
                    self->velocity.x = 0;

                if (abs(prevVelocityX) < 0x80000)
                    self->velocity.x = 0x80000;
                else
                    self->velocity.x += 0x10000;

                if (prevVelocityY != 0)
                    self->velocity.y = 0;
            }
        }

        if (self->camera && !Zone->autoScrollSpeed) {
            self->scrollDelay   = 8;
            self->camera->state = Camera_State_FollowY;
        }
    }

    if (self->jumpHold) {
        Player_State_Air();
        if (++self->jumpAbilityState >= 22) {
            self->state           = Player_State_DropDash;
            self->nextGroundState = StateMachine_None;
            self->nextAirState    = StateMachine_None;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_DROPDASH, &self->animator, false, 0);
            RSDK.PlaySfx(Player->sfxDropdash, false, 255);
        }
    }
    else {
        self->jumpAbilityState = 0;
        self->state = Player_State_Air;
    }
}

#if GAME_INCLUDE_EDITOR
void Player_EditorDraw(void)
{
    RSDK_THIS(Player);

    RSDK.SetSpriteAnimation(Player->sonicFrames, 0, &self->animator, true, self->characterID);
    RSDK.DrawSprite(&self->animator, NULL, false);
}

void Player_EditorLoad(void)
{
    Player->sonicFrames = RSDK.LoadSpriteAnimation("Editor/PlayerIcons.bin", SCOPE_STAGE);

    RSDK_ACTIVE_VAR(Player, characterID);
    RSDK_ENUM_VAR("None", PLAYER_CHAR_NONE);
    RSDK_ENUM_VAR("Sonic", PLAYER_CHAR_SONIC);
    RSDK_ENUM_VAR("Tails", PLAYER_CHAR_TAILS);
    RSDK_ENUM_VAR("Sonic & Tails", PLAYER_CHAR_SONIC_TAILS);
    RSDK_ENUM_VAR("Knuckles", PLAYER_CHAR_KNUX);
    RSDK_ENUM_VAR("Sonic & Knuckles", PLAYER_CHAR_SONIC_KNUX);
    RSDK_ENUM_VAR("Tails & Knuckles", PLAYER_CHAR_TAILS_KNUX);
    RSDK_ENUM_VAR("Sonic, Tails & Knuckles", PLAYER_CHAR_SONIC_TAILS_KNUX);
}
#endif

void Player_Serialize(void) { RSDK_EDITABLE_VAR(Player, VAR_ENUM, characterID); }
