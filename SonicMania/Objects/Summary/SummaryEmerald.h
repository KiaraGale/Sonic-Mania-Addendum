#ifndef OBJ_SUMMARYEMERALD_H
#define OBJ_SUMMARYEMERALD_H

#include "Game.h"

#if MANIA_USE_PLUS

typedef enum {
    SUMMARY_GEMTYPE_EMERALD,
    SUMMARY_GEMTYPE_TIMESTONE,
} SummaryGemType;

// Object Class
struct ObjectSummaryEmerald {
    RSDK_OBJECT
    uint16 aniFrames;
    TABLE(int32 timeStoneColors[36],
          { 0x5A0024, 0x7B0029, 0xB8001A, 0xDC0000, 0xFF4229, 0x300061, 0x420087, 0x7D7DFF, 0x6200C4, 0x840EF1, 0xAB49FF, 0x5C5CFF,
            0x3C3CEC, 0x2D2DB3, 0x251D8C, 0x00BFB3, 0x004875, 0x006091, 0x008EA8, 0x40F2AD, 0x005B00, 0x2B8200, 0x48B400, 0x62D100,
            0x90FC00, 0xF1F141, 0xD6C004, 0xB89800, 0x926700, 0x6F4900, 0x840909, 0xB41B0C, 0xE84200, 0xFF8C12, 0xFF5E0F, 0xE8E8E8 });
};

// Entity Class
struct EntitySummaryEmerald {
    RSDK_ENTITY
    int32 type;
    int32 emeraldID;
    int32 timeStoneID;
    Animator animator;
};

// Object Struct
extern ObjectSummaryEmerald *SummaryEmerald;

// Standard Entity Events
void SummaryEmerald_Update(void);
void SummaryEmerald_LateUpdate(void);
void SummaryEmerald_StaticUpdate(void);
void SummaryEmerald_Draw(void);
void SummaryEmerald_Create(void *data);
void SummaryEmerald_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void SummaryEmerald_EditorDraw(void);
void SummaryEmerald_EditorLoad(void);
#endif
void SummaryEmerald_Serialize(void);

// Extra Entity Functions
#endif

#endif //! OBJ_SUMMARYEMERALD_H
