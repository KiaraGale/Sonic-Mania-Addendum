#ifndef OBJ_LEVELSELECT_H
#define OBJ_LEVELSELECT_H

#include "Game.h"

typedef enum {
    LSELECT_PLAYER_NONE,
    LSELECT_PLAYER_SONIC,
    LSELECT_PLAYER_TAILS,
    LSELECT_PLAYER_KNUCKLES,
#if MANIA_USE_PLUS
    LSELECT_PLAYER_MIGHTY,
    LSELECT_PLAYER_RAY,
    LSELECT_PLAYER_AMY,
#endif
} LevelSelectPlayerIDs;

// Object Class
struct ObjectLevelSelect {
    RSDK_OBJECT
#if MANIA_USE_PLUS
    STATIC(int32 bgAniDuration, 240);
    TABLE(int32 bgAniDurationTable[4], { 240, 3, 3, 3 });
    TABLE(int32 cheat_RickyMode[9], { 1, 9, 7, 9, 0, 8, 1, 1, 255 });
    TABLE(int32 cheat_AllEmeralds[5], { 4, 1, 2, 6, 255 });
    TABLE(int32 cheat_MaxContinues[9], { 1, 9, 9, 2, 1, 1, 2, 4, 255 });
    TABLE(int32 cheat_SwapGameMode[9], { 2, 0, 1, 8, 0, 6, 2, 3, 255 });
    TABLE(int32 cheat_UnlockAllMedals[9], { 1, 9, 8, 9, 0, 5, 0, 1, 255 });
    TABLE(int32 cheat_SuperDash[9], { 2, 0, 1, 7, 0, 8, 1, 5, 255 });
    TABLE(int32 cheat_MaxControl[5], { 9, 0, 0, 1, 255 }); // says there's 9 values here in static obj & IDA but only 5 are loaded so it is what it is ig
    TABLE(int32 cheat_ToggleSuperMusic[9], { 6, 2, 1, 4, 255, 0, 0, 0, 0 });
    TABLE(int32 cheat_AllTimeStones[9], { 2, 0, 2, 3, 1, 0, 2, 3, 255 }); // initial release date for Addendum
    TABLE(int32 cheat_AllSuperEmeralds[5], { 4, 1, 2, 6, 255 });
    TABLE(int32 cheat_Secret[8], { 13, 5, 7, 1, 13, 9, 24, 255 });
    int32 bgAniFrame;
    int32 startMusicID;
    int32 soundTestMax;
    uint16 sfxFail;
    uint16 sfxRing;
    uint16 sfxAltRing;
    uint16 sfxEmerald;
    uint16 sfxContinue;
    uint16 sfxMedalGot;
    int32 *cheatCodePtrs[11];
    int32 cheatCodePos[11];
    void (*checkCheatActivated[11])(void);
#else
    STATIC(int32 bgAniDuration, 240);
    int32 bgAniFrame;
    TABLE(int32 bgAniDurationTable[4], { 240, 3, 3, 3 });
    int32 startMusicID;
    int32 soundTestMax;
    uint16 sfxFail;
#endif
    uint8 touchDir;
    uint8 touchConfirm;
    uint8 touchSwap;
    uint8 touchSwapP2;
    uint16 dpadFrames;
    Animator dpadAnimator;
    Animator dpadTouchAnimator;
    Vector2 dpadPos;
    int32 dpadAlpha;
    Vector2 confirmPos;
    int32 confirmAlpha;
    Vector2 swapPos;
    int32 swapAlpha;
    Vector2 swapP2Pos;
    int32 swapP2Alpha;
    bool32 allEmeralds;
};

// Entity Class
struct EntityLevelSelect {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    int32 labelID;
    int32 soundTestID;
    int32 leaderCharacterID;
    int32 sidekickCharacterID;
    EntityUIText *zoneNameLabels[32];
    EntityUIText *stageIDLabels[32];
    EntityUIText *soundTestLabel;
    EntityUIPicture *zoneIcon;
    EntityUIPicture *player1Icon;
    EntityUIPicture *player2Icon;
#if MANIA_USE_PLUS
    EntityUIText *pinballLabel;
#endif
    int32 labelCount;
#if MANIA_USE_PLUS
    int32 offsetUFO;
    int32 offsetBSS;
    int32 unused1;
    int32 unused2;
    int32 unused3;
    int32 unused4;
#endif
};

// Object Struct
extern ObjectLevelSelect *LevelSelect;

// Standard Entity Events
void LevelSelect_Update(void);
void LevelSelect_LateUpdate(void);
void LevelSelect_StaticUpdate(void);
void LevelSelect_Draw(void);
void LevelSelect_Create(void *data);
void LevelSelect_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void LevelSelect_EditorDraw(void);
void LevelSelect_EditorLoad(void);
#endif
void LevelSelect_Serialize(void);

// Extra Entity Functions
#if MANIA_USE_PLUS
void LevelSelect_Cheat_AllEmeralds(void);
void LevelSelect_Cheat_AllSuperEmeralds(void);
void LevelSelect_Cheat_AllTimeStones(void);
void LevelSelect_Cheat_ToggleSuperMusic(void);
void LevelSelect_Cheat_MaxContinues(void);
void LevelSelect_Cheat_MaxControl(void);
void LevelSelect_Cheat_RickyMode(void);
void LevelSelect_Cheat_SuperDash(void);
void LevelSelect_Cheat_SwapGameMode(void);
void LevelSelect_Cheat_UnlockAllMedals(void);
void LevelSelect_Cheat_Secret(void);
#endif

void LevelSelect_Draw_Fade(void);

void LevelSelect_State_Init(void);
void LevelSelect_State_FadeIn(void);
void LevelSelect_State_Navigate(void);
void LevelSelect_State_FadeOut(void);

void LevelSelect_ManagePlayerIcon(void);
void LevelSelect_SetLabelHighlighted(bool32 highlight);
void LevelSelect_HandleColumnChange(void);
void LevelSelect_HandleNewStagePos(void);

void LevelSelect_HandleTouchInput(void);
void LevelSelect_DrawTouchUI(void);
int32 LevelSelect_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);

#endif //! OBJ_LEVELSELECT_H
