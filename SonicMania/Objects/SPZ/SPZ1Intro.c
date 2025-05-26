// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: SPZ1Intro Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectSPZ1Intro *SPZ1Intro;

void SPZ1Intro_Update(void)
{
    RSDK_THIS(SPZ1Intro);

    if (!self->activated) {
        if (!isMainGameMode() || !globals->enableIntro || CutsceneRules_CheckStageReload()) {
            self->active = ACTIVE_NEVER;
        }
        else {
            self->activated = true;
            CutsceneSeq_StartSequence(self, SPZ1Intro_Cutscene_SetupAct, SPZ1Intro_Cutscene_ExitPipe, SPZ1Intro_Cutscene_BeginAct1, StateMachine_None);

#if MANIA_USE_PLUS
            CutsceneSeq_SetSkipType(SKIPTYPE_DISABLED);
#endif
        }
    }
}

void SPZ1Intro_LateUpdate(void) {}

void SPZ1Intro_StaticUpdate(void) {}

void SPZ1Intro_Draw(void) {}

void SPZ1Intro_Create(void *data)
{
    RSDK_THIS(SPZ1Intro);

    INIT_ENTITY(self);
    CutsceneRules_SetupEntity(self, &self->size, &self->hitbox);
    self->active = ACTIVE_NORMAL;
}

void SPZ1Intro_StageLoad(void)
{
    SPZ1Intro->sfxGasPop = RSDK.GetSfx("OOZ/GasPop.wav");
    SPZ1Intro->sfxPon    = RSDK.GetSfx("Stage/Pon.wav");

    SPZ1Intro->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/ManholeCover.bin", SCOPE_STAGE);
}

bool32 SPZ1Intro_Cutscene_SetupAct(EntityCutsceneSeq *host)
{
    RSDK_THIS(SPZ1Intro);
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);

    Entity *curEnt = host->activeEntity;
    if (!host->timer) {
        player1->position.x = self->position.x;
        camera->position.x  = self->position.x;
        player1->position.y += 0x250000;
        player1->camera         = StateMachine_None;
        player1->tileCollisions = TILECOLLISION_NONE;
        player1->onGround       = false;
        player1->state          = Player_State_Static;
        player1->stateInput     = StateMachine_None;
        CutsceneSeq_LockAllPlayerControl();
        RSDK.SetSpriteAnimation(player1->aniFrames, ANI_JUMP, &player1->animator, false, 0);

        if (player2->classID == Player->classID) {
            player2->position.x     = player1->position.x;
            player2->position.y     = player1->position.y;
            player2->tileCollisions = TILECOLLISION_NONE;
            player2->onGround       = false;
            player2->velocity.y     = -1;
            player2->state          = Player_State_Static;
            player2->stateInput     = StateMachine_None;
            RSDK.SetSpriteAnimation(player2->aniFrames, ANI_JUMP, &player2->animator, false, 0);
        }
        if (player3->classID == Player->classID) {
            player3->position.x     = player2->position.x;
            player3->position.y     = player2->position.y;
            player3->tileCollisions = TILECOLLISION_NONE;
            player3->onGround       = false;
            player3->velocity.y     = -1;
            player3->state          = Player_State_Static;
            player3->stateInput     = StateMachine_None;
            RSDK.SetSpriteAnimation(player3->aniFrames, ANI_JUMP, &player3->animator, false, 0);
        }
        if (player4->classID == Player->classID) {
            player4->position.x     = player3->position.x;
            player4->position.y     = player3->position.y;
            player4->tileCollisions = TILECOLLISION_NONE;
            player4->onGround       = false;
            player4->velocity.y     = -1;
            player4->state          = Player_State_Static;
            player4->stateInput     = StateMachine_None;
            RSDK.SetSpriteAnimation(player4->aniFrames, ANI_JUMP, &player4->animator, false, 0);
        }

        EntityDebris *lid  = CREATE_ENTITY(Debris, NULL, curEnt->position.x, curEnt->position.y + 0x390000);
        lid->drawGroup     = Zone->playerDrawGroup[1];
        lid->state         = StateMachine_None;
        lid->drawFX        = FX_SCALE | FX_ROTATE;
        lid->scale.x       = 0x200;
        lid->scale.y       = 0x200;
        lid->updateRange.x = 0x800000;
        lid->updateRange.y = 0x800000;
        RSDK.SetSpriteAnimation(SPZ1Intro->aniFrames, 0, &lid->animator, true, 0);
        SPZ1Intro->sewerLid = lid;
    }

    if (!RSDK.GetEntityCount(TitleCard->classID, false) && !RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu)->classID && !host->values[0]) {
        host->values[0]   = true;
        host->storedTimer = host->timer;
    }

    if (host->values[0]) {
        if (host->timer == 45)
            RSDK.PlaySfx(Player->sfxRoll, false, 0xFF);

        if (host->timer == 90)
            return true;
    }

    SceneInfo->timeEnabled  = false;
    SceneInfo->milliseconds = 0;
    camera->state           = StateMachine_None;

    return false;
}

