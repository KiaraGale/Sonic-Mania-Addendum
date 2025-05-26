// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: FBZ1Outro Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectFBZ1Outro *FBZ1Outro;

void FBZ1Outro_Update(void)
{
    RSDK_THIS(FBZ1Outro);

    if (!self->activated) {
        FBZ1Outro_StartCutscene();
        self->activated = true;
    }
}

void FBZ1Outro_LateUpdate(void) {}

void FBZ1Outro_StaticUpdate(void) {}

void FBZ1Outro_Draw(void) {}

void FBZ1Outro_Create(void *data)
{
    RSDK_THIS(FBZ1Outro);

    INIT_ENTITY(self);
    CutsceneRules_SetupEntity(self, &self->size, &self->hitbox);
    self->active = ACTIVE_NEVER;
}

void FBZ1Outro_StageLoad(void)
{
    foreach_all(BigSqueeze, boss)
    {
        switch (boss->type) {
            default: break;

            case BIGSQUEEZE_CRUSHER_L: FBZ1Outro->bossBorderL = boss; break;
            case BIGSQUEEZE_CRUSHER_R: FBZ1Outro->bossBorderR = boss; break;
            case BIGSQUEEZE_MANAGER: FBZ1Outro->bossManager = boss; break;
        }
    }

    foreach_all(CollapsingPlatform, platform)
    {
        if (platform->eventOnly) {
            FBZ1Outro->collapsingPlatform = platform;
            foreach_break;
        }
    }

    foreach_all(Crane, crane)
    {
        if (crane->position.x == 0x33400000 && crane->position.y == 0x9100000)
            FBZ1Outro->craneP1 = crane;

        if (crane->position.x == 0x33640000 && crane->position.y == 0x9100000)
            FBZ1Outro->craneP2 = crane;

        if (crane->position.x == 0x33880000 && crane->position.y == 0x9100000)
            FBZ1Outro->craneP3 = crane;

        if (crane->position.x == 0x33AC0000 && crane->position.y == 0x9100000)
            FBZ1Outro->craneP4 = crane;
    }

    FBZ1Outro->sfxDrop = RSDK.GetSfx("Stage/Drop.wav");
}

void FBZ1Outro_StartCutscene(void)
{
    RSDK_THIS(FBZ1Outro);

    CutsceneSeq_StartSequence(self, FBZ1Outro_Cutscene_CrushTrash, FBZ1Outro_Cutscene_TrashDrop, FBZ1Outro_Cutscene_CraneRide,
                              FBZ1Outro_Cutscene_PrepareFBZ2, StateMachine_None);

#if MANIA_USE_PLUS
    CutsceneSeq_SetSkipType(SKIPTYPE_RELOADSCN);
#endif
}

void FBZ1Outro_HandleTrash(void)
{
    foreach_active(FBZTrash, trash) { trash->velocity.y = 0; }
    foreach_active(FBZSinkTrash, sinkTrash) { sinkTrash->velocity.y = 0; }

    foreach_active(SignPost, signPost)
    {
        signPost->velocity.x = 0;
        signPost->velocity.y = 0;
        signPost->position.y = BigSqueeze->boundsB - 0x180000;

        int32 boundsL = BigSqueeze->crusherX[BIGSQUEEZE_CRUSHER_L] + 0x180000;
        int32 boundsR = BigSqueeze->crusherX[BIGSQUEEZE_CRUSHER_R] - 0x180000;

        signPost->position.x = CLAMP(signPost->position.x, boundsL, boundsR);
    }
}

void FBZ1Outro_DispenseTrash(void)
{
    foreach_active(FBZTrash, trash)
    {
        trash->state = StateMachine_None;
        trash->position.y += trash->velocity.y;
        trash->velocity.y += 0x3800;
    }

    foreach_active(FBZSinkTrash, sinkTrash)
    {
        sinkTrash->position.y += sinkTrash->velocity.y;
        sinkTrash->velocity.y += 0x3800;
        sinkTrash->type = FBZSINKTRASH_DECOR;
    }

    foreach_active(SignPost, signPost)
    {
        signPost->position.y += signPost->velocity.y;
        signPost->velocity.y += 0x3800;
        signPost->type = SIGNPOST_COMP;
    }
}

