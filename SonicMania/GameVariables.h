#ifndef GAME_VARIABLES_H
#define GAME_VARIABLES_H

// =========================
// GAME ENUMS
// =========================

typedef enum {
#if !MANIA_USE_PLUS
    MODE_NOSAVE,
#endif
    MODE_MANIA, // officially called "MODE_SAVEGAME" in pre-plus, but it's easier to re-use names lol
#if MANIA_USE_PLUS
    MODE_ENCORE,
#endif
    MODE_TIMEATTACK,
    MODE_COMPETITION,
} GameModes;

typedef enum {
    ID_NONE     = 0 << 0,
    ID_SONIC    = 1 << 0,
    ID_TAILS    = 1 << 1,
    ID_KNUCKLES = 1 << 2,
#if MANIA_USE_PLUS
    ID_MIGHTY = 1 << 3,
    ID_RAY    = 1 << 4,
    ID_AMY    = 1 << 5, // thank you troopsushi
#endif
    ID_SONIC_ASSIST  = ID_SONIC << 8,
    ID_TAILS_ASSIST  = ID_TAILS << 8,
    ID_KNUX_ASSIST   = ID_KNUCKLES << 8,
    ID_MIGHTY_ASSIST = ID_MIGHTY << 8,
    ID_RAY_ASSIST    = ID_RAY << 8,
    ID_AMY_ASSIST    = ID_AMY << 8,

    ID_DEFAULT_PLAYER = ID_SONIC | ID_TAILS_ASSIST,
} PlayerIDs;

#define GET_CHARACTER_ID(playerNum)                (((globals->playerID >> (8 * ((playerNum)-1))) & 0xFF))
#define CHECK_CHARACTER_ID(characterID, playerNum) (((globals->playerID >> (8 * ((playerNum)-1))) & 0xFF) == (characterID))

#if MANIA_USE_PLUS
#define GET_STOCK_ID(stockNum)                (((globals->stock >> (8 * ((stockNum)-1))) & 0xFF))
#define CHECK_STOCK_ID(characterID, stockNum) (((globals->stock >> (8 * ((stockNum)-1))) & 0xFF) == (characterID))
#endif

typedef enum { ITEMS_FIXED, ITEMS_RANDOM, ITEMS_TELEPORT } ItemModes;

typedef enum {
    MEDAL_DEBUGMODE   = 1 << 0,
    MEDAL_SIDEKICK    = 1 << 1,
    MEDAL_PEELOUT     = 1 << 2,
    MEDAL_INSTASHIELD = 1 << 3,
    MEDAL_NODROPDASH  = 1 << 4,
#if MANIA_USE_PLUS
    MEDAL_NOTIMEOVER  = 1 << 5,
    MEDAL_P2NONE      = 1 << 6,
    MEDAL_P2SONIC     = 1 << 7,
    MEDAL_P2TAILS     = 1 << 8,
    MEDAL_P2KNUX      = 1 << 9,
    MEDAL_P2MIGHTY    = 1 << 10,
    MEDAL_P2RAY       = 1 << 11,
    MEDAL_P2AMY       = 1 << 12,
#endif
} MedalMods;

typedef enum {
    COMP_FIXEDITEMS  = 1 << 0,
    COMP_RANDOMITEMS = 1 << 1,
    COMP_TELEPORTERS = 1 << 2,
    COMP_ROUNDAMOUNT = 1 << 3,
    COMP_NORMALRUN   = 1 << 4,
    COMP_SUPERRUN    = 1 << 5,
    COMP_HYPERRUN    = 1 << 6,
    COMP_MIRACLERUN  = 1 << 7,
} CompetitionRules;

typedef enum { MEDIA_DEMO } CategoryIDS;

typedef enum { FORCE_SPLIT } ScreenSplit;

typedef enum { NO_SAVE_SLOT = 255 } SaveSlots;

typedef enum { WIDE_SCR_XSIZE = 424, WIDE_SCR_XCENTER = 212 } ScreenSizes;

