// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: SaveGame Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectSaveGame *SaveGame;

void SaveGame_Update(void) {}

void SaveGame_LateUpdate(void) {}

void SaveGame_StaticUpdate(void) {}

void SaveGame_Draw(void) {}

void SaveGame_Create(void *data) {}

void SaveGame_StageLoad(void)
{
#if !MANIA_USE_PLUS
    SaveGame_LoadSaveData();
#endif
}

SaveRAM *SaveGame_GetSaveRAM(void) { return SaveGame->saveRAM; }
AddendumData *Addendum_GetSaveRAM(void) { return SaveGame->addendumData; }
AddendumOptions *Addendum_GetOptionsRAM(void) { return SaveGame->addendumMods; }

#if MANIA_USE_PLUS
int32 *SaveGame_GetDataPtr(int32 slot, bool32 encore)
{
    if (slot == NO_SAVE_SLOT)
        return globals->noSaveSlot;

    if (encore)
        return &globals->saveRAM[0x100 * (slot % 3 + 10)];
    else
        return &globals->saveRAM[0x100 * (slot % 8)];
}
#else
int32 *SaveGame_GetDataPtr(int32 slot)
{
    if (slot == NO_SAVE_SLOT)
        return globals->noSaveSlot;
    else
        return &globals->saveRAM[0x100 * (slot % 8)];
}
#endif

#if MANIA_USE_PLUS
int32 *Addendum_GetDataPtr(int32 slot, bool32 encore)
{
    if (slot == NO_SAVE_SLOT)
        return addendumVar->noSaveSlot;

    if (encore)
        return &addendumVar->saveRAM[0x100 * (slot % 3 + 10)];
    else
        return &addendumVar->saveRAM[0x100 * (slot % 8)];
}

int32 *Addendum_GetOptionsPtr(int32 slot) { return &addendumOpt->optionsRAM[0]; } // always set slot to 0
#endif

