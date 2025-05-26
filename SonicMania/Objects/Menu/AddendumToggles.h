#ifndef OBJ_ADDENDUMTOGGLES_H
#define OBJ_ADDENDUMTOGGLES_H

#include "Game.h"

// Object Class
struct ObjectAddendumToggles {
    RSDK_OBJECT
};

// Entity Class
struct EntityAddendumToggles {
    RSDK_ENTITY
};

// Object Struct
extern ObjectAddendumToggles *AddendumToggles;

// Standard Entity Events
void AddendumToggles_Update(void);
void AddendumToggles_LateUpdate(void);
void AddendumToggles_StaticUpdate(void);
void AddendumToggles_Draw(void);
void AddendumToggles_Create(void *data);
void AddendumToggles_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void AddendumToggles_EditorDraw(void);
void AddendumToggles_EditorLoad(void);
#endif
void AddendumToggles_Serialize(void);

// Extra Entity Functions
void AddendumToggles_Initialize(void);
void AddendumToggles_MenuButton_ActionCB(void);
void AddendumToggles_SetToggleButtons_Gameplay(void);
void AddendumToggles_GetTogglesFromSelection_Gameplay(void);
void AddendumToggles_SetToggleButtons_Style(void);
void AddendumToggles_GetTogglesFromSelection_Style(void);
void AddendumToggles_SetToggleButtons_Music(void);
void AddendumToggles_GetTogglesFromSelection_Music(void);
void AddendumToggles_SetToggleButtons_Multiplayer(void);
void AddendumToggles_GetTogglesFromSelection_Multiplayer(void);
void AddendumToggles_SaveTogglesCB(bool32 success);
void AddendumToggles_ChangeMenuSpriteStyle(void);

#endif // OBJ_ADDENDUMTOGGLES_H