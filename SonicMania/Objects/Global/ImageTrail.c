// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: ImageTrail Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectImageTrail *ImageTrail;

void ImageTrail_Update(void) {}

void ImageTrail_LateUpdate(void)
{
    RSDK_THIS(ImageTrail);

    EntityPlayer *player = self->player;

    if (!player || (player->classID != self->playerClassID && player->classID != DebugMode->classID)) {
        destroyEntity(self);
    }
    else {
        // Check for fadeouts/destroy triggers
        if (player->superState == SUPERSTATE_SUPER) {
            self->baseAlpha = 0x100;
        }
#if MANIA_USE_PLUS
        else if (player->speedShoesTimer < 16 && player->state == Player_State_MightyHammerDrop) {
            self->fadeoutTimer = 16;
        }
#endif
        else if (self->fadeoutTimer <= 0 && player->speedShoesTimer < 32) {
            self->baseAlpha = 8 * player->speedShoesTimer;
            if (!self->baseAlpha && player->state != Player_State_RayGlide) 
                destroyEntity(self);
        }
        else if (self->fadeoutTimer > 0) {
            self->fadeoutTimer--;
            self->baseAlpha = 16 * self->fadeoutTimer;
            if (!self->baseAlpha && player->state != Player_State_RayGlide)
                destroyEntity(self);
        }
    }

    // if we destroyed this entity, skip any more logic
    if (!self->classID)
        return;

    // Update recordings
    for (int32 i = IMAGETRAIL_TRACK_COUNT - 1; i > 0; --i) {
        self->statePos[i].x     = self->statePos[i - 1].x;
        self->statePos[i].y     = self->statePos[i - 1].y;
        self->stateRotation[i]  = self->stateRotation[i - 1];
        self->stateScale[i]     = self->stateScale[i - 1];
        self->stateDirection[i] = self->stateDirection[i - 1];
        self->stateVisible[i]   = self->stateVisible[i - 1];
        memcpy(&self->stateAnimator[i], &self->stateAnimator[i - 1], sizeof(Animator));

        self->stateTailPos[i].x     = self->stateTailPos[i - 1].x;
        self->stateTailPos[i].y     = self->stateTailPos[i - 1].y;
        self->stateTailRotation[i]  = self->stateTailRotation[i - 1];
        self->stateTailScale[i]     = self->stateTailScale[i - 1];
        self->stateTailDirection[i] = self->stateTailDirection[i - 1];
        self->stateTailVisible[i]   = self->stateTailVisible[i - 1];
        memcpy(&self->stateTailAnimator[i], &self->stateTailAnimator[i - 1], sizeof(Animator));
    }

    self->statePos[0].x     = self->currentPos.x;
    self->statePos[0].y     = self->currentPos.y;
    self->stateRotation[0]  = self->currentRotation;
    self->stateDirection[0] = self->currentDirection;
    self->stateScale[0]     = self->currentScale;
    self->stateVisible[0]   = self->currentVisible;
    memcpy(&self->stateAnimator[0], &self->currentAnimator, sizeof(Animator));

    self->stateTailPos[0].x     = self->currentTailPos.x;
    self->stateTailPos[0].y     = self->currentTailPos.y;
    self->stateTailRotation[0]  = self->currentTailRotation;
    self->stateTailDirection[0] = self->currentTailDirection;
    self->stateTailScale[0]     = self->currentTailScale;
    self->stateTailVisible[0]   = self->currentTailVisible;
    memcpy(&self->stateTailAnimator[0], &self->curTailAnimator, sizeof(Animator));

    // Record Player
    self->drawGroup        = player->drawGroup - 1;
    self->currentPos.x     = player->position.x;
    self->currentPos.y     = player->position.y;
    self->currentRotation  = player->rotation;
    self->currentDirection = player->direction;
    memcpy(&self->currentAnimator, &player->animator, sizeof(Animator));
    if (player->isChibi || !(player->drawFX & FX_SCALE))
        self->currentScale = 0x200;
    else
        self->currentScale = player->scale.x;

    if (player->characterID == ID_TAILS) {
        self->drawGroup            = player->drawGroup - 1;
        self->currentTailPos.x     = player->position.x;
        self->currentTailPos.y     = player->position.y;
        self->currentTailRotation  = player->tailRotation;
        self->currentTailDirection = player->tailDirection;
        memcpy(&self->curTailAnimator, &player->tailAnimator, sizeof(Animator));

        if (player->isChibi || !(player->drawFX & FX_SCALE))
            self->currentTailScale = 0x200;
        else
            self->currentTailScale = player->scale.x;
    }

    self->currentVisible     = player->visible;
    self->currentTailVisible = player->visible;
}