void SaveGame_LoadSaveData(void)
{
    EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *player2 = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

    int32 slot = globals->saveSlotID;

    if (slot == NO_SAVE_SLOT)
        SaveGame->saveRAM = (SaveRAM *)globals->noSaveSlot;
    else
#if MANIA_USE_PLUS
        SaveGame->saveRAM = (SaveRAM *)SaveGame_GetDataPtr(slot, globals->gameMode == MODE_ENCORE);
#else
        SaveGame->saveRAM = (SaveRAM *)SaveGame_GetDataPtr(slot);
#endif

    LogHelpers_Print("dataPtr: %X", SaveGame->saveRAM);

    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    if (!saveRAM->lives)
        saveRAM->lives = 3;

    while (saveRAM->score1UP <= saveRAM->score) saveRAM->score1UP += 50000;

    if (Player) {
#if MANIA_USE_PLUS
        if (!TitleCard || TitleCard->suppressCB != Zone_TitleCard_SupressCB) {
#endif
            Player->savedLives    = saveRAM->lives;
            Player->savedScore    = saveRAM->score;
            Player->savedScore1UP = saveRAM->score1UP;
#if MANIA_USE_PLUS
            globals->continues      = saveRAM->continues;
            globals->stock          = saveRAM->stock;
            globals->characterFlags = saveRAM->characterFlags;
        }
#endif
    }

    if (Zone && SceneInfo->activeCategory < 3) {
        Zone->prevListPos = Zone->listPos;
        Zone->listPos     = SceneInfo->listPos;
    }

    if (globals->recallEntities) {
        if (SceneInfo->activeCategory < 3 && SceneInfo->activeCategory > 0) {
            for (int32 p = 0; p < 4; ++p) {
                StarPost->playerPositions[p].x = globals->restartPos[(p * 2) + 0];
                StarPost->playerPositions[p].y = globals->restartPos[(p * 2) + 1];
                StarPost->playerDirections[p]  = globals->restartDir[p];
                StarPost->postIDs[p]           = globals->restartSlot[p];
            }

            StarPost->storedMS      = globals->restartMilliseconds;
            StarPost->storedSeconds = globals->restartSeconds;
            StarPost->storedMinutes = globals->restartMinutes;

            SceneInfo->milliseconds = globals->tempMilliseconds;
            SceneInfo->seconds      = globals->tempSeconds;
            SceneInfo->minutes      = globals->tempMinutes;

            Player->savedScore      = globals->restartScore;
            Player->ringExtraLife   = globals->restart1UP;
            for (int32 p = 0; p < addendumVar->playerCount; ++p) {
                EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
                player->rings     = globals->restartRings[p];
                globals->restartRings[p] = 0;
                player->hyperRing = globals->restartHyperRing[p];
                globals->restartHyperRing[p] = 0;
                player->shield    = globals->restartShield[p];
                globals->restartShield[p] = 0;
            }

            globals->restart1UP = 100;

            LogHelpers_Print("RecallCollectedEntities");

            for (int32 e = RESERVE_ENTITY_COUNT; e < RESERVE_ENTITY_COUNT + SCENEENTITY_COUNT; ++e) {
                switch (globals->atlEntityData[(0x200 * 1) + e]) {
                    default:
                    case SAVERECALL_NORMAL: break;

                    case SAVERECALL_DISABLED: {
                        Entity *entity  = RSDK_GET_ENTITY_GEN(e);
                        entity->classID = TYPE_BLANK;
                        entity->active  = ACTIVE_DISABLED;
                        break;
                    }

                    case SAVERECALL_BROKENITEMBOX: {
                        EntityItemBox *itemBox = RSDK_GET_ENTITY(e, ItemBox);
                        RSDK.SetSpriteAnimation(ItemBox->aniFrames, 1, &itemBox->boxAnimator, true, 0);
                        RSDK.SetSpriteAnimation(-1, 0, &itemBox->overlayAnimator, true, 0);
                        RSDK.SetSpriteAnimation(-1, 0, &itemBox->debrisAnimator, true, 0);
                        RSDK.SetSpriteAnimation(-1, 0, &itemBox->contentsAnimator, true, 0);
                        itemBox->state = ItemBox_State_Broken;
                        break;
                    }
                }
            }

            globals->recallEntities      = false;
            globals->restartMilliseconds = 0;
            globals->restartSeconds      = 0;
            globals->restartMinutes      = 0;
            memset(globals->atlEntityData, 0, SCENEENTITY_COUNT * sizeof(int32));
        }
    }
    else if (!Zone || Zone->listPos != Zone->prevListPos) {
        if (StarPost) {
            for (int32 p = 0; p < PLAYER_COUNT; ++p) {
                StarPost->playerPositions[p].x = 0;
                StarPost->playerPositions[p].y = 0;
                StarPost->playerDirections[p]  = FLIP_NONE;
                StarPost->postIDs[p]           = 0;
            }

            StarPost->storedMS      = 0;
            StarPost->storedSeconds = 0;
            StarPost->storedMinutes = 0;
        }

        globals->tempMilliseconds = 0;
        globals->tempSeconds      = 0;
        globals->tempMinutes      = 0;
    }
}

#if MANIA_USE_PLUS
void Addendum_LoadSaveData(void)
{
    int32 slot = addendumVar->saveSlotID;

    if (slot == NO_SAVE_SLOT)
        SaveGame->addendumData = (AddendumData *)addendumVar->noSaveSlot;
    else
        SaveGame->addendumData = (AddendumData *)Addendum_GetDataPtr(slot, globals->gameMode == MODE_ENCORE);

    LogHelpers_Print("dataPtr: %X", SaveGame->addendumData);
}

void Addendum_LoadOptionsData(void)
{
    SaveGame->addendumMods = (AddendumOptions *)Addendum_GetOptionsPtr(0);

    LogHelpers_Print("dataPtr: %X", SaveGame->addendumMods);
}
#endif

void SaveGame_LoadFile(void (*callback)(bool32 success))
{
    LogHelpers_Print("Got to SaveGame_LoadFile");
#if MANIA_USE_PLUS
    if (!SaveGame->saveRAM || globals->saveLoaded == STATUS_CONTINUE) {
        if (callback)
            callback(false);
        return;
    }

    if (globals->saveLoaded == STATUS_OK) {
        if (callback)
            callback(true);
        return;
    }
#else
    if (!SaveGame->saveRAM || globals->saveLoaded == STATUS_CONTINUE)
        return;

    if (globals->saveLoaded == STATUS_OK) {
        if (callback)
            callback(true);
        return;
    }
#endif

    globals->saveLoaded     = STATUS_CONTINUE;
    SaveGame->loadEntityPtr = SceneInfo->entity;
    SaveGame->loadCallback  = callback;
    API_LoadUserFile("SaveDataAddendum.bin", globals->saveRAM, sizeof(globals->saveRAM), SaveGame_LoadFile_CB);
}

