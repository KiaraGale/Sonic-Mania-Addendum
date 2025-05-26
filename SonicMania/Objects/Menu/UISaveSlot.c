// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: UISaveSlot Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectUISaveSlot *UISaveSlot;

void UISaveSlot_Update(void)
{
    RSDK_THIS(UISaveSlot);
    SaveRAM *saveRAM           = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
    AddendumData *addendumData = (AddendumData *)Addendum_GetDataPtr(self->slotID, self->encoreMode);

    UISaveSlot_SetupButtonElements();

    if (self->textFrames != UIWidgets->textFrames) {
        UISaveSlot_SetupAnimators();
        UISaveSlot_HandleSaveIcons();
        self->textFrames = UIWidgets->textFrames;
    }

    StateMachine_Run(self->state);

    if (++self->zoneIconSprX >= 192)
        self->zoneIconSprX -= 192;

    EntityUIControl *control = (EntityUIControl *)self->parent;

    // ???
    for (int32 i = 0; i < control->buttonCount; ++i) {
        if (self == (EntityUISaveSlot *)control->buttons[i])
            break;
    }

    if (self->isSelected) {
        self->textBouncePos -= 0x600;
        self->textBounceOffset += self->textBouncePos;

        if (self->textBounceOffset >= 0x13600)
            self->textBounceOffset = 0x13600;

        if (self->textBounceOffset <= 0x10000 && self->textBouncePos < 0) {
            self->textBounceOffset = 0x10000;
            self->textBouncePos    = 0;
        }

        self->buttonBouncePos -= 0x1800;
        self->buttonBounceOffset += self->buttonBouncePos;

        if (self->buttonBounceOffset >= 0x11800)
            self->buttonBounceOffset = 0x11800;

        if (self->buttonBounceOffset <= 0x8000 && self->buttonBouncePos < 0) {
            self->buttonBounceOffset = 0x8000;
            self->buttonBouncePos    = 0;
        }
    }
    else if (self->state != UISaveSlot_State_Selected) {
        if (self->textBounceOffset > 0) {
            self->textBounceOffset -= 0x2000;

            if (self->textBounceOffset < 0)
                self->textBounceOffset = 0;
        }

        if (self->buttonBounceOffset > 0) {
            self->buttonBounceOffset -= 0x2000;

            if (self->buttonBounceOffset < 0)
                self->buttonBounceOffset = 0;
        }
    }

    if (self->currentlySelected && (control->buttons[control->lastButtonID] != (EntityUIButton *)self || control->buttonID == -1)) {
        self->isSelected        = false;
        self->currentlySelected = false;
        self->state             = UISaveSlot_State_NotSelected;
#if MANIA_USE_PLUS
        self->stateInput = StateMachine_None;
#endif
    }
    if (control->state != UIControl_ProcessInputs || control->active != ACTIVE_ALWAYS) {
        if (self->currentlySelected) {
            self->isSelected        = false;
            self->currentlySelected = false;
            self->state             = UISaveSlot_State_NotSelected;
#if MANIA_USE_PLUS
            self->stateInput = StateMachine_None;
#endif
        }

        self->active = ACTIVE_BOUNDS;
    }

    if (saveRAM->saveState == SAVEGAME_INPROGRESS)
        self->actNameAnimator.frameID = self->saveActID;

    if (self->actNameAnimator.animationID != 23) // failsafe in case the game does fucky shit while retrieving the act number data
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 23, &self->actNameAnimator, true, 0);
}

void UISaveSlot_LateUpdate(void) {}

void UISaveSlot_StaticUpdate(void) {}

