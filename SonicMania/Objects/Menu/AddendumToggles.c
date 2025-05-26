// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania Addendum
// Object Description: AddendumToggles Object
// Object Author: KiaraGale
// ---------------------------------------------------------------------

#include "Game.h"

ObjectAddendumToggles *AddendumToggles;

void AddendumToggles_Update(void) {}

void AddendumToggles_LateUpdate(void) {}

void AddendumToggles_StaticUpdate(void) {}

void AddendumToggles_Draw(void) {}

void AddendumToggles_Create(void *data)
{
    RSDK_THIS(AddendumToggles);

    self->active = ACTIVE_ALWAYS;
}

void AddendumToggles_StageLoad(void) {}

void AddendumToggles_Initialize(void)
{
    RSDK_THIS(UIControl);

    String tag;
    INIT_STRING(tag);

    foreach_all(UIControl, control)
    {
        RSDK.SetString(&tag, "Addendum Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->addendumControl = control;
            control->menuUpdateCB     = MainMenu_AddendumMenu_MenuUpdateCB;

            for (int32 b = 0; b < 10; ++b)
                control->buttons[b]->actionCB = AddendumToggles_MenuButton_ActionCB;
        }

        RSDK.SetString(&tag, "Gameplay Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->gameplayOptsControl = control;
            control->menuUpdateCB         = MainMenu_AddendumMenu_SubMenuUpdateCB;
        }

        RSDK.SetString(&tag, "Style Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->styleOptsControl = control;
            control->menuUpdateCB      = MainMenu_AddendumMenu_SubMenuUpdateCB;
        }

        RSDK.SetString(&tag, "Music Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->musicOptsControl = control;
            control->menuUpdateCB      = MainMenu_AddendumMenu_SubMenuUpdateCB;
        }

        RSDK.SetString(&tag, "Multiplayer Options");
        if (RSDK.CompareStrings(&tag, &control->tag, false)) {
            MainMenu->multiplayerOptsControl = control;
            control->menuUpdateCB      = MainMenu_AddendumMenu_SubMenuUpdateCB;
        }
    }
}

void AddendumToggles_MenuButton_ActionCB(void) { UITransition_StartTransition(MainMenu_HandleToAddendumSubMenuTransitionCB, 0); }

