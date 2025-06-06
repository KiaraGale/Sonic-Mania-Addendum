// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: TTCutscene Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectTTCutscene *TTCutscene;

void TTCutscene_Update(void)
{
    RSDK_THIS(TTCutscene);

    if (!self->activated) {
        TTCutscene_StartCutscene();
        self->activated = true;
    }
}

void TTCutscene_LateUpdate(void) {}

void TTCutscene_StaticUpdate(void) {}

void TTCutscene_Draw(void) {}

void TTCutscene_Create(void *data)
{
    RSDK_THIS(TTCutscene);

    self->active  = ACTIVE_NORMAL;
    self->visible = false;
    CutsceneRules_SetupEntity(self, &self->size, &self->hitbox);
}

void TTCutscene_StageLoad(void)
{
    EntityPlayer *leader   = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

    TTCutscene->fxFade = NULL;

    foreach_all(FXFade, fade)
    {
        TTCutscene->fxFade = fade;
        foreach_break;
    }

    for (int32 p = 0; p < 4; ++p) {
        EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
        if (player->classID == Player->classID)
            player->shield = globals->restartShield[p];
    }
}

void TTCutscene_StartCutscene(void)
{
    RSDK_THIS(TTCutscene);

    CutsceneSeq_StartSequence(self, TTCutscene_Cutscene_Setup, TTCutscene_Cutscene_FlyIn, TTCutscene_Cutscene_Wait, TTCutscene_Cutscene_FlyOut,
                              TTCutscene_Cutscene_NextScene, StateMachine_None);

#if MANIA_USE_PLUS
    CutsceneSeq_SetSkipTypeCallback(TTCutscene_Cutscene_SkipCB);
#endif
}

#if MANIA_USE_PLUS
void TTCutscene_Cutscene_SkipCB(void)
{
    EntityPlayer *leader   = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

    if (globals->gameMode == MODE_ENCORE)
        RSDK.SetScene("Encore Mode", "Stardust Speedway Zone+ 1");
    else
        RSDK.SetScene("Mania Mode", "Stardust Speedway Zone 1");

    ++SceneInfo->listPos;

    for (int32 p = 0; p < 4; ++p) {
        EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
        if (player->classID == Player->classID)
            globals->restartShield[p] = player->shield;
    }
}
#endif

bool32 TTCutscene_Cutscene_Setup(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);

    if (!host->timer) {
        Zone->playerBoundActiveB[0] = false;
        Zone->playerBoundActiveB[1] = false;
        Zone->playerBoundActiveB[2] = false;
        Zone->playerBoundActiveB[3] = false;

        Zone->deathBoundary[0] = 0x7FFF0000;
        Zone->deathBoundary[1] = 0x7FFF0000;
        Zone->deathBoundary[2] = 0x7FFF0000;
        Zone->deathBoundary[3] = 0x7FFF0000;

        camera->target      = NULL;
        player1->camera     = NULL;
        player1->stateInput = StateMachine_None;
        CutsceneSeq_LockAllPlayerControl();

        player1->state      = Player_State_Static;
        player1->position.x = player1->position.x;
        player1->position.y = (ScreenInfo->position.y + 32 + ScreenInfo->size.y) << 16;
        RSDK.SetSpriteAnimation(player1->aniFrames, ANI_SPRING_TWIRL, &player1->animator, false, 0);

        if (player2->classID == Player->classID) {
            if (player3->classID != Player->classID)
                player1->position.x += 0x100000;
            player2->stateInput = StateMachine_None;

            player2->position.x = (player3->classID == Player->classID) ? player1->position.x - 0x300000 : player1->position.x - 0x200000;
            player2->position.y = player1->position.y;
            player2->state      = Player_State_Static;

            RSDK.SetSpriteAnimation(player2->aniFrames, ANI_SPRING_TWIRL, &player2->animator, false, 0);
        }
        if (player3->classID == Player->classID) {
            if (player4->classID != Player->classID)
                player1->position.x -= 0x100000;
            player3->stateInput = StateMachine_None;

            player3->position.x = player1->position.x + 0x200000;
            player3->position.y = player1->position.y;
            player3->state      = Player_State_Static;

            RSDK.SetSpriteAnimation(player3->aniFrames, ANI_SPRING_TWIRL, &player3->animator, false, 0);
        }
        if (player4->classID == Player->classID) {
            player4->stateInput = StateMachine_None;

            player4->position.x = player1->position.x - 0x400000;
            player4->position.y = player1->position.y;
            player4->state      = Player_State_Static;

            RSDK.SetSpriteAnimation(player4->aniFrames, ANI_SPRING_TWIRL, &player4->animator, false, 0);
        }
    }

    return host->timer == 64;
}

