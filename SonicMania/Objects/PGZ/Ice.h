#ifndef OBJ_ICE_H
#define OBJ_ICE_H

#include "Game.h"

#if MANIA_USE_PLUS
typedef enum {
    ICEANI_ICEBLOCK,
    ICEANI_PLAYERBLOCK,
    ICEANI_PLAYERGLINT,
    ICEANI_PILLARBLOCK,
    ICEANI_PILLARGLINT,
    ICEANI_SHARD,
    ICEANI_LARGEGLINT,
    ICEANI_SMALLGLINT,
    ICEANI_PIECE,
    ICEANI_RINGS,
    ICEANI_SONICIDLE,
    ICEANI_SONICLEFT,
    ICEANI_SONICRIGHT,
    ICEANI_SONICSHAKE,
    ICEANI_SUPERSONICIDLE,
    ICEANI_SUPERSONICLEFT,
    ICEANI_SUPERSONICRIGHT,
    ICEANI_SUPERSONICSHAKE,
    ICEANI_TAILSIDLE,
    ICEANI_TAILSLEFT,
    ICEANI_TAILSRIGHT,
    ICEANI_TAILSSHAKE,
    ICEANI_KNUXIDLE,
    ICEANI_KNUXLEFT,
    ICEANI_KNUXRIGHT,
    ICEANI_KNUXSHAKE,
    ICEANI_MIGHTYIDLE,
    ICEANI_MIGHTYLEFT,
    ICEANI_MIGHTYRIGHT,
    ICEANI_MIGHTYSHAKE,
    ICEANI_RAYIDLE,
    ICEANI_RAYLEFT,
    ICEANI_RAYRIGHT,
    ICEANI_RAYSHAKE,
    ICEANI_AMYIDLE,
    ICEANI_AMYLEFT,
    ICEANI_AMYRIGHT,
    ICEANI_AMYSHAKE,
    ICEANI_MIRACLESONICIDLE,
    ICEANI_MIRACLESONICLEFT,
    ICEANI_MIRACLESONICRIGHT,
    ICEANI_MIRACLESONICSHAKE,
    ICEANI_MIRACLETAILSIDLE,
    ICEANI_MIRACLETAILSLEFT,
    ICEANI_MIRACLETAILSRIGHT,
    ICEANI_MIRACLETAILSSHAKE,
    ICEANI_MIRACLEKNUXIDLE,
    ICEANI_MIRACLEKNUXLEFT,
    ICEANI_MIRACLEKNUXRIGHT,
    ICEANI_MIRACLEKNUXSHAKE,
    ICEANI_MIRACLEMIGHTYIDLE,
    ICEANI_MIRACLEMIGHTYLEFT,
    ICEANI_MIRACLEMIGHTYRIGHT,
    ICEANI_MIRACLEMIGHTYSHAKE,
    ICEANI_MIRACLERAYIDLE,
    ICEANI_MIRACLERAYLEFT,
    ICEANI_MIRACLERAYRIGHT,
    ICEANI_MIRACLERAYSHAKE,
    ICEANI_MIRACLEAMYIDLE,
    ICEANI_MIRACLEAMYLEFT,
    ICEANI_MIRACLEAMYRIGHT,
    ICEANI_MIRACLEAMYSHAKE
} IceAni;
#else
typedef enum {
    ICEANI_ICEBLOCK,
    ICEANI_PLAYERBLOCK,
    ICEANI_RINGS,
    ICEANI_SONIC,
    ICEANI_TAILS,
    ICEANI_KNUX,
    ICEANI_PILLARBLOCK,
    ICEANI_PLAYERGLINT,
    ICEANI_PILLARGLINT,
    ICEANI_SHARD,
    ICEANI_LARGEGLINT,
    ICEANI_SMALLGLINT,
    ICEANI_PIECE
} IceAni;
#endif

typedef enum {
    ICE_SIZE_LARGE,
    ICE_SIZE_SMALL,
} IceSizes;