void AddendumToggles_SetToggleButtons_Gameplay(void)
{
    EntityUIControl *control         = MainMenu->gameplayOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (addendumOptions->timeLimit == TIMELIMIT_OFF)
        UIButton_SetChoiceSelection(control->buttons[0], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[0], 0);

    if (addendumOptions->debugMode == DEBUGMODE_ON)
        UIButton_SetChoiceSelection(control->buttons[1], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[1], 0);

    if (addendumOptions->sonicMoveset == SONICMOVESET_MANIA)
        UIButton_SetChoiceSelection(control->buttons[2], 1);
    else if (addendumOptions->sonicMoveset == SONICMOVESET_S3K)
        UIButton_SetChoiceSelection(control->buttons[2], 2);
    else if (addendumOptions->sonicMoveset == SONICMOVESET_CD)
        UIButton_SetChoiceSelection(control->buttons[2], 3);
    else
        UIButton_SetChoiceSelection(control->buttons[2], 0);

    if (addendumOptions->tailsMoveset == TAILSMOVESET_MANIA)
        UIButton_SetChoiceSelection(control->buttons[3], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[3], 0);

    if (addendumOptions->knuxMoveset == KNUXMOVESET_MANIA)
        UIButton_SetChoiceSelection(control->buttons[4], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[4], 0);

    if (addendumOptions->mightyMoveset == MIGHTYMOVESET_MANIA)
        UIButton_SetChoiceSelection(control->buttons[5], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[5], 0);

    if (addendumOptions->rayMoveset == RAYMOVESET_MANIA)
        UIButton_SetChoiceSelection(control->buttons[6], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[6], 0);

    if (addendumOptions->amyMoveset == AMYMOVESET_ORIGINS)
        UIButton_SetChoiceSelection(control->buttons[7], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[7], 0);

    if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALLEXCEPTAMY)
        UIButton_SetChoiceSelection(control->buttons[8], 1);
    else if (addendumOptions->peeloutAbility == PEELOUTABILITY_ALL)
        UIButton_SetChoiceSelection(control->buttons[8], 2);
    else if (addendumOptions->peeloutAbility == PEELOUTABILITY_NONE)
        UIButton_SetChoiceSelection(control->buttons[8], 3);
    else
        UIButton_SetChoiceSelection(control->buttons[8], 0);

    if (addendumOptions->spindashType == SPINDASHTYPE_CD)
        UIButton_SetChoiceSelection(control->buttons[9], 1);
    else if (addendumOptions->spindashType == SPINDASHTYPE_NONE)
        UIButton_SetChoiceSelection(control->buttons[9], 2);
    else
        UIButton_SetChoiceSelection(control->buttons[9], 0);

    if (addendumOptions->lifeSystem == LIFESYSTEM_UNCAPPED)
        UIButton_SetChoiceSelection(control->buttons[10], 1);
    else if (addendumOptions->lifeSystem == LIFESYSTEM_INFINITE)
        UIButton_SetChoiceSelection(control->buttons[10], 2);
    else
        UIButton_SetChoiceSelection(control->buttons[10], 0);

    if (addendumOptions->secondaryGems == SECONDGEMS_SUPEREMERALD)
        UIButton_SetChoiceSelection(control->buttons[11], 0);
    else if (addendumOptions->secondaryGems == SECONDGEMS_TIMESTONE)
        UIButton_SetChoiceSelection(control->buttons[11], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[11], 2);

    if (addendumOptions->shieldTransfer == SHIELDTRANSFER_OFF)
        UIButton_SetChoiceSelection(control->buttons[12], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[12], 0);

    if (addendumOptions->itemboxShields == ITEMBOXSHIELDS_ONLYBLUE)
        UIButton_SetChoiceSelection(control->buttons[13], 1);
    else if (addendumOptions->itemboxShields == ITEMBOXSHIELDS_ONLYBUBBLE)
        UIButton_SetChoiceSelection(control->buttons[13], 2);
    else if (addendumOptions->itemboxShields == ITEMBOXSHIELDS_ONLYFLAME)
        UIButton_SetChoiceSelection(control->buttons[13], 3);
    else if (addendumOptions->itemboxShields == ITEMBOXSHIELDS_ONLYLIGHTNING)
        UIButton_SetChoiceSelection(control->buttons[13], 4);
    else if (addendumOptions->itemboxShields == ITEMBOXSHIELDS_CYCLEELEMENTAL)
        UIButton_SetChoiceSelection(control->buttons[13], 5);
    else if (addendumOptions->itemboxShields == ITEMBOXSHIELDS_CYCLEALL)
        UIButton_SetChoiceSelection(control->buttons[13], 6);
    else
        UIButton_SetChoiceSelection(control->buttons[13], 0);

    Addendum_SaveOptions(AddendumToggles_SaveTogglesCB);
}

