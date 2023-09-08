#ifndef OBJ_HPZEMERALD_H
#define OBJ_HPZEMERALD_H

#include "Game.h"

typedef enum {
    HPZEMERALD_MASTER,
    HPZEMERALD_EMERALD_LOW,
    HPZEMERALD_EMERALD_HIGH,
} HPZEmeraldTypes;

// Object Class
struct ObjectHPZEmerald {
    RSDK_OBJECT
    uint16 aniFrames;
    TABLE(int32 masterColors[11], { 0x202020, 0x302040, 0x202040, 0x303070, 0x203060, 0x204080, 0x206040, 0x308060, 0x40A080, 0x60C0A0, 0x80E0C0 });
    int32 colorStorage[11];
};

// Entity Class
struct EntityHPZEmerald {
    RSDK_ENTITY
    StateMachine(state); // unused
    uint8 type;
    bool32 solid;
    Vector2 startPos;
    Hitbox *hitbox;
    Animator emeraldAnimator;
    Animator overlayAnimator;
};

// Object Struct
extern ObjectHPZEmerald *HPZEmerald;

// Standard Entity Events
void HPZEmerald_Update(void);
void HPZEmerald_LateUpdate(void);
void HPZEmerald_StaticUpdate(void);
void HPZEmerald_Draw(void);
void HPZEmerald_Create(void *data);
void HPZEmerald_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void HPZEmerald_EditorDraw(void);
void HPZEmerald_EditorLoad(void);
#endif
void HPZEmerald_Serialize(void);

// Extra Entity Functions

#endif //! OBJ_HPZEMERALD_H