void UISaveSlot_Draw(void)
{
    RSDK_THIS(UISaveSlot);
    AddendumData* addendumData       = (AddendumData *)Addendum_GetDataPtr(self->slotID, self->encoreMode);
    AddendumOptions* addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    Vector2 drawPos;
    if (self->type == UISAVESLOT_REGULAR) {
        drawPos.y = self->position.y + 0x30000;
        drawPos.x = self->position.x + 0x30000;
        RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y - 0x580000, 0x600000, 0xB60000, 0xFFFFFF, 127, INK_BLEND, false);

        drawPos.x = self->position.x - 0x2D0000;
        drawPos.y = self->position.y - 0x190000;
        UIWidgets_DrawRightTriangle(drawPos.x, drawPos.y, (self->textBounceOffset >> 11), 232, 40, 88);

        drawPos.x = self->position.x + 0x2D0000;
        drawPos.y = 0x580000 + self->position.y;
        UIWidgets_DrawRightTriangle(drawPos.x, drawPos.y, (-64 * self->textBounceOffset) >> 16, 0x60, 0xA0, 0xB0);
        UIWidgets_DrawRightTriangle(drawPos.x, drawPos.y, (-44 * self->textBounceOffset) >> 16, 0x58, 0x70, 0xE0);

        drawPos.x = self->position.x + 0x30000;
        drawPos.y = self->position.y + 0x30000;
        UIWidgets_DrawRectOutline_Blended(drawPos.x, drawPos.y, 96, 182);

        RSDK.DrawRect(drawPos.x - 0x2D0000, drawPos.y - 0x1C0000, 0x5A0000, 0x30000, 0x000000, 0xFF, INK_BLEND, false);

        if (self->isSelected)
            UIWidgets_DrawRectOutline_Flash(self->position.x, self->position.y, 96, 182);
        else
            UIWidgets_DrawRectOutline_Black(self->position.x, self->position.y, 96, 182);

        self->uiAnimator.frameID = 0;
        drawPos.x                = self->position.x;
        drawPos.y                = self->position.y - 0x300000;
        RSDK.DrawSprite(&self->uiAnimator, &drawPos, false);

        if (self->isNewSave || self->saveZoneID == 0xFF) {
            RSDK.DrawSprite(&self->iconBGAnimator, &drawPos, false);
            RSDK.DrawSprite(&self->saveStatusAnimator, &drawPos, false);
        }
        else if ((self->isSelected || self->state == UISaveSlot_State_Selected) && self->saveZoneID <= ZONE_COUNT_SAVEFILE) {
            SpriteFrame *frame = RSDK.GetFrame(UISaveSlot->aniFrames, 5, self->saveZoneID);
            frame->pivotX      = -43;
            frame->width       = 86;
            frame->sprX        = self->zoneIconSprX;

            if (frame->sprX > 106) {
                int32 width  = frame->sprX - 106;
                frame->width = 86 - width;
                RSDK.DrawSprite(&self->zoneIconAnimator, &drawPos, false);

                frame->pivotX += frame->width;
                frame->sprX  = 0;
                frame->width = width;
            }

            RSDK.DrawSprite(&self->zoneIconAnimator, &drawPos, false);
            RSDK.DrawSprite(&self->zoneNameAnimator, &drawPos, false);
            RSDK.DrawSprite(&self->actNameAnimator, &drawPos, false);
        }
        else {
            drawPos.y    -= 0x90000;
            self->drawFX = FX_FLIP;
            RSDK.DrawSprite(&self->fuzzAnimator, &drawPos, false);

            drawPos.y    += 0x90000;
            self->drawFX = FX_NONE;
            RSDK.DrawSprite(&self->zoneNameAnimator, &drawPos, false);

            RSDK.DrawSprite(&self->actNameAnimator, &drawPos, false);
        }

        if (self->isNewSave) {
            drawPos.x = self->position.x;
            drawPos.y = self->position.y + 0x1D0000;
            UISaveSlot_DrawPlayerIcons(drawPos.x, drawPos.y);
        }
        else { // oh boy here we go
            if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y + 0x3E0000, 0x5A0000, 0x1A0000, 0x000000, 0xFF, INK_NONE, false);

                drawPos.x = self->position.x;
                drawPos.y = self->position.y + 0x4F0000;

                for (int32 c = 0; c < 36; ++c) {
                    UISaveSlot->colorStorage[c] = RSDK.GetPaletteEntry(0, 128 + c);
                    RSDK.SetPaletteEntry(0, 128 + c, UISaveSlot->emeraldPalettes[c + (addendumOptions->emeraldPalette * 36)]);
                }

                for (int32 i = 0; i < 7; ++i) {
                    if (self->emeraldsTransferred) {
                        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 28, &self->emeraldsAnimator, true, 0);
                        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 29, &self->emeraldGlowAnimator, true, 0);

                        self->emeraldsAnimator.frameID    = (((1 << i) & self->saveSuperEmeralds) ? i : 7) + (8 * addendumOptions->spriteStyle);
                        self->emeraldGlowAnimator.frameID = (((1 << i) & self->saveSuperEmeralds) ? i : 7) + (8 * addendumOptions->spriteStyle);
                    }
                    else {
                        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 4, &self->emeraldsAnimator, true, 0);
                        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 26, &self->emeraldGlowAnimator, true, 0);

                        self->emeraldsAnimator.frameID    = (((1 << i) & self->saveEmeralds) ? i : 7) + (8 * addendumOptions->spriteStyle);
                        self->emeraldGlowAnimator.frameID = (((1 << i) & self->saveEmeralds) ? i : 7) + (8 * addendumOptions->spriteStyle);
                    }

                    switch (i) {
                        case 0: // green
                            break;

                        case 1: // yellow
                            drawPos.x -= 0xB0000;
                            drawPos.y += 0xB0000;
                            break;

                        case 2: // blue
                            drawPos.x += 0x160000;
                            break;

                        case 3: // purple
                            drawPos.x -= 0x210000;
                            drawPos.y -= 0xB0000;
                            break;

                        case 4: // silver
                            drawPos.x += 0x2C0000;
                            break;

                        case 5: // cyan
                            drawPos.x -= 0x370000;
                            drawPos.y += 0xB0000;
                            break;

                        case 6: // red
                            drawPos.x += 0x420000;
                            break;
                    }

                    if (!self->alpha) {
                        self->alpha = abs(RSDK.Sin256(self->glowTimer * 1.1) / 3);
                        self->alpha >>= 1;
                        self->inkEffect = INK_NONE;
                        RSDK.DrawSprite(&self->emeraldsAnimator, &drawPos, false);
                        self->alpha <<= 1;
                        self->inkEffect = INK_ADD;
                        RSDK.DrawSprite(&self->emeraldGlowAnimator, &drawPos, false);
                        self->alpha = 0;
                        ++self->glowTimer;
                    }
                }

                for (int32 c = 0; c < 36; ++c) {
                    RSDK.SetPaletteEntry(0, 128 + c, UISaveSlot->colorStorage[c]);
                }

                self->inkEffect = INK_NONE;
            }
            else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE) {
                RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y + 0x3C0000, 0x5A0000, 0x1C0000, 0x000000, 0xFF, INK_NONE, false);

                drawPos.x = self->position.x - 0x240000;
                drawPos.y = 0x4C0000 + self->position.y;

                for (int32 c = 0; c < 96; ++c) {
                    UISaveSlot->colorStorage[c] = RSDK.GetPaletteEntry(0, 128 + c);
                }

                for (int32 c = 0; c < 36; ++c) {
                    RSDK.SetPaletteEntry(0, 128 + c, UISaveSlot->emeraldPalettes[c + (addendumOptions->emeraldPalette * 36)]);
                    RSDK.SetPaletteEntry(0, 176 + c, UISaveSlot->emeraldPalettes[c + 72]);
                }

                for (int32 i = 0; i < 7; ++i) {
                    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 4, &self->emeraldsAnimator, true, 0);
                    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 26, &self->emeraldGlowAnimator, true, 0);

                    self->emeraldsAnimator.frameID    = (((1 << i) & self->saveEmeralds) ? i : 7) + (8 * addendumOptions->spriteStyle);
                    self->emeraldGlowAnimator.frameID = (((1 << i) & self->saveEmeralds) ? i : 7) + (8 * addendumOptions->spriteStyle);

                    if (!self->alpha) {
                        self->alpha = abs(RSDK.Sin256(self->glowTimer * 1.1) / 3);
                        self->alpha >>= 1;
                        self->inkEffect = INK_NONE;
                        RSDK.DrawSprite(&self->emeraldsAnimator, &drawPos, false);
                        self->alpha <<= 1;
                        self->inkEffect = INK_ADD;
                        RSDK.DrawSprite(&self->emeraldGlowAnimator, &drawPos, false);
                        self->alpha = 0;
                        ++self->glowTimer;
                    }

                    drawPos.x += 0xC0000;
                }
                self->inkEffect = INK_NONE;

                RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y + 0x480000, 0x5A0000, 0x100000, 0x000000, 0xFF, INK_NONE, false);

                drawPos.x = self->position.x - 0x240000;
                for (int32 i = 0; i < 7; ++i) {
                    self->stonesAnimator.frameID    = (((1 << i) & self->saveTimeStones) ? i : 7) + (8 * addendumOptions->spriteStyle);
                    self->stoneGlowAnimator.frameID = (((1 << i) & self->saveTimeStones) ? i : 7) + (8 * addendumOptions->spriteStyle);

                    if (!self->alpha) {
                        self->alpha = abs(RSDK.Sin256(self->glowTimer * 1.1) / 3);
                        self->alpha >>= 1;
                        self->inkEffect = INK_NONE;
                        RSDK.DrawSprite(&self->stonesAnimator, &drawPos, false);
                        self->alpha <<= 1;
                        self->inkEffect = INK_ADD;
                        RSDK.DrawSprite(&self->stoneGlowAnimator, &drawPos, false);
                        self->alpha = 0;
                        ++self->glowTimer;
                    }

                    drawPos.x += 0xC0000;
                }

                for (int32 c = 0; c < 96; ++c) {
                    RSDK.SetPaletteEntry(0, 128 + c, UISaveSlot->colorStorage[c]);
                }

                self->inkEffect = INK_NONE;
            }
            else {
                RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y + 0x480000, 0x5A0000, 0x100000, 0x000000, 0xFF, INK_NONE, false);

                for (int32 c = 0; c < 96; ++c) {
                    UISaveSlot->colorStorage[c] = RSDK.GetPaletteEntry(0, 128 + c);
                }

                for (int32 c = 0; c < 36; ++c) {
                    RSDK.SetPaletteEntry(0, 128 + c, UISaveSlot->emeraldPalettes[c + (addendumOptions->emeraldPalette * 36)]);
                }

                drawPos.x = self->position.x - 0x240000;
                drawPos.y = 0x590000 + self->position.y;
                for (int32 i = 0; i < 7; ++i) {
                    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 4, &self->emeraldsAnimator, true, 0);
                    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 26, &self->emeraldGlowAnimator, true, 0);

                    self->emeraldsAnimator.frameID    = (((1 << i) & self->saveEmeralds) ? i : 7) + (8 * addendumOptions->spriteStyle);
                    self->emeraldGlowAnimator.frameID = (((1 << i) & self->saveEmeralds) ? i : 7) + (8 * addendumOptions->spriteStyle);

                    if (!self->alpha) {
                        self->alpha = abs(RSDK.Sin256(self->glowTimer * 1.1) / 3);
                        self->alpha >>= 1;
                        self->inkEffect = INK_NONE;
                        RSDK.DrawSprite(&self->emeraldsAnimator, &drawPos, false);
                        self->alpha <<= 1;
                        self->inkEffect = INK_ADD;
                        RSDK.DrawSprite(&self->emeraldGlowAnimator, &drawPos, false);
                        self->alpha = 0;
                        ++self->glowTimer;
                    }

                    drawPos.x += 0xC0000;
                }

                for (int32 c = 0; c < 96; ++c) {
                    RSDK.SetPaletteEntry(0, 128 + c, UISaveSlot->colorStorage[c]);
                }

                self->inkEffect = INK_NONE;
            }

            drawPos.x = self->position.x;
            drawPos.y = self->position.y - 0x20000;
#if MANIA_USE_PLUS
            if (!self->encoreMode || self->type == UISAVESLOT_NOSAVE) {
                if (!self->saveContinues) {
                    drawPos.y += 0x20000;
                }
                drawPos.y += 0x20000;
            }
            else
                drawPos.y += 0x80000;
#else
            if (self->type == UISAVESLOT_NOSAVE)
                drawPos.y += 0x20000;
            else
                drawPos.y += 0x80000;
#endif
            drawPos.y += 0x90000;
            UISaveSlot_DrawPlayerIcons(drawPos.x, drawPos.y);

            drawPos.x = self->position.x;
            if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
                drawPos.y = self->position.y + 0x3C0000;
            else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
                drawPos.y = self->position.y + 0x3A0000;
            else
                drawPos.y = self->position.y + 0x460000;
            UISaveSlot_DrawPlayerInfo(drawPos.x, drawPos.y);
        }
    }
    else {
        drawPos.y = self->position.y + 0x30000;
        drawPos.x = self->position.x + 0x30000;
        RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y - 0x1F0000, 0x600000, 0x440000, 0xFFFFFF, 0x7F, INK_BLEND, false);

        drawPos.x = self->position.x + 0x30000;
        drawPos.y = self->position.y + 0x30000;
        UIWidgets_DrawRectOutline_Blended(drawPos.x, drawPos.y, 96, 68);

        self->uiAnimator.frameID = 1;
        RSDK.DrawSprite(&self->uiAnimator, NULL, false);

        drawPos = self->position;
        UISaveSlot_DrawPlayerIcons(self->position.x, self->position.y);
        RSDK.DrawSprite(&self->zoneNameAnimator, NULL, false);
    }

    if (self->isSelected || self->type == UISAVESLOT_REGULAR) {
        if (self->type == UISAVESLOT_NOSAVE)
            UIWidgets_DrawRectOutline_Flash(self->position.x, self->position.y, 96, 68);

        if (self->isSelected && !(self->zoneIconSprX & 8)) {
            drawPos.x = self->position.x;
            drawPos.y = self->position.y;
#if MANIA_USE_PLUS
            if (!self->encoreMode) {
#endif
                if (self->type == UISAVESLOT_NOSAVE) {
                    drawPos.y -= 0x60000;
                    UIWidgets_DrawUpDownArrows(drawPos.x, drawPos.y, 40);
                }
                else if (self->isNewSave) {
                    drawPos.y += 0x200000;
                    UIWidgets_DrawUpDownArrows(drawPos.x, drawPos.y - 0x90000, 64);
                }
                else if (self->listID == 1) {
                    drawPos.y -= 0x300000;
                    UIWidgets_DrawUpDownArrows(drawPos.x, drawPos.y - 0x90000, 40);
                }
#if MANIA_USE_PLUS
            }
            else if (self->listID == 1) {
                drawPos.y -= 0x300000;
                UIWidgets_DrawUpDownArrows(drawPos.x, drawPos.y - 0x90000, 40);
            }
#endif
        }
    }

    RSDK.DrawCircle(ScreenInfo->center.x, ScreenInfo->center.y, self->fxRadius, 0x000000, self->alpha, INK_ALPHA, true);
}