bool32 SPZ1Intro_Cutscene_ExitPipe(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);
    UNUSED(camera);

    if (!host->timer) {
        player1->velocity.x      = 0;
        player1->velocity.y      = -0x80000;
        player1->state           = Player_State_Air;
        player1->nextAirState    = StateMachine_None;
        player1->nextGroundState = StateMachine_None;
        RSDK.PlaySfx(SPZ1Intro->sfxGasPop, false, 0xFF);
        RSDK.PlaySfx(SPZ1Intro->sfxPon, false, 0xFF);
        RSDK.StopSfx(Player->sfxRoll);
        Camera_ShakeScreen(0, 0, 2);
        EntityDebris *lid    = SPZ1Intro->sewerLid;
        lid->state           = Debris_State_Fall;
        lid->velocity.y      = -0x60000;
        lid->velocity.x      = -0x18000;
        lid->gravityStrength = 0x3800;
        lid->scaleSpeed.x    = 8;
        lid->scaleSpeed.y    = 8;
        lid->rotSpeed        = -1;
        RSDK.SetSpriteAnimation(SPZ1Intro->aniFrames, 1, &lid->animator, true, 0);
    }

    if (player1->velocity.y > 0)
        player1->tileCollisions = TILECOLLISION_DOWN;

    if (player2->classID == Player->classID) {
        if (player3->classID == Player->classID) {
            if (player4->classID == Player->classID) {
                if (host->timer == 30) {
                    player4->velocity.x      = 0;
                    player4->velocity.y      = -0x80000;
                    player4->state           = Player_State_Air;
                    player4->nextAirState    = StateMachine_None;
                    player4->nextGroundState = StateMachine_None;
                }

                if (player4->velocity.y > 0)
                    player4->tileCollisions = TILECOLLISION_DOWN;

                if (player1->onGround && player2->onGround && player3->onGround && player4->onGround)
                    return true;
            }
            else {
                if (player1->onGround && player2->onGround && player3->onGround)
                    return true;
            }

            if (host->timer == 20) {
                player3->velocity.x      = 0;
                player3->velocity.y      = -0x80000;
                player3->state           = Player_State_Air;
                player3->nextAirState    = StateMachine_None;
                player3->nextGroundState = StateMachine_None;
            }

            if (player3->velocity.y > 0)
                player3->tileCollisions = TILECOLLISION_DOWN;
        }
        else {
            if (player1->onGround && player2->onGround)
                return true;
        }

        if (host->timer == 10) {
            player2->velocity.x      = 0;
            player2->velocity.y      = -0x80000;
            player2->state           = Player_State_Air;
            player2->nextAirState    = StateMachine_None;
            player2->nextGroundState = StateMachine_None;
        }

        if (player2->velocity.y > 0)
            player2->tileCollisions = TILECOLLISION_DOWN;
    }
    else if (player1->onGround) {
        return true;
    }

    return false;
}

bool32 SPZ1Intro_Cutscene_BeginAct1(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);

    if (!host->timer) {
        camera->target      = (Entity *)player1;
        camera->state       = Camera_State_FollowXY;
        player1->stateInput = Player_Input_P1;
        player1->state      = Player_State_Ground;
        player1->camera     = camera;

        if (player2->classID == Player->classID)
            player2->stateInput = Player_Input_P2_AI;
        if (player3->classID == Player->classID)
            player3->stateInput = Player_Input_P2_AI;
        if (player4->classID == Player->classID)
            player4->stateInput = Player_Input_P2_AI;

        SceneInfo->timeEnabled = true;
        return true;
    }

    return false;
}

#if GAME_INCLUDE_EDITOR
void SPZ1Intro_EditorDraw(void)
{
    RSDK_THIS(SPZ1Intro);

    if (showGizmos())
        CutsceneRules_DrawCutsceneBounds(self, &self->size);
}

void SPZ1Intro_EditorLoad(void) {}
#endif

void SPZ1Intro_Serialize(void) { RSDK_EDITABLE_VAR(SPZ1Intro, VAR_VECTOR2, size); }