#if RETRO_REV02
typedef enum {
    // General Filters
    FILTER_NONE  = 0 << 0,
    FILTER_SLOT1 = 1 << 0,
    FILTER_SLOT2 = 1 << 1,
    FILTER_SLOT3 = 1 << 2,
    FILTER_SLOT4 = 1 << 3,
    FILTER_SLOT5 = 1 << 4,
    FILTER_SLOT6 = 1 << 5,
    FILTER_SLOT7 = 1 << 6,
    FILTER_SLOT8 = 1 << 7,
    FILTER_ANY   = FILTER_SLOT1 | FILTER_SLOT2 | FILTER_SLOT3 | FILTER_SLOT4 | FILTER_SLOT5 | FILTER_SLOT6 | FILTER_SLOT7 | FILTER_SLOT8,
} SceneFilters;
#endif

#if MANIA_USE_PLUS
typedef enum {
    // Mania-Specific filter uses
    FILTER_BOTH   = FILTER_SLOT1,
    FILTER_MANIA  = FILTER_SLOT2,
    FILTER_ENCORE = FILTER_SLOT3,
} ManiaFilters;

typedef enum { DLC_PLUS } GameDLC;
#endif

typedef enum {
    PLANEFILTER_NONE,
    PLANEFILTER_AL,     // - Plane A, Low Layer
    PLANEFILTER_BL,     // - Plane B, Low Layer
    PLANEFILTER_AH,     // - Plane A, High Layer
    PLANEFILTER_BH,     // - Plane B, High Layer
} PlaneFilterTypes;

typedef enum {
    SLOT_PLAYER1 = 0,
    SLOT_PLAYER2 = 1,
#if MANIA_USE_PLUS
    SLOT_PLAYER3    = 2,
    SLOT_PLAYER4    = 3,
    SLOT_POWERUP1   = 4,
    SLOT_PLAYER5    = 4, // Used in TMZ2Outro
    SLOT_POWERUP2   = 5,
    SLOT_PLAYER6    = 5, // Used in TMZ2Outro
    SLOT_POWERUP3   = 6,
    SLOT_POWERUP4   = 7,
    SLOT_POWERUP1_2 = 8,
    SLOT_POWERUP2_2 = 9,
    SLOT_POWERUP3_2 = 10,
    SLOT_POWERUP4_2 = 11,
#else
    SLOT_POWERUP1   = 2,
    SLOT_POWERUP2   = 3,
    SLOT_POWERUP1_2 = 4,
    SLOT_POWERUP2_2 = 5,
#endif
    SLOT_BSS_SETUP   = 8,
    SLOT_PBL_SETUP   = 8,
    SLOT_UFO_SETUP   = 8,
    SLOT_MUSIC       = 9,
    SLOT_BSS_HUD     = 10,
    SLOT_UFO_CAMERA  = 10,
    SLOT_PBL_CAMERA  = 10,
    SLOT_BSS_MESSAGE = 11,
    SLOT_UFO_HUD     = 11,
    SLOT_ZONE        = MANIA_USE_PLUS ? 12 : 8,
    SLOT_POWERUP1_3  = 13, // custom-added for Addendum
    SLOT_POWERUP2_3  = 14, // custom-added for Addendum
    SLOT_CUTSCENESEQ         = 15,
    SLOT_PAUSEMENU           = 16,
    SLOT_GAMEOVER            = 16,
    SLOT_ACTCLEAR            = 16,
    SLOT_PAUSEMENU_UICONTROL = 17,
    SLOT_PAUSEMENU_BUTTON1   = 18,
    SLOT_PAUSEMENU_BUTTON2   = 19,
    SLOT_PAUSEMENU_BUTTON3   = 20,
    SLOT_DIALOG              = 21,
    SLOT_DIALOG_UICONTROL    = 22,
    SLOT_DIALOG_BUTTONS      = 23,
    SLOT_DIALOG_BUTTON2      = 24,
    SLOT_DIALOG_BUTTON3      = 25,
#if MANIA_USE_PLUS
    SLOT_POPOVER           = 26,
    SLOT_POPOVER_UICONTROL = 27,
    SLOT_POPOVER_BUTTONS   = 28,
    SLOT_POPOVER_BUTTON2   = 29,
    SLOT_POPOVER_BUTTON3   = 30,
    SLOT_POPOVER_BUTTON4   = 31,
#endif
    SLOT_BIGBUBBLE_P1 = 32,
    SLOT_BIGBUBBLE_P2 = 33,
#if MANIA_USE_PLUS
    SLOT_BIGBUBBLE_P3 = 34,
    SLOT_BIGBUBBLE_P4 = 36,
#endif
    SLOT_BSS_HORIZON    = 32,
    SLOT_UFO_SPEEDLINES = 34,
    SLOT_UFO_PLASMA     = 36,
#if MANIA_USE_PLUS
    SLOT_REPLAYRECORDER_PLAYBACK = 36,
    SLOT_REPLAYRECORDER_RECORD   = 37,
    SLOT_MUSICSTACK_START        = 40,
    //[41-47] are part of the music stack
    SLOT_MUSICSTACK_END = 48,
#endif
    SLOT_CAMERA1 = 60,
    SLOT_CAMERA2 = 61,
    SLOT_CAMERA3 = 62,
    SLOT_CAMERA4 = 63,
} ReservedEntities;

