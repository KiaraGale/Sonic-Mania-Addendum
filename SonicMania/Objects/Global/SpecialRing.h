#ifndef OBJ_SPECIALRING_H
#define OBJ_SPECIALRING_H

#include "Game.h"

// Object Class
struct ObjectSpecialRing {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitbox;
    uint16 sfxSpecialRing;
    uint16 sfxSpecialWarp;
    uint16 modelIndex;
    uint16 sceneIndex;
    TABLE(int32 silverRingColors[6], { 0x000000, 0x606060, 0x909090, 0x000000, 0xC0C0C0, 0xE0E0E0 });
    TABLE(int32 hyperRingColors[6], { 0xEAEB00, 0xADD43A, 0x24B424, 0x6C8FB2, 0xBD89BD, 0xD8B424 });
    int32 colorStorage[6];
    int32 hyperColorState;
    int32 hyperTimer;
};

// Entity Class
struct EntitySpecialRing {
    RSDK_ENTITY
    StateMachine(state);
    int32 id;
    int32 planeFilter;
    int32 warpTimer;
    int32 sparkleRadius;
    Animator warpAnimator;
    int32 angleZ;
    int32 angleY;
    bool32 enabled;
    Matrix matTempRot;
    Matrix matTransform;
    Matrix matWorld;
    Matrix matNormal;
};

// Object Struct
extern ObjectSpecialRing *SpecialRing;

// Standard Entity Events
void SpecialRing_Update(void);
void SpecialRing_LateUpdate(void);
void SpecialRing_StaticUpdate(void);
void SpecialRing_Draw(void);
void SpecialRing_Create(void *data);
void SpecialRing_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void SpecialRing_EditorDraw(void);
void SpecialRing_EditorLoad(void);
#endif
void SpecialRing_Serialize(void);

// Extra Entity Functions
void SpecialRing_DebugDraw(void);
void SpecialRing_DebugSpawn(void);

void SpecialRing_State_Idle(void);
void SpecialRing_State_Flash(void);
void SpecialRing_State_Warp(void);

void SpecialRing_Draw_Sparkles(void);

#endif //! OBJ_SPECIALRING_H
