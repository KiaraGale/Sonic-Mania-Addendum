// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: SuperSparkle Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectSuperSparkle *SuperSparkle;

void SuperSparkle_Update(void)
{
    RSDK_THIS(SuperSparkle);

    EntityPlayer *player = self->player;

    StateMachine_Run(self->state);

    if (!(Zone->timer & 7)) {
        int32 x = player->position.x + RSDK.Rand(-TO_FIXED(12), TO_FIXED(12));
        int32 y = player->position.y + RSDK.Rand(-TO_FIXED(18), TO_FIXED(18));

        EntityRing *sparkle = CREATE_ENTITY(Ring, NULL, x, y);
        sparkle->state      = Ring_State_Sparkle;
        sparkle->stateDraw  = Ring_Draw_Sparkle;
        sparkle->active     = ACTIVE_NORMAL;
        sparkle->visible    = false;
        sparkle->velocity.y = -TO_FIXED(1);
        sparkle->drawGroup  = player->drawGroup;
        switch (player->characterID) {
            case ID_SONIC: RSDK.SetSpriteAnimation(SuperSparkle->superFrames, Zone->timer % 3, &sparkle->animator, true, 0); break;
            case ID_TAILS: RSDK.SetSpriteAnimation(SuperSparkle->superFrames, Zone->timer % 3 + 3, &sparkle->animator, true, 0); break;
            case ID_KNUCKLES: RSDK.SetSpriteAnimation(SuperSparkle->superFrames, Zone->timer % 3 + 6, &sparkle->animator, true, 0); break;
            case ID_MIGHTY: RSDK.SetSpriteAnimation(SuperSparkle->superFrames, Zone->timer % 3 + 9, &sparkle->animator, true, 0); break;
            case ID_RAY: RSDK.SetSpriteAnimation(SuperSparkle->superFrames, Zone->timer % 3 + 12, &sparkle->animator, true, 0); break;
            case ID_AMY: RSDK.SetSpriteAnimation(SuperSparkle->superFrames, Zone->timer % 3 + 15, &sparkle->animator, true, 0); break;
        }
        int32 cnt = sparkle->animator.frameCount;
        switch (sparkle->animator.animationID) {
            case 0:
            case 3:
            case 6:
            case 9:
            case 12:
            case 15:
            sparkle->alpha = 0xE0;
            cnt >>= 1;
            break;
        }
        sparkle->maxFrameCount  = cnt - 1;
        sparkle->animator.speed = RSDK.Rand(6, 8);
    }

    if (player->superState != SUPERSTATE_SUPER || player->classID != Player->classID)
        destroyEntity(self);
}

void SuperSparkle_LateUpdate(void)
{
    RSDK_THIS(SuperSparkle);
    EntityPlayer *player = self->player;

    if (!self->state) {
        if (player->superState == SUPERSTATE_SUPER) {
            if (player->hyperState) {
                self->state = SuperSparkle_State_PlayerHyper;
                RSDK.ProcessAnimation(&self->sparkleAnimator);
                RSDK.ProcessAnimation(&self->sparkleAddAnimator);
            }
            else
                self->state = SuperSparkle_State_PlayerSuper;
        }
    }
}

void SuperSparkle_StaticUpdate(void) {}

void SuperSparkle_Draw(void)
{
    RSDK_THIS(SuperSparkle);

    if (self->state == SuperSparkle_State_PlayerHyper) {
        RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 1, &self->sparkleAnimator, true, 1);
        RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 2, &self->sparkleAddAnimator, true, 1);

        // Sparkle 1
        Vector2 drawPos = self->player->position;
        int32 timer     = self->timer % 8;

        uint8 tOffset  = timer + 2;
        uint8 tOffset2 = timer + 9;

        if (tOffset > -1)
            tOffset2 = tOffset;

        timer   = tOffset - (tOffset2 & -8);
        drawPos = self->player->position;

        drawPos.x += timer * 0x180 * RSDK.Cos1024(self->angle);
        drawPos.y += timer * 0x180 * RSDK.Sin1024(self->angle);

        self->sparkleAnimator.frameID    = timer;
        self->sparkleAddAnimator.frameID = timer;

        if (self->sparkleAnimator.frameID > 7)
            self->sparkleAnimator.frameID = 7;

        if (self->sparkleAddAnimator.frameID > 7)
            self->sparkleAddAnimator.frameID = 7;

        self->inkEffect = INK_ALPHA;
        self->alpha     = 0x40;
        RSDK.DrawSprite(&self->sparkleAddAnimator, &drawPos, false);
        self->inkEffect = INK_NONE;
        self->alpha     = 0x100;
        RSDK.DrawSprite(&self->sparkleAnimator, &drawPos, false);

        // Sparkle 2
        tOffset  = timer + 2;
        tOffset2 = timer + 9;

        if (tOffset > -1)
            tOffset2 = tOffset;

        timer   = tOffset - (tOffset2 & -8);
        drawPos = self->player->position;

        drawPos.x += timer * 0x180 * RSDK.Cos1024(self->angle + 0x100);
        drawPos.y += timer * 0x180 * RSDK.Sin1024(self->angle + 0x100);

        self->sparkleAnimator.frameID = timer;
        self->sparkleAddAnimator.frameID = timer;

        if (self->sparkleAnimator.frameID > 7)
            self->sparkleAnimator.frameID = 7;

        if (self->sparkleAddAnimator.frameID > 7)
            self->sparkleAddAnimator.frameID = 7;

        self->inkEffect = INK_ALPHA;
        self->alpha     = 0x40;
        RSDK.DrawSprite(&self->sparkleAddAnimator, &drawPos, false);
        self->inkEffect = INK_NONE;
        self->alpha     = 0x100;
        RSDK.DrawSprite(&self->sparkleAnimator, &drawPos, false);

        // Sparkle 3
        tOffset  = timer + 2;
        tOffset2 = timer + 9;

        if (tOffset > -1)
            tOffset2 = tOffset;

        timer   = tOffset - (tOffset2 & -8);
        drawPos = self->player->position;

        drawPos.x += timer * 0x180 * RSDK.Cos1024(self->angle + 0x200);
        drawPos.y += timer * 0x180 * RSDK.Sin1024(self->angle + 0x200);

        self->sparkleAnimator.frameID    = timer;
        self->sparkleAddAnimator.frameID = timer;

        if (self->sparkleAnimator.frameID > 7)
            self->sparkleAnimator.frameID = 7;

        if (self->sparkleAddAnimator.frameID > 7)
            self->sparkleAddAnimator.frameID = 7;

        self->inkEffect = INK_ALPHA;
        self->alpha     = 0x40;
        RSDK.DrawSprite(&self->sparkleAddAnimator, &drawPos, false);
        self->inkEffect = INK_NONE;
        self->alpha     = 0x100;
        RSDK.DrawSprite(&self->sparkleAnimator, &drawPos, false);

        // Sparkle 4
        tOffset  = timer + 2;
        tOffset2 = timer + 9;

        if (tOffset > -1)
            tOffset2 = tOffset;

        timer   = tOffset - (tOffset2 & -8);
        drawPos = self->player->position;

        drawPos.x += timer * 0x180 * RSDK.Cos1024(self->angle + 0x300);
        drawPos.y += timer * 0x180 * RSDK.Sin1024(self->angle + 0x300);

        self->sparkleAnimator.frameID    = timer;
        self->sparkleAddAnimator.frameID = timer;

        if (self->sparkleAnimator.frameID > 7)
            self->sparkleAnimator.frameID = 7;

        if (self->sparkleAddAnimator.frameID > 7)
            self->sparkleAddAnimator.frameID = 7;

        self->inkEffect = INK_ALPHA;
        self->alpha     = 0x40;
        RSDK.DrawSprite(&self->sparkleAddAnimator, &drawPos, false);
        self->inkEffect = INK_NONE;
        self->alpha     = 0x100;
        RSDK.DrawSprite(&self->sparkleAnimator, &drawPos, false);
    }
}