typedef enum {
    PRESENCE_GENERIC,
    PRESENCE_MENU,
    PRESENCE_MANIA,
#if MANIA_USE_PLUS
    PRESENCE_ENCORE,
#endif
    PRESENCE_TA,
    PRESENCE_COMP,
    PRESENCE_TITLE,
} PresenceTypes;

#if MANIA_USE_PLUS
typedef enum {
    SECRET_RICKYMODE = 1 << 0,
    SECRET_SUPERDASH = 1 << 1,
} GameCheats;
#endif

// =========================
// GLOBAL VARIABLES
// =========================

typedef struct {
    int32 gameMode;
    int32 playerID; // active character IDs (usually leader & sidekick)
    int32 specialCleared;
    int32 specialRingID;
    int32 blueSpheresID;
    int32 blueSpheresInit;
    int32 atlEnabled;
    int32 atlEntityCount;
    int32 atlEntitySlot[0x20];
    int32 atlEntityData[0x4000];
    int32 saveLoaded;
    int32 saveRAM[0x4000];
    int32 saveSlotID;
    int32 noSaveSlot[0x400];
    int32 menuParam[0x4000];
    int32 itemMode;
    int32 suppressTitlecard;
    int32 suppressAutoMusic;
    int32 competitionSession[0x4000];
    int32 medalMods;
    int32 parallaxOffset[0x100];
    int32 enableIntro;
    int32 optionsLoaded;
    int32 optionsRAM[0x80];
    int32 presenceID;
    int32 medallionDebug;
    int32 noSave;
    int32 notifiedAutosave;
    int32 recallEntities;
    int32 restartRings[4];
    int32 restart1UP;
    int32 restartHyperRing[4];
    int32 restartShield[4];
    int32 restartPos[8];
    int32 restartSlot[4];
    int32 restartDir[4];
    int32 restartMinutes;
    int32 restartSeconds;
    int32 restartMilliseconds;
    int32 tempMinutes;
    int32 tempSeconds;
    int32 tempMilliseconds;
    int32 restartScore;
    int32 restartScore1UP;
    int32 restartLives[4];
#if GAME_VERSION != VER_100
    int32 restartMusicID;
#endif
    int32 restartFlags;
    int32 tempFlags;
    int32 continues;
    int32 initCoolBonus;
    int32 coolBonus[4];
#if MANIA_USE_PLUS
    int32 replayWriteBuffer[0x40000];
    int32 replayReadBuffer[0x40000];
    int32 replayTempWBuffer[0x40000];
    int32 replayTempRBuffer[0x40000];
    int32 replayTableID;
    int32 replayTableLoaded;
    int32 taTableID;
    int32 taTableLoaded;
    int32 stock;          // order of buddies (not including the leader/sidekick)
    int32 characterFlags; // characters in the "party"
    int32 vapeMode;
    int32 secrets;
    int32 superSecret;
    int32 superMusicEnabled;
    int32 lastHasPlus;
    int32 hasPlusInitial;
    bool32 startSuper;
    int32 storedRings[4];
    int32 storedHyperRings[4];
    int32 storedShields[4];
#endif
} GlobalVariables;

extern GlobalVariables *globals;

// =========================
// ADDENDUM VARIABLES
// =========================

typedef struct {
    int32 saveLoaded;
    int32 saveRAM[0x4000];
    int32 saveSlotID;
    int32 noSaveSlot[0x400];
    int32 saveActID;
    bool32 doHPZResults;
    int32 carryOverValue[5];
    int32 player2ID;
    int32 player3ID;
    int32 player4ID;
    int32 playerCount;
    bool32 secretMovesets;
} AddendumVariables;

