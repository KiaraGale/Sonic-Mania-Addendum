#ifndef OBJ_GAMEPROGRESS_H
#define OBJ_GAMEPROGRESS_H

#include "Game.h"

#define GAMEPROGRESS_MEDAL_COUNT   (32)
#define GAMEPROGRESS_ZONE_COUNT    (12)
#define GAMEPROGRESS_EMERALD_COUNT (7)
#define ADDENDUMPROGRESS_TIMESTONE_COUNT    (7)
#define ADDENDUMPROGRESS_SUPEREMERALD_COUNT (7)

typedef enum {
    GAMEPROGRESS_UNLOCK_TIMEATTACK,
    GAMEPROGRESS_UNLOCK_COMPETITION,
    GAMEPROGRESS_UNLOCK_PEELOUT,
    GAMEPROGRESS_UNLOCK_INSTASHIELD,
    GAMEPROGRESS_UNLOCK_ANDKNUX,
    GAMEPROGRESS_UNLOCK_DEBUGMODE,
    GAMEPROGRESS_UNLOCK_MEANBEAN,
    GAMEPROGRESS_UNLOCK_DAGARDEN,
    GAMEPROGRESS_UNLOCK_BLUESPHERES,
    GAMEPROGRESS_UNLOCK_COUNT,
} GameProgressUnlockIDs;

typedef enum {
    GAMEPROGRESS_ENDING_NONE,
    GAMEPROGRESS_ENDING_BAD,
    GAMEPROGRESS_ENDING_GOOD,
} GameProgressEndingIDs;

typedef enum {
    GAMEPROGRESS_MEDAL_NONE,
    GAMEPROGRESS_MEDAL_SILVER,
    GAMEPROGRESS_MEDAL_GOLD,
} GameProgressMedalIDs;

typedef enum {
    ACH_GOLD_MEDAL,
    ACH_SILVER_MEDAL,
    ACH_EMERALDS,
    ACH_GAME_CLEARED,
    ACH_STARPOST,
    ACH_SIGNPOST,
    ACH_GHZ,
    ACH_CPZ,
    ACH_SPZ,
    ACH_FBZ,
    ACH_PGZ,
    ACH_SSZ,
    ACH_HCZ,
    ACH_MSZ,
    ACH_OOZ,
    ACH_LRZ,
    ACH_MMZ,
    ACH_TMZ,
    ACH_ERZ,
    ACH_GHZ2,
    ACH_CPZ2,
    ACH_SPZ2,
    ACH_FBZ2,
    ACH_PGZ2,
    ACH_SSZ2,
    ACH_HCZ2,
    ACH_MSZ2,
    ACH_OOZ2,
    ACH_LRZ2,
    ACH_MMZ2,
    ACH_TMZ2,
    ACH_TIMESTONES,
    ACH_SUPEREMERALDS,
    ACH_INSTAREFLECT,
    ACH_FOURSHIELDS,
} AchievementIDs;

extern AchievementID achievementList[];

// Using a seperate ProgressRAM struct
// Normally (and officially) the ObjectGameProgress struct was used here
// but due to v5U updating the entity (and thus the ProgressRAM "spec")
// ObjectGameProgress is no longer easily compatible across versions
// so I gave it dummy data and will be using this struct to interact with progressRAM
// this one was also broken with plus since medals[] were aligned by 1 byte
// so when "filter" was added, all medals were offset by 1 without this fix
typedef struct {
    uint8 padding[0x56]; // aka sizeof(Entity) for pre-plus

    uint8 medals[GAMEPROGRESS_MEDAL_COUNT];
    bool32 allGoldMedals;
    bool32 allSilverMedals;
    bool32 zoneCleared[GAMEPROGRESS_ZONE_COUNT];
    bool32 allZonesCleared;
    bool32 emeraldObtained[GAMEPROGRESS_EMERALD_COUNT];
    bool32 allEmeraldsObtained;
    bool32 unreadNotifs[GAMEPROGRESS_UNLOCK_COUNT];
    bool32 specialCleared[GAMEPROGRESS_EMERALD_COUNT];
    bool32 allSpecialCleared;
    bool32 unlockedEndingID;
    int32 goldMedalCount;
    int32 silverMedalCount;
} ProgressRAM;

typedef struct {
    uint8 padding[0x54];

    bool32 timeStoneObtained[ADDENDUMPROGRESS_TIMESTONE_COUNT];
    bool32 allTimeStonesObtained;
    bool32 superEmeraldObtained[ADDENDUMPROGRESS_SUPEREMERALD_COUNT];
    bool32 allSuperEmeraldsObtained;
    bool32 specialCleared[ADDENDUMPROGRESS_TIMESTONE_COUNT];
    bool32 allSpecialCleared;
} AddendumProgress;

// Object Class
struct ObjectGameProgress {
    RSDK_OBJECT
};

// Entity Class
struct EntityGameProgress {
    RSDK_ENTITY
    // padding to match whatever it would be normally
    // not required, but its for safety :)
    uint8 padding[sizeof(ProgressRAM) - sizeof(Entity)];
    uint8 paddingA[sizeof(AddendumProgress) - sizeof(Entity)];
};

// Object Struct
extern ObjectGameProgress *GameProgress;

// Standard Entity Events
void GameProgress_Update(void);
void GameProgress_LateUpdate(void);
void GameProgress_StaticUpdate(void);
void GameProgress_Draw(void);
void GameProgress_Create(void *data);
void GameProgress_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void GameProgress_EditorDraw(void);
void GameProgress_EditorLoad(void);
#endif
void GameProgress_Serialize(void);

// Extra Entity Events
int32 GameProgress_GetNotifStringID(int32 type);
void GameProgress_ShuffleBSSID(void);
ProgressRAM *GameProgress_GetProgressRAM(void);
#if MANIA_USE_PLUS
AddendumProgress *Addendum_GetProgressRAM(void);
#endif
bool32 GameProgress_GetZoneUnlocked(int32 zoneID);
float GameProgress_GetCompletionPercent(ProgressRAM *progress);
#if MANIA_USE_PLUS
float Addendum_GetCompletionPercent(AddendumProgress *progress);
#endif
#if MANIA_USE_PLUS
void GameProgress_TrackGameProgress(void (*callback)(bool32 success));
#else
void GameProgress_TrackGameProgress(void (*callback)(void));
#endif
#if MANIA_USE_PLUS
void Addendum_TrackGameProgress(void (*callback)(bool32 success));
#endif
void GameProgress_ClearBSSSave(void);
void GameProgress_UnlockAll(void);
void GameProgress_LockAllSpecialClear(void);
void GameProgress_ClearProgress(void);
void GameProgress_MarkZoneCompleted(int32 zoneID);
bool32 GameProgress_CheckZoneClear(void);
void GameProgress_GiveEmerald(int32 emeraldID);
#if MANIA_USE_PLUS
void Addendum_GiveSuperEmerald(int32 emeraldID);
void Addendum_GiveTimeStone(int32 timeStoneID);
#endif
void GameProgress_GiveMedal(uint8 medalID, uint8 type);
void GameProgress_GiveEnding(uint8 ending);
void GameProgress_PrintSaveProgress(void);
#if MANIA_USE_PLUS
void Addendum_PrintSaveProgress(void);
void Addendum_PrintOptionsProgress(void);
#endif
int32 GameProgress_CountUnreadNotifs(void);
int32 GameProgress_GetNextNotif(void);
bool32 GameProgress_CheckUnlock(uint8 id);

#endif //! OBJ_GAMEPROGRESS_H