void ImageTrail_StaticUpdate(void) {}

void ImageTrail_Draw(void)
{
    RSDK_THIS(ImageTrail);
    EntityPlayer *player = self->player;

    // int32 alpha[3] = { 0xA0 * self->baseAlpha >> 8, self->baseAlpha >> 1, 0x60 * self->baseAlpha >> 8 };
    int32 alpha = 0x60 * self->baseAlpha >> 8;
    int32 inc   = 0x40 / (IMAGETRAIL_TRACK_COUNT / 3);

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

    for (int32 i = (IMAGETRAIL_TRACK_COUNT / 3); i >= 0; --i) {
        int32 id = (i * 3) - (i - 1);
        if (self->stateVisible[id]) {
            if (self->stateScale[id] != 0x200) {
                self->drawFX |= FX_SCALE;
                self->scale.x = self->stateScale[id];
                self->scale.y = self->stateScale[id];
            }
            self->alpha = alpha;
            alpha += inc;
            self->rotation  = self->stateRotation[id];
            self->direction = self->stateDirection[id];
            RSDK.DrawSprite(&self->stateAnimator[id], &self->statePos[id], false);
            self->drawFX &= ~FX_SCALE;

            if (player->characterID == ID_TAILS) {
                if (self->stateTailScale[id] != 0x200) {
                    self->drawFX |= FX_SCALE;
                    self->scale.x = self->stateTailScale[id];
                    self->scale.y = self->stateTailScale[id];
                }
                self->alpha = alpha;
                alpha += inc;
                self->rotation  = self->stateTailRotation[id];
                self->direction = self->stateTailDirection[id];
                RSDK.DrawSprite(&self->stateTailAnimator[id], &self->stateTailPos[id], false);
                self->drawFX &= ~FX_SCALE;
            }
        }
    }

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

void ImageTrail_Create(void *data)
{
    RSDK_THIS(ImageTrail);

    if (!SceneInfo->inEditor) {
        EntityPlayer *player = (EntityPlayer *)data;
        self->active         = ACTIVE_ALWAYS;
        self->visible        = true;
        self->player         = player;
        self->playerClassID  = player->classID; // dunno what this is for, maybe a v4 leftover where frames were per-object?
        self->baseAlpha      = 0x100;
        self->drawFX         = FX_FLIP | FX_SCALE | FX_ROTATE;
        self->inkEffect      = INK_ALPHA;

        for (int32 i = IMAGETRAIL_TRACK_COUNT - 1; i >= 0; --i) {
            self->statePos[i].x     = player->position.x;
            self->statePos[i].y     = player->position.y;
            self->stateRotation[i]  = player->rotation;
            self->stateDirection[i] = player->direction;
            self->stateVisible[i]   = false;
        }

        for (int32 i = IMAGETRAIL_TRACK_COUNT - 1; i >= 0; --i) {
            self->stateTailPos[i].x     = player->position.x;
            self->stateTailPos[i].y     = player->position.y;
            self->stateTailRotation[i]  = player->tailRotation;
            self->stateTailDirection[i] = player->tailDirection;
            self->stateTailVisible[i]   = false;
        }
    }
}

void ImageTrail_StageLoad(void) {}

#if GAME_INCLUDE_EDITOR
void ImageTrail_EditorDraw(void) {}

void ImageTrail_EditorLoad(void) {}
#endif

void ImageTrail_Serialize(void) {}
