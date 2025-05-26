// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: MainMenu Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

#if MANIA_USE_PLUS
ObjectMainMenu *MainMenu;

void MainMenu_Update(void) {}

void MainMenu_LateUpdate(void) {}

void MainMenu_StaticUpdate(void)
{
    bool32 ultraWide = false;
#if RETRO_USE_MOD_LOADER
    Mod.LoadModInfo("AddendumAndroid", NULL, NULL, NULL, &ultraWide);
#endif

    if (ultraWide) {
        int32 extraWidth = (ScreenInfo->size.x - 424) / 2;
        if (MainMenu->menuControl) {
            foreach_all(UIDiorama, diorama)
            {
                int32 x = MainMenu->menuControl->startPos.x - MainMenu->menuControl->cameraOffset.x;
                int32 y = MainMenu->menuControl->startPos.y - MainMenu->menuControl->cameraOffset.y;

                Hitbox hitbox;
                hitbox.right  = (((MainMenu->menuControl->size.x) >> 17) + extraWidth);
                hitbox.left   = -(((MainMenu->menuControl->size.x) >> 17) + extraWidth);
                hitbox.bottom = (MainMenu->menuControl->size.y >> 17);
                hitbox.top    = -(MainMenu->menuControl->size.y >> 17);

                if (MathHelpers_PointInHitbox(x, y, diorama->position.x, diorama->position.y, FLIP_NONE, &hitbox)) {
                    MainMenu->diorama = diorama;
                    diorama->parent   = MainMenu->menuControl;
                }
            }
        }
    }

    EntityUIControl *control = MainMenu->menuControl;

    if (control && control->active) {
        EntityUIDiorama *diorama         = MainMenu->diorama;
        MainMenu->confirmPrompt->visible = ((int32)(control->shifter->shiftOffset.y & 0xFFFF0000)) > -0x700000;
        EntityUIButton *button           = control->buttons[control->lastButtonID];

        if (button) {
            switch (button->frameID) {
                case 0: diorama->dioramaID = UIDIORAMA_MANIAMODE; break;
                case 1: diorama->dioramaID = UIDIORAMA_TIMEATTACK; break;
                case 2: diorama->dioramaID = UIDIORAMA_COMPETITION; break;
                case 3: diorama->dioramaID = UIDIORAMA_OPTIONS; break;
                case 4: diorama->dioramaID = UIDIORAMA_EXTRAS; break;
                case 5: diorama->dioramaID = UIDIORAMA_ENCOREMODE; break;
                case 6: diorama->dioramaID = UIDIORAMA_PLUSUPSELL; break;
                case 7: diorama->dioramaID = UIDIORAMA_EXIT; break;
                case 8: diorama->dioramaID = UIDIORAMA_ACHIEVEMENTS; break;
                default: break;
            }

            if (button->disabled)
                diorama->timer = 12;
        }
    }
}

void MainMenu_Draw(void) {}

void MainMenu_Create(void *data) {}

void MainMenu_StageLoad(void) {}

void MainMenu_Initialize(void)
{
    String tag;
    INIT_STRING(tag);

    foreach_all(UIControl, control)
    {
        RSDK.SetString(&tag, "Main Menu");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->menuControl = control;
            control->backPressCB  = MainMenu_BackPressCB_ReturnToTitle;
        }

        RSDK.SetString(&tag, "Addendum Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->addendumControl = control;
            control->menuUpdateCB     = MainMenu_AddendumMenu_MenuUpdateCB;
        }
    }

    // Make sure the toggles are initialized without being forced to go into the toggles menu
    CREATE_ENTITY(AddendumToggles, NULL, MainMenu->menuControl->position.x, MainMenu->menuControl->position.y);
    AddendumToggles_Initialize();

    EntityUIControl *menuControl = MainMenu->menuControl;

    foreach_all(UIButtonPrompt, prompt)
    {
        if (UIControl_ContainsPos(menuControl, &prompt->position) && prompt->buttonID == 0)
            MainMenu->confirmPrompt = prompt;
    }

    foreach_all(UIDiorama, diorama)
    {
        if (UIControl_ContainsPos(menuControl, &diorama->position)) {
            MainMenu->diorama = diorama;
            diorama->parent   = menuControl;
        }
    }

