// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: DASetup Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectDASetup *DASetup;

void DASetup_Update(void) {}

void DASetup_LateUpdate(void) {}

void DASetup_StaticUpdate(void)
{
    if (!DASetup->initialized) {
        DASetup_SetupUI();
        DASetup->initialized = true;
    }

    EntityFXFade *fade = DASetup->fxFade;
    if (DASetup->returnToMenu && fade->timer == 512) {
        Music_FadeOut(0.02);
        RSDK.SetScene("Presentation", "Menu");
        RSDK.LoadScene();
    }

    EntityUIControl *control = DASetup->control;
    if (!control->childHasFocus)
        control->childHasFocus = true;
}

void DASetup_Draw(void)
{
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls) {
        RSDK_THIS(DASetup);

        int32 alphaStore   = self->alpha;
        int32 inkStore     = self->inkEffect;
        int32 fxStore      = self->drawFX;
        Vector2 scaleStore = self->scale;

        DASetup->dpadPos.x = TO_FIXED(56);
        DASetup->dpadPos.y = TO_FIXED(184);

        DASetup->playPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 56);
        DASetup->playPos.y = TO_FIXED(188);

        self->inkEffect = INK_ALPHA;
        self->drawFX    = FX_SCALE;

        int32 opacity = (int32)(0x100 * 0.625);
        self->scale.x = 0x200;
        self->scale.y = 0x200;

        bool32 canMove = true;
        bool32 canPlay = true;
        bool32 canBack = true;

        if (canMove) {
            if (DASetup->dpadAlpha < opacity)
                DASetup->dpadAlpha += 4;

            // Draw DPad
            self->alpha                   = DASetup->dpadAlpha;
            DASetup->dpadAnimator.frameID = 10;
            RSDK.DrawSprite(&DASetup->dpadAnimator, &DASetup->dpadPos, true);

            if (DASetup->touchDir == 2) {
                self->alpha                        = opacity;
                DASetup->dpadTouchAnimator.frameID = 6;
                RSDK.DrawSprite(&DASetup->dpadTouchAnimator, &DASetup->dpadPos, true);
            }
            else {
                self->alpha                   = DASetup->dpadAlpha;
                DASetup->dpadAnimator.frameID = 6;
                RSDK.DrawSprite(&DASetup->dpadAnimator, &DASetup->dpadPos, true);
            }

            if (DASetup->touchDir == 1) {
                self->alpha                        = opacity;
                DASetup->dpadTouchAnimator.frameID = 9;
                RSDK.DrawSprite(&DASetup->dpadTouchAnimator, &DASetup->dpadPos, true);
            }
            else {
                self->alpha                   = DASetup->dpadAlpha;
                DASetup->dpadAnimator.frameID = 9;
                RSDK.DrawSprite(&DASetup->dpadAnimator, &DASetup->dpadPos, true);
            }

            if (DASetup->touchDir == 0) {
                self->alpha                        = opacity;
                DASetup->dpadTouchAnimator.frameID = 7;
                RSDK.DrawSprite(&DASetup->dpadTouchAnimator, &DASetup->dpadPos, true);
            }
            else {
                self->alpha                   = DASetup->dpadAlpha;
                DASetup->dpadAnimator.frameID = 7;
                RSDK.DrawSprite(&DASetup->dpadAnimator, &DASetup->dpadPos, true);
            }

            if (DASetup->touchDir == 3) {
                self->alpha                        = opacity;
                DASetup->dpadTouchAnimator.frameID = 8;
                RSDK.DrawSprite(&DASetup->dpadTouchAnimator, &DASetup->dpadPos, true);
            }
            else {
                self->alpha                   = DASetup->dpadAlpha;
                DASetup->dpadAnimator.frameID = 8;
                RSDK.DrawSprite(&DASetup->dpadAnimator, &DASetup->dpadPos, true);
            }
        }
        else {
            if (DASetup->dpadAlpha > 0) {
                DASetup->dpadAlpha -= 4;
            }

            self->alpha = DASetup->dpadAlpha;
            if (self->alpha > 0) {
                DASetup->dpadAnimator.frameID = 0;
                RSDK.DrawSprite(&DASetup->dpadAnimator, &DASetup->dpadPos, true);
            }
        }

        int32 frameID = 1 + (DASetup->activeTrack == DASetup->trackID);
        if (canPlay) {
            if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
                if (DASetup->playAlpha < opacity)
                    DASetup->playAlpha += 4;

                if (ControllerInfo->keyA.down) {
                    self->alpha                        = opacity;
                    DASetup->dpadTouchAnimator.frameID = frameID;
                    RSDK.DrawSprite(&DASetup->dpadTouchAnimator, &DASetup->playPos, true);
                }
                else {
                    self->alpha                   = DASetup->playAlpha;
                    DASetup->dpadAnimator.frameID = frameID;
                    RSDK.DrawSprite(&DASetup->dpadAnimator, &DASetup->playPos, true);
                }
            }
            else {
                DASetup->playAlpha = 0;
            }
        }
        else {
            if (DASetup->playAlpha > 0)
                DASetup->playAlpha -= 4;

            self->alpha = DASetup->playAlpha;
            if (self->alpha > 0) {
                DASetup->dpadAnimator.frameID = frameID;
                RSDK.DrawSprite(&DASetup->dpadAnimator, &DASetup->playPos, true);
            }
        }

        self->alpha     = alphaStore;
        self->inkEffect = inkStore;
        self->drawFX    = fxStore;
        self->scale     = scaleStore;
    }
}