bool32 TTCutscene_Cutscene_FlyIn(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);
    UNUSED(camera);

    int32 targetY = (ScreenInfo->position.y + ScreenInfo->center.y) << 16;
    int32 startY  = (ScreenInfo->position.y + ScreenInfo->size.y + 32) << 16;

    if (host->timer) {
        if (host->timer >= 60) {
            player1->position.y = targetY;
        }
        else {
            Vector2 *playerPos = &player1->position;
            Vector2 point = MathHelpers_GetBezierPoint((host->timer << 16) / 60, playerPos->x, startY, playerPos->x, targetY - 0x800000, playerPos->x,
                                                       targetY, playerPos->x, targetY);
            player1->position.y = point.y;
        }
    }
    else {
        player1->position.y = startY;
    }

    player1->velocity.x = 0;
    player1->velocity.y = 0;

    if (player2->classID == Player->classID) {
        int32 timerP2 = host->timer - 15;
        if (timerP2 > 0) {
            if (timerP2 >= 60) {
                player2->position.y = targetY;
            }
            else if (timerP2 < 60) {
                Vector2 *playerPos = &player2->position;
                Vector2 point = MathHelpers_GetBezierPoint((timerP2 << 16) / 60, playerPos->x, startY, playerPos->x, targetY - 0x800000, playerPos->x,
                                                           targetY, playerPos->x, targetY);
                player2->position.y = point.y;
            }
        }
        else {
            player2->position.y = startY;
        }

        player2->velocity.x = 0;
        player2->velocity.y = 0;
    }

    if (player3->classID == Player->classID) {
        int32 timerP3 = host->timer - 30;
        if (timerP3 > 0) {
            if (timerP3 >= 60) {
                player3->position.y = targetY;
            }
            else if (timerP3 < 60) {
                Vector2 *playerPos = &player3->position;
                Vector2 point = MathHelpers_GetBezierPoint((timerP3 << 16) / 60, playerPos->x, startY, playerPos->x, targetY - 0x800000, playerPos->x,
                    targetY, playerPos->x, targetY);
                player3->position.y = point.y;
            }
        }
        else {
            player3->position.y = startY;
        }

        player3->velocity.x = 0;
        player3->velocity.y = 0;
    }

    if (player4->classID == Player->classID) {
        int32 timerP4 = host->timer - 45;
        if (timerP4 > 0) {
            if (timerP4 >= 60) {
                player4->position.y = targetY;
            }
            else if (timerP4 < 60) {
                Vector2 *playerPos = &player4->position;
                Vector2 point = MathHelpers_GetBezierPoint((timerP4 << 16) / 60, playerPos->x, startY, playerPos->x, targetY - 0x800000, playerPos->x,
                    targetY, playerPos->x, targetY);
                player4->position.y = point.y;
            }
        }
        else {
            player4->position.y = startY;
        }

        player4->velocity.x = 0;
        player4->velocity.y = 0;
    }

    return host->timer == 75;
}

bool32 TTCutscene_Cutscene_Wait(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);
    UNUSED(camera);

    player1->position.y = (ScreenInfo->center.y + ScreenInfo->position.y) << 16;
    if (player2->classID == Player->classID)
        player2->position.y = (ScreenInfo->center.y + ScreenInfo->position.y) << 16;
    if (player3->classID == Player->classID)
        player3->position.y = (ScreenInfo->center.y + ScreenInfo->position.y) << 16;
    if (player4->classID == Player->classID)
        player4->position.y = (ScreenInfo->center.y + ScreenInfo->position.y) << 16;

    return host->timer == 100;
}