#if MANIA_USE_PLUS
    int32 button1Frame = 5; // Encore Mode
    int32 button2Frame = 1; // Time Attack
    int32 button3Frame = 2; // Competition
    // int32 button4Frame = 8; Achievements
    int32 button4Frame = 3; // Options
    int32 button5Frame = 4; // Extras

    // bool32 button3StopMus = false; Achievements button does NOT stop music
    bool32 button3StopMus    = true; // Competition button stops music
    bool32 button4Transition = true; // Options does a transition
    bool32 button5Transition = true; // Extras does a transition

    EntityUIButton *buttonManiaMode = menuControl->buttons[0];
    buttonManiaMode->frameID        = 0;
    buttonManiaMode->transition     = true;
    buttonManiaMode->stopMusic      = true;

    EntityUIButton *buttonEncoreMode = menuControl->buttons[1];
    buttonEncoreMode->frameID        = button1Frame;
    buttonEncoreMode->transition     = true;
    buttonEncoreMode->stopMusic      = true;

    EntityUIButton *buttonTimeAttack = menuControl->buttons[2];
    buttonTimeAttack->frameID        = button2Frame;
    buttonTimeAttack->transition     = true;
    buttonTimeAttack->stopMusic      = true;

    EntityUIButton *buttonCompetition = menuControl->buttons[3];
    buttonCompetition->frameID        = button3Frame;
    buttonCompetition->transition     = true;
    buttonCompetition->stopMusic      = button3StopMus;

    /*
    EntityUIButton *buttonAchievements = menuControl->buttons[4];
    buttonAchievements->frameID        = button4Frame;
    buttonAchievements->transition     = true;
    buttonAchievements->stopMusic      = false;
    */

    EntityUIButton *buttonOptions = menuControl->buttons[4];
    buttonOptions->frameID        = button4Frame;
    buttonOptions->transition     = true;
    buttonOptions->stopMusic      = false;

    EntityUIButton *buttonExtras = menuControl->buttons[5];
    buttonExtras->frameID        = button5Frame;
    buttonExtras->transition     = button5Transition;
    buttonExtras->stopMusic      = false;

    EntityUIButton *buttonExit = menuControl->buttons[6];
    buttonExit->frameID        = 7;
    buttonExit->transition     = false;
    buttonExit->stopMusic      = false;
#endif
}

void MainMenu_YPressCB_GoToAddendumOptions(void)
{
    EntityUIControl *control = MainMenu->menuControl;

    if (control->active == ACTIVE_ALWAYS) {
        if (!MainMenu->inAddendumMenu) {
            AddendumToggles_SetToggleButtons_Gameplay();
            AddendumToggles_SetToggleButtons_Style();
            AddendumToggles_SetToggleButtons_Music();
            AddendumToggles_SetToggleButtons_Multiplayer();
            MainMenu->inAddendumMenu = true;
        }

        RSDK.PlaySfx(UIWidgets->sfxAccept, false, 255);
        UIControl->inputLocked = true;

        UITransition_StartTransition(MainMenu_HandleToAddendumTransitionCB, 0);
    }
}

void MainMenu_HandleToAddendumTransitionCB(void)
{
    EntityUIControl *control = MainMenu->menuControl;
    control->childHasFocus   = true;
    UIControl_MatchMenuTag("Addendum Options");
}

void MainMenu_HandleFromAddendumTransitionCB(void)
{
    EntityUIControl *control = MainMenu->menuControl;
    control->childHasFocus   = false;
    UIControl_MatchMenuTag("Main Menu");
}

void MainMenu_HandleToAddendumSubMenuTransitionCB(void)
{
    EntityUIControl* control = MainMenu->addendumControl;
    control->childHasFocus   = true;

    if (control->buttonID == 0)
        UIControl_MatchMenuTag("Gameplay Options");
    
    if (control->buttonID == 1)
        UIControl_MatchMenuTag("Style Options");

    if (control->buttonID == 2)
        UIControl_MatchMenuTag("Music Options");

    if (control->buttonID == 3)
        UIControl_MatchMenuTag("Multiplayer Options");
}

void MainMenu_HandleFromAddendumSubMenuTransitionCB(void)
{
    EntityUIControl *control = MainMenu->addendumControl;
    control->childHasFocus   = false;
    UIControl_MatchMenuTag("Addendum Options");
}

bool32 MainMenu_BackPressCB_ReturnToTitle(void)
{
    ManiaModeMenu_StartReturnToTitle();

    return true;
}