void SuperSparkle_Create(void *data)
{
    RSDK_THIS(SuperSparkle);

    if (!SceneInfo->inEditor) {
        self->active = ACTIVE_NORMAL;
        self->player = (EntityPlayer *)data;

        if (self->player->classID == Player->classID) {
            if (!self->player->hyperState) {
                self->state = SuperSparkle_State_PlayerSuper;
            }
            else {
                self->visible = true;
                RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 1, &self->sparkleAnimator, false, 0);
                self->drawGroup = self->player->drawGroup - 1;
                self->state = SuperSparkle_State_PlayerHyper;
            }
        }

        RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 1, &self->sparkleAnimator, false, 0);
        RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 2, &self->sparkleAddAnimator, false, 0);
    }
}

void SuperSparkle_StageLoad(void)
{
    SuperSparkle->aniFrames   = RSDK.LoadSpriteAnimation("Global/SuperSparkle.bin", SCOPE_STAGE);
    SuperSparkle->superFrames = RSDK.LoadSpriteAnimation("Global/SuperParticles.bin", SCOPE_STAGE);
}

void SuperSparkle_State_PlayerSuper(void)
{
    RSDK_THIS(SuperSparkle);
    EntityPlayer *player = self->player;

    if (!player) {
        destroyEntity(self);
    }
    else {
        if (player->groundedStore)
            self->canSpawnSparkle = abs(player->velocity.y) + abs(player->velocity.x) > TO_FIXED(6);

        if (self->canSpawnSparkle) {
            if (++self->timer == 12) {
                self->timer = 0;

                EntityDebris *sparkle = CREATE_ENTITY(Debris, NULL, player->position.x, player->position.y);
                sparkle->state        = Debris_State_Move;
                sparkle->timer        = 16;
                sparkle->inkEffect    = INK_ADD;
                sparkle->alpha        = 0x100;
                sparkle->drawGroup    = Zone->objectDrawGroup[1];
                sparkle->drawGroup    = player->drawGroup;
                RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 0, &sparkle->animator, true, 0);
            }
        }
        else {
            self->timer = 0;
        }
    }

    if (player->superState != SUPERSTATE_SUPER || player->active == ACTIVE_NEVER)
        destroyEntity(self);
}

void SuperSparkle_State_PlayerHyper(void)
{
    RSDK_THIS(SuperSparkle);

    self->drawGroup = self->player->drawGroup - 1;
    ++self->timer;

    if ((self->player->direction | FLIP_Y) == FLIP_Y)
        self->angle += 8;
    else
        self->angle -= 8;
}

#if GAME_INCLUDE_EDITOR
void SuperSparkle_EditorDraw(void)
{
    Animator animator;
    RSDK.SetSpriteAnimation(SuperSparkle->aniFrames, 0, &animator, true, 3);

    RSDK.DrawSprite(&animator, NULL, false);
}

void SuperSparkle_EditorLoad(void)
{
    SuperSparkle->aniFrames   = RSDK.LoadSpriteAnimation("Global/SuperSparkle.bin", SCOPE_STAGE);
    SuperSparkle->superFrames = RSDK.LoadSpriteAnimation("Global/SuperParticles.bin", SCOPE_STAGE);
}
#endif

void SuperSparkle_Serialize(void) {}