void UISaveSlot_Create(void *data)
{
    RSDK_THIS(UISaveSlot);

    if (!SceneInfo->inEditor) {
        SaveRAM* saveRAM = SaveGame_GetSaveRAM();
        self->visible         = true;
        self->drawGroup       = 2;
        self->active          = ACTIVE_BOUNDS;
        self->updateRange.x   = 0x800000;
        self->updateRange.y   = 0x300000;
        self->processButtonCB = UISaveSlot_ProcessButtonCB;
        self->state           = UISaveSlot_State_NotSelected;

        if (self->type == UISAVESLOT_REGULAR) {
            UISaveSlot_LoadSaveInfo();
        }
        else {
            self->slotID = NO_SAVE_SLOT;
            UISaveSlot_SetupAnimators();
        }

        self->textFrames = UIWidgets->textFrames;
        UISaveSlot_HandleSaveIcons();
    }
}

void UISaveSlot_StageLoad(void) { UISaveSlot->aniFrames = RSDK.LoadSpriteAnimation("UI/SaveSelect.bin", SCOPE_STAGE); }

#if MANIA_USE_PLUS
uint8 UISaveSlot_GetPlayerIDFromID(uint8 id)
{
    switch (id) {
        case 1: return ID_SONIC;
        case 2: return ID_TAILS;
        case 3: return ID_KNUCKLES;
        case 4: return ID_MIGHTY;
        case 5: return ID_RAY;
        case 6: return ID_AMY;
        default: break;
    }

    return ID_NONE;
}
uint8 UISaveSlot_GetIDFromPlayerID(uint8 playerID)
{
    switch (playerID) {
        case ID_SONIC: return 1;
        case ID_TAILS: return 2;
        case ID_KNUCKLES: return 3;
        case ID_MIGHTY: return 4;
        case ID_RAY: return 5;
        case ID_AMY: return 6;
        default: break;
    }

    return ID_NONE;
}

void UISaveSlot_DrawPlayerIcon_Encore(uint8 playerID, bool32 isSilhouette, uint8 buddyID, uint8 *friendIDs, uint8 friendCount, int32 drawX,
                                      int32 drawY)
{
    RSDK_THIS(UISaveSlot);

    Vector2 drawPos;
    Animator *animator = !isSilhouette ? &self->playersAnimator : &self->shadowsAnimator;

    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, (isSilhouette != 0) + 19, animator, true, 0);
    self->drawFX |= FX_FLIP;
    self->direction = FLIP_NONE;
    switch (buddyID) {
        default:
        case ID_SONIC: animator->frameID = 0; break;
        case ID_TAILS: animator->frameID = 1; break;
        case ID_KNUCKLES: animator->frameID = 2; break;
        case ID_MIGHTY: animator->frameID = 3; break;
        case ID_RAY: animator->frameID = 4; break;
        case ID_AMY: animator->frameID = 5; break;
    }

    int32 y = drawY;
    if (friendCount)
        y = drawY - 0x80000;
    drawPos.x = drawX + 0x100000;
    drawPos.y = y - 0x40000;

    self->direction = !animator->frameID || animator->frameID == 3;
    RSDK.DrawSprite(animator, &drawPos, false);

    switch (playerID) {
        default:
        case ID_SONIC: animator->frameID = 0; break;
        case ID_TAILS: animator->frameID = 1; break;
        case ID_KNUCKLES: animator->frameID = 2; break;
        case ID_MIGHTY: animator->frameID = 3; break;
        case ID_RAY: animator->frameID = 4; break;
        case ID_AMY: animator->frameID = 5; break;
    }

    y = drawY;
    if (friendCount)
        y = drawY - 0x80000;

    drawPos.x       = drawX - 0xF0000;
    drawPos.y       = y + 0x30000;
    self->direction = animator->frameID && animator->frameID != 3;
    RSDK.DrawSprite(animator, &drawPos, false);

    self->direction = FLIP_NONE;
    self->drawFX    = FX_NONE;
    if (friendCount && !isSilhouette) {
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 3, animator, true, 0);
        int32 x      = drawX;
        int32 offset = 0x120000;
        if (self->saveContinues > 0) {
            offset = 0xA0000;
            x      = drawX - 0x160000;
        }

        drawPos.x = x + ((offset * (friendCount - 1)) >> 1);
        drawPos.y = drawY + 0x1A0000;

        for (int32 f = friendCount - 1; f >= 0; --f) {
            switch (friendIDs[f]) {
                default:
                case ID_SONIC: animator->frameID = 0; break;
                case ID_TAILS: animator->frameID = 1; break;
                case ID_KNUCKLES: animator->frameID = 2; break;
                case ID_MIGHTY: animator->frameID = 3; break;
                case ID_RAY: animator->frameID = 4; break;
                case ID_AMY: animator->frameID = 5; break;
            }
            RSDK.DrawSprite(animator, &drawPos, false);

            drawPos.x -= offset;
        }
    }
}
#endif

void UISaveSlot_DrawPlayerIcons(int32 drawX, int32 drawY)
{
    RSDK_THIS(UISaveSlot);
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
    AddendumOptions* addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);
    Vector2 drawPos;

    if (self->p2Active) {
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 19, &self->playersAnimator, true, 0);
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 20, &self->shadowsAnimator, true, 0);
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 19, &self->sidekickAnimator, true, 0);
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 20, &self->sidekickShadowAnimator, true, 0);
    }
    else {
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 1, &self->playersAnimator, true, 0);
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 2, &self->shadowsAnimator, true, 0);
        RSDK.SetSpriteAnimation(-1, -1, &self->sidekickAnimator, true, 0);
        RSDK.SetSpriteAnimation(-1, -1, &self->sidekickShadowAnimator, true, 0);
    }

    if (self->p3Active)
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 3, &self->buddy1Animator, true, 0);
    else
        RSDK.SetSpriteAnimation(-1, -1, &self->buddy1Animator, true, 0);

    if (self->p4Active)
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 3, &self->buddy2Animator, true, 0);
    else
        RSDK.SetSpriteAnimation(-1, -1, &self->buddy2Animator, true, 0);

