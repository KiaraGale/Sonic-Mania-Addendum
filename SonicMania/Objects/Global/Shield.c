// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: Shield Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectShield *Shield;
Hitbox Insta_Hitbox  = { -24, -24, 24, 24 };
Hitbox Shield_Hitbox = { -16, -16, 16, 16 };

void Shield_Update(void)
{
    RSDK_THIS(Shield);
    StateMachine_Run(self->state);

    EntityPlayer *player = self->player;
    if (player) {
        // bit 0 = flipX
        // bit 1 = flipY
        // if bit 2 is set, draw on player draw order (draw above player), else draw behind player
        // bits 3-7 aren't used, the values are stored as 0-9 in ASCII because thats how RSDK anim editor treats it
        if (self->frameFlags < 0 || !(self->frameFlags & ~3))
            self->drawGroup = player->drawGroup - 1;
        else
            self->drawGroup = player->drawGroup;
        self->visible      = self->forceVisible & player->visible;
        self->forceVisible = true;
    }
}

void Shield_LateUpdate(void) {}

void Shield_StaticUpdate(void) {}

void Shield_Draw(void)
{
    RSDK_THIS(Shield);

    EntityPlayer *player = self->player;
    if (player) {
        if (player->isChibi) {
            self->drawFX |= FX_SCALE;
            self->scale.x = 0x100;
            self->scale.y = 0x100;
        }
        else {
            if (player->drawFX & FX_SCALE)
                self->drawFX |= FX_SCALE;
            else
                self->drawFX &= ~FX_SCALE;
            self->scale.x = player->scale.x;
            self->scale.y = player->scale.y;
        }

        self->position = player->position;

        Hitbox *playerHitbox = RSDK.GetHitbox(&player->animator, 0);
        if (playerHitbox) {
            if (player->direction & FLIP_X)
                self->position.x += (playerHitbox->left << 15) - (playerHitbox->right << 15) - (playerHitbox->left << 16);
            else
                self->position.x += ((playerHitbox->right + 2 * playerHitbox->left) << 15) - (playerHitbox->left << 15);
            if ((player->direction & FLIP_Y) || player->invertGravity)
                self->position.y += (playerHitbox->top << 15) - (playerHitbox->bottom << 15) - (playerHitbox->top << 16);
            else
                self->position.y += ((playerHitbox->bottom + 2 * playerHitbox->top) << 15) - (playerHitbox->top << 15);
        }
    }

    if (self->type == SHIELD_BUBBLE && player->superState != SUPERSTATE_SUPER) {
        self->inkEffect = INK_ADD;
        RSDK.DrawSprite(&self->fxAnimator, NULL, false);
        self->inkEffect = INK_BLEND;
    }

    if (self->type == SHIELD_BLUE && player->characterID == ID_KNUCKLES) {
        for (int32 c = 0; c < 6; ++c) {
            Shield->colorStorage[c] = RSDK.GetPaletteEntry(0, 2 + c);
            RSDK.SetPaletteEntry(0, 2 + c, Shield->shieldPalette_Knux[c]);
        }

        RSDK.DrawSprite(&self->shieldAnimator, NULL, false);

        for (int32 c = 0; c < 6; ++c) {
            RSDK.SetPaletteEntry(0, 2 + c, Shield->colorStorage[c]);
        }
    }
    else {
        RSDK.DrawSprite(&self->shieldAnimator, NULL, false);
    }
}

void Shield_Create(void *data)
{
    RSDK_THIS(Shield);

    self->active  = ACTIVE_NORMAL;
    self->visible = true;

    if (data) {
        EntityPlayer *player = (EntityPlayer *)data;
        if (player->classID == Player->classID)
            self->type = player->shield;
        self->player = player;
    }

    self->drawFX = FX_FLIP;
    self->state  = Shield_State_Default;
    switch (self->type) {
        case SHIELD_BLUE:
            RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_BLUE, &self->shieldAnimator, true, 0);
            self->inkEffect = INK_ADD;
            self->alpha     = 0x80;
            break;

        case SHIELD_BUBBLE:
            RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_BUBBLEADD, &self->fxAnimator, true, 0);
            RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_BUBBLE, &self->shieldAnimator, true, 0);
            self->alpha = 0x100;
            break;

        case SHIELD_FIRE: RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_FIRE, &self->shieldAnimator, true, 0); break;

        case SHIELD_LIGHTNING: RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_LIGHTNING, &self->shieldAnimator, true, 0); break;

        default: break;
    }
}

void Shield_StageLoad(void)
{
    Shield->aniFrames = RSDK.LoadSpriteAnimation("Global/Shields.bin", SCOPE_STAGE);

    Shield->sfxBlueShield      = RSDK.GetSfx("Global/BlueShield.wav");
    Shield->sfxBubbleShield    = RSDK.GetSfx("Global/BubbleShield.wav");
    Shield->sfxFireShield      = RSDK.GetSfx("Global/FireShield.wav");
    Shield->sfxLightningShield = RSDK.GetSfx("Global/LightningShield.wav");
    Shield->sfxInstaShield     = RSDK.GetSfx("Global/InstaShield.wav");
    Shield->sfxBubbleBounce    = RSDK.GetSfx("Global/BubbleBounce.wav");
    Shield->sfxFireDash        = RSDK.GetSfx("Global/FireDash.wav");
    Shield->sfxLightningJump   = RSDK.GetSfx("Global/LightningJump.wav");
}

