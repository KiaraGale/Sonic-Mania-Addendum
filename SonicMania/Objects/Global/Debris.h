#ifndef OBJ_DEBRIS_H
#define OBJ_DEBRIS_H

#include "Game.h"

// Structs
typedef struct {
    int32 frame;
    int32 direction;
    Vector2 velocity;
} DebrisEntry;

typedef struct {
    int32 frame;
    int32 direction;
    Vector2 velocity;
    Vector2 offset;
} DebrisOffsetEntry;

// Object Class
struct ObjectDebris {
    RSDK_OBJECT
    uint16 emeraldFrames;
    uint16 stoneFrames;
    uint16 powerFrames;
    TABLE(int32 powerColors[96],
          { 0xA00000, 0xB01820, 0xC03040, 0xD04860, 0xE06080, 0x4040C8, 0x5858C8, 0xE060E0, 0x7070C8, 0x8888C8, 0xA0A0C8, 0xC048C8,
            0xA030B0, 0x801898, 0x600080, 0x88B8E0, 0x80E0,   0x2890E0, 0x58A8E0, 0xB8D0E0, 0x208000, 0x409800, 0x60B000, 0x80C800,
            0xA0E000, 0xE0E0A0, 0xD0C878, 0xC0B050, 0xB09828, 0xA08000, 0x808080, 0x909090, 0xA0A0A0, 0xC0C0C0, 0xB0B0B0, 0xE8E8E8,
            0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
            0x5A0024, 0x7B0029, 0xB8001A, 0xDC0000, 0xFF4229, 0x300061, 0x420087, 0x7D7DFF, 0x6200C4, 0x840EF1, 0xAB49FF, 0x5C5CFF,
            0x3C3CEC, 0x2D2DB3, 0x251D8C, 0x00BFB3, 0x004875, 0x006091, 0x008EA8, 0x40F2AD, 0x005B00, 0x2B8200, 0x48B400, 0x62D100,
            0x90FC00, 0xF1F141, 0xD6C004, 0xB89800, 0x926700, 0x6F4900, 0x840909, 0xB41B0C, 0xE84200, 0xFF8C12, 0xFF5E0F, 0xE8E8E8,
            0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000 });
    int32 colorStorage[96];
    int32 colorStorage_HCZ[96];
    int32 colorStorage_CPZ[96];
};

// Entity Class
struct EntityDebris {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 gravityStrength;
    int32 rotSpeed;
    Vector2 scaleSpeed;
    int32 delay;
    Animator animator;
    Animator emeraldsAnimator;
    Animator stonesAnimator;
    Animator powerAnimator;
    Vector2 originPos;
    int32 radius;
};

// Object Struct
extern ObjectDebris *Debris;

// Standard Entity Events
void Debris_Update(void);
void Debris_LateUpdate(void);
void Debris_StaticUpdate(void);
void Debris_Draw(void);
void Debris_Create(void *data);
void Debris_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void Debris_EditorDraw(void);
void Debris_EditorLoad(void);
#endif
void Debris_Serialize(void);

// Extra Entity Functions

// 'entries' format: int32 count, [count] entries of type DebrisEntry
void Debris_CreateFromEntries(int32 aniFrames, int32 *entries, int32 animationID);
// 'entries' format: int32 count, [count] entries of type DebrisOffsetEntry
void Debris_CreateFromEntries_UseOffset(int32 aniFrames, int32 *entries);

void Debris_State_Move(void);
void Debris_State_Fall(void);
void Debris_State_FallAndFlicker(void);
void Debris_State_Rotate(void);

#endif //! OBJ_DEBRIS_H
