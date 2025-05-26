#ifndef OBJ_DASETUP_H
#define OBJ_DASETUP_H

#include "Game.h"

// Object Class
struct ObjectDASetup {
    RSDK_OBJECT
    bool32 initialized;
    int32 returnToMenu;
    int32 trackCount;
    int32 trackID;
    int32 activeTrack;
    EntityUIControl *control;
    EntityUIInfoLabel *trackSelLabel;
    EntityUIInfoLabel *trackTitleLabel;
    EntityFXFade *fxFade;
    EntityMusic *trackList[64];
    uint16 sfxEmerald;
    uint16 sfxMedal;
    uint16 sfxSSExit;
    uint16 sfxScoreTotal;
    uint8 touchDir;
    uint8 touchConfirm;
    uint8 touchBack;
    uint16 dpadFrames;
    Animator dpadAnimator;
    Animator dpadTouchAnimator;
    Vector2 dpadPos;
    int32 dpadAlpha;
    Vector2 playPos;
    int32 playAlpha;
};

// Entity Class
struct EntityDASetup {
    RSDK_ENTITY
};

// Object Struct
extern ObjectDASetup *DASetup;

// Standard Entity Events
void DASetup_Update(void);
void DASetup_LateUpdate(void);
void DASetup_StaticUpdate(void);
void DASetup_Draw(void);
void DASetup_Create(void *data);
void DASetup_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void DASetup_EditorDraw(void);
void DASetup_EditorLoad(void);
#endif
void DASetup_Serialize(void);

// Extra Entity Functions
void DASetup_DisplayTrack(int32 trackID);
bool32 DASetup_HandleMedallionDebug(void);
void DASetup_SetupUI(void);
void DASetup_State_ManageControl(void);
void DASetup_HandleTouchInput(void);
void DASetup_DrawUI(void);
int32 DASetup_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);

#endif //! OBJ_DASETUP_H