bool32 TTCutscene_Cutscene_FlyOut(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);
    UNUSED(camera);

    int32 startY  = (ScreenInfo->position.y + ScreenInfo->center.y) << 16;
    int32 targetY = (ScreenInfo->position.y - 32) << 16;

    if (host->timer) {
        if (host->timer >= 60) {
            player1->position.y = targetY;
        }
        else {
            Vector2 *playerPos = &player1->position;
            Vector2 point      = MathHelpers_GetBezierPoint((host->timer << 16) / 60, playerPos->x, startY, playerPos->x, startY, playerPos->x,
                                                       startY + 0x800000, playerPos->x, targetY);
            playerPos->y       = point.y;
        }
    }
    else {
        player1->position.y = startY;
    }

    player1->velocity.x = 0;
    player1->velocity.y = 0;

    if (player2->classID == Player->classID) {
        int32 timerP2 = host->timer - 15;
        if (timerP2 > 0) {
            if (timerP2 >= 60) {
                player2->position.y = targetY;
            }
            else {
                Vector2 *playerPos = &player2->position;
                Vector2 point      = MathHelpers_GetBezierPoint((timerP2 << 16) / 60, playerPos->x, startY, playerPos->x, startY, playerPos->x,
                                                           startY + 0x800000, playerPos->x, targetY);
                playerPos->y       = point.y;
            }
        }
        else {
            player2->position.y = startY;
        }

        player2->velocity.x = 0;
        player2->velocity.y = 0;
    }

    if (player3->classID == Player->classID) {
        int32 timerP3 = host->timer - 30;
        if (timerP3 > 0) {
            if (timerP3 >= 60) {
                player3->position.y = targetY;
            }
            else {
                Vector2 *playerPos = &player3->position;
                Vector2 point      = MathHelpers_GetBezierPoint((timerP3 << 16) / 60, playerPos->x, startY, playerPos->x, startY, playerPos->x,
                    startY + 0x800000, playerPos->x, targetY);
                playerPos->y       = point.y;
            }
        }
        else {
            player3->position.y = startY;
        }

        player3->velocity.x = 0;
        player3->velocity.y = 0;
    }

    if (player4->classID == Player->classID) {
        int32 timerP4 = host->timer - 45;
        if (timerP4 > 0) {
            if (timerP4 >= 60) {
                player4->position.y = targetY;
            }
            else {
                Vector2 *playerPos = &player4->position;
                Vector2 point      = MathHelpers_GetBezierPoint((timerP4 << 16) / 60, playerPos->x, startY, playerPos->x, startY, playerPos->x,
                    startY + 0x800000, playerPos->x, targetY);
                playerPos->y       = point.y;
            }
        }
        else {
            player4->position.y = startY;
        }

        player4->velocity.x = 0;
        player4->velocity.y = 0;
    }

    if (player3->classID != Player->classID) {
        if (host->timer == 75) {
            EntityPlayer *leader      = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
            EntityPlayer *sidekick    = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

            TTCutscene->fxFade->state = FXFade_State_FadeOut;

            for (int32 p = 0; p < 4; ++p) {
                EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
                if (player->classID == Player->classID)
                    globals->restartShield[p] = player->shield;
            }
        }

        return host->timer == 75;
    }
    else if (player3->classID == Player->classID && player4->classID != Player->classID) {
        if (host->timer == 90) {
            EntityPlayer *leader      = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
            EntityPlayer *sidekick    = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

            TTCutscene->fxFade->state = FXFade_State_FadeOut;

            for (int32 p = 0; p < 4; ++p) {
                EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
                if (player->classID == Player->classID)
                    globals->restartShield[p] = player->shield;
            }
        }

        return host->timer == 90;
    }
    else {
        if (host->timer == 105) {
            EntityPlayer *leader      = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
            EntityPlayer *sidekick    = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

            TTCutscene->fxFade->state = FXFade_State_FadeOut;

            for (int32 p = 0; p < 4; ++p) {
                EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
                if (player->classID == Player->classID)
                    globals->restartShield[p] = player->shield;
            }
        }

        return host->timer == 105;
    }
}

bool32 TTCutscene_Cutscene_NextScene(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);
    UNUSED(player1);
    UNUSED(player2);
    UNUSED(player3);
    UNUSED(player4);
    UNUSED(camera);

    if (host->timer >= 64) {

#if MANIA_USE_PLUS
        if (globals->gameMode == MODE_ENCORE)
            RSDK.SetScene("Encore Mode", "Stardust Speedway Zone+ 1");
        else
#endif
            RSDK.SetScene("Mania Mode", "Stardust Speedway Zone 1");
        ++SceneInfo->listPos;

        Zone_StartFadeOut(10, 0x000000);
        return true;
    }

    return false;
}

#if GAME_INCLUDE_EDITOR
void TTCutscene_EditorDraw(void)
{
    RSDK_THIS(TTCutscene);

    CutsceneRules_DrawCutsceneBounds(self, &self->size);
}

void TTCutscene_EditorLoad(void) {}
#endif

void TTCutscene_Serialize(void) { RSDK_EDITABLE_VAR(TTCutscene, VAR_VECTOR2, size); }