#if MANIA_USE_PLUS
void Addendum_LoadFile(void (*callback)(bool32 success))
{
    LogHelpers_Print("Got to Addendum_LoadFile");
    if (!SaveGame->addendumData || addendumVar->saveLoaded == STATUS_CONTINUE) {
        LogHelpers_Print("AData not Loaded...");
        if (callback)
            callback(false);
        return;
    }

    if (addendumVar->saveLoaded == STATUS_OK) {
        LogHelpers_Print("AData Loaded!");
        if (callback)
            callback(true);
        return;
    }

    addendumVar->saveLoaded  = STATUS_CONTINUE;
    SaveGame->loadEntityPtr2 = SceneInfo->entity;
    SaveGame->loadCallback2  = callback;
    API_LoadUserFile("AddendumData.bin", addendumVar->saveRAM, sizeof(addendumVar->saveRAM), Addendum_LoadFile_CB);
}

void Addendum_LoadOptions(void (*callback)(bool32 success))
{
    if (!SaveGame->addendumMods || addendumOpt->optionsLoaded == STATUS_CONTINUE) {
        if (callback)
            callback(false);
        return;
    }

    if (addendumOpt->optionsLoaded == STATUS_OK) {
        if (callback)
            callback(true);
        return;
    }

    addendumOpt->optionsLoaded = STATUS_CONTINUE;
    SaveGame->loadEntityPtr3   = SceneInfo->entity;
    SaveGame->loadCallback3    = callback;
    API_LoadUserFile("AddendumOptions.bin", addendumOpt->optionsRAM, sizeof(addendumOpt->optionsRAM), Addendum_LoadOptions_CB);
}
#endif

#if MANIA_USE_PLUS
void SaveGame_SaveFile(void (*callback)(bool32 success))
#else
void SaveGame_SaveFile(void (*callback)(void))
#endif
{
    if (API_GetNoSave() || !SaveGame->saveRAM || globals->saveLoaded != STATUS_OK) {
#if MANIA_USE_PLUS
        if (callback)
            callback(false);
#else
        if (callback)
            callback();
#endif
    }
    else {
        SaveGame->saveEntityPtr = SceneInfo->entity;
        SaveGame->saveCallback  = callback;
#if MANIA_USE_PLUS
        API_SaveUserFile("SaveDataAddendum.bin", globals->saveRAM, sizeof(globals->saveRAM), SaveGame_SaveFile_CB, false);
#else
        API_SaveUserFile("SaveDataAddendum.bin", globals->saveRAM, sizeof(globals->saveRAM), SaveGame_SaveFile_CB);
#endif
    }
}

#if MANIA_USE_PLUS
void Addendum_SaveFile(void (*callback)(bool32 success))
{
    if (API_GetNoSave() || !SaveGame->addendumData || addendumVar->saveLoaded != STATUS_OK) {
        if (callback)
            callback(false);
    }
    else {
        SaveGame->saveEntityPtr2 = SceneInfo->entity;
        SaveGame->saveCallback2  = callback;
        API_SaveUserFile("AddendumData.bin", addendumVar->saveRAM, sizeof(addendumVar->saveRAM), Addendum_SaveFile_CB, false);
    }
}

void Addendum_SaveOptions(void (*callback)(bool32 success))
{
    if (!SaveGame->addendumMods || addendumOpt->optionsLoaded != STATUS_OK) {
        if (callback)
            callback(false);
    }
    else {
        SaveGame->saveCallback3 = callback;
        API_SaveUserFile("AddendumOptions.bin", addendumOpt->optionsRAM, sizeof(addendumOpt->optionsRAM), Addendum_SaveOptions_CB, false);
    }
}
#endif