#if MANIA_USE_PLUS
    uint8 friendIDs[4];
    int32 playerID    = 0;
    int32 buddyID     = 0;
    int32 friendCount = 0;

    if (!self->encoreMode) {
#endif
        self->shadowsAnimator.frameID = self->frameID + (8 * addendumOptions->spriteStyle);
        self->playersAnimator.frameID = self->frameID + (8 * addendumOptions->spriteStyle);
        self->sidekickAnimator.frameID = self->altFrameID + (8 * addendumOptions->spriteStyle);
        self->sidekickShadowAnimator.frameID = self->altFrameID + (8 * addendumOptions->spriteStyle);
        self->buddy1Animator.frameID = self->buddyFrameID1 + (6 * addendumOptions->spriteStyle);
        self->buddy2Animator.frameID = self->buddyFrameID2 + (6 * addendumOptions->spriteStyle);
#if MANIA_USE_PLUS
    }
    else if (!SceneInfo->inEditor) {
        if (!self->isNewSave && self->type != UISAVESLOT_NOSAVE) {
            playerID = self->saveEncorePlayer;
            buddyID  = self->saveEncoreBuddy;

            for (int32 i = 0; i < 4; ++i) {
                friendIDs[i] = 0;
                if (!self->saveEncoreFriends[i])
                    continue;

                ++friendCount;
                friendIDs[i] = self->saveEncoreFriends[i];
            }

            if (!buddyID) {
                switch (playerID) {
                    default:
                    case ID_SONIC: playerID = 0; break;
                    case ID_TAILS: playerID = 1; break;
                    case ID_KNUCKLES: playerID = 2; break;
                    case ID_MIGHTY: playerID = 3; break;
                    case ID_RAY: playerID = 4; break;
                    case ID_AMY: playerID = 5; break;
                }

                self->shadowsAnimator.frameID = playerID;
                self->playersAnimator.frameID = playerID;
            }
            else if (playerID) {
                drawX += 4 * self->buttonBounceOffset;
                drawY += 4 * self->buttonBounceOffset;

                UISaveSlot_DrawPlayerIcon_Encore(playerID, true, buddyID, friendIDs, friendCount, drawX, drawY);
                UISaveSlot_DrawPlayerIcon_Encore(playerID, false, buddyID, friendIDs, friendCount, drawX - 8 * self->buttonBounceOffset,
                                                 drawY - 8 * self->buttonBounceOffset);
                return;
            }
        }
        else {
            self->playersAnimator.frameID = 6;
            self->shadowsAnimator.frameID = 6;
        }
    }
    else if (self->debugEncoreDraw) {
        playerID     = UISaveSlot_GetPlayerIDFromID(self->dCharPoint);
        buddyID      = UISaveSlot_GetPlayerIDFromID(self->dCharPartner);
        friendIDs[0] = UISaveSlot_GetPlayerIDFromID(self->dCharStock1);
        friendIDs[1] = UISaveSlot_GetPlayerIDFromID(self->dCharStock2);
        friendIDs[2] = UISaveSlot_GetPlayerIDFromID(self->dCharStock3);
        friendIDs[3] = UISaveSlot_GetPlayerIDFromID(self->dCharStock4);

        if (friendIDs[0])
            friendCount = 1;
        if (friendIDs[0] && friendIDs[1])
            friendCount = 2;
        if (friendIDs[0] && friendIDs[1] && friendIDs[2])
            friendCount = 3;
        if (friendIDs[0] && friendIDs[1] && friendIDs[2] && friendIDs[3])
            friendCount = 4;

        if (!buddyID) {
            switch (playerID) {
                default:
                case ID_SONIC: playerID = 0; break;
                case ID_TAILS: playerID = 1; break;
                case ID_KNUCKLES: playerID = 2; break;
                case ID_MIGHTY: playerID = 3; break;
                case ID_RAY: playerID = 4; break;
                case ID_AMY: playerID = 5; break;
            }

            self->shadowsAnimator.frameID = playerID;
            self->playersAnimator.frameID = playerID;
        }
        else if (playerID) {
            drawX += 4 * self->buttonBounceOffset;
            drawY += 4 * self->buttonBounceOffset;

            UISaveSlot_DrawPlayerIcon_Encore(playerID, true, buddyID, friendIDs, friendCount, drawX, drawY);
            UISaveSlot_DrawPlayerIcon_Encore(playerID, false, buddyID, friendIDs, friendCount, drawX - 8 * self->buttonBounceOffset,
                                             drawY - 8 * self->buttonBounceOffset);
            return;
        }
    }
    else {
        self->playersAnimator.frameID = 6;
        self->shadowsAnimator.frameID = 6;
    }
#endif

    if (self->p2Active) {
        self->drawFX = FX_FLIP;
        drawX += 4 * self->buttonBounceOffset;
        drawY += 4 * self->buttonBounceOffset;
        drawPos.x = drawX + 0x100000;
        drawPos.y = (self->p3Active || self->p4Active) ? drawY - 0x90000 : drawY + 0x30000;

        self->direction = FLIP_X;
        RSDK.DrawSprite(&self->sidekickShadowAnimator, &drawPos, false);

        self->direction = FLIP_NONE;
        drawPos.x = drawX - 0xF0000;
        RSDK.DrawSprite(&self->shadowsAnimator, &drawPos, false);

        drawX -= 8 * self->buttonBounceOffset;
        drawY -= 8 * self->buttonBounceOffset;
        drawPos.x = drawX + 0x100000;
        drawPos.y = (self->p3Active || self->p4Active) ? drawY - 0x90000 : drawY + 0x30000;
        self->direction = FLIP_X;
        RSDK.DrawSprite(&self->sidekickAnimator, &drawPos, false);

        self->direction = FLIP_NONE;
        drawPos.x = drawX - 0xF0000;
        RSDK.DrawSprite(&self->playersAnimator, &drawPos, false);

        self->drawFX = FX_NONE;
    }
    else {
        self->drawFX = FX_NONE;
        self->direction = FLIP_NONE;
        drawX += 4 * self->buttonBounceOffset;
        drawY += 4 * self->buttonBounceOffset;
        drawPos.x = drawX;
        drawPos.y = drawY;
        RSDK.DrawSprite(&self->shadowsAnimator, &drawPos, false);

        drawX -= 8 * self->buttonBounceOffset;
        drawY -= 8 * self->buttonBounceOffset;
        drawPos.x = drawX;
        drawPos.y = drawY;
        RSDK.DrawSprite(&self->playersAnimator, &drawPos, false);
    }

    if (self->p3Active) {
        self->drawFX = FX_NONE;
        self->direction = FLIP_NONE;
        drawPos.x = self->p4Active ? drawX - 0xF0000 : drawX + 0x10000;
        drawPos.y = drawY + 0x190000;
        RSDK.DrawSprite(&self->buddy1Animator, &drawPos, false);
    }

    if (self->p4Active) {
        self->drawFX = FX_NONE;
        self->direction = FLIP_NONE;
        drawPos.x = drawX + 0x100000;
        drawPos.y = drawY + 0x190000;
        RSDK.DrawSprite(&self->buddy2Animator, &drawPos, false);
    }
}

void UISaveSlot_DrawPlayerInfo(int32 drawX, int32 drawY)
{
    RSDK_THIS(UISaveSlot);
    AddendumOptions* addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 3, &self->livesAnimator, true, 0);
#if MANIA_USE_PLUS
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 21, &self->continuesAnimator, true, 0);
#endif

    int32 playerID = 0;
#if MANIA_USE_PLUS
    if (self->encoreMode) {
        if (self->isNewSave || self->type == UISAVESLOT_NOSAVE)
            return;

        if (self->debugEncoreDraw && SceneInfo->inEditor) {
            switch (UISaveSlot_GetPlayerIDFromID(self->dCharPoint)) {
                default:
                case ID_SONIC: playerID = 0; break;
                case ID_TAILS: playerID = 1; break;
                case ID_KNUCKLES: playerID = 2; break;
                case ID_MIGHTY: playerID = 3; break;
                case ID_RAY: playerID = 4; break;
                case ID_AMY: playerID = 5; break;
            }
        }
        else {
            switch (self->saveEncorePlayer) {
                default:
                case ID_SONIC: playerID = 0; break;
                case ID_TAILS: playerID = 1; break;
                case ID_KNUCKLES: playerID = 2; break;
                case ID_MIGHTY: playerID = 3; break;
                case ID_RAY: playerID = 4; break;
                case ID_AMY: playerID = 5; break;
            }
        }
    }
    else {
#endif
        playerID = self->frameID;
#if MANIA_USE_PLUS
    }
#endif

    self->livesAnimator.frameID = playerID + (6 * addendumOptions->spriteStyle);
#if MANIA_USE_PLUS
    self->continuesAnimator.frameID = playerID + (6 * addendumOptions->spriteStyle);
#endif

    Animator *animators[2];
    animators[0] = &self->livesAnimator;
#if MANIA_USE_PLUS
    animators[1] = &self->continuesAnimator;
#endif

    int32 retries[2];
    retries[0] = MIN(self->saveLives, 99);
#if MANIA_USE_PLUS
    retries[1] = MIN(self->saveContinues, 99);
#else
    retries[1] = 0;
#endif

    Vector2 positions[2];
    positions[0].x = drawX;
    positions[0].y = drawY;
    positions[1].y = drawY;
    positions[1].x = drawX;

    int32 count = 1;
    if (retries[1] <= 0) {
        positions[0].x = drawX - 0x20000;
    }
    else {
        positions[0].x = drawX - 0x170000;
        positions[1].x = drawX + 0x170000;
        count          = 2;
    }

    for (int32 i = 0; i < count; ++i) {
        Vector2 drawPos;

        drawPos.x = positions[i].x;
        drawPos.y = positions[i].y;
        if (
#if MANIA_USE_PLUS
            i || !self->encoreMode
#else
            true
#endif
        ) {
            self->uiAnimator.frameID = 3;
            RSDK.DrawSprite(&self->uiAnimator, &drawPos, false);

            drawPos.x -= 0xC0000;
            RSDK.DrawSprite(animators[i], &drawPos, false);

            drawPos.x += 0x140000;
            self->numbersAnimator.frameID = retries[i] / 10;
            RSDK.DrawSprite(&self->numbersAnimator, &drawPos, false);

            drawPos.x += 0x80000;
            self->numbersAnimator.frameID = retries[i] % 10;
            RSDK.DrawSprite(&self->numbersAnimator, &drawPos, false);
        }
    }
}

