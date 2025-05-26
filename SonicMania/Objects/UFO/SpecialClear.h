#ifndef OBJ_SPECIALCLEAR_H
#define OBJ_SPECIALCLEAR_H

#include "Game.h"

typedef enum {
    SC_MSG_SPECIALCLEAR,
    SC_MSG_GOTEMERALD,
    SC_MSG_ALLEMERALDS,
    SC_MSG_SUPER,
    SC_MSG_GOTSECONDGEM,
    SC_MSG_ALLSECONDGEMS,
    SC_MSG_NEWPOWERFORM,
} SpecialClearTypes;

typedef enum {
    SC_ANI_SONIC,
    SC_ANI_TAILS,
    SC_ANI_KNUX,
#if MANIA_USE_PLUS
    SC_ANI_MIGHTY,
    SC_ANI_RAY,
#endif
    SC_ANI_BONUS,
    SC_ANI_NUMBERS,
    SC_ANI_EMERALDS,
#if MANIA_USE_PLUS
    SC_ANI_CONTINUE,
    SC_ANI_AMY,
    SC_ANI_TIMESTONES,
#endif
} SpecialClearAniIDs;

// Object Class
struct ObjectSpecialClear {
    RSDK_OBJECT
    uint16 aniFrames;
#if !MANIA_USE_PLUS
    uint16 continueFrames;
#endif
    uint16 sfxScoreAdd;
    uint16 sfxScoreTotal;
    uint16 sfxEvent;
    uint16 sfxSpecialWarp;
    uint16 sfxContinue;
    uint16 sfxEmerald;
    uint16 sfxTimeStone;
    uint16 sfx1up;
    TABLE(color miracleColors[6], { 0x6D2661, 0x952D82, 0xBC34A3, 0xD94AB1, 0xF16AC2, 0xFF88CA });
    int32 colorStorage[6];
    bool32 startFadingBackground;
    int32 storedSpecialStageID;
    bool32 failedStage;
    int32 backgroundFade;
    int32 sparkleAniFrames;
    int32 sparkleType; // 0 - none, 1 - normal, 2 - inverted
    Vector2 sparkleTarget;
    int32 sparkleAngle;
    int32 sparkleDistance;
    Vector2 sparklePos[16];
    int32 specialStageID;
    EntityHPZEmerald *SortedSuperEmeralds[8];
    TABLE(int32 emeraldPalettes[180],
        { 0xA00000, 0xB01820, 0xC03040, 0xD04860, 0xE06080, 0x4040C8, 0x5858C8, 0xE060E0, 0x7070C8, 0x8888C8, 0xA0A0C8, 0xC048C8,
          0xA030B0, 0x801898, 0x600080, 0x88B8E0, 0x0081E0, 0x2890E0, 0x58A8E0, 0xB8D0E0, 0x208000, 0x409800, 0x60B000, 0x80C800,
          0xA0E000, 0xE0E0A0, 0xD0C878, 0xC0B050, 0xB09828, 0xA08000, 0x808080, 0x909090, 0xA0A0A0, 0xC0C0C0, 0xB0B0B0, 0xF0F0F0,
          0x004747, 0x007D7D, 0x00A2A2, 0x00DDDD, 0x89FAFA, 0x4F001E, 0x852465, 0xDAF970, 0xC040A0, 0xE060C0, 0xF195E1, 0xA0E000,
          0x60C000, 0x00A000, 0x006000, 0xA4A4A4, 0x404040, 0x656565, 0x898989, 0xCACACA, 0x1A1A75, 0x4040A0, 0x6060C0, 0x8080E0,
          0xAAA8FC, 0xEEF48E, 0xE0E000, 0xC0A000, 0x886600, 0x563000, 0x4E0000, 0x8A0000, 0xD60000, 0xF97F8D, 0xEB385C, 0xF0F0F0,
          0x5A0024, 0x7B0029, 0xB8001A, 0xDC0000, 0xFF4229, 0x6F4900, 0x926700, 0x7D7DFF, 0xB89800, 0xD6C004, 0xF1F141, 0x5C5CFF,
          0x3C3CEC, 0x2D2DB3, 0x251D8C, 0x840EF1, 0x300061, 0x420087, 0x6200C4, 0xAB49FF, 0x005B00, 0x2B8200, 0x48B400, 0x62D100,
          0x90FC00, 0xFF8C12, 0xFF5E0F, 0xE84200, 0xB41B0C, 0x840909, 0x004875, 0x006091, 0x008EA8, 0x40F2AD, 0x00BFB3, 0xF0F0F0, 
          0x6A6A6A, 0x808080, 0xA0A0A0, 0xC0C0C0, 0xE1E1E1, 0x890000, 0xAA0000, 0xFFC3FF, 0xD00000, 0xF2214D, 0xFF69A5, 0xFF80F2,
          0xF455EE, 0xDD38E0, 0xC026BB, 0x94E000, 0x207F00, 0x3E9A00, 0x5EBC00, 0xCDF386, 0x007AD5, 0x0099D9, 0x00BEE0, 0x3DDBEE,
          0x7FFFFA, 0xD768F3, 0xAE29EC, 0x8000C0, 0x6B008F, 0x550072, 0xA88700, 0xC7A600, 0xE0C000, 0xF3ECB0, 0xF2DA3B, 0xF0F0F0, 
          0x375A9C, 0x4E72BA, 0x6998C7, 0xB2D1F1, 0xD7E7F6, 0x85006A, 0xAA0088, 0x9D98FF, 0xD21AAA, 0xFF71DC, 0xFFB1E3, 0x7171FF,
          0x3E4AE8, 0x212CC0, 0x212187, 0xF6812C, 0x82000F, 0xA60000, 0xE71B1B, 0xF7AB59, 0x014501, 0x006C01, 0x00A700, 0x8AEF04,
          0xD3FF7D, 0xF7ED9C, 0xFFD513, 0xE0941A, 0xC5690D, 0xA64717, 0x665D7C, 0x807BA1, 0xACACD3, 0xECECF5, 0xD3D3F9, 0xF0F0F0 });
};

