#ifndef OBJ_SUPERSPARKLE_H
#define OBJ_SUPERSPARKLE_H

#include "Game.h"

// Object Class
struct ObjectSuperSparkle {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 superFrames;
};

// Entity Class
struct EntitySuperSparkle {
    RSDK_ENTITY
    StateMachine(state);
    EntityPlayer *player;
    int32 timer;
    bool32 canSpawnSparkle;
    Animator sparkleAnimator;
    Animator sparkleAddAnimator;
};

// Object Struct
extern ObjectSuperSparkle *SuperSparkle;

// Standard Entity Events
void SuperSparkle_Update(void);
void SuperSparkle_LateUpdate(void);
void SuperSparkle_StaticUpdate(void);
void SuperSparkle_Draw(void);
void SuperSparkle_Create(void *data);
void SuperSparkle_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void SuperSparkle_EditorDraw(void);
void SuperSparkle_EditorLoad(void);
#endif
void SuperSparkle_Serialize(void);

// Extra Entity Functions
void SuperSparkle_State_PlayerSuper(void);
void SuperSparkle_State_PlayerHyper(void);

#endif //! OBJ_SUPERSPARKLE_H