void UISaveSlot_SetupButtonElements(void)
{
    RSDK_THIS(UISaveSlot);

    self->touchCB            = UIButton_ProcessTouchCB_Multi;
    self->selectedCB         = UISaveSlot_SelectedCB;
    self->failCB             = StateMachine_None;
    self->buttonEnterCB      = UISaveSlot_ButtonEnterCB;
    self->buttonLeaveCB      = UISaveSlot_ButtonLeaveCB;
    self->checkButtonEnterCB = UISaveSlot_CheckButtonEnterCB;
    self->checkSelectedCB    = UISaveSlot_CheckSelectedCB;

#if MANIA_USE_PLUS
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
#else
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID);
#endif

    if (self->type == UISAVESLOT_NOSAVE) {
        self->touchPosSizeM[0].x   = 0x600000;
        self->touchPosSizeM[0].y   = 0x440000;
        self->touchPosOffsetM[0].x = 0;
        self->touchPosOffsetM[0].y = 0;
        self->touchPosCallbacks[0] = UISaveSlot_SelectedCB;

        self->touchPosSizeM[1].x   = 0x200000;
        self->touchPosSizeM[1].y   = 0x200000;
        self->touchPosOffsetM[1].x = 0;
        self->touchPosOffsetM[1].y = -0x1A0000;
        self->touchPosCallbacks[1] = UISaveSlot_NextCharacter;

        self->touchPosSizeM[2].x   = 0x200000;
        self->touchPosSizeM[2].y   = 0x200000;
        self->touchPosOffsetM[2].x = 0;
        self->touchPosOffsetM[2].y = 0xE0000;
        self->touchPosCallbacks[2] = UISaveSlot_PrevCharacter;

        self->touchPosCount = 3;
    }
    else {
        self->touchPosSizeM[0].x   = 0x600000;
        self->touchPosSizeM[0].y   = 0xA40000;
        self->touchPosOffsetM[0].x = 0;
        self->touchPosOffsetM[0].y = 0;
        self->touchPosCallbacks[0] = UISaveSlot_SelectedCB;

        switch (saveRAM->saveState) {
            default:
            case SAVEGAME_BLANK:
                self->touchPosSizeM[1].x   = 0x200000;
                self->touchPosSizeM[1].y   = 0x200000;
                self->touchPosOffsetM[1].x = 0;
                self->touchPosOffsetM[1].y = 0;
                self->touchPosCallbacks[1] = UISaveSlot_NextCharacter;

                self->touchPosSizeM[2].x   = 0x200000;
                self->touchPosSizeM[2].y   = 0x200000;
                self->touchPosOffsetM[2].x = 0;
                self->touchPosOffsetM[2].y = 0x400000;
                self->touchPosCallbacks[2] = UISaveSlot_PrevCharacter;

                self->touchPosCount = 3;
                break;

            case SAVEGAME_INPROGRESS: self->touchPosCount = 1; break;

            case SAVEGAME_COMPLETE:
                self->touchPosSizeM[1].x   = 0x200000;
                self->touchPosSizeM[1].y   = 0x200000;
                self->touchPosOffsetM[1].y = -0x440000;
                self->touchPosOffsetM[1].x = 0;
                self->touchPosCallbacks[1] = UISaveSlot_NextZone;

                self->touchPosSizeM[2].x   = 0x200000;
                self->touchPosSizeM[2].y   = 0x200000;
                self->touchPosOffsetM[2].x = 0;
                self->touchPosOffsetM[2].y = 0x280000 - 0x440000;
                self->touchPosCallbacks[2] = UISaveSlot_PrevZone;

                self->touchPosCount = 3;
                break;
        }
    }
}

void UISaveSlot_SetupAnimators(void)
{
    RSDK_THIS(UISaveSlot);

    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 0, &self->uiAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 1, &self->playersAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 2, &self->shadowsAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 19, &self->sidekickAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 20, &self->sidekickShadowAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 3, &self->livesAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 0, &self->iconBGAnimator, true, 2);
    RSDK.SetSpriteAnimation(UIWidgets->textFrames, 2, &self->saveStatusAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 7, &self->fuzzAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 4, &self->emeraldsAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 5, &self->zoneIconAnimator, true, 0);
#if MANIA_USE_PLUS
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 22, &self->stonesAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 23, &self->actNameAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 26, &self->emeraldGlowAnimator, true, 0);
    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 27, &self->stoneGlowAnimator, true, 0);
#endif

    if (self->type == UISAVESLOT_NOSAVE)
        RSDK.SetSpriteAnimation(UIWidgets->textFrames, 2, &self->zoneNameAnimator, true, 2);
    else
        RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 6, &self->zoneNameAnimator, true, 0);

    RSDK.SetSpriteAnimation(UISaveSlot->aniFrames, 8, &self->numbersAnimator, true, 0);
}

void UISaveSlot_LoadSaveInfo(void)
{
    RSDK_THIS(UISaveSlot);

#if MANIA_USE_PLUS
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
    AddendumData *addendumData = (AddendumData *)Addendum_GetDataPtr(self->slotID, self->encoreMode);
#else
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID);
#endif

    if (saveRAM->saveState == SAVEGAME_BLANK) {
        addendumData->player2ID = 7;
        addendumData->player3ID = 7;
        addendumData->player4ID = 7;
        self->p2Active = false;
        self->p3Active = false;
        self->p4Active = false;
    }
    else {
        if (addendumData->player2ID <= 5)
            self->p2Active = true;
        else
            self->p2Active = false;

        if (addendumData->player3ID <= 5)
            self->p3Active = true;
        else
            self->p3Active = false;

        if (addendumData->player4ID <= 5)
            self->p4Active = true;
        else
            self->p4Active = false;
    }

    int32 saveState = saveRAM->saveState;
    if (saveState == SAVEGAME_INPROGRESS || saveState == SAVEGAME_COMPLETE) {
#if MANIA_USE_PLUS
        if (self->encoreMode) {
            self->saveEncorePlayer = saveRAM->playerID & 0xFF;
            self->saveEncoreBuddy  = (saveRAM->playerID >> 8) & 0xFF;

            int32 friends = saveRAM->stock;
            for (int32 i = 0; i < 4; ++i) {
                self->saveEncoreFriends[i] = ID_NONE;
                if (!friends)
                    continue;

                self->saveEncoreFriends[i] = friends & 0xFF;
                friends >>= 8;
            }

            self->frameID = self->saveEncorePlayer;
        }
        else {
#endif
            self->frameID = saveRAM->characterID;
            self->altFrameID = addendumData->player2ID;
            self->buddyFrameID1 = addendumData->player3ID;
            self->buddyFrameID2 = addendumData->player4ID;
#if MANIA_USE_PLUS
        }
#endif
    }

    switch (saveState) {
        default: break;

        case SAVEGAME_BLANK:
            self->saveZoneID     = ZONE_GHZ;
            self->saveActID      = ACT_1;
            self->saveEmeralds   = 0;
            self->saveLives      = 3;
#if MANIA_USE_PLUS
            self->saveContinues       = 0;
            self->frameID             = self->encoreMode ? 6 : 0;
            self->altFrameID          = 7;
            self->buddyFrameID1       = 7;
            self->buddyFrameID2       = 7;
            self->saveSuperEmeralds   = 0;
            self->emeraldsTransferred = false;
            self->saveTimeStones      = 0;
#else
            self->frameID = 0;
#endif
            self->isNewSave = true;
            self->listID    = 0;
            break;

        case SAVEGAME_INPROGRESS:
            self->saveZoneID   = saveRAM->zoneID;
            self->saveActID    = addendumData->actID;
            self->saveEmeralds = saveRAM->collectedEmeralds;
            self->saveLives    = saveRAM->lives;
#if MANIA_USE_PLUS
            self->saveContinues       = saveRAM->continues;
            self->saveSuperEmeralds   = addendumData->collectedSuperEmeralds;
            self->emeraldsTransferred = addendumData->emeraldsTransferred;
            self->saveTimeStones      = addendumData->collectedTimeStones;
#endif
            self->isNewSave = false;
            self->listID    = 0;
            break;

        case SAVEGAME_COMPLETE:
            self->saveZoneID   = NO_SAVE_SLOT;
            self->saveActID    = NO_SAVE_SLOT;
            self->saveEmeralds = saveRAM->collectedEmeralds;
            self->saveLives    = saveRAM->lives;
#if MANIA_USE_PLUS
            self->saveContinues       = saveRAM->continues;
            self->saveSuperEmeralds   = addendumData->collectedSuperEmeralds;
            self->emeraldsTransferred = addendumData->emeraldsTransferred;
            self->saveTimeStones      = addendumData->collectedTimeStones;
#endif
            self->listID    = 1;
            self->isNewSave = false;
            break;
    }

    UISaveSlot_SetupAnimators();
    UISaveSlot_HandleSaveIcons();
}
void UISaveSlot_HandleSaveIcons(void)
{
    RSDK_THIS(UISaveSlot);

    self->saveStatusAnimator.frameID = self->listID;
    self->zoneIconAnimator.frameID   = self->saveZoneID;

    if (self->type == UISAVESLOT_REGULAR) {
        self->zoneNameAnimator.frameID = self->saveZoneID;

        if (self->currentlySelected) {
#if MANIA_USE_PLUS
            if (self->encoreMode)
                RSDK.CopyPalette(((self->saveZoneID >> 3) + 4), 32 * self->saveZoneID, 0, 224, 32);
            else {
#endif
                if (self->saveZoneID < ZONE_ERZ) {
                    RSDK.CopyPalette(((self->saveZoneID >> 3) + 1), 32 * self->saveZoneID, 0, 224, 32);
                }
                else {
                    for (int32 c = 0; c < 32; ++c) {
                        RSDK.SetPaletteEntry(0, 224 + c, UISaveSlot->erzColors[c]);
                    }
                }
            }
        }
    }
}