void MainMenu_AddendumMenu_MenuUpdateCB(void)
{
    RSDK_THIS(UIControl);
    EntityUIControl *control = MainMenu->addendumControl;

    if (control->active == ACTIVE_ALWAYS) {
        if (UIControl->anyBackPress) {
            MainMenu_StartReturnToParentScreen();
        }
    }
}

void MainMenu_StartReturnToParentScreen(void)
{
    if (MainMenu->inAddendumMenu) {
        AddendumToggles_GetTogglesFromSelection_Gameplay();
        AddendumToggles_SetToggleButtons_Gameplay();
        AddendumToggles_GetTogglesFromSelection_Style();
        AddendumToggles_SetToggleButtons_Style();
        AddendumToggles_GetTogglesFromSelection_Music();
        AddendumToggles_SetToggleButtons_Music();
        AddendumToggles_GetTogglesFromSelection_Multiplayer();
        AddendumToggles_SetToggleButtons_Multiplayer();
        AddendumToggles_ChangeMenuSpriteStyle();
        MainMenu->inAddendumMenu = false;
    }
    else
        UITransition_StartTransition(MainMenu_HandleFromAddendumTransitionCB, 0);
}

void MainMenu_AddendumMenu_SubMenuUpdateCB(void)
{
    RSDK_THIS(UIControl);
    String tag;
    INIT_STRING(tag);

    foreach_all(UIControl, control)
    {
        RSDK.SetString(&tag, "Gameplay Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->gameplayOptsControl = control;
            control->backPressCB = MainMenu_AddendumSubMenu_ReturnToAddendumMenu;
        }

        RSDK.SetString(&tag, "Style Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->styleOptsControl = control;
            control->backPressCB = MainMenu_AddendumSubMenu_ReturnToAddendumMenu;
        }

        RSDK.SetString(&tag, "Music Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->musicOptsControl = control;
            control->backPressCB = MainMenu_AddendumSubMenu_ReturnToAddendumMenu;
        }

        RSDK.SetString(&tag, "Multiplayer Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->multiplayerOptsControl = control;
            control->backPressCB = MainMenu_AddendumSubMenu_ReturnToAddendumMenu;
        }
    }
}

bool32 MainMenu_AddendumSubMenu_ReturnToAddendumMenu(void) { UITransition_StartTransition(MainMenu_HandleFromAddendumSubMenuTransitionCB, 0); return true; }

void MainMenu_SaveOptionsCB(bool32 success) { UIWaitSpinner_FinishWait(); }

void MainMenu_ExitGame(void) { API.ExitGame(); }

void MainMenu_ExitButton_ActionCB(void)
{
    String msg;
    Localization_GetString(&msg, STR_QUITWARNING);

    UIDialog_CreateDialogYesNo(&msg, MainMenu_StartExitGame, StateMachine_None, true, true);
}

void MainMenu_StartExitGame(void)
{
    if (UIControl_GetUIControl())
        UIControl_GetUIControl()->state = StateMachine_None;

    Music_FadeOut(0.02);

    MenuSetup_StartTransition(MainMenu_ExitGame, 64);
}