void SaveGame_SaveLoadedCB(bool32 success)
{
#if MANIA_USE_PLUS
    LogHelpers_Print("SaveLoadedCB(%d)", success);
#endif

    if (success) {
        foreach_all(UISaveSlot, entity)
        {
            if (!entity->type) {
                Entity *store = SceneInfo->entity;

                SceneInfo->entity = (Entity *)entity;
                UISaveSlot_LoadSaveInfo();
                UISaveSlot_HandleSaveIcons();

                SceneInfo->entity = store;
            }
        }

        GameProgress_ShuffleBSSID();
        GameProgress_PrintSaveProgress();
    }

#if MANIA_USE_PLUS
    if ((globals->taTableID == -1 || globals->taTableLoaded != STATUS_OK) && globals->taTableLoaded != STATUS_CONTINUE)
        TimeAttackData_LoadDB(NULL);
#endif
}

#if MANIA_USE_PLUS
void Addendum_SaveLoadedCB(bool32 success)
{
    LogHelpers_Print("SaveLoadedCB(%d)", success);

    if (success) {
        foreach_all(UISaveSlot, entity)
        {
            if (!entity->type) {
                Entity *store = SceneInfo->entity;

                SceneInfo->entity = (Entity *)entity;
                UISaveSlot_LoadSaveInfo();
                UISaveSlot_HandleSaveIcons();

                SceneInfo->entity = store;
            }
        }

        Addendum_PrintSaveProgress();
    }
}

void Addendum_OptionsLoadedCB(bool32 success)
{
    LogHelpers_Print("OptionsLoadedCB(%d)", success);

    if (success) {
        foreach_all(LogoSetup, logoSetup) { SceneInfo->entity = (Entity *)logoSetup; }

        Addendum_PrintOptionsProgress();
    }
}
#endif

