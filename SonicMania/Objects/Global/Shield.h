#ifndef OBJ_SHIELD_H
#define OBJ_SHIELD_H

#include "Game.h"

typedef enum {
    SHIELDANI_BLUE,
    SHIELDANI_FIRE,
    SHIELDANI_FIREATTACK,
    SHIELDANI_LIGHTNING,
    SHIELDANI_LIGHTINGSPARK,
    SHIELDANI_BUBBLEADD,
    SHIELDANI_BUBBLE,
    SHIELDANI_BUBBLEATTACKDADD,
    SHIELDANI_BUBBLEATTACKD,
    SHIELDANI_BUBBLEATTACKUPADD,
    SHIELDANI_INSTA,
    SHIELDANI_SUPERINSTA,
    SHIELDANI_MIRACLEINSTA,
} ShieldAniIDs;

// Object Class
struct ObjectShield {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxBlueShield;
    uint16 sfxBubbleShield;
    uint16 sfxFireShield;
    uint16 sfxLightningShield;
    uint16 sfxInstaShield;
    uint16 sfxBubbleBounce;
    uint16 sfxFireDash;
    uint16 sfxLightningJump;
    TABLE(color shieldPalette_Knux[6], { 0x404040, 0x606060, 0x808080, 0xA0A0A0, 0xB0B0B0, 0xD0D0D0 });
    int32 colorStorage[6];
};

// Entity Class
struct EntityShield {
    RSDK_ENTITY
    EntityPlayer *player;
    StateMachine(state);
    int32 type;
    int32 timer;
    int32 frameFlags;
    bool32 forceVisible;
    Animator shieldAnimator;
    Animator fxAnimator;
    Hitbox *outerbox;
};

// Object Struct
extern ObjectShield *Shield;

// Standard Entity Events
void Shield_Update(void);
void Shield_LateUpdate(void);
void Shield_StaticUpdate(void);
void Shield_Draw(void);
void Shield_Create(void *data);
void Shield_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void Shield_EditorDraw(void);
void Shield_EditorLoad(void);
#endif
void Shield_Serialize(void);

// Extra Entity Functions
void Shield_State_Default(void);
void Shield_State_BubbleDrop(void);
void Shield_State_BubbleBounced(void);
void Shield_State_FireDash(void);
void Shield_State_LightningSparks(void);
void Shield_State_Insta(void);
bool32 Shield_State_Reflect(EntityShield *shield, void *p);
bool32 Shield_CheckCollisionTouch(EntityShield *shield, void *e, Hitbox *entityHitbox);

#endif //! OBJ_SHIELD_H
