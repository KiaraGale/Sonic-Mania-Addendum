// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: TitleSonic Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectTitleSonic *TitleSonic;

void TitleSonic_Update(void)
{
    RSDK_THIS(TitleSonic);

    RSDK.ProcessAnimation(&self->animatorSonic);

    if (!self->transcendence) {
        if (self->animatorSonic.frameID == self->animatorSonic.frameCount - 1)
            RSDK.ProcessAnimation(&self->animatorFinger);
    }
}

void TitleSonic_LateUpdate(void) {}

void TitleSonic_StaticUpdate(void) {}

void TitleSonic_Draw(void)
{
    RSDK_THIS(TitleSonic);

    RSDK.SetClipBounds(0, 0, 0, ScreenInfo->size.x, 160);
    RSDK.DrawSprite(&self->animatorSonic, NULL, false);

    RSDK.SetClipBounds(0, 0, 0, ScreenInfo->size.x, ScreenInfo->size.y);

    if (!self->transcendence) {
        if (self->animatorSonic.frameID == self->animatorSonic.frameCount - 1)
            RSDK.DrawSprite(&self->animatorFinger, NULL, false);
    }
    else {
        if (self->animatorSonic.frameID == 21) {
            self->animatorSonic.speed = 0;
        }
    }
}

void TitleSonic_Create(void *data)
{
    RSDK_THIS(TitleSonic);
    int32 result = RSDK.Rand(0, 99);

    if (result == 69) { // nice
        RSDK.SetSpriteAnimation(TitleSonic->aniFrames, 0, &self->animatorSonic, true, 0);
        self->transcendence = true;
    }
    else {
        RSDK.SetSpriteAnimation(TitleSonic->aniFrames, 0, &self->animatorSonic, true, 0);
        RSDK.SetSpriteAnimation(TitleSonic->aniFrames, 1, &self->animatorFinger, true, 0);
        self->transcendence = false;
    }

    if (!SceneInfo->inEditor) {
        self->visible   = false;
        self->active    = ACTIVE_NEVER;
        self->drawGroup = 4;
    }
}

void TitleSonic_StageLoad(void) {
    AddendumOptions* addendumOptions = Addendum_GetOptionsRAM();

    if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS)
        TitleSonic->aniFrames = RSDK.LoadSpriteAnimation("Title/CE+Sonic.bin", SCOPE_STAGE);
    else
        TitleSonic->aniFrames = RSDK.LoadSpriteAnimation("Title/Sonic.bin", SCOPE_STAGE);
}

#if GAME_INCLUDE_EDITOR
void TitleSonic_EditorDraw(void)
{
    RSDK_THIS(TitleSonic);

    self->animatorSonic.frameID = self->animatorSonic.frameCount - 1;

    RSDK.DrawSprite(&self->animatorSonic, NULL, false);
    RSDK.DrawSprite(&self->animatorFinger, NULL, false);
}

void TitleSonic_EditorLoad(void) { TitleSonic->aniFrames = RSDK.LoadSpriteAnimation("Title/Sonic.bin", SCOPE_STAGE); }
#endif

void TitleSonic_Serialize(void) {}
