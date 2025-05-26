// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: HCZ1Intro Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectHCZ1Intro *HCZ1Intro;

void HCZ1Intro_Update(void)
{
    RSDK_THIS(HCZ1Intro);

    if (!self->activated) {
        if (!isMainGameMode() || !globals->enableIntro || CutsceneRules_CheckStageReload()) {
            self->active = ACTIVE_NEVER;
        }
        else {
            self->activated = true;
            CutsceneSeq_StartSequence(self, HCZ1Intro_Cutscene_Intro, StateMachine_None);

#if MANIA_USE_PLUS
            CutsceneSeq_SetSkipType(SKIPTYPE_DISABLED);
#endif
        }
    }
}

void HCZ1Intro_LateUpdate(void) {}

void HCZ1Intro_StaticUpdate(void) {}

void HCZ1Intro_Draw(void) {}

void HCZ1Intro_Create(void *data)
{
    RSDK_THIS(HCZ1Intro);

    INIT_ENTITY(self);
    CutsceneRules_SetupEntity(self, &self->size, &self->hitbox);
    self->active = ACTIVE_NORMAL;
}

void HCZ1Intro_StageLoad(void)
{
    if (isMainGameMode() && globals->enableIntro && !CutsceneRules_CheckStageReload() && !Zone->actID) {
        Water->disableWaterSplash = true;
    }
}

bool32 HCZ1Intro_Cutscene_Intro(EntityCutsceneSeq *host)
{
    RSDK_THIS(HCZ1Intro);

    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *player2 = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    EntityPlayer *player3 = RSDK_GET_ENTITY(SLOT_PLAYER3, Player);
    EntityPlayer *player4 = RSDK_GET_ENTITY(SLOT_PLAYER4, Player);
    EntityCamera *camera  = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);

    if (!host->timer) {
        camera->position.x = self->position.x;
        camera->position.y = 0;

        player1->position.x = self->position.x - 0x200000;
        player1->camera     = NULL;
        player1->onGround   = false;
        player1->state      = Player_State_Air;
        player1->stateInput = StateMachine_None;
        CutsceneSeq_LockAllPlayerControl();

#if MANIA_USE_PLUS
        RSDK.SetSpriteAnimation(player1->aniFrames, ANI_FLUME, &player1->animator, false, 0);
#else
        RSDK.SetSpriteAnimation(player1->aniFrames, ANI_HURT, &player1->animator, false, 0);
#endif

        if (player2->classID == Player->classID) {
            player2->position.x = player1->position.x - 0x200000;
            player2->position.y = player1->position.y;
            player2->state      = Player_State_Air;
            player2->onGround   = false;
            player2->stateInput = StateMachine_None;

#if MANIA_USE_PLUS
            RSDK.SetSpriteAnimation(player2->aniFrames, ANI_FLUME, &player2->animator, false, 0);
#else
            RSDK.SetSpriteAnimation(player2->aniFrames, ANI_HURT, &player2->animator, false, 0);
#endif
        }

        if (player3->classID == Player->classID) {
            player3->position.x = player2->position.x - 0x200000;
            player3->position.y = player2->position.y;
            player3->state      = Player_State_Air;
            player3->onGround   = false;
            player3->stateInput = StateMachine_None;

            RSDK.SetSpriteAnimation(player3->aniFrames, ANI_FLUME, &player3->animator, false, 0);
        }

        if (player4->classID == Player->classID) {
            player4->position.x = player3->position.x - 0x200000;
            player4->position.y = player3->position.y;
            player4->state      = Player_State_Air;
            player4->onGround   = false;
            player4->stateInput = StateMachine_None;

            RSDK.SetSpriteAnimation(player4->aniFrames, ANI_FLUME, &player4->animator, false, 0);
        }
    }

    if (host->timer >= 8) {
        if (host->timer == 8) {
            camera->target            = (Entity *)player1;
            camera->state             = Camera_State_FollowXY;
            player1->stateInput       = Player_Input_P1;
            player1->camera           = camera;
            Water->disableWaterSplash = 0;
        }
    }
    else {
        player1->position.y = 0;
        player1->velocity.x = 0;
        player1->velocity.y = 0;

        if (player2->classID == Player->classID) {
            player2->position.y = 0;
            player2->velocity.x = 0;
            player2->velocity.y = 0;
        }

        if (player3->classID == Player->classID) {
            player3->position.y = 0;
            player3->velocity.x = 0;
            player3->velocity.y = 0;
        }

        if (player4->classID == Player->classID) {
            player4->position.y = 0;
            player4->velocity.x = 0;
            player4->velocity.y = 0;
        }
    }

    if (RSDK.GetEntityCount(TitleCard->classID, false) || RSDK_GET_ENTITY(SLOT_ACTCLEAR, TitleCard)->classID) {
        if (!host->values[0])
            return false;
    }
    else if (!host->values[0]) {
        host->values[0]   = true;
        host->storedTimer = host->timer;
    }

    if (host->timer >= 8) {
        if (player2->classID != Player->classID)
            return true;

        if (player2->underwater) {
            player2->stateInput = Player_Input_P2_AI;
            return true;
        }

        if (player3->classID == Player->classID) {
            if (player3->underwater) {
                player3->stateInput = Player_Input_P2_AI;
            }
        }

        if (player4->classID == Player->classID) {
            if (player4->underwater) {
                player4->stateInput = Player_Input_P2_AI;
                return true;
            }
        }
    }

    return false;
}

#if GAME_INCLUDE_EDITOR
void HCZ1Intro_EditorDraw(void)
{
    RSDK_THIS(HCZ1Intro);

    CutsceneRules_DrawCutsceneBounds(self, &self->size);
}

void HCZ1Intro_EditorLoad(void) {}
#endif

void HCZ1Intro_Serialize(void) { RSDK_EDITABLE_VAR(HCZ1Intro, VAR_VECTOR2, size); }