void AddendumToggles_GetTogglesFromSelection_Gameplay(void)
{
    EntityUIControl *control         = MainMenu->gameplayOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (control->buttons[0]->selection == 1)
        addendumOptions->timeLimit = TIMELIMIT_OFF;
    else
        addendumOptions->timeLimit = TIMELIMIT_ON;

    if (control->buttons[1]->selection == 1)
        addendumOptions->debugMode = DEBUGMODE_ON;
    else
        addendumOptions->debugMode = DEBUGMODE_OFF;

    if (control->buttons[2]->selection == 1)
        addendumOptions->sonicMoveset = SONICMOVESET_MANIA;
    else if (control->buttons[2]->selection == 2)
        addendumOptions->sonicMoveset = SONICMOVESET_S3K;
    else if (control->buttons[2]->selection == 3)
        addendumOptions->sonicMoveset = SONICMOVESET_CD;
    else
        addendumOptions->sonicMoveset = SONICMOVESET_ADDENDUM;

    if (control->buttons[3]->selection == 1)
        addendumOptions->tailsMoveset = TAILSMOVESET_MANIA;
    else
        addendumOptions->tailsMoveset = TAILSMOVESET_ADDENDUM;

    if (control->buttons[4]->selection == 1)
        addendumOptions->knuxMoveset = KNUXMOVESET_MANIA;
    else
        addendumOptions->knuxMoveset = KNUXMOVESET_ADDENDUM;

    if (control->buttons[5]->selection == 1)
        addendumOptions->mightyMoveset = MIGHTYMOVESET_MANIA;
    else
        addendumOptions->mightyMoveset = MIGHTYMOVESET_ADDENDUM;

    if (control->buttons[6]->selection == 1)
        addendumOptions->rayMoveset = RAYMOVESET_MANIA;
    else
        addendumOptions->rayMoveset = RAYMOVESET_ADDENDUM;

    if (control->buttons[7]->selection == 1)
        addendumOptions->amyMoveset = AMYMOVESET_ORIGINS;
    else
        addendumOptions->amyMoveset = AMYMOVESET_ADDENDUM;

    if (control->buttons[8]->selection == 1)
        addendumOptions->peeloutAbility = PEELOUTABILITY_ALLEXCEPTAMY;
    else if (control->buttons[8]->selection == 2)
        addendumOptions->peeloutAbility = PEELOUTABILITY_ALL;
    else if (control->buttons[8]->selection == 3)
        addendumOptions->peeloutAbility = PEELOUTABILITY_NONE;
    else
        addendumOptions->peeloutAbility = PEELOUTABILITY_SONICONLY;

    if (control->buttons[9]->selection == 1)
        addendumOptions->spindashType = SPINDASHTYPE_CD;
    else if (control->buttons[9]->selection == 2)
        addendumOptions->spindashType = SPINDASHTYPE_NONE;
    else
        addendumOptions->spindashType = SPINDASHTYPE_MANIA;

    if (control->buttons[10]->selection == 1)
        addendumOptions->lifeSystem = LIFESYSTEM_UNCAPPED;
    else if (control->buttons[10]->selection == 2)
        addendumOptions->lifeSystem = LIFESYSTEM_INFINITE;
    else
        addendumOptions->lifeSystem = LIFESYSTEM_MANIA;

    if (control->buttons[11]->selection == 0)
        addendumOptions->secondaryGems = SECONDGEMS_SUPEREMERALD;
    else if (control->buttons[11]->selection == 1)
        addendumOptions->secondaryGems = SECONDGEMS_TIMESTONE;
    else if (control->buttons[11]->selection == 2)
        addendumOptions->secondaryGems = SECONDGEMS_NONE;

    if (control->buttons[12]->selection == 1)
        addendumOptions->shieldTransfer = SHIELDTRANSFER_OFF;
    else
        addendumOptions->shieldTransfer = SHIELDTRANSFER_ON;

    if (control->buttons[13]->selection == 1)
        addendumOptions->itemboxShields = ITEMBOXSHIELDS_ONLYBLUE;
    else if (control->buttons[13]->selection == 2)
        addendumOptions->itemboxShields = ITEMBOXSHIELDS_ONLYBUBBLE;
    else if (control->buttons[13]->selection == 3)
        addendumOptions->itemboxShields = ITEMBOXSHIELDS_ONLYFLAME;
    else if (control->buttons[13]->selection == 4)
        addendumOptions->itemboxShields = ITEMBOXSHIELDS_ONLYLIGHTNING;
    else if (control->buttons[13]->selection == 5)
        addendumOptions->itemboxShields = ITEMBOXSHIELDS_CYCLEELEMENTAL;
    else if (control->buttons[13]->selection == 6)
        addendumOptions->itemboxShields = ITEMBOXSHIELDS_CYCLEALL;
    else
        addendumOptions->itemboxShields = ITEMBOXSHIELDS_DEFAULT;
}