void SaveGame_SaveGameState(void)
{
    SaveRAM *saveRAM        = SaveGame_GetSaveRAM();
    globals->recallEntities = true;

    for (int32 p = 0; p < PLAYER_COUNT; ++p) {
        globals->restartPos[(p * 2) + 0] = StarPost->playerPositions[p].x;
        globals->restartPos[(p * 2) + 1] = StarPost->playerPositions[p].y;
        globals->restartDir[p]           = StarPost->playerDirections[p];
        globals->restartSlot[p]          = StarPost->postIDs[p];
    }

    EntityPlayer *player1        = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    globals->restartMilliseconds = StarPost->storedMS;
    globals->restartSeconds      = StarPost->storedSeconds;
    globals->restartMinutes      = StarPost->storedMinutes;
    globals->tempMinutes         = SceneInfo->milliseconds;
    globals->tempSeconds         = SceneInfo->seconds;
    globals->tempMinutes         = SceneInfo->minutes;

    saveRAM->lives           = player1->lives;
    globals->restartLives[0] = player1->lives;
    saveRAM->continues       = globals->continues;
#if MANIA_USE_PLUS
    saveRAM->playerID       = globals->playerID;
    saveRAM->characterFlags = globals->characterFlags;
    saveRAM->stock          = globals->stock;
#endif
    saveRAM->score             = player1->score;
    globals->restartScore      = player1->score;
    saveRAM->score1UP          = player1->score1UP;
    globals->restartScore1UP   = player1->score1UP;
    globals->restart1UP          = player1->ringExtraLife;

    for (int32 p = 0; p < addendumVar->playerCount; ++p) {
        EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
        globals->storedRings[p]      = player->rings;
        LogHelpers_Print("storedRings[%d] set to %d", p, player->rings);
        globals->storedHyperRings[p] = player->hyperRing;
        LogHelpers_Print("storedHyperRings[%d] set to %d", p, player->hyperRing);
        globals->storedShields[p]    = player->shield;
        LogHelpers_Print("storedShields[%d] set to %d", p, player->shield);
    }

    for (int32 i = RESERVE_ENTITY_COUNT; i < RESERVE_ENTITY_COUNT + SCENEENTITY_COUNT; ++i) {
        EntityItemBox *itemBox = RSDK_GET_ENTITY(i, ItemBox);

        globals->atlEntityData[(0x200 * 1) + i] = SAVERECALL_NORMAL;
        if (!itemBox->classID && itemBox->active == ACTIVE_DISABLED)
            globals->atlEntityData[(0x200 * 1) + i] = SAVERECALL_DISABLED;
        else if (itemBox->classID == ItemBox->classID && itemBox->state == ItemBox_State_Broken)
            globals->atlEntityData[(0x200 * 1) + i] = SAVERECALL_BROKENITEMBOX;
    }
}
void SaveGame_SaveProgress(void)
{
    SaveRAM *saveRAM = SaveGame_GetSaveRAM();

    saveRAM->lives    = Player->savedLives;
    saveRAM->score    = Player->savedScore;
    saveRAM->score1UP = Player->savedScore1UP;
#if MANIA_USE_PLUS
    saveRAM->continues      = globals->continues;
    saveRAM->characterFlags = globals->characterFlags;
    saveRAM->stock          = globals->stock;
    saveRAM->playerID       = globals->playerID;

    if (!ActClear || ActClear->displayedActID <= 0) {
        if (globals->saveSlotID != NO_SAVE_SLOT) {
#else

    if (globals->gameMode == MODE_MANIA) {
#endif
            if (Zone_IsZoneLastAct()) {
                if (saveRAM->zoneID < Zone_GetZoneID() + 1)
                    saveRAM->zoneID = Zone_GetZoneID() + 1;

                if (saveRAM->characterID != ID_SONIC) {
                    if (saveRAM->zoneID > ZONE_TMZ) {
                        saveRAM->saveState = SAVEGAME_COMPLETE;
                        saveRAM->zoneID    = ZONE_COUNT_SAVEFILE;
                    }
                }
                else {
                    if (SaveGame_AllChaosEmeralds()) {
                        if (saveRAM->zoneID > ZONE_ERZ) {
                            saveRAM->saveState = SAVEGAME_COMPLETE;
                            saveRAM->zoneID    = ZONE_COUNT_SAVEFILE;
                        }
                    }
                    else {
                        if (saveRAM->zoneID > ZONE_TMZ) {
                            saveRAM->saveState = SAVEGAME_COMPLETE;
                            saveRAM->zoneID    = ZONE_COUNT_SAVEFILE;
                        }
                    }
                }
            }
#if MANIA_USE_PLUS
        }
#endif
    }
}
#if MANIA_USE_PLUS
void Addendum_SaveProgress(void)
{
    AddendumData *addendumData = Addendum_GetSaveRAM();

    if (RSDK.CheckSceneFolder("OOZ1") || RSDK.CheckSceneFolder("OOZ2")) {
        // do nothing, i fucking hate this zone
    }
    else if (!AIZSetup) {
        if (Zone_CheckLastActualAct()) {
            addendumData->actID = 0;
        }
        else {
            addendumData->actID += 1;
        }
    }
}
#endif
void SaveGame_ClearRestartData(void)
{
    globals->recallEntities      = false;
    globals->restartMilliseconds = 0;
    globals->restartSeconds      = 0;
    globals->restartMinutes      = 0;

    memset(globals->atlEntityData, 0, (RESERVE_ENTITY_COUNT + SCENEENTITY_COUNT) * sizeof(int32));
}
void SaveGame_SavePlayerState(void)
{
    SaveRAM *saveRAM     = SaveGame_GetSaveRAM();
    EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);

    globals->restartSlot[0] = 0;
    globals->restartSlot[1] = 0;
    globals->restartSlot[2] = 0;
    globals->restartSlot[3] = 0;

    globals->restartMilliseconds = SceneInfo->milliseconds;
    globals->restartSeconds      = SceneInfo->seconds;
    globals->restartMinutes      = SceneInfo->minutes;

#if MANIA_USE_PLUS
    if (saveRAM && TitleCard->suppressCB != Zone_TitleCard_SupressCB) {
#else
    if (saveRAM) {
#endif
        saveRAM->lives    = player->lives;
        saveRAM->score    = player->score;
        saveRAM->score1UP = player->score1UP;
#if MANIA_USE_PLUS
        saveRAM->continues      = globals->continues;
        saveRAM->characterFlags = globals->characterFlags;
        saveRAM->stock          = globals->stock;
        saveRAM->playerID       = globals->playerID;
#endif
    }
    globals->restart1UP        = player->ringExtraLife;

    for (int32 p = 0; p < addendumVar->playerCount; ++p) {
        EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
        globals->storedRings[p]      = player->rings;
        LogHelpers_Print("storedRings[%d] set to %d", p, player->rings);
        globals->storedHyperRings[p] = player->hyperRing;
        LogHelpers_Print("storedHyperRings[%d] set to %d", p, player->hyperRing);
        globals->storedShields[p]    = player->shield;
        LogHelpers_Print("storedShields[%d] set to %d", p, player->shield);
    }
}
void SaveGame_LoadPlayerState(void)
{
    SceneInfo->milliseconds = globals->restartMilliseconds;
    SceneInfo->seconds      = globals->restartSeconds;
    SceneInfo->minutes      = globals->restartMinutes;

    for (int32 p = 0; p < addendumVar->playerCount; ++p) {
        EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
        player->rings                = globals->storedRings[p];
        globals->storedRings[p]      = 0;
        player->hyperRing            = globals->storedHyperRings[p];
        globals->storedHyperRings[p] = 0;
        player->shield               = globals->storedShields[p];
        globals->storedShields[p]    = 0;
    }
    Player->ringExtraLife = globals->restart1UP;

    globals->restart1UP = 100;
}
void SaveGame_ResetPlayerState(void)
{
    globals->restartMilliseconds = 0;
    globals->restartSeconds      = 0;
    globals->restartMinutes      = 0;
    globals->restart1UP          = 0;

    if (Player) {
        Player->ringExtraLife = globals->restart1UP;
        for (int32 p = 0; p < addendumVar->playerCount; ++p) {
            EntityPlayer *player = RSDK_GET_ENTITY(p, Player);
            globals->storedRings[p]      = 0;
            player->rings                = globals->storedRings[p];
            globals->storedHyperRings[p] = 0;
            player->hyperRing            = globals->storedHyperRings[p];
            globals->storedShields[p]    = 0;
            player->shield               = globals->storedShields[p];
        }
    }
}
void SaveGame_LoadFile_CB(int32 status)
{
    bool32 success = false;
#if MANIA_USE_PLUS
    if (status == STATUS_OK || status == STATUS_NOTFOUND) {
        success             = true;
        globals->saveLoaded = STATUS_OK;
        LogHelpers_Print("Save Data Files Loaded!");
    }
    else {
        success             = false;
        globals->saveLoaded = STATUS_ERROR;
        LogHelpers_Print("Save Data Files Failed to Load...");
    }
#else
    if (status) {
        success             = true;
        globals->saveLoaded = STATUS_OK;
    }
    else {
        success             = false;
        globals->saveLoaded = STATUS_ERROR;
    }
#endif

    if (SaveGame->loadCallback) {
        Entity *store = SceneInfo->entity;
        if (SaveGame->loadEntityPtr)
            SceneInfo->entity = SaveGame->loadEntityPtr;

        SaveGame->loadCallback(success);
        SceneInfo->entity = store;

        SaveGame->loadCallback  = NULL;
        SaveGame->loadEntityPtr = NULL;
    }
}
#if MANIA_USE_PLUS
void Addendum_LoadFile_CB(int32 status)
{
    bool32 success = false;
    if (status == STATUS_OK || status == STATUS_NOTFOUND) {
        success                 = true;
        addendumVar->saveLoaded = STATUS_OK;
    }
    else {
        success                 = false;
        addendumVar->saveLoaded = STATUS_ERROR;
    }

    if (SaveGame->loadCallback2) {
        Entity *store = SceneInfo->entity;
        if (SaveGame->loadEntityPtr2)
            SceneInfo->entity = SaveGame->loadEntityPtr2;

        SaveGame->loadCallback2(success);
        SceneInfo->entity = store;

        SaveGame->loadCallback2  = NULL;
        SaveGame->loadEntityPtr2 = NULL;
    }
}

void Addendum_LoadOptions_CB(int32 status)
{
    bool32 success = false;
    if (status == STATUS_OK || status == STATUS_NOTFOUND) {
        success                    = true;
        addendumOpt->optionsLoaded = STATUS_OK;
        LogHelpers_Print("Addendum Options File Loaded!");
    }
    else {
        success                    = false;
        addendumOpt->optionsLoaded = STATUS_ERROR;
        LogHelpers_Print("Addendum Options File Failed To Load...");
    }

    if (SaveGame->loadCallback3) {
        Entity *store = SceneInfo->entity;
        if (SaveGame->loadEntityPtr3)
            SceneInfo->entity = SaveGame->loadEntityPtr3;

        SaveGame->loadCallback3(success);
        SceneInfo->entity = store;

        SaveGame->loadCallback3 = NULL;
        SaveGame->loadEntityPtr3 = NULL;
    }
}
#endif
void SaveGame_SaveFile_CB(int32 status)
{
    if (SaveGame->saveCallback) {
        Entity *store = SceneInfo->entity;
        if (SaveGame->saveEntityPtr)
            SceneInfo->entity = SaveGame->saveEntityPtr;

#if MANIA_USE_PLUS
        SaveGame->saveCallback(status == STATUS_OK);
#else
        SaveGame->saveCallback();
#endif

        SceneInfo->entity = store;

        SaveGame->saveCallback  = NULL;
        SaveGame->saveEntityPtr = NULL;
    }
}

void Addendum_SaveFile_CB(int32 status)
{
    if (SaveGame->saveCallback2) {
        Entity *store = SceneInfo->entity;
        if (SaveGame->saveEntityPtr2)
            SceneInfo->entity = SaveGame->saveEntityPtr2;

        SaveGame->saveCallback2(status == STATUS_OK);

        SceneInfo->entity = store;

        SaveGame->saveCallback2  = NULL;
        SaveGame->saveEntityPtr2 = NULL;
    }
}

void Addendum_SaveOptions_CB(int32 status)
{
    if (SaveGame->saveCallback3) {
        SaveGame->saveCallback3(status == STATUS_OK);
        SaveGame->saveCallback3  = NULL;
    }
}

bool32 SaveGame_AllChaosEmeralds(void)
{
    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    return saveRAM->collectedEmeralds == 0b01111111;
}
#if MANIA_USE_PLUS
bool32 Addendum_AllSuperEmeralds(void)
{
    AddendumData *addendumData = Addendum_GetSaveRAM();
    return addendumData->collectedSuperEmeralds == 0b01111111;
}

bool32 Addendum_AllTimeStones(void)
{
    AddendumData *addendumData = Addendum_GetSaveRAM();
    return addendumData->collectedTimeStones == 0b01111111;
}
#endif

bool32 SaveGame_GetEmerald(uint8 emeraldID)
{
    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    return (saveRAM->collectedEmeralds >> emeraldID) & 1;
}
#if MANIA_USE_PLUS
bool32 Addendum_GetSuperEmerald(uint8 emeraldID)
{
    AddendumData *addendumData = Addendum_GetSaveRAM();
    return (addendumData->collectedSuperEmeralds >> emeraldID) & 1;
}

bool32 Addendum_GetTimeStone(uint8 timeStoneID)
{
    AddendumData *addendumData = Addendum_GetSaveRAM();
    return (addendumData->collectedTimeStones >> timeStoneID) & 1;
}
#endif
void SaveGame_SetEmerald(uint8 emeraldID)
{
    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    saveRAM->collectedEmeralds |= 1 << emeraldID;
}
#if MANIA_USE_PLUS
void Addendum_SetSuperEmerald(uint8 emeraldID)
{
    AddendumData *addendumData = Addendum_GetSaveRAM();
    addendumData->collectedSuperEmeralds |= 1 << emeraldID;
}

void Addendum_SetTimeStone(uint8 timeStoneID)
{
    AddendumData *addendumData = Addendum_GetSaveRAM();
    addendumData->collectedTimeStones |= 1 << timeStoneID;
}
#endif
void SaveGame_ClearCollectedSpecialRings(void)
{
    SaveRAM *saveRAM               = SaveGame_GetSaveRAM();
    saveRAM->collectedSpecialRings = 0;
}
bool32 SaveGame_GetCollectedSpecialRing(uint8 id)
{
    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    return saveRAM->collectedSpecialRings & (1 << (16 * Zone->actID - 1 + id));
}
void SaveGame_SetCollectedSpecialRing(uint8 id)
{
    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    saveRAM->collectedSpecialRings |= 1 << (16 * Zone->actID - 1 + id);
}

#if GAME_INCLUDE_EDITOR
void SaveGame_EditorDraw(void) {}

void SaveGame_EditorLoad(void) {}
#endif

void SaveGame_Serialize(void) {}