typedef enum {
    ICE_BLOCK,
    ICE_1RING,
    ICE_3RINGS,
    ICE_5RINGS,
    ICE_SPIKES,
    ICE_ITEMBOX_RINGS,
    ICE_ITEMBOX_BLUESHIELD,
    ICE_ITEMBOX_BUBBLESHIELD,
    ICE_ITEMBOX_FIRESHIELD,
    ICE_ITEMBOX_LIGHTNINGSHIELD,
    ICE_ITEMBOX_INVINCIBILITY,
    ICE_ITEMBOX_SNEAKERS,
    ICE_ITEMBOX_1UP,
    ICE_ITEMBOX_EGGMAN,
    ICE_ITEMBOX_HYPERRING,
    ICE_ITEMBOX_SWAP,
    ICE_ITEMBOX_RANDOM,
    ICE_ITEMBOX_SUPER,
    ICE_SPRING,
} IceTypes;

typedef enum {
    ICE_CHILD_NONE,
    ICE_CHILD_PLAYER,
    ICE_CHILD_PILLAR,
    ICE_CHILD_SHARD,
} IceChildTypes;

// Object Class
struct ObjectIce {
    RSDK_OBJECT
    uint16 aniFrames;
    Hitbox hitboxPlayerBlockInner;
    Hitbox hitboxPlayerBlockOuter;
    int32 playerTimers[PLAYER_COUNT];
    uint16 sfxFreeze;
    uint16 sfxLedgeBreak;
    uint16 sfxWindowShatter;
    uint16 sfxStruggle;
    TABLE(int32 miracleColors[32],
        { 0x4A2644, 0x2C0656, 0xFCA6DA, 0xFEC8EB, 0xFEE1F5, 0x623259, 0x8A407D, 0xC67595, 0xE5A9B4, 0xFDD6D7, 0xFFF0F0, 0x490198, 0x8A01D0, 0xC53AE9, 0xEC9FEF, 0x58CA9F,
          0x76DBB6, 0x91EDCE, 0xBEF4E2, 0x8D4311, 0xC15A15, 0xE27F22, 0xEAA939, 0xEED253, 0xEBE67A, 0x6A21B5, 0x8735ED, 0x9066F4, 0x9E93F0, 0xF990C6, 0xFDBAE4, 0x942981 });
    int32 colorStorage[32];
};

// Entity Class
struct EntityIce {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    uint8 size;
    uint8 type;
    uint8 subType;
    uint8 subFlip;
    bool32 bottomSmash;
    bool32 knuxSmash;
    uint8 timer;
    uint8 animationID;
    Animator blockAnimator;
    Animator contentsAnimator;
    Animator altContentsAnimator;
    Animator glintAnimator;
    EntityPlayer *playerPtr;
    Vector2 playerMoveOffset;
    Vector2 contentsOffset;
    int32 glintTimer;
    Hitbox hitboxBlock;
    Hitbox hitboxFallCheck;
    Hitbox hitboxPlayerBlockCheck;
};

// Object Struct
extern ObjectIce *Ice;

// Standard Entity Events
void Ice_Update(void);
void Ice_LateUpdate(void);
void Ice_StaticUpdate(void);
void Ice_Draw(void);
void Ice_Create(void *data);
void Ice_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void Ice_EditorDraw(void);
void Ice_EditorLoad(void);
#endif
void Ice_Serialize(void);

// Extra Entity Functions
void Ice_VSSwap_CheckFrozen(void);

void Ice_FreezePlayer(EntityPlayer *player);
bool32 Ice_CheckPlayerBlockSmashH(void);
bool32 Ice_CheckPlayerBlockSmashV(void);
void Ice_PlayerState_Frozen(void);
void Ice_ShatterGenerator(int32 count, int32 sizeX, int32 sizeY, int32 velX, int32 velY, int32 canBreak);
void Ice_FullShatter(EntityPlayer *player, int32 velX, int32 velY);
void Ice_BreakPlayerBlock(EntityPlayer *player);
EntityItemBox *Ice_Shatter(EntityIce *ice, int32 velX, int32 velY);
void Ice_TimeOver_CheckFrozen(void);

void Ice_UpdateBlockGravity(void);
void Ice_State_IceBlock(void);
void Ice_State_StartBlockFall(void);
void Ice_State_BlockFallDelay(void);
void Ice_State_IceBlockFall(void);
void Ice_State_PlayerBlock(void);
void Ice_State_Shard(void);

void Ice_Draw_IceBlock(void);
void Ice_Draw_PlayerBlock(void);
void Ice_Draw_Pillar(void);
void Ice_Draw_Shard(void);

#endif //! OBJ_ICE_H