void UISaveSlot_DeleteDLG_CB(void)
{
    EntityUIDialog *dialog     = (EntityUIDialog *)UIDialog->activeDialog;
    EntityUISaveSlot *saveSlot = (EntityUISaveSlot *)dialog->entityPtr;

    dialog->parent->state = StateMachine_None;

    UIWaitSpinner_StartWait();

#if MANIA_USE_PLUS
    int32 *saveRAM = SaveGame_GetDataPtr(saveSlot->slotID % 8, saveSlot->encoreMode);
#else
    int32 *saveRAM = SaveGame_GetDataPtr(saveSlot->slotID % 8);
#endif
#if MANIA_USE_PLUS
    AddendumData *addendumData = (AddendumData *)Addendum_GetDataPtr(saveSlot->slotID, saveSlot->encoreMode);
#endif
    // Bug Details(?):
    // sizeof(globals->noSaveSlot) and sizeof(saveData) is 4096 (sizeof(int32) * 0x400)
    // but the memset size is only 1024 (sizeof(uint8) * 0x400)
    // so only about 1/4th of the save slot is cleared, though nothin uses the extra space so it's not a big deal
    memset(saveRAM, 0, 0x400);
    memset(addendumData, 0, 0x400);

    SaveGame_SaveFile(UISaveSlot_DeleteSaveCB);
#if MANIA_USE_PLUS
    Addendum_SaveFile(UISaveSlot_DeleteSaveCB);
#endif
}

#if MANIA_USE_PLUS
void UISaveSlot_DeleteSaveCB(bool32 success)
#else
void UISaveSlot_DeleteSaveCB(void)
#endif
{
    EntityUIDialog *dialog     = (EntityUIDialog *)UIDialog->activeDialog;
    EntityUISaveSlot *saveSlot = (EntityUISaveSlot *)dialog->entityPtr;
    UIWaitSpinner_FinishWait();
    UIDialog_CloseOnSel_HandleSelection(dialog, StateMachine_None);

    Entity *storeEntity = SceneInfo->entity;
    SceneInfo->entity   = (Entity *)saveSlot;
    UISaveSlot_LoadSaveInfo();
    UISaveSlot_HandleSaveIcons();
    SceneInfo->entity = storeEntity;
}

void UISaveSlot_ProcessButtonCB(void)
{
    RSDK_THIS(UISaveSlot);
    EntityUIControl *control = (EntityUIControl *)self->parent;
#if MANIA_USE_PLUS
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
#else
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID);
#endif

    self->active = ACTIVE_NORMAL;

#if MANIA_USE_PLUS
    UIControl_SetTargetPos(control, self->position.x, 0);
#else
    control->targetPos.x = self->position.x;
#endif

    if (control->position.x == control->targetPos.x) {
        if (control->columnCount > 1) {
            if (UIControl->anyLeftPress) {
                if (control->buttonID > 0) {
                    control->buttonID--;
                    RSDK.PlaySfx(UIWidgets->sfxBleep, false, 255);
                    UISaveSlot_HandleSaveIconChange();
                    return;
                }
            }
            else if (UIControl->anyRightPress) {
                if (control->buttonID < control->buttonCount - 1) {
                    control->buttonID++;
                    RSDK.PlaySfx(UIWidgets->sfxBleep, false, 255);
                    UISaveSlot_HandleSaveIconChange();
                    return;
                }
            }
        }

#if MANIA_USE_PLUS
        StateMachine_Run(self->stateInput);
#endif

        String msg;
        INIT_STRING(msg);

        if (UIControl->anyConfirmPress) {
#if MANIA_USE_PLUS
            if (API.CheckDLC(DLC_PLUS) || self->frameID < 4) {
                UISaveSlot_SelectedCB();
            }
            else {
                Localization_GetString(&msg, STR_ENCOREREQUIRED);
                UIDialog_CreateDialogOk(&msg, NULL, true);
            }
#else
            UISaveSlot_SelectedCB();
#endif
        }
        else if (UIControl->anyXPress && saveRAM->saveState != SAVEGAME_BLANK && self->type == UISAVESLOT_REGULAR) {
            Localization_GetString(&msg, STR_DELETEPOPUP);
            EntityUIDialog* dialog = UIDialog_CreateDialogYesNo(&msg, UISaveSlot_DeleteDLG_CB, NULL, false, true);
            if (dialog) {
                dialog->entityPtr = (Entity*)self;
            }
        }
        else if (!self->currentlySelected && control->buttons[control->lastButtonID] == (EntityUIButton*)self && control->state == UIControl_ProcessInputs) {
            UISaveSlot_ButtonEnterCB();
        }
        
        if (!self->encoreMode) {
            int32 id = API_GetInputDeviceID(UISubHeading->assignedControllers + 1);
            if (ControllerInfo->keyY.press && !API_IsInputDeviceAssigned(id)) {
                API_AssignInputSlotToDevice(UISubHeading->assignedControllers + 1, INPUT_AUTOASSIGN);
                UISubHeading->assignedControllers += 1;
            }

            if (ControllerInfo[CONT_P2].keyY.press)
                UISaveSlot_NextCharacter_ExtraPlayers(1);
            if (ControllerInfo[CONT_P3].keyY.press)
                UISaveSlot_NextCharacter_ExtraPlayers(2);
            if (ControllerInfo[CONT_P4].keyY.press)
                UISaveSlot_NextCharacter_ExtraPlayers(3);
        }
    }
}

void UISaveSlot_SelectedCB(void)
{
    RSDK_THIS(UISaveSlot);

    EntityUIControl *control = (EntityUIControl *)self->parent;

    if (control->position.x == control->targetPos.x) {
        control->state          = 0;
        self->state             = UISaveSlot_State_Selected;
        self->isSelected        = false;
        self->currentlySelected = false;
        self->processButtonCB   = NULL;

        foreach_all(UISaveSlot, saveSlot)
        {
            if (saveSlot != self) {
                if (saveSlot->position.x >= self->position.x) {
                    if (saveSlot->position.x > self->position.x)
                        saveSlot->velocity.x = 0x200000;
                }
                else {
                    saveSlot->velocity.x = -0x200000;
                }
                saveSlot->state = UISaveSlot_State_OtherWasSelected;
            }
        }

        foreach_all(UIButtonPrompt, prompt) { prompt->visible = false; }

#if MANIA_USE_PLUS
        int32 id = API_GetFilteredInputDeviceID(true, false, 5);
#else
        int32 id = API_GetFilteredInputDeviceID(INPUT_NONE);
#endif
        API_ResetInputSlotAssignments();
        API_AssignInputSlotToDevice(CONT_P1, id);

        RSDK.PlaySfx(UIWidgets->sfxAccept, false, 255);
        Music_Stop();
    }
}

void UISaveSlot_NextCharacter(void)
{
    RSDK_THIS(UISaveSlot);

    ++self->frameID;
    int32 player = self->frameID;

#if MANIA_USE_PLUS
    int32 max = API.CheckDLC(DLC_PLUS) ? 6 : 3;
#else
    int32 max = 3;
#endif
    while (player >= max) player -= max;

    self->frameID            = player;
    self->buttonBouncePos    = 0x8000;
    self->buttonBounceOffset = 0;

    RSDK.PlaySfx(UIWidgets->sfxBleep, false, 255);

    UISaveSlot_HandleSaveIcons();
}

void UISaveSlot_PrevCharacter(void)
{
    RSDK_THIS(UISaveSlot);

    --self->frameID;
    int32 player = self->frameID;

#if MANIA_USE_PLUS
    int32 max = API.CheckDLC(DLC_PLUS) ? 6 : 3;
#else
    int32 max = 3;
#endif
    while (player < 0) player += max;

    self->frameID            = player;
    self->buttonBouncePos    = 0x8000;
    self->buttonBounceOffset = 0;

    RSDK.PlaySfx(UIWidgets->sfxBleep, false, 255);

    UISaveSlot_HandleSaveIcons();
}

