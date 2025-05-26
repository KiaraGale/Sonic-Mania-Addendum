#ifndef OBJ_PBL_HUD_H
#define OBJ_PBL_HUD_H

#include "Game.h"

#if MANIA_USE_PLUS

typedef enum {
    PBL_HUD_MSG_SCROLL_LEFT_SLOW,
    PBL_HUD_MSG_SCROLL_LEFT,
    PBL_HUD_MSG_SCROLL_RIGHT_SLOW,
    PBL_HUD_MSG_SCROLL_RIGHT,
    PBL_HUD_MSG_SHOW_RISE,
    PBL_HUD_MSG_SHOW_FALL,
    PBL_HUD_MSG_FLASH,
    PBL_HUD_MSG_FLASH_CRANE,
} PBL_HUDMessageTypes;

// Object Class
struct ObjectPBL_HUD {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 unused1;
    uint16 dpadFrames;
    Animator dpadAnimator;
    Animator dpadTouchAnimator;
    Vector2 dpadPos;
    int32 dpadAlpha;
    Vector2 actionPos;
    Vector2 pausePos;
    int32 pauseAlpha;
    bool32 craneControlsActive;
};

// Entity Class
struct EntityPBL_HUD {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    Vector2 offset;
    String text;
    Animator displayAnimator;
    Animator baseAnimator;
    Animator textAnimator;
};

// Object Struct
extern ObjectPBL_HUD *PBL_HUD;

// Standard Entity Events
void PBL_HUD_Update(void);
void PBL_HUD_LateUpdate(void);
void PBL_HUD_StaticUpdate(void);
void PBL_HUD_Draw(void);
void PBL_HUD_Create(void *data);
void PBL_HUD_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void PBL_HUD_EditorDraw(void);
void PBL_HUD_EditorLoad(void);
#endif
void PBL_HUD_Serialize(void);

// Extra Entity Functions
void PBL_HUD_DisplayMessage(EntityPBL_HUD *entity, const char *message, int32 type);

void PBL_HUD_StateMessage_ScrollLeftSlow(void);
void PBL_HUD_StateMessage_ScrollLeftFast(void);
void PBL_HUD_StateMessage_ScrollRightSlow(void);
void PBL_HUD_StateMessage_ScrollRightFast(void);
void PBL_HUD_StateMessage_ShowMove(void);
void PBL_HUD_StateMessage_Flash(void);
void PBL_HUD_StateMessage_FlashThenCrane(void);

void PBL_HUD_Draw_Basic(void);
void PBL_HUD_Draw_Message(void);
void PBL_HUD_Draw_Score(void);

void PBL_HUD_State_RevealCrane(void);
void PBL_HUD_State_HideCrane(void);

void PBL_HUD_DrawTouchControls(bool32 craneControls);
int32 PBL_HUD_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);
#endif

#endif //! OBJ_PBL_HUD_H
