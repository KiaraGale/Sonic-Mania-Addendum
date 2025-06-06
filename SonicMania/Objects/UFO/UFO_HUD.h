#ifndef OBJ_UFO_HUD_H
#define OBJ_UFO_HUD_H

#include "Game.h"

// Object Class
struct ObjectUFO_HUD {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 dpadFrames;
    Animator dpadAnimator;
    Animator dpadTouchAnimator;
    Vector2 dpadPos;
    int32 dpadAlpha;
    Vector2 actionPos;
    Vector2 pausePos;
    int32 pauseAlpha;
};

// Entity Class
struct EntityUFO_HUD {
    RSDK_ENTITY
    bool32 showRingCount;
    int32 timer;
    uint8 machPaletteBank;
    Animator hudAnimator;
    Animator numbersAnimator;
    Animator machAnimator;
    Animator stripeAnimator;
};

// Object Struct
extern ObjectUFO_HUD *UFO_HUD;

// Standard Entity Events
void UFO_HUD_Update(void);
void UFO_HUD_LateUpdate(void);
void UFO_HUD_StaticUpdate(void);
void UFO_HUD_Draw(void);
void UFO_HUD_Create(void *data);
void UFO_HUD_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void UFO_HUD_EditorDraw(void);
void UFO_HUD_EditorLoad(void);
#endif
void UFO_HUD_Serialize(void);

// Extra Entity Functions
void UFO_HUD_CheckLevelUp(void);
void UFO_HUD_LevelUpMach(void);
void UFO_HUD_DrawNumbers(Vector2 *drawPos, int32 value);
void UFO_HUD_DrawTouchControls(void);
int32 UFO_HUD_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);

#endif //! OBJ_UFO_HUD_H
