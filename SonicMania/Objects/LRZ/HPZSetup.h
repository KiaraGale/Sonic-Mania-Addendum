#ifndef OBJ_HPZSETUP_H
#define OBJ_HPZSETUP_H

#include "Game.h"

// Object Class
struct ObjectHPZSetup {
	RSDK_OBJECT
};

// Entity Class
struct EntityHPZSetup {
	RSDK_ENTITY
};

// Object Struct
extern ObjectHPZSetup* HPZSetup;

// Standard Entity Events
void HPZSetup_Update(void);
void HPZSetup_LateUpdate(void);
void HPZSetup_StaticUpdate(void);
void HPZSetup_Draw(void);
void HPZSetup_Create(void *data);
void HPZSetup_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void HPZSetup_EditorDraw(void);
void HPZSetup_EditorLoad(void);
#endif
void HPZSetup_Serialize(void);

#endif //! OBJ_HPZSETUP_H