// Entity Class
struct EntitySpecialClear {
    RSDK_ENTITY
    StateMachine(state);
    bool32 isBSS;
    int32 messageType;
    int32 timer;
    bool32 showFade;
    bool32 continueIconVisible;
    bool32 hasContinues;
    int32 fillColor;
    int32 score;
    int32 score1UP;
    int32 lives;
    int32 ringBonus;
    int32 perfectBonus;
    int32 machBonus;
    Vector2 messagePos1;
    Vector2 messagePos2;
    Vector2 scoreBonusPos;
    Vector2 ringBonusPos;
    Vector2 perfectBonusPos;
    Vector2 machBonusPos;
    Vector2 continuePos;
    int32 emeraldPositions[7];
    int32 emeraldSpeeds[7];
    int32 timeStonePositions[7];
    int32 timeStoneSpeeds[7];
    int32 unused1;
    int32 unused2;
    int32 unused3;
    int32 unused4;
    int32 unused5;
    int32 unused6;
    bool32 saveInProgress;
    Animator playerNameAnimator;
    Animator bonusAnimator;
    Animator numbersAnimator;
    Animator emeraldsAnimator;
    Animator timeStonesAnimator;
    Animator continueAnimator;
    Animator sparkleAnimator[16];
};

// Object Struct
extern ObjectSpecialClear *SpecialClear;

// Standard Entity Events
void SpecialClear_Update(void);
void SpecialClear_LateUpdate(void);
void SpecialClear_StaticUpdate(void);
void SpecialClear_Draw(void);
void SpecialClear_Create(void *data);
void SpecialClear_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void SpecialClear_EditorDraw(void);
void SpecialClear_EditorLoad(void);
#endif
void SpecialClear_Serialize(void);

// Extra Entity Functions
void SpecialClear_DrawNumbers(Vector2 *pos, int32 value);
void SpecialClear_GiveScoreBonus(int32 score);

#if MANIA_USE_PLUS
void SpecialClear_SaveCB(bool32 success);
#else
void SpecialClear_SaveCB(void);
#endif

void SpecialClear_State_SetupDelay(void);
void SpecialClear_State_EnterText(void);
void SpecialClear_State_AdjustText(void);
void SpecialClear_HandleEmeraldAppear(void);
void SpecialClear_State_EnterBonuses(void);
void SpecialClear_State_ScoreShownDelay(void);
void SpecialClear_State_TallyScore(void);
void SpecialClear_State_ShowTotalScore_Continues(void);
void SpecialClear_State_ShowTotalScore_NoContinues(void);
void SpecialClear_State_ExitFinishMessageSuper(void);
void SpecialClear_State_ExitFinishMessageMiracle(void);
void SpecialClear_State_EnterSuperMessage(void);
void SpecialClear_State_ShowSuperMessage(void);
void SpecialClear_State_ExitFadeOut(void);
void SpecialClear_State_ExitResults(void);

void SpecialClear_State_WaitToRevealSuperEmerald(void);
void SpecialClear_State_RevealSuperEmerald(void);
void SpecialClear_State_ActivateSuperEmerald(void);
void SpecialClear_State_RevealMasterEmerald(void);
void SpecialClear_State_ActivateMasterEmerald(void);
void SpecialClear_State_EnterHyperMessage(void);
void SpecialClear_State_ShowHyperMessage(void);

#endif //! OBJ_SPECIALCLEAR_H
