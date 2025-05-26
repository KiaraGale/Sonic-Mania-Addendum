#ifndef OBJ_MOSQUI_H
#define OBJ_MOSQUI_H

#include "Game.h"

typedef enum {
	MOSQUI_MOVELEFT,
	MOSQUI_MOVERIGHT,
	MOSQUI_TURNDOWN,
	MOSQUI_DART,
	MOSQUI_BLANK,
	MOSQUI_RESTORE,
} MosquiMovementStates;

typedef enum {
	MOSQUI_NORMAL,
	MOSQUI_BROKEN,
} MosquiQualityStates;

// Object Class
struct ObjectMosqui {
	RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxBadnik;
    uint16 sfxJab;
};

// Entity Class
struct EntityMosqui {
	RSDK_ENTITY
    StateMachine(state);
	int32 turnTimer;
    int32 timer;
    Vector2 startPos;
    uint8 startDir;
    bool32 wasTurning;
    Animator animator;
    bool32 broken;
};

// Object Struct
extern ObjectMosqui *Mosqui;

// Standard Entity Events
void Mosqui_Update(void);
void Mosqui_LateUpdate(void);
void Mosqui_StaticUpdate(void);
void Mosqui_Draw(void);
void Mosqui_Create(void *data);
void Mosqui_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void Mosqui_EditorDraw(void);
void Mosqui_EditorLoad(void);
#endif
void Mosqui_Serialize(void);

// Extra Entity Functions
void Mosqui_DebugDraw(void);
void Mosqui_DebugSpawn(void);

void Mosqui_CheckOffScreen(void);
void Mosqui_CheckPlayerCollisions(void);

// States
void Mosqui_State_Init(void);
void Mosqui_State_Move(void);
void Mosqui_State_Idle(void);
void Mosqui_State_Turn(void);
void Mosqui_State_PointDown(void);
void Mosqui_State_Attack(void);
void Mosqui_State_Stuck(void);

#endif // OBJ_MOSQUI_H