extern AddendumVariables *addendumVar;

typedef enum {
    TIMELIMIT_ON                  = 0,
    DEBUGMODE_OFF                 = 0,
    SONICMOVESET_ADDENDUM         = 0,
    TAILSMOVESET_ADDENDUM         = 0,
    KNUXMOVESET_ADDENDUM          = 0,
    MIGHTYMOVESET_ADDENDUM        = 0,
    RAYMOVESET_ADDENDUM           = 0,
    AMYMOVESET_ADDENDUM           = 0,
    PEELOUTABILITY_SONICONLY      = 0,
    SPINDASHTYPE_MANIA            = 0,
    LIFESYSTEM_MANIA              = 0,
    SECONDGEMS_NONE               = 0,
    SHIELDTRANSFER_OFF            = 0,
    ITEMBOXSHIELDS_DEFAULT        = 0,
    SPRITESTYLE_MANIA             = 0,
    EMERALDPALETTE_MANIA          = 0,
    SUPERMUSIC_ON                 = 0,
    VAPEMODE_OFF                  = 0,
    COOPSTYLE_MANIA               = 0,
    P2CAMERA_OFF                  = 0,
    TIMELIMIT_OFF                 = 1,
    DEBUGMODE_ON                  = 1,
    SONICMOVESET_MANIA            = 1,
    TAILSMOVESET_MANIA            = 1,
    KNUXMOVESET_MANIA             = 1,
    MIGHTYMOVESET_MANIA           = 1,
    RAYMOVESET_MANIA              = 1,
    AMYMOVESET_ORIGINS            = 1,
    PEELOUTABILITY_ALLEXCEPTAMY   = 1,
    SPINDASHTYPE_CD               = 1,
    LIFESYSTEM_UNCAPPED           = 1,
    SECONDGEMS_SUPEREMERALD       = 1,
    SHIELDTRANSFER_ON             = 1,
    ITEMBOXSHIELDS_ONLYBLUE       = 1,
    SPRITESTYLE_CHAREDITSPLUS     = 1,
    EMERALDPALETTE_S1             = 1,
    SUPERMUSIC_OFF                = 1,
    VAPEMODE_ON                   = 1,
    COOPSTYLE_TOGETHER            = 1,
    P2CAMERA_ON                   = 1,
    SONICMOVESET_S3K              = 2,
    PEELOUTABILITY_ALL            = 2,
    SPINDASHTYPE_NONE             = 2,
    LIFESYSTEM_INFINITE           = 2,
    SECONDGEMS_TIMESTONE          = 2,
    ITEMBOXSHIELDS_ONLYBUBBLE     = 2,
    EMERALDPALETTE_CD             = 2,
    COOPSTYLE_APART               = 2,
    SONICMOVESET_CD               = 3,
    PEELOUTABILITY_NONE           = 3,
    ITEMBOXSHIELDS_ONLYFLAME      = 3,
    EMERALDPALETTE_S2             = 3,
    ITEMBOXSHIELDS_ONLYLIGHTNING  = 4,
    EMERALDPALETTE_S3             = 4,
    ITEMBOXSHIELDS_CYCLEELEMENTAL = 5,
    ITEMBOXSHIELDS_CYCLEALL       = 6,
} AddendumModEnums;

typedef struct {
    int32 optionsLoaded;
    int32 optionsRAM[0x4000];
    int8 timeLimit;
    int8 debugMode;
    int8 sonicMoveset;
    int8 tailsMoveset;
    int8 knuxMoveset;
    int8 mightyMoveset;
    int8 rayMoveset;
    int8 amyMoveset;
    int8 peeloutAbility;
    int8 spindashType;
    int8 lifeSystem;
    int8 secondaryGems;
    bool32 shieldTransfer;
    int8 itemboxShields;
    int8 spriteStyle;
    int8 emeraldPalette;
    bool32 superMusic;
    bool32 vapeMode;
    int8 coopStyle;
    int32 competitonMods;
} AddendumOptVar;

extern AddendumOptVar *addendumOpt;

// =========================
// GAME HELPERS
// =========================

#if MANIA_USE_PLUS
#define isMainGameMode() (globals->gameMode == MODE_MANIA || globals->gameMode == MODE_ENCORE)
#else
#define isMainGameMode() (globals->gameMode == MODE_NOSAVE || globals->gameMode == MODE_MANIA)
#endif

