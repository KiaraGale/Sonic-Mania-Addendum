#ifndef OBJ_SUPERFLICKY_H
#define OBJ_SUPERFLICKY_H

#include "Game.h"

#define SUPER_FLICKY_COUNT (4);

struct ObjectSuperFlicky {
    RSDK_OBJECT
};

struct EntitySuperFlicky {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(storedState);
    int32 targetPlayerID;
    Vector2 startPos;
    int32 targetSlot;
    int32 flickyID;
    Vector2 targetVelocity;
    Vector2 targetPosition;
    int32 attackDelay;
    int32 attackListPos;
    int32 superBlendState;
    int32 superBlendTimer;
    uint8 superPaletteIndex;
};

extern ObjectSuperFlicky *SuperFlicky;

#endif // OBJ_SUPERFLICKY_H