void Shield_State_Default(void)
{
    RSDK_THIS(Shield);

    RSDK.ProcessAnimation(&self->shieldAnimator);
    RSDK.ProcessAnimation(&self->fxAnimator);
    self->frameFlags = RSDK.GetFrameID(&self->shieldAnimator) & 7;
    self->direction  = self->frameFlags & 3;
}

void Shield_State_BubbleDrop(void)
{
    RSDK_THIS(Shield);

    Shield_State_Default();

    if (self->fxAnimator.frameID == self->fxAnimator.frameCount - 1) {
        RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_BUBBLEATTACKUPADD, &self->fxAnimator, true, 0);
        RSDK.SetSpriteAnimation(-1, 0, &self->shieldAnimator, true, 0);
        self->state = Shield_State_BubbleBounced;
    }
}

void Shield_State_BubbleBounced(void)
{
    RSDK_THIS(Shield);

    Shield_State_Default();

    if (self->fxAnimator.frameID == self->fxAnimator.frameCount - 1) {
        RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_BUBBLEADD, &self->fxAnimator, true, 0);
        RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_BUBBLE, &self->shieldAnimator, true, 0);
        self->state = Shield_State_Default;
    }
}

void Shield_State_FireDash(void)
{
    RSDK_THIS(Shield);

    RSDK.ProcessAnimation(&self->shieldAnimator);
    self->frameFlags = RSDK.GetFrameID(&self->shieldAnimator) & 7;

    if (++self->timer > 24) {
        self->timer = 0;
        RSDK.SetSpriteAnimation(Shield->aniFrames, SHIELDANI_FIRE, &self->shieldAnimator, true, 0);
        self->state = Shield_State_Default;
    }
}

void Shield_State_LightningSparks(void)
{
    RSDK_THIS(Shield);

    RSDK.ProcessAnimation(&self->shieldAnimator);
    self->frameFlags = RSDK.GetFrameID(&self->shieldAnimator) & 7;
    self->direction  = self->frameFlags & 3;

    if (self->player) {
        self->position.x = self->player->position.x;
        self->position.y = self->player->position.y;
    }

    EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
    debris->timer        = 22;
    debris->velocity.x   = -TO_FIXED(2);
    debris->velocity.y   = -TO_FIXED(2);
    debris->drawGroup    = Zone->playerDrawGroup[1];
    RSDK.SetSpriteAnimation(Shield->aniFrames, 4, &debris->animator, true, 0);
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
    RSDK.SetSpriteAnimation(Shield->aniFrames, 4, &debris->animator, true, 0);
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
    RSDK.SetSpriteAnimation(Shield->aniFrames, 4, &debris->animator, true, 0);
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
    RSDK.SetSpriteAnimation(Shield->aniFrames, 4, &debris->animator, true, 0);
    if (self->drawFX & FX_SCALE) {
        debris->drawFX |= FX_SCALE;
        debris->scale.x = self->scale.x;
        debris->scale.y = self->scale.y;
    }

    self->state = Shield_State_Default;
}

void Shield_State_Insta(void)
{
    RSDK_THIS(Shield);

    RSDK.ProcessAnimation(&self->shieldAnimator);

    if (self->player)
        self->player->invincibleTimer = 1;

    if (self->shieldAnimator.frameID == self->shieldAnimator.frameCount - 1)
        destroyEntity(self);
}

bool32 Shield_State_Reflect(EntityShield *shield, void *p)
{
    RSDK_THIS(Shield);
    EntityPlayer *player = self->player;
    bool32 deflected = false;

    if (shield->state == Shield_State_Insta) {
        Entity *projectile = (Entity *)p;

        RSDK.PlaySfx(Player->sfxMightyDeflect, false, 0xFE);
        int32 angle             = RSDK.ATan2(shield->position.x - projectile->position.x, shield->position.y - projectile->position.y);
        projectile->velocity.x  = -0x800 * RSDK.Cos256(angle);
        projectile->velocity.y  = -0x800 * RSDK.Sin256(angle);
        projectile->interaction = false;
        if (!Player->hasReflectAchievement) {
            API_UnlockAchievement(&achievementList[ACH_INSTAREFLECT]);
            Player->hasReflectAchievement = true;
        }

        if (player->superState == SUPERSTATE_SUPER) {
            if (player->miracleState)
                Player_GiveRings(player, 3, true);
            else
                Player_GiveRings(player, 2, true);
        }

        return true;
    }
    else {
        return false;
    }
}

bool32 Shield_CheckCollisionTouch(EntityShield *shield, void *e, Hitbox *entityHitbox)
{
    RSDK_THIS(Shield);
    Hitbox *shieldHitbox = &Insta_Hitbox;
    Entity *entity       = (Entity *)e;

    return RSDK.CheckObjectCollisionTouchBox(entity, entityHitbox, shield, shieldHitbox);
}

#if GAME_INCLUDE_EDITOR
void Shield_EditorDraw(void)
{
    RSDK_THIS(Shield);

    RSDK.SetSpriteAnimation(Shield->aniFrames, 0, &self->shieldAnimator, false, 0);
    self->inkEffect = INK_ADD;
    self->alpha     = 0x80;

    RSDK.DrawSprite(&self->shieldAnimator, NULL, false);
}

void Shield_EditorLoad(void) { Shield->aniFrames = RSDK.LoadSpriteAnimation("Global/Shields.bin", SCOPE_STAGE); }
#endif

void Shield_Serialize(void) {}