void DASetup_Create(void *data) {}

void DASetup_StageLoad(void)
{

    foreach_all(UIControl, control)
    {
        DASetup->control              = control;
        control->processButtonInputCB = DASetup_State_ManageControl;
    }

    foreach_all(FXFade, fade) { DASetup->fxFade = fade; }

    foreach_all(UIInfoLabel, label)
    {
        if (DASetup->trackTitleLabel) {
            if (!DASetup->trackSelLabel) {
                DASetup->trackSelLabel = label;
                foreach_break;
            }
        }
        else {
            DASetup->trackTitleLabel = label;
        }
    }

    int32 trackCount = 0;
    foreach_all(Music, track) { DASetup->trackList[trackCount++] = track; }

    DASetup->trackCount  = trackCount;
    DASetup->activeTrack = TRACK_NONE;

    DASetup->sfxEmerald    = RSDK.GetSfx("Special/Emerald.wav");
    DASetup->sfxMedal      = RSDK.GetSfx("Special/Medal.wav");
    DASetup->sfxSSExit     = RSDK.GetSfx("Special/SSExit.wav");
    DASetup->sfxScoreTotal = RSDK.GetSfx("Global/ScoreTotal.wav");

    DASetup->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(DASetup->dpadFrames, 0, &DASetup->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(DASetup->dpadFrames, 1, &DASetup->dpadTouchAnimator, true, 0);

    DASetup->touchDir = -1;
}

void DASetup_DisplayTrack(int32 trackID)
{
    char buffer[0x10];
    String text;
    INIT_STRING(text);

    EntityUIInfoLabel *trackTitleLabel = DASetup->trackTitleLabel;
    EntityMusic *trackCountTrack       = DASetup->trackList[trackID];

    memset(buffer, 0, 0x10 * sizeof(char));
    strcpy(&buffer[2], " - ");
    buffer[0] = (trackID / 10) + '0';
    buffer[1] = trackID - 10 * (trackID / 10) + '0';
    RSDK.SetString(&text, buffer);
    RSDK.AppendString(&text, &trackCountTrack->soundTestTitle);
    UIInfoLabel_SetString(trackTitleLabel, &text);
}

bool32 DASetup_HandleMedallionDebug(void)
{
    ProgressRAM *progress = GameProgress_GetProgressRAM();

    if (globals->medallionDebug && progress) {
        switch (DASetup->trackID) {
            case 8: // Act Clear/1UP - unlock all zones
                if (GameProgress_CheckZoneClear()) {
                    RSDK.PlaySfx(DASetup->sfxScoreTotal, false, 255);
                    return true;
                }
                break;

            case 44: // Blue Spheres/ERZ Pinch Mode - unlock all medals (silver first if not all unlocked, if all unlocked then gold)
                if (progress->silverMedalCount < 32) {
                    GameProgress_GiveMedal(globals->blueSpheresID, 1);
                    GameProgress_ShuffleBSSID();
                    RSDK.PlaySfx(DASetup->sfxMedal, false, 255);
                    return true;
                }
                else if (progress->goldMedalCount < 32) {
                    GameProgress_GiveMedal(globals->blueSpheresID, 2);
                    GameProgress_ShuffleBSSID();
                    RSDK.PlaySfx(DASetup->sfxMedal, false, 255);
                    return true;
                }
                break;

            case 46: // Super/Blue Spheres - unlock all
                if (!progress->allGoldMedals) {
                    GameProgress_UnlockAll();
                    GameProgress_LockAllSpecialClear();
                    RSDK.PlaySfx(DASetup->sfxEmerald, false, 255);
                    return true;
                }
                break;

            case 48: // Game Over/Credits - reset progress
                if (progress->silverMedalCount > 0 || progress->zoneCleared[0]) {
                    GameProgress_ClearProgress();
                    progress->allSpecialCleared = false;
                    RSDK.PlaySfx(DASetup->sfxSSExit, false, 255);
                    return true;
                }
                break;

            default: break;
        }
    }

    return false;
}

void DASetup_SetupUI(void)
{
    String buffer;
    INIT_STRING(buffer);

    TitleBG_SetupFX();
    DASetup_DisplayTrack(0);
    EntityUIInfoLabel *trackSelLabel = DASetup->trackSelLabel;
    Localization_GetString(&buffer, STR_SELECTATRACK);
#if MANIA_USE_PLUS
    LogHelpers_PrintString(&buffer);
#endif
    UIInfoLabel_SetString(trackSelLabel, &buffer);
}

void DASetup_State_ManageControl(void)
{
    bool32 touchControls = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &touchControls);
#endif

    if (touchControls)
        DASetup_HandleTouchInput();

    int32 prevTrack = DASetup->trackID;
    if (UIControl->anyRightPress)
        DASetup->trackID++;
    else if (UIControl->anyLeftPress)
        DASetup->trackID--;
    else if (UIControl->anyUpPress)
        DASetup->trackID += 10;
    else if (UIControl->anyDownPress)
        DASetup->trackID -= 10;

    if (DASetup->trackID < 0)
        DASetup->trackID += DASetup->trackCount;
    if (DASetup->trackID >= DASetup->trackCount)
        DASetup->trackID -= DASetup->trackCount;

    if (prevTrack != DASetup->trackID) {
        RSDK.PlaySfx(UIWidgets->sfxBleep, false, 255);
        DASetup_DisplayTrack(DASetup->trackID);
    }

    if (UIControl->anyConfirmPress) {
        if (DASetup->activeTrack == DASetup->trackID) {
            Music_Stop();
            DASetup->activeTrack = TRACK_NONE;
        }
        else {
            EntityMusic *track = DASetup->trackList[DASetup->trackID];
            if (!DASetup_HandleMedallionDebug()) {
                if (track->trackFile.length) {
                    DASetup->activeTrack = DASetup->trackID;
                    Music_PlayTrackPtr(track);
                }
                else {
                    DASetup->activeTrack = TRACK_NONE;
                    Music_Stop();
                }
            }
        }
    }

    if (!DASetup->returnToMenu && UIControl->anyBackPress) {
        DASetup->returnToMenu = true;

        EntityFXFade *fade = DASetup->fxFade;
        fade->state        = FXFade_State_FadeOut;
        fade->timer        = 0;
    }
}