void AddendumToggles_SetToggleButtons_Style(void)
{
    EntityUIControl *control         = MainMenu->styleOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS)
        UIButton_SetChoiceSelection(control->buttons[0], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[0], 0);

    if (addendumOptions->emeraldPalette == EMERALDPALETTE_S1)
        UIButton_SetChoiceSelection(control->buttons[1], 1);
    else if (addendumOptions->emeraldPalette == EMERALDPALETTE_CD)
        UIButton_SetChoiceSelection(control->buttons[1], 2);
    else if (addendumOptions->emeraldPalette == EMERALDPALETTE_S2)
        UIButton_SetChoiceSelection(control->buttons[1], 3);
    else if (addendumOptions->emeraldPalette == EMERALDPALETTE_S3)
        UIButton_SetChoiceSelection(control->buttons[1], 4);
    else
        UIButton_SetChoiceSelection(control->buttons[1], 0);

    Addendum_SaveOptions(AddendumToggles_SaveTogglesCB);
}

void AddendumToggles_GetTogglesFromSelection_Style(void)
{
    EntityUIControl *control         = MainMenu->styleOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (control->buttons[0]->selection == 1)
        addendumOptions->spriteStyle = SPRITESTYLE_CHAREDITSPLUS;
    else
        addendumOptions->spriteStyle = SPRITESTYLE_MANIA;

    if (control->buttons[1]->selection == 1)
        addendumOptions->emeraldPalette = EMERALDPALETTE_S1;
    else if (control->buttons[1]->selection == 2)
        addendumOptions->emeraldPalette = EMERALDPALETTE_CD;
    else if (control->buttons[1]->selection == 3)
        addendumOptions->emeraldPalette = EMERALDPALETTE_S2;
    else if (control->buttons[1]->selection == 4)
        addendumOptions->emeraldPalette = EMERALDPALETTE_S3;
    else
        addendumOptions->emeraldPalette = EMERALDPALETTE_MANIA;
}

void AddendumToggles_SetToggleButtons_Music(void)
{
    EntityUIControl *control         = MainMenu->musicOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (addendumOptions->superMusic == SUPERMUSIC_OFF)
        UIButton_SetChoiceSelection(control->buttons[0], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[0], 0);

    if (addendumOptions->vapeMode == VAPEMODE_ON)
        UIButton_SetChoiceSelection(control->buttons[1], 1);
    else
        UIButton_SetChoiceSelection(control->buttons[1], 0);

    Addendum_SaveOptions(AddendumToggles_SaveTogglesCB);
}

void AddendumToggles_GetTogglesFromSelection_Music(void)
{
    EntityUIControl *control         = MainMenu->musicOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (control->buttons[0]->selection == 1)
        addendumOptions->superMusic = SUPERMUSIC_OFF;
    else
        addendumOptions->superMusic = SUPERMUSIC_ON;

    if (control->buttons[1]->selection == 1)
        addendumOptions->vapeMode = VAPEMODE_ON;
    else
        addendumOptions->vapeMode = VAPEMODE_OFF;
}

void AddendumToggles_GetTogglesFromSelection_Multiplayer(void)
{
    EntityUIControl *control         = MainMenu->multiplayerOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (addendumOptions->coopStyle == COOPSTYLE_TOGETHER)
        UIButton_SetChoiceSelection(control->buttons[0], 1);
    else if (addendumOptions->coopStyle == COOPSTYLE_APART)
        UIButton_SetChoiceSelection(control->buttons[0], 2);
    else
        UIButton_SetChoiceSelection(control->buttons[0], 0);

    LogHelpers_Print("coopStyle (file) is %d", addendumOpt->coopStyle);
    LogHelpers_Print("coopStyle (RAM) is %d", addendumOptions->coopStyle);
    LogHelpers_Print("button selection is %d", control->buttons[0]->selection);

    Addendum_SaveOptions(AddendumToggles_SaveTogglesCB);
}

