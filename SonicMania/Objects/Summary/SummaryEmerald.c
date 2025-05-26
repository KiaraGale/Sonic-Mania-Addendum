// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: SummaryEmerald Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

#if MANIA_USE_PLUS
ObjectSummaryEmerald *SummaryEmerald;

void SummaryEmerald_Update(void) {}

void SummaryEmerald_LateUpdate(void) {}

void SummaryEmerald_StaticUpdate(void) {}

void SummaryEmerald_Draw(void)
{
    RSDK_THIS(SummaryEmerald);

    RSDK.DrawSprite(&self->animator, NULL, false);
}

void SummaryEmerald_Create(void *data)
{
    RSDK_THIS(SummaryEmerald);
    AddendumOptions *addendumOptions = Addendum_GetOptionsRAM();
    int32 playerID = GET_CHARACTER_ID(1);

    self->active        = ACTIVE_NORMAL;
    self->drawGroup     = 3;
    self->visible       = true;
    self->updateRange.x = 0x800000;
    self->updateRange.y = 0x800000;

    for (int32 c = 0; c < 36; c++) {
        RSDK.SetPaletteEntry(0, 192 + c, SummaryEmerald->timeStoneColors[c]);
    }

    if (!SceneInfo->inEditor) {
        // what no custom entities does to a gal
        if (self->emeraldID <= 6) {
            self->type = SUMMARY_GEMTYPE_EMERALD;
        }
        if (self->emeraldID > 6) {
            self->type = SUMMARY_GEMTYPE_TIMESTONE;
            if (self->emeraldID == 8) {
                self->emeraldID   = 0;
                self->timeStoneID = 0;
            }
            else if (self->emeraldID == 9) {
                self->emeraldID   = 0;
                self->timeStoneID = 1;
            }
            else if (self->emeraldID == 10) {
                self->emeraldID   = 0;
                self->timeStoneID = 2;
            }
            else if (self->emeraldID == 11) {
                self->emeraldID   = 0;
                self->timeStoneID = 3;
            }
            else if (self->emeraldID == 12) {
                self->emeraldID   = 0;
                self->timeStoneID = 4;
            }
            else if (self->emeraldID == 13) {
                self->emeraldID   = 0;
                self->timeStoneID = 5;
            }
            else if (self->emeraldID == 14) {
                self->emeraldID   = 0;
                self->timeStoneID = 6;
            }
            else {
                self->emeraldID   = 0;
                self->timeStoneID = 7;
            }
        }

        if (self->type == SUMMARY_GEMTYPE_EMERALD) {
            if (SaveGame_GetEmerald(self->emeraldID))
                RSDK.SetSpriteAnimation(SummaryEmerald->aniFrames, 0, &self->animator, true, self->emeraldID % 7);
            else
                RSDK.SetSpriteAnimation(SummaryEmerald->aniFrames, 0, &self->animator, true, 7);
        }

        if (self->type == SUMMARY_GEMTYPE_TIMESTONE) {
            if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                if (Addendum_GetSuperEmerald(self->timeStoneID))
                    RSDK.SetSpriteAnimation(SummaryEmerald->aniFrames, 0, &self->animator, true, (self->timeStoneID % 7) + 16);
                else
                    RSDK.SetSpriteAnimation(SummaryEmerald->aniFrames, 0, &self->animator, true, 23);
            }
            else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
                if (Addendum_GetTimeStone(self->timeStoneID))
                    RSDK.SetSpriteAnimation(SummaryEmerald->aniFrames, 0, &self->animator, true, (self->timeStoneID % 7) + 8);
                else
                    RSDK.SetSpriteAnimation(SummaryEmerald->aniFrames, 0, &self->animator, true, 15);
            }
        }
    }
}

void SummaryEmerald_StageLoad(void) { SummaryEmerald->aniFrames = RSDK.LoadSpriteAnimation("Summary/SummaryEmerald.bin", SCOPE_STAGE); }

#if GAME_INCLUDE_EDITOR
void SummaryEmerald_EditorDraw(void)
{
    RSDK_THIS(SummaryEmerald);

    if (self->type == SUMMARY_GEMTYPE_EMERALD)
        RSDK.SetSpriteAnimation(SummaryEmerald->aniFrames, 0, &self->animator, true, self->emeraldID % 7);
    if (self->type == SUMMARY_GEMTYPE_TIMESTONE)
        RSDK.SetSpriteAnimation(SummaryEmerald->aniFrames, 0, &self->animator, true, (self->timeStoneID % 7) + 8);

    SummaryEmerald_Draw();
}

void SummaryEmerald_EditorLoad(void)
{
    SummaryEmerald->aniFrames = RSDK.LoadSpriteAnimation("Summary/SummaryEmerald.bin", SCOPE_STAGE);

    RSDK_ACTIVE_VAR(SummaryEmerald, type);
    RSDK_ENUM_VAR("Chaos Emerald", SUMMARY_GEMTYPE_EMERALD);
    RSDK_ENUM_VAR("Time Stone", SUMMARY_GEMTYPE_TIMESTONE);

    RSDK_ACTIVE_VAR(SummaryEmerald, emeraldID);
    RSDK_ENUM_VAR("Green", CHAOSEMERALD_GREEN);
    RSDK_ENUM_VAR("Yellow", CHAOSEMERALD_YELLOW);
    RSDK_ENUM_VAR("Blue", CHAOSEMERALD_BLUE);
    RSDK_ENUM_VAR("Purple", CHAOSEMERALD_PURPLE);
    RSDK_ENUM_VAR("Gray", CHAOSEMERALD_GRAY);
    RSDK_ENUM_VAR("Cyan", CHAOSEMERALD_CYAN);
    RSDK_ENUM_VAR("Red", CHAOSEMERALD_RED);

    RSDK_ACTIVE_VAR(SummaryEmerald, timeStoneID);
    RSDK_ENUM_VAR("Green", TIMESTONE_GREEN);
    RSDK_ENUM_VAR("Orange", TIMESTONE_ORANGE);
    RSDK_ENUM_VAR("Yellow", TIMESTONE_YELLOW);
    RSDK_ENUM_VAR("Blue", TIMESTONE_BLUE);
    RSDK_ENUM_VAR("Cyan", TIMESTONE_CYAN);
    RSDK_ENUM_VAR("Purple", TIMESTONE_PURPLE);
    RSDK_ENUM_VAR("Red", TIMESTONE_RED);
}
#endif

void SummaryEmerald_Serialize(void)
{
    RSDK_EDITABLE_VAR(SummaryEmerald, VAR_ENUM, type);
    RSDK_EDITABLE_VAR(SummaryEmerald, VAR_ENUM, emeraldID);
    RSDK_EDITABLE_VAR(SummaryEmerald, VAR_ENUM, timeStoneID);
}
#endif
