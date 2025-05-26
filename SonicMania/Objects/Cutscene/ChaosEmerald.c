// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: ChaosEmerald Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectChaosEmerald *ChaosEmerald;

void ChaosEmerald_Update(void)
{
    RSDK_THIS(ChaosEmerald);

    StateMachine_Run(self->state);
}

void ChaosEmerald_LateUpdate(void) {}

void ChaosEmerald_StaticUpdate(void) {}

void ChaosEmerald_Draw(void)
{
    RSDK_THIS(ChaosEmerald);

    for (int32 c = 0; c < 96; ++c)
        ChaosEmerald->colorStorage[c] = RSDK.GetPaletteEntry(0, 128 + c);

    for (int32 c = 0; c < 36; ++c) {
        RSDK.SetPaletteEntry(0, 128 + c, ChaosEmerald->powerColors[c + (Addendum_GetOptionsRAM()->emeraldPalette * 36)]);
        RSDK.SetPaletteEntry(0, 176 + c, ChaosEmerald->powerColors[72 + c]);
    }

    RSDK.DrawSprite(&self->animator, NULL, false);

    for (int32 c = 0; c < 96; ++c) {
        RSDK.SetPaletteEntry(0, c + 128, ChaosEmerald->colorStorage[c]);
    }
}

void ChaosEmerald_Create(void *data)
{
    RSDK_THIS(ChaosEmerald);

    self->active        = ACTIVE_BOUNDS;
    self->drawGroup     = Zone->objectDrawGroup[1];
    self->originPos     = self->position;
    self->visible       = true;
    self->drawFX        = FX_FLIP;
    self->updateRange.x = 0x800000;
    self->updateRange.y = 0x800000;
    self->state         = ChaosEmerald_State_None;
    if (Addendum_GetOptionsRAM()->secondaryGems == SECONDGEMS_SUPEREMERALD) {
        RSDK.SetSpriteAnimation(ChaosEmerald->aniFrames, 1, &self->animator, true, self->type);
    }
    else {
        RSDK.SetSpriteAnimation(ChaosEmerald->aniFrames, 0, &self->animator, true, self->type);
    }
}

void ChaosEmerald_StageLoad(void) { ChaosEmerald->aniFrames = RSDK.LoadSpriteAnimation("Cutscene/Emeralds.bin", SCOPE_STAGE); }

void ChaosEmerald_State_None(void)
{
    // hello
}
void ChaosEmerald_State_Rotate(void)
{
    RSDK_THIS(ChaosEmerald);

    self->angle += self->groundVel;
    self->position.x = self->radius * RSDK.Cos256(self->angle >> 8) + self->originPos.x;
    self->position.y = self->radius * RSDK.Sin256(self->angle >> 8) + self->originPos.y;
}

#if GAME_INCLUDE_EDITOR
void ChaosEmerald_EditorDraw(void)
{
    RSDK_THIS(ChaosEmerald);

    RSDK.SetSpriteAnimation(ChaosEmerald->aniFrames, 0, &self->animator, true, self->type);
    RSDK.DrawSprite(&self->animator, NULL, false);
}

void ChaosEmerald_EditorLoad(void)
{
    ChaosEmerald->aniFrames = RSDK.LoadSpriteAnimation("Cutscene/Emeralds.bin", SCOPE_STAGE);

    RSDK_ACTIVE_VAR(ChaosEmerald, type);
    RSDK_ENUM_VAR("Green CE", CHAOSEMERALD_GREEN);
    RSDK_ENUM_VAR("Yellow CE", CHAOSEMERALD_YELLOW);
    RSDK_ENUM_VAR("Blue CE", CHAOSEMERALD_BLUE);
    RSDK_ENUM_VAR("Purple CE", CHAOSEMERALD_PURPLE);
    RSDK_ENUM_VAR("Gray CE", CHAOSEMERALD_GRAY);
    RSDK_ENUM_VAR("Cyan CE", CHAOSEMERALD_CYAN);
    RSDK_ENUM_VAR("Red CE", CHAOSEMERALD_RED);
    RSDK_ENUM_VAR("Green TS", TIMESTONE_GREEN);
    RSDK_ENUM_VAR("Orange TS", TIMESTONE_ORANGE);
    RSDK_ENUM_VAR("Yellow TS", TIMESTONE_YELLOW);
    RSDK_ENUM_VAR("Blue TS", TIMESTONE_BLUE);
    RSDK_ENUM_VAR("Cyan TS", TIMESTONE_CYAN);
    RSDK_ENUM_VAR("Purple TS", TIMESTONE_PURPLE);
    RSDK_ENUM_VAR("Red TS", TIMESTONE_RED);
}
#endif

void ChaosEmerald_Serialize(void) { RSDK_EDITABLE_VAR(ChaosEmerald, VAR_UINT8, type); }