void AddendumToggles_SetToggleButtons_Multiplayer(void)
{
    EntityUIControl *control         = MainMenu->multiplayerOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (control->buttons[0]->selection == 1)
        addendumOptions->coopStyle = COOPSTYLE_TOGETHER;
    else if (control->buttons[0]->selection == 2)
        addendumOptions->coopStyle = COOPSTYLE_APART;
    else
        addendumOptions->coopStyle = COOPSTYLE_MANIA;

    LogHelpers_Print("button selection is %d", control->buttons[0]->selection);
    LogHelpers_Print("coopStyle (RAM) is %d", addendumOptions->coopStyle);
    LogHelpers_Print("coopStyle (file) is %d", addendumOpt->coopStyle);
}

void AddendumToggles_SaveTogglesCB(bool32 success) { UIWaitSpinner_FinishWait(); }

void AddendumToggles_ChangeMenuSpriteStyle(void)
{
    RSDK_THIS(AddendumToggles);
    EntityUIControl *control         = MainMenu->styleOptsControl;
    AddendumOptions *addendumOptions = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    if (addendumOptions->spriteStyle == SPRITESTYLE_MANIA) {
        // Diorama
        UIDiorama->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
        UIDiorama->tailsFrames   = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
        UIDiorama->knuxFrames    = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
        UIDiorama->knuxFramesAIZ = RSDK.LoadSpriteAnimation("Players/KnuxCutsceneAIZ.bin", SCOPE_STAGE);
        UIDiorama->knuxFramesHCZ = RSDK.LoadSpriteAnimation("Players/KnuxCutsceneHPZ.bin", SCOPE_STAGE);
        UIDiorama->mightyFrames  = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
        UIDiorama->rayFrames     = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
    }
    else if (addendumOptions->spriteStyle == SPRITESTYLE_CHAREDITSPLUS) {
        // Diorama
        UIDiorama->sonicFrames   = RSDK.LoadSpriteAnimation("CE+/Sonic.bin", SCOPE_STAGE);
        UIDiorama->tailsFrames   = RSDK.LoadSpriteAnimation("CE+/Tails.bin", SCOPE_STAGE);
        UIDiorama->knuxFrames    = RSDK.LoadSpriteAnimation("CE+/Knux.bin", SCOPE_STAGE);
        UIDiorama->knuxFramesAIZ = RSDK.LoadSpriteAnimation("CE+/KnuxCutsceneAIZ.bin", SCOPE_STAGE);
        UIDiorama->knuxFramesHCZ = RSDK.LoadSpriteAnimation("CE+/KnuxCutsceneHPZ.bin", SCOPE_STAGE);
        UIDiorama->mightyFrames  = RSDK.LoadSpriteAnimation("CE+/Mighty.bin", SCOPE_STAGE);
        UIDiorama->rayFrames     = RSDK.LoadSpriteAnimation("CE+/Ray.bin", SCOPE_STAGE);
    }
    else {
        // Diorama
        UIDiorama->sonicFrames   = RSDK.LoadSpriteAnimation("Players/Sonic.bin", SCOPE_STAGE);
        UIDiorama->tailsFrames   = RSDK.LoadSpriteAnimation("Players/Tails.bin", SCOPE_STAGE);
        UIDiorama->knuxFrames    = RSDK.LoadSpriteAnimation("Players/Knux.bin", SCOPE_STAGE);
        UIDiorama->knuxFramesAIZ = RSDK.LoadSpriteAnimation("Players/KnuxCutsceneAIZ.bin", SCOPE_STAGE);
        UIDiorama->knuxFramesHCZ = RSDK.LoadSpriteAnimation("Players/KnuxCutsceneHPZ.bin", SCOPE_STAGE);
        UIDiorama->mightyFrames  = RSDK.LoadSpriteAnimation("Players/Mighty.bin", SCOPE_STAGE);
        UIDiorama->rayFrames     = RSDK.LoadSpriteAnimation("Players/Ray.bin", SCOPE_STAGE);
    }
}

#if GAME_INCLUDE_EDITOR
void AddendumToggles_EditorDraw(void) {}

void AddendumToggles_EditorLoad(void) {}
#endif

void AddendumToggles_Serialize(void) {}