void MainMenu_MenuButton_ActionCB(void)
{
    RSDK_THIS(UIButton);

    switch (self->frameID) {
        case 0: // Mania Mode
            if (API_GetNoSave()) {
                UIControl_MatchMenuTag("No Save Mode");
            }
            else {
                EntityUIControl *saveSelect = ManiaModeMenu->saveSelectMenu;
                saveSelect->buttonID        = 1;
#if MANIA_USE_PLUS
                saveSelect->menuWasSetup           = false;
                ManiaModeMenu->saveSelLastButtonID = -1;

                for (int32 i = 0; i < saveSelect->buttonCount; ++i) {
                    Entity *store     = SceneInfo->entity;
                    SceneInfo->entity = (Entity *)saveSelect->buttons[i];
                    UISaveSlot_HandleSaveIconChange();
                    SceneInfo->entity = store;
                }

                UISubHeading->assignedControllers = 0;

                int32 id = API_GetFilteredInputDeviceID(true, false, 10);
                API_ResetInputSlotAssignments();
                API_AssignInputSlotToDevice(CONT_P1, id);
                UISubHeading->assignedControllers += 1;
#endif
                UIControl_MatchMenuTag("Save Select");
            }
            break;

        case 1: // Time Attack
            if (true) { // looks pointless but i swear it's here for a reason
                EntityUIControl *control = TimeAttackMenu->timeAttackControl;
                control->buttonID        = 0;
                control->menuWasSetup    = false;
                UIControl_MatchMenuTag("Time Attack");
            }
            break;

        case 2: // Competition
            UIControl_MatchMenuTag("Competition");
            break;

        case 3: // Options
            UIControl_MatchMenuTag("Options");
            break;

        case 4: // Extras
            UIControl_MatchMenuTag("Extras");
            break;

        case 5: // Encore
            if (API_GetNoSave()) {
                UIControl_MatchMenuTag("No Save Encore");
            }
            else {
                EntityUIControl *encoreSaveSel = ManiaModeMenu->encoreSaveSelect;
                encoreSaveSel->buttonID        = 1;
                encoreSaveSel->menuWasSetup    = false;
                for (int32 i = 0; i < encoreSaveSel->buttonCount; ++i) {
                    Entity *store     = SceneInfo->entity;
                    SceneInfo->entity = (Entity *)encoreSaveSel->buttons[i];
                    UISaveSlot_HandleSaveIconChange();
                    SceneInfo->entity = store;
                }
                UIControl_MatchMenuTag("Encore Mode");
            }
            break;

        case 6: // Buy Plus DLC
#if MANIA_USE_EGS
            API.SetupExtensionOverlay();

            if (!API.CheckDLC(DLC_PLUS)) {
                if (!API.CanShowExtensionOverlay(0) || !API.ShowExtensionOverlay(0)) {
                    if (API.CanShowAltExtensionOverlay(0)) {
                        int32 connectingMessage = API.GetConnectingStringID();
                        if (connectingMessage >= 0) {
                            String message;
                            INIT_STRING(message);
                            Localization_GetString(&message, connectingMessage);

                            UIDialog_CreateDialogOkCancel(&message, MainMenu_BuyPlusDialogCB, StateMachine_None, true, true);
                        }
                        else {
                            API.ShowAltExtensionOverlay(0);
                        }
                    }
                }
            }
#else
            API.ShowExtensionOverlay(0);
#endif
            break;

            /*
        case 8: // Achievements
            UIControl_MatchMenuTag("Achievements");
            break;
            */

        default: break;
    }
}

#if MANIA_USE_EGS
void MainMenu_BuyPlusDialogCB(void) { API.ShowAltExtensionOverlay(0); }
#endif

void MainMenu_HandleUnlocks(void)
{
    EntityUIControl *control = MainMenu->menuControl;

    EntityUIButton *taButton = API.CheckDLC(DLC_PLUS) ? control->buttons[2] : control->buttons[1];
    taButton->disabled       = !GameProgress_CheckUnlock(GAMEPROGRESS_UNLOCK_TIMEATTACK);

    EntityUIButton *compButton = API.CheckDLC(DLC_PLUS) ? control->buttons[3] : control->buttons[2];
    compButton->disabled       = !GameProgress_CheckUnlock(GAMEPROGRESS_UNLOCK_COMPETITION);
}

void MainMenu_SetupActions(void)
{
    foreach_all(UIButton, button)
    {
        if (button->listID == 1) {
            if (button->frameID == 7) {
                if (sku_platform != PLATFORM_PC && sku_platform != PLATFORM_DEV) {
                    EntityUIControl *control = MainMenu->menuControl;

                    // Remove "Exit" Button if not on PC or DEV platform
                    destroyEntity(button);
                    --control->buttonCount;
                    --control->rowCount;
                    control->buttons[7] = NULL;
                }
                else {
                    button->actionCB = MainMenu_ExitButton_ActionCB;
                }
            }
            else {
                button->actionCB = MainMenu_MenuButton_ActionCB;
            }
        }
    }

    MainMenu->menuControl->menuSetupCB = MainMenu_MenuSetupCB;

    MainMenu->menuControl->yPressCB = MainMenu_YPressCB_GoToAddendumOptions;
}

void MainMenu_MenuSetupCB(void) { MainMenu->diorama->lastDioramaID = -1; }

void MainMenu_AddendumOptionsCB(bool32 success) { UIWaitSpinner_FinishWait(); }

#if GAME_INCLUDE_EDITOR
void MainMenu_EditorDraw(void) {}

void MainMenu_EditorLoad(void) {}
#endif

void MainMenu_Serialize(void) {}
#endif