// used mainly for cutscenes
#define MANIA_GET_PLAYER(p1, p2, p3, p4, cam)                                                                                                        \
    EntityPlayer *p1  = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);                                                                                       \
    EntityPlayer *p2  = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);                                                                                       \
    EntityPlayer *p3  = RSDK_GET_ENTITY(SLOT_PLAYER3, Player);                                                                                       \
    EntityPlayer *p4  = RSDK_GET_ENTITY(SLOT_PLAYER4, Player);                                                                                       \
    EntityCamera *cam = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);

// "Base" Classes
#define MANIA_PLATFORM_BASE                                                                                                                          \
    RSDK_ENTITY                                                                                                                                      \
    StateMachine(state);                                                                                                                             \
    StateMachine(stateCollide);                                                                                                                      \
    int32 type;                                                                                                                                      \
    Vector2 amplitude;                                                                                                                               \
    int32 speed;                                                                                                                                     \
    bool32 hasTension;                                                                                                                               \
    int8 frameID;                                                                                                                                    \
    uint8 collision;                                                                                                                                 \
    Vector2 tileOrigin;                                                                                                                              \
    Vector2 centerPos;                                                                                                                               \
    Vector2 drawPos;                                                                                                                                 \
    Vector2 collisionOffset;                                                                                                                         \
    int32 stood;                                                                                                                                     \
    int32 timer;                                                                                                                                     \
    int32 stoodAngle;                                                                                                                                \
    uint8 stoodPlayers;                                                                                                                              \
    uint8 pushPlayersL;                                                                                                                              \
    uint8 pushPlayersR;                                                                                                                              \
    Hitbox hitbox;                                                                                                                                   \
    Animator animator;                                                                                                                               \
    int32 childCount;

#define MANIA_BUTTON_BASE                                                                                                                            \
    RSDK_ENTITY                                                                                                                                      \
    int32 type;                                                                                                                                      \
    bool32 walkOnto;                                                                                                                                 \
    uint8 tag;                                                                                                                                       \
    bool32 down;                                                                                                                                     \
    bool32 toggled;                                                                                                                                  \
    bool32 currentlyActive;                                                                                                                          \
    bool32 activated;                                                                                                                                \
    bool32 wasActivated;                                                                                                                             \
    int32 pressPos;

#define MANIA_UI_ITEM_BASE                                                                                                                           \
    RSDK_ENTITY                                                                                                                                      \
    StateMachine(state);                                                                                                                             \
    void (*processButtonCB)(void);                                                                                                                   \
    bool32 (*touchCB)(void);                                                                                                                         \
    void (*actionCB)(void);                                                                                                                          \
    void (*selectedCB)(void);                                                                                                                        \
    void (*failCB)(void);                                                                                                                            \
    void (*buttonEnterCB)(void);                                                                                                                     \
    void (*buttonLeaveCB)(void);                                                                                                                     \
    bool32 (*checkButtonEnterCB)(void);                                                                                                              \
    bool32 (*checkSelectedCB)(void);                                                                                                                 \
    int32 timer;                                                                                                                                     \
    Vector2 startPos;                                                                                                                                \
    Entity *parent;                                                                                                                                  \
    Vector2 touchPosSizeS;                                                                                                                           \
    Vector2 touchPosOffsetS;                                                                                                                         \
    bool32 touchPressed;                                                                                                                             \
    Vector2 touchPosSizeM[4];   /*size of the touchPos: in 16-bit shifted format*/                                                                   \
    Vector2 touchPosOffsetM[4]; /*offset of the touchPos: 0,0 is entity pos, negative is left/up, positive is right/down*/                           \
    void (*touchPosCallbacks[4])(void);                                                                                                              \
    int32 touchPosCount;                                                                                                                             \
    int32 touchPosID;                                                                                                                                \
    bool32 isSelected;                                                                                                                               \
    bool32 disabled;

#define MANIA_CUTSCENE_BASE                                                                                                                          \
    RSDK_ENTITY                                                                                                                                      \
    Vector2 size;                                                                                                                                    \
    bool32 activated;                                                                                                                                \
    Animator animator; /* unused, afaik */                                                                                                           \
    Hitbox hitbox;

#endif //! GAME_VARIABLES_H