void UISaveSlot_NextCharacter_ExtraPlayers(int32 playerID)
{
    RSDK_THIS(UISaveSlot);
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
    AddendumData *addendumData = (AddendumData *)Addendum_GetDataPtr(self->slotID, self->encoreMode);

    if (playerID == 1) {
        if (self->altFrameID < 5) {
            self->p2Active = true;
            ++self->altFrameID;
        }
        else if (self->altFrameID == 5) {
            self->altFrameID = 7;
            self->p2Active   = false;
        }
        else if (self->altFrameID > 6) {
            self->altFrameID = 0;
            self->p2Active   = true;
        }
    }

    if (playerID == 2) {
        if (self->buddyFrameID1 < 5) {
            self->p3Active = true;
            ++self->buddyFrameID1;
        }
        else if (self->buddyFrameID1 == 5) {
            self->buddyFrameID1 = 7;
            self->p3Active   = false;
        }
        else if (self->buddyFrameID1 > 6) {
            self->buddyFrameID1 = 0;
            self->p3Active   = true;
        }
    }

    if (playerID == 3) {
        if (self->buddyFrameID2 < 5) {
            self->p4Active = true;
            ++self->buddyFrameID2;
        }
        else if (self->buddyFrameID2 == 5) {
            self->buddyFrameID2 = 7;
            self->p4Active   = false;
        }
        else if (self->buddyFrameID2 > 6) {
            self->buddyFrameID2 = 0;
            self->p4Active   = true;
        }
    }

    self->buttonBouncePos    = 0x8000;
    self->buttonBounceOffset = 0;

    if (saveRAM->saveState != SAVEGAME_BLANK) {
        addendumData->player2ID = self->altFrameID;
        addendumData->player3ID = self->buddyFrameID1;
        addendumData->player4ID = self->buddyFrameID2;
    }

    RSDK.PlaySfx(UIWidgets->sfxBleep, false, 255);

    UISaveSlot_HandleSaveIcons();
}

void UISaveSlot_NextZone(void)
{
    RSDK_THIS(UISaveSlot);
    SaveRAM *saveRAM            = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
    AddendumData *addendumData  = (AddendumData *)Addendum_GetDataPtr(self->slotID, self->encoreMode);
    AddendumOptVar *addendumOpt = (AddendumOptVar *)Addendum_GetOptionsPtr(self->slotID);

    if (self->saveZoneID == NO_SAVE_SLOT) {
        self->saveZoneID = ZONE_GHZ;
    }
    else {
        self->saveZoneID++;
        if (!self->encoreMode && self->playersAnimator.frameID == 0 && saveRAM->collectedEmeralds == 0b01111111) {
            if (addendumOpt->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                if (addendumData->emeraldsTransferred) {
                    if (addendumData->collectedSuperEmeralds != 0b01111111) {
                        if (self->saveZoneID > ZONE_TMZ)
                            self->saveZoneID = ZONE_GHZ;
                    }
                    else {
                        if (self->saveZoneID > ZONE_ERZ)
                            self->saveZoneID = ZONE_GHZ;
                    }
                }
                else {
                    if (self->saveZoneID > ZONE_ERZ)
                        self->saveZoneID = ZONE_GHZ;
                }
            }
            else {
                if (self->saveZoneID > ZONE_ERZ)
                    self->saveZoneID = ZONE_GHZ;
            }
        }
        else {
            if (self->saveZoneID > ZONE_TMZ)
                self->saveZoneID = ZONE_GHZ;
        }
    }

    RSDK.PlaySfx(UIWidgets->sfxBleep, false, 255);

    UISaveSlot_HandleSaveIcons();
}

void UISaveSlot_PrevZone(void)
{
    RSDK_THIS(UISaveSlot);
    SaveRAM *saveRAM            = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
    AddendumData *addendumData  = (AddendumData *)Addendum_GetDataPtr(self->slotID, self->encoreMode);
    AddendumOptVar *addendumOpt = (AddendumOptVar *)Addendum_GetOptionsPtr(self->slotID);

    if (self->saveZoneID == NO_SAVE_SLOT) {
        if (!self->encoreMode && self->playersAnimator.frameID == 0 && saveRAM->collectedEmeralds == 0b01111111) {
            if (addendumOpt->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                if (addendumData->emeraldsTransferred) {
                    if (addendumData->collectedSuperEmeralds != 0b01111111)
                        self->saveZoneID = ZONE_TMZ;
                    else
                        self->saveZoneID = ZONE_ERZ;
                }
                else
                    self->saveZoneID = ZONE_ERZ;
            }
            else
                self->saveZoneID = ZONE_ERZ;
        }
        else
            self->saveZoneID = ZONE_TMZ;
    }
    else {
        self->saveZoneID--;
        if (!self->encoreMode && self->playersAnimator.frameID == 0 && saveRAM->collectedEmeralds == 0b01111111) {
            if (addendumOpt->secondaryGems == SECONDGEMS_SUPEREMERALD) {
                if (addendumData->emeraldsTransferred) {
                    if (addendumData->collectedSuperEmeralds != 0b01111111) {
                        if (self->saveZoneID < ZONE_GHZ)
                            self->saveZoneID = ZONE_TMZ;
                    }
                    else {
                        if (self->saveZoneID < ZONE_GHZ)
                            self->saveZoneID = ZONE_ERZ;
                    }
                }
                else {
                    if (self->saveZoneID < ZONE_GHZ)
                        self->saveZoneID = ZONE_ERZ;
                }
            }
            else {
                if (self->saveZoneID < ZONE_GHZ)
                    self->saveZoneID = ZONE_ERZ;
            }
        }
        else {
            if (self->saveZoneID < ZONE_GHZ)
                self->saveZoneID = ZONE_TMZ;
        }
    }

    RSDK.PlaySfx(UIWidgets->sfxBleep, false, 255);

    UISaveSlot_HandleSaveIcons();
}

bool32 UISaveSlot_CheckButtonEnterCB(void)
{
    RSDK_THIS(UISaveSlot);

    return self->isSelected;
}
bool32 UISaveSlot_CheckSelectedCB(void)
{
    RSDK_THIS(UISaveSlot);

    return self->state == UISaveSlot_State_Selected;
}

void UISaveSlot_ButtonEnterCB(void)
{
    RSDK_THIS(UISaveSlot);

    if (!self->currentlySelected) {
        self->isSelected        = true;
        self->currentlySelected = true;

        UISaveSlot_HandleSaveIcons();

        self->textBouncePos   = 0x4000;
        self->buttonBouncePos = 0x8000;
#if MANIA_USE_PLUS
        self->stateInput = StateMachine_None;
#endif

        if (!self->isNewSave && self->type != UISAVESLOT_NOSAVE) {
            if (self->listID)
                self->state = UISaveSlot_State_CompletedSave;
            else
                self->state = UISaveSlot_State_ActiveSave;
        }
#if MANIA_USE_PLUS
        else if (self->encoreMode) {
            self->state = UISaveSlot_State_ActiveSave;
        }
#endif
        else {
            self->state = UISaveSlot_State_NewSave;
#if MANIA_USE_PLUS
            self->stateInput = UISaveSlot_StateInput_NewSave;
#endif
        }
    }
}

void UISaveSlot_ButtonLeaveCB(void)
{
    RSDK_THIS(UISaveSlot);

    self->isSelected        = false;
    self->currentlySelected = false;
    self->state             = UISaveSlot_State_NotSelected;
#if MANIA_USE_PLUS
    self->stateInput = StateMachine_None;
#endif
}

void UISaveSlot_HandleSaveIconChange(void)
{
    RSDK_THIS(UISaveSlot);

#if MANIA_USE_PLUS
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID, self->encoreMode);
#else
    SaveRAM *saveRAM = (SaveRAM *)SaveGame_GetDataPtr(self->slotID);
#endif

    if (saveRAM->saveState == SAVEGAME_BLANK) {
#if MANIA_USE_PLUS
        int32 frame = self->encoreMode ? 6 : 0;
#else
        int32 frame = 0;
#endif
        if (self->frameID != frame) {
            self->frameID = frame;
            UISaveSlot_HandleSaveIcons();
        }
    }

    if (self->type == UISAVESLOT_REGULAR && saveRAM->saveState == SAVEGAME_COMPLETE) {
        self->saveZoneID = NO_SAVE_SLOT;
        UISaveSlot_HandleSaveIcons();
    }
}

void UISaveSlot_State_NotSelected(void)
{
    RSDK_THIS(UISaveSlot);

    RSDK.ProcessAnimation(&self->fuzzAnimator);

    self->direction = self->fuzzAnimator.frameID & 3;
}

void UISaveSlot_State_OtherWasSelected(void)
{
    RSDK_THIS(UISaveSlot);

    self->position.x += self->velocity.x;
    self->position.y += self->velocity.y;
}

void UISaveSlot_State_NewSave(void)
{
#if MANIA_USE_PLUS
    // lol
#else
    RSDK_THIS(UISaveSlot);
    EntityUIControl *control = (EntityUIControl *)self->parent;

    if (control->active == ACTIVE_ALWAYS) {
        if (UIControl->anyUpPress)
            UISaveSlot_NextCharacter();
        else if (UIControl->anyDownPress)
            UISaveSlot_PrevCharacter();
    }
#endif
}