void DASetup_HandleTouchInput(void)
{
    uint8 dir = -1;

    int32 tx = 0, ty = 0;
    if (DASetup_CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, &tx, &ty) >= 0) {
        tx -= 56;
        ty -= 184;

        switch (((RSDK.ATan2(tx, ty) + 32) & 0xFF) >> 6) {
            case 0:
                ControllerInfo->keyRight.down |= true;
                dir = 0;
                break;

            case 1:
                ControllerInfo->keyDown.down |= true;
                dir = 1;
                break;

            case 2:
                ControllerInfo->keyLeft.down |= true;
                dir = 2;
                break;

            case 3:
                ControllerInfo->keyUp.down |= true;
                dir = 3;
                break;
        }
    }

    // fixes a bug with button vs touch
    bool32 touchedConfirm = false;
    if (DASetup_CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
        ControllerInfo->keyA.down |= true;
        touchedConfirm = true;
    }

    bool32 touchedBack = false;
    if (DASetup_CheckTouchRect(ScreenInfo->size.x - 0x80, 0, ScreenInfo->size.x, 0x40, NULL, NULL) >= 0) {
        ControllerInfo->keyB.down |= true;
        touchedBack = true;
    }

    if (dir != DASetup->touchDir && ControllerInfo->keyUp.down)
        ControllerInfo->keyUp.press |= ControllerInfo->keyUp.down;

    if (dir != DASetup->touchDir && ControllerInfo->keyDown.down)
        ControllerInfo->keyDown.press |= ControllerInfo->keyDown.down;

    if (dir != DASetup->touchDir && ControllerInfo->keyLeft.down)
        ControllerInfo->keyLeft.press |= ControllerInfo->keyLeft.down;

    if (dir != DASetup->touchDir && ControllerInfo->keyRight.down)
        ControllerInfo->keyRight.press |= ControllerInfo->keyRight.down;

    if (!DASetup->touchConfirm && touchedConfirm)
        ControllerInfo->keyA.press |= ControllerInfo->keyA.down;

    if (!DASetup->touchBack && touchedBack)
        ControllerInfo->keyB.press |= ControllerInfo->keyB.down;

    DASetup->touchConfirm = ControllerInfo->keyA.down;
    DASetup->touchBack    = ControllerInfo->keyB.down;
    DASetup->touchDir     = dir;

    UIControl->anyRightPress |= ControllerInfo->keyRight.press;
    UIControl->anyLeftPress |= ControllerInfo->keyLeft.press;
    UIControl->anyUpPress |= ControllerInfo->keyUp.press;
    UIControl->anyDownPress |= ControllerInfo->keyDown.press;
    UIControl->anyConfirmPress |= ControllerInfo->keyA.press;
    UIControl->anyBackPress |= ControllerInfo->keyB.press;
}

int32 DASetup_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy)
{
    if (fx)
        *fx = 0;
    if (fy)
        *fy = 0;

    for (int32 t = 0; t < TouchInfo->count; ++t) {
        int32 tx = (int32)(TouchInfo->x[t] * ScreenInfo->size.x);
        int32 ty = (int32)(TouchInfo->y[t] * ScreenInfo->size.y);

        if (TouchInfo->down[t]) {
            if (tx >= x1 && ty >= y1 && tx <= x2 && ty <= y2) {
                if (fx)
                    *fx = tx;
                if (fy)
                    *fy = ty;

                return t;
            }
        }
    }

    return -1;
}

#if GAME_INCLUDE_EDITOR
void DASetup_EditorDraw(void) {}

void DASetup_EditorLoad(void) {}
#endif

void DASetup_Serialize(void) {}