bool32 FBZ1Outro_Cutscene_CrushTrash(EntityCutsceneSeq *host)
{
    RSDK_THIS(FBZ1Outro);

    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);
    UNUSED(camera);

    EntityBigSqueeze *bossBorderL = FBZ1Outro->bossBorderL;
    EntityBigSqueeze *bossBorderR = FBZ1Outro->bossBorderR;
    EntityBigSqueeze *bossManager = FBZ1Outro->bossManager;

    EntityCollapsingPlatform *platform = FBZ1Outro->collapsingPlatform;

    if (!host->timer) {
        player1->stateInput = StateMachine_None;
        RSDK.SetSpriteAnimation(player1->aniFrames, ANI_BALANCE_1, &player1->animator, false, 0);

        player1->state = Player_State_Static;
        CutsceneSeq_LockPlayerControl(player1);

        if (player2->classID == Player->classID) {
            RSDK.SetSpriteAnimation(player2->aniFrames, ANI_BALANCE_1, &player2->animator, false, 0);

            player2->state = Player_State_Static;
            CutsceneSeq_LockPlayerControl(player2);
        }
        if (player3->classID == Player->classID) {
            RSDK.SetSpriteAnimation(player3->aniFrames, ANI_BALANCE_1, &player3->animator, false, 0);

            player3->state = Player_State_Static;
            CutsceneSeq_LockPlayerControl(player3);
        }
        if (player4->classID == Player->classID) {
            RSDK.SetSpriteAnimation(player4->aniFrames, ANI_BALANCE_1, &player4->animator, false, 0);

            player4->state = Player_State_Static;
            CutsceneSeq_LockPlayerControl(player4);
        }
    }

    player1->nextGroundState = StateMachine_None;
    player1->nextAirState    = StateMachine_None;
    if (player2->classID == Player->classID) {
        player2->nextGroundState = StateMachine_None;
        player2->nextAirState    = StateMachine_None;
    }
    if (player3->classID == Player->classID) {
        player3->nextGroundState = StateMachine_None;
        player3->nextAirState    = StateMachine_None;
    }
    if (player4->classID == Player->classID) {
        player4->nextGroundState = StateMachine_None;
        player4->nextAirState    = StateMachine_None;
    }

    if (BigSqueeze->crusherX[BIGSQUEEZE_CRUSHER_R] - BigSqueeze->crusherX[BIGSQUEEZE_CRUSHER_L] <= 0xB00000) {
        BigSqueeze->isCrushing = false;
        RSDK.SetSpriteAnimation(player1->aniFrames, ANI_HURT, &player1->animator, false, 0);
        player1->state    = Player_State_Air;
        player1->onGround = false;
        if (player2->classID == Player->classID) {
            RSDK.SetSpriteAnimation(player2->aniFrames, ANI_HURT, &player2->animator, false, 0);
            player2->state    = Player_State_Air;
            player2->onGround = false;
        }
        else {
            destroyEntity(FBZ1Outro->craneP2);
            self->grabbedPlayers |= 2;
        }
        if (player3->classID == Player->classID) {
            RSDK.SetSpriteAnimation(player3->aniFrames, ANI_HURT, &player3->animator, false, 0);
            player3->state    = Player_State_Air;
            player3->onGround = false;
        }
        else {
            destroyEntity(FBZ1Outro->craneP3);
            self->grabbedPlayers |= 3;
        }
        if (player4->classID == Player->classID) {
            RSDK.SetSpriteAnimation(player4->aniFrames, ANI_HURT, &player4->animator, false, 0);
            player4->state    = Player_State_Air;
            player4->onGround = false;
        }
        else {
            destroyEntity(FBZ1Outro->craneP4);
            self->grabbedPlayers |= 4;
        }

        bossBorderL->setupTimer = 0;
        bossBorderL->state      = BigSqueeze_StateCrusher_BeginCrushing;
        bossBorderR->setupTimer = 0;
        bossBorderR->state      = BigSqueeze_StateCrusher_BeginCrushing;
        bossManager->state      = BigSqueeze_StateManager_HandleOutro;
        Zone->cameraBoundsB[0]  = 2660;
        Zone->cameraBoundsB[1]  = 2660;
        Zone->cameraBoundsR[0]  = 14080;
        Zone->cameraBoundsR[1]  = 14080;
        platform->stoodPos.x    = 1;
        RSDK.PlaySfx(FBZ1Outro->sfxDrop, false, 255);

        return true;
    }
    else {
        BigSqueeze->isCrushing = true;
        FBZ1Outro_HandleTrash();
        if (host->values[0])
            host->values[0] = true;

        bossBorderL->setupTimer = 0;
        bossBorderL->state      = BigSqueeze_StateCrusher_Crushing;
        bossBorderR->setupTimer = 0;
        bossBorderR->state      = BigSqueeze_StateCrusher_Crushing;
    }

    return false;
}
bool32 FBZ1Outro_Cutscene_TrashDrop(EntityCutsceneSeq *host)
{
    RSDK_THIS(FBZ1Outro);

    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);
    UNUSED(camera);

    EntityBigSqueeze *bossBorderL = FBZ1Outro->bossBorderL;
    EntityBigSqueeze *bossBorderR = FBZ1Outro->bossBorderR;
    bossBorderL->setupTimer       = 0;
    bossBorderL->state            = BigSqueeze_StateCrusher_BeginCrushing;
    bossBorderR->setupTimer       = 0;
    bossBorderR->state            = BigSqueeze_StateCrusher_BeginCrushing;

    EntityCrane *craneP1 = FBZ1Outro->craneP1;
    craneP1->position.x  = player1->position.x;
    if (craneP1->state == Crane_State_RiseUp) {
        craneP1->startPos.x = player1->position.x;
        craneP1->startPos.y = craneP1->position.y;
        self->grabbedPlayers |= 1;
    }

    if (player2->classID == Player->classID) {
        EntityCrane *craneP2 = FBZ1Outro->craneP2;
        craneP2->position.x  = player2->position.x;
        if (craneP2->state == Crane_State_RiseUp) {
            craneP2->startPos.x = craneP2->position.x;
            craneP2->startPos.y = craneP2->position.y;
            self->grabbedPlayers |= 2;
        }
    }
    if (player3->classID == Player->classID) {
        EntityCrane *craneP3 = FBZ1Outro->craneP3;
        craneP3->position.x  = player3->position.x;
        if (craneP3->state == Crane_State_RiseUp) {
            craneP3->startPos.x = craneP3->position.x;
            craneP3->startPos.y = craneP3->position.y;
            self->grabbedPlayers |= 3;
        }
    }
    if (player4->classID == Player->classID) {
        EntityCrane *craneP4 = FBZ1Outro->craneP4;
        craneP4->position.x  = player4->position.x;
        if (craneP4->state == Crane_State_RiseUp) {
            craneP4->startPos.x = craneP4->position.x;
            craneP4->startPos.y = craneP4->position.y;
            self->grabbedPlayers |= 4;
        }
    }

    if (self->grabbedPlayers == (1 | 2 | 3 | 4))
        return true;

    FBZ1Outro_DispenseTrash();

    return false;
}
bool32 FBZ1Outro_Cutscene_CraneRide(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);
    UNUSED(camera);

    FBZ1Outro_DispenseTrash();

    return player1->onGround && (player2->classID != Player->classID || player2->onGround) 
        && (player3->classID != Player->classID || player3->onGround) && (player4->classID != Player->classID || player4->onGround);
}
bool32 FBZ1Outro_Cutscene_PrepareFBZ2(EntityCutsceneSeq *host)
{
    MANIA_GET_PLAYER(player1, player2, player3, player4, camera);

    if (!host->timer) {
        Zone->cameraBoundsL[0]      = 13568;
        Zone->cameraBoundsL[1]      = 13568;
        Zone->cameraBoundsB[0]      = 2660;
        Zone->cameraBoundsB[0]      = 2660;
        Zone->playerBoundActiveL[0] = true;
    }

    RSDK.SetSpriteAnimation(player1->aniFrames, ANI_IDLE, &player1->animator, false, 0);
    if (player2->classID == Player->classID)
        RSDK.SetSpriteAnimation(player2->aniFrames, ANI_IDLE, &player2->animator, false, 0);
    if (player3->classID == Player->classID)
        RSDK.SetSpriteAnimation(player3->aniFrames, ANI_IDLE, &player3->animator, false, 0);
    if (player4->classID == Player->classID)
        RSDK.SetSpriteAnimation(player4->aniFrames, ANI_IDLE, &player4->animator, false, 0);

    if (camera->offset.x || ScreenInfo->position.x < Zone->cameraBoundsL[0] || host->timer < 30) {
        if (ScreenInfo->position.x < Zone->cameraBoundsL[0])
            ScreenInfo->position.x++;
        if (camera->offset.x > 0)
            camera->offset.x -= 0x10000;
    }
    else {
        Zone_StoreEntities(13780 << 16, 2660 << 16);
        RSDK.LoadScene();

        int32 id         = 0;
        TileLayer *layer = RSDK.GetTileLayer(1);
        for (int32 i = 0; i < layer->scrollInfoCount; ++i) {
            globals->parallaxOffset[id++] = layer->scrollInfo[i].scrollPos + layer->scrollInfo[i].parallaxFactor * ScreenInfo->position.x;
        }

        foreach_all(ParallaxSprite, parallaxSprite)
        {
            globals->parallaxOffset[id++] = parallaxSprite->scrollPos.x + parallaxSprite->parallaxFactor.x * ScreenInfo->position.x;
        }

        return true;
    }
    return false;
}

#if GAME_INCLUDE_EDITOR
void FBZ1Outro_EditorDraw(void)
{
    RSDK_THIS(FBZ1Outro);
    CutsceneRules_DrawCutsceneBounds(self, &self->size);
}

void FBZ1Outro_EditorLoad(void) {}
#endif

void FBZ1Outro_Serialize(void) { RSDK_EDITABLE_VAR(FBZ1Outro, VAR_VECTOR2, size); }