void UISaveSlot_State_ActiveSave(void)
{
    RSDK_THIS(UISaveSlot);

    if (!self->currentlySelected)
        self->state = UISaveSlot_State_NotSelected;
}

#if MANIA_USE_PLUS
void UISaveSlot_StateInput_NewSave(void)
{
    RSDK_THIS(UISaveSlot);

    EntityUIControl *control = (EntityUIControl *)self->parent;

    if (control->active == ACTIVE_ALWAYS) {
        if (UIControl->anyUpPress)
            UISaveSlot_NextCharacter();
        else if (UIControl->anyDownPress)
            UISaveSlot_PrevCharacter();
    }
}
#endif

void UISaveSlot_State_CompletedSave(void)
{
    RSDK_THIS(UISaveSlot);

    EntityUIControl *control = (EntityUIControl *)self->parent;

    if (control->active == ACTIVE_ALWAYS) {
        if (UIControl->anyUpPress)
            UISaveSlot_NextZone();
        else if (UIControl->anyDownPress)
            UISaveSlot_PrevZone();

        if (UIControl->anyZPress || UIControl->anySelectPress)
            self->actNameAnimator.frameID++;

        switch (self->saveZoneID) {
            case ZONE_GHZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_CPZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_SPZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_FBZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_PGZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_SSZ:
                if (self->actNameAnimator.frameID > 2)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 2;
                break;
            case ZONE_HCZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_MSZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_OOZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_LRZ:
                if (self->actNameAnimator.frameID > 2)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 2;
                break;
            case ZONE_MMZ:
                if (self->actNameAnimator.frameID > 1)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 1;
                break;
            case ZONE_TMZ:
                if (self->actNameAnimator.frameID > 2)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 2;
                break;
            case ZONE_ERZ:
                if (self->actNameAnimator.frameID > 0)
                    self->actNameAnimator.frameID = 0;
                self->actTotal = 0;
                break;
        }

        if (self->actNameAnimator.frameID > self->actTotal)
            self->actNameAnimator.frameID = 0;
    }
}

void UISaveSlot_State_Selected(void)
{
    RSDK_THIS(UISaveSlot);

    ++self->timer;

    // helps counteract an issue to where the player could get a carry-over shield in one file and enter another file with that shield
    for (int32 p = 0; p < 4; ++p) {
        globals->restartShield[p]    = 0;
        globals->restartHyperRing[p] = 0;
    }
    globals->startSuper = 0;

#if MANIA_USE_PLUS
    if (self->encoreMode && (self->isNewSave || self->type == UISAVESLOT_NOSAVE)) {
        EntityFXRuby *fxRuby = self->fxRuby;
        int32 rubyY          = self->position.y;

        int32 offset = (4 * self->buttonBounceOffset);
        if (self->type != UISAVESLOT_NOSAVE)
            rubyY += 0x200000;

        if (self->timer == 32) {
            PhantomRuby_PlaySfx(RUBYSFX_REDCUBE);
            fxRuby            = CREATE_ENTITY(FXRuby, NULL, self->position.x - offset, rubyY - offset);
            fxRuby->fadeWhite = 0;
            fxRuby->fadeBlack = 0;
            fxRuby->drawGroup = 15;
            self->fxRuby      = fxRuby;
        }

        if (fxRuby) {
            fxRuby->position.x = self->position.x - offset;
            fxRuby->position.y = rubyY - offset;
        }

        if (self->timer == 152)
            PhantomRuby_PlaySfx(RUBYSFX_ATTACK1);

        if (self->timer >= 92) {
            if (fxRuby->fadeWhite < 512) {
                fxRuby->fadeWhite += 8;
            }
            else if (fxRuby->fadeBlack < 512) {
                fxRuby->fadeBlack += 8;
            }
            else if (self->timer == 302) {
                StateMachine_Run(self->actionCB);
                self->state = StateMachine_None;
            }
        }
    }
    else {
#endif
        if (self->timer == 32)
            RSDK.PlaySfx(UIWidgets->sfxWarp, false, 255);

        if (self->timer > 32) {
            self->alpha += 0x20;
            self->fxRadius += 12;
        }

        if (self->fxRadius > 0x200) {
            StateMachine_Run(self->actionCB);
            self->state = StateMachine_None;
        }
#if MANIA_USE_PLUS
    }
#endif
}

#if GAME_INCLUDE_EDITOR
void UISaveSlot_EditorDraw(void)
{
    RSDK_THIS(UISaveSlot);

    self->drawGroup     = 2;
    self->updateRange.x = 0x800000;
    self->updateRange.y = 0x300000;

    if (self->type == UISAVESLOT_REGULAR) {
        UISaveSlot_LoadSaveInfo();
    }
    else {
        self->slotID = NO_SAVE_SLOT;
        UISaveSlot_SetupAnimators();
    }

    self->textFrames = UIWidgets->textFrames;
    UISaveSlot_HandleSaveIcons();

    UISaveSlot_Draw();
}

void UISaveSlot_EditorLoad(void)
{
    UISaveSlot->aniFrames = RSDK.LoadSpriteAnimation("UI/SaveSelect.bin", SCOPE_STAGE);

    RSDK_ACTIVE_VAR(UISaveSlot, type);
    RSDK_ENUM_VAR("Regular Save Slot", UISAVESLOT_REGULAR);
    RSDK_ENUM_VAR("No Save Slot", UISAVESLOT_NOSAVE);

#if MANIA_USE_PLUS
    RSDK_ACTIVE_VAR(UISaveSlot, dCharPoint);
    RSDK_ENUM_VAR("None", ID_NONE);
    RSDK_ENUM_VAR("Sonic", sonic);
    RSDK_ENUM_VAR("Tails", tails);
    RSDK_ENUM_VAR("Knuckles", knux);
    RSDK_ENUM_VAR("Mighty", mighty);
    RSDK_ENUM_VAR("Ray", ray);
    RSDK_ENUM_VAR("Amy", amy);

    RSDK_ACTIVE_VAR(UISaveSlot, dCharPartner);
    RSDK_ENUM_VAR("None", ID_NONE);
    RSDK_ENUM_VAR("Sonic", sonic);
    RSDK_ENUM_VAR("Tails", tails);
    RSDK_ENUM_VAR("Knuckles", knux);
    RSDK_ENUM_VAR("Mighty", mighty);
    RSDK_ENUM_VAR("Ray", ray);
    RSDK_ENUM_VAR("Amy", amy);

    RSDK_ACTIVE_VAR(UISaveSlot, dCharStock1);
    RSDK_ENUM_VAR("None", ID_NONE);
    RSDK_ENUM_VAR("Sonic", sonic);
    RSDK_ENUM_VAR("Tails", tails);
    RSDK_ENUM_VAR("Knuckles", knux);
    RSDK_ENUM_VAR("Mighty", mighty);
    RSDK_ENUM_VAR("Ray", ray);
    RSDK_ENUM_VAR("Amy", amy);

    RSDK_ACTIVE_VAR(UISaveSlot, dCharStock2);
    RSDK_ENUM_VAR("None", ID_NONE);
    RSDK_ENUM_VAR("Sonic", sonic);
    RSDK_ENUM_VAR("Tails", tails);
    RSDK_ENUM_VAR("Knuckles", knux);
    RSDK_ENUM_VAR("Mighty", mighty);
    RSDK_ENUM_VAR("Ray", ray);
    RSDK_ENUM_VAR("Amy", amy);

    RSDK_ACTIVE_VAR(UISaveSlot, dCharStock3);
    RSDK_ENUM_VAR("None", ID_NONE);
    RSDK_ENUM_VAR("Sonic", sonic);
    RSDK_ENUM_VAR("Tails", tails);
    RSDK_ENUM_VAR("Knuckles", knux);
    RSDK_ENUM_VAR("Mighty", mighty);
    RSDK_ENUM_VAR("Ray", ray);
    RSDK_ENUM_VAR("Amy", amy);

    RSDK_ACTIVE_VAR(UISaveSlot, dCharStock4);
    RSDK_ENUM_VAR("None", ID_NONE);
    RSDK_ENUM_VAR("Sonic", sonic);
    RSDK_ENUM_VAR("Tails", tails);
    RSDK_ENUM_VAR("Knuckles", knux);
    RSDK_ENUM_VAR("Mighty", mighty);
    RSDK_ENUM_VAR("Ray", ray);
    RSDK_ENUM_VAR("Amy", amy);
#endif
}
#endif

void UISaveSlot_Serialize(void)
{
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_BOOL, disabled);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_ENUM, type);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_ENUM, slotID);
#if MANIA_USE_PLUS
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_BOOL, encoreMode);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_BOOL, debugEncoreDraw);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_UINT8, dCharPoint);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_UINT8, dCharPartner);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_UINT8, dCharStock1);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_UINT8, dCharStock2);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_UINT8, dCharStock3);
    RSDK_EDITABLE_VAR(UISaveSlot, VAR_UINT8, dCharStock4);
#endif
}
