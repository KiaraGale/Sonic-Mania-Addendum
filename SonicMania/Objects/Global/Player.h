#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include "Game.h"

// Helper Constants
#define PLAYER_PALETTE_INDEX_SONIC_OLD (2) // sonic's original palette indices, here for legacy reasons. Only exists in a few places in the final game.

#define PLAYER_PALETTE_INDEX_SONIC     (64)
#define PLAYER_PALETTE_INDEX_TAILS     (70)
#define PLAYER_PALETTE_INDEX_KNUX      (80)
#if MANIA_USE_PLUS
#define PLAYER_PALETTE_INDEX_MIGHTY (96)
#define PLAYER_PALETTE_INDEX_RAY    (112)
#define PLAYER_PALETTE_INDEX_AMY    (86)
#endif

#define PLAYER_PRIMARY_COLOR_COUNT (6)

// Helper Enums
typedef enum {
    ANI_IDLE,
    ANI_BORED_1,
    ANI_BORED_2,
    ANI_LOOK_UP,
    ANI_CROUCH,
    ANI_WALK,
    ANI_AIR_WALK,
    ANI_JOG,
    ANI_RUN,
    ANI_DASH,
    ANI_JUMP,
    ANI_SPRING_TWIRL,
    ANI_SPRING_DIAGONAL,
    ANI_SKID,
    ANI_SKID_TURN,
    ANI_SPINDASH,
    ANI_ABILITY_0,
    ANI_PUSH,
    ANI_HURT,
    ANI_DIE,
    ANI_DROWN,
    ANI_BALANCE_1,
    ANI_BALANCE_2,
    ANI_SPRING_CS,
    ANI_STAND_CS,
    ANI_FAN,
    ANI_VICTORY,
    ANI_OUTTA_HERE,
    ANI_HANG,
    ANI_HANG_MOVE,
    ANI_POLE_SWING_H,
    ANI_POLE_SWING_V,
    ANI_SHAFT_SWING,
    ANI_TURNTABLE,
    ANI_TWISTER,
    ANI_SPIRAL_RUN,
    ANI_STICK,
    ANI_PULLEY_HOLD,
    ANI_SHIMMY_IDLE,
    ANI_SHIMMY_MOVE,
    ANI_BREATHE,
    ANI_BUBBLE,
    ANI_RIDE,
    ANI_CLING,
    ANI_BUNGEE,
    ANI_TWIST_RUN,
#if MANIA_USE_PLUS
    ANI_FLUME,
#endif
    ANI_TRANSFORM,
    ANI_ABILITY_1,
    ANI_ABILITY_2,
    ANI_ABILITY_3,
    ANI_ABILITY_4,
    ANI_ABILITY_5,
    ANI_ABILITY_6,
    ANI_ABILITY_7,

    // Sonic Ability Anim Aliases
    ANI_DROPDASH = ANI_ABILITY_0,
    ANI_PEELOUT  = ANI_ABILITY_1,

    // Tails Ability Anim Aliases
    ANI_FLY            = ANI_ABILITY_1,
    ANI_FLY_TIRED      = ANI_ABILITY_2,
    ANI_FLY_LIFT       = ANI_ABILITY_3,
    ANI_FLY_LIFT_TIRED = ANI_ABILITY_4,
    ANI_SWIM           = ANI_ABILITY_5,
    ANI_SWIM_TIRED     = ANI_ABILITY_6,
    ANI_SWIM_LIFT      = ANI_ABILITY_7,

    // Knux Ability Anim Aliases
    ANI_LEDGE_PULL_UP = ANI_ABILITY_0,
    ANI_GLIDE         = ANI_ABILITY_1,
    ANI_GLIDE_DROP    = ANI_ABILITY_2,
    ANI_GLIDE_LAND    = ANI_ABILITY_3,
    ANI_GLIDE_SLIDE   = ANI_ABILITY_4,
    ANI_CLIMB_IDLE    = ANI_ABILITY_5,
    ANI_CLIMB_UP      = ANI_ABILITY_6,
    ANI_CLIMB_DOWN    = ANI_ABILITY_7,

#if MANIA_USE_PLUS
    // Mighty Ability Anim Aliases
    ANI_HAMMERDROP = ANI_ABILITY_0,
    ANI_UNSPIN     = ANI_ABILITY_1,

    // Ray Ability Anim Aliases
    ANI_HANG2    = ANI_ABILITY_0,
    ANI_FLY_UP   = ANI_ABILITY_1,
    ANI_FLY_DOWN = ANI_ABILITY_2,

    // Amy Ability Anim Aliases
    ANI_HAMMER_HIT    = ANI_ABILITY_1,
    ANI_SPIN_JUMP     = ANI_ABILITY_2,
    ANI_FREE_FALL     = ANI_ABILITY_3,
    ANI_HELI_HAMMER   = ANI_ABILITY_4,
    ANI_DASH_NOHAMMER = ANI_ABILITY_5,
    ANI_CDSPINDASH    = ANI_ABILITY_6,
#endif
} PlayerAnimationIDs;

// for "characterID" in editor
typedef enum {
    PLAYER_CHAR_NONE,
    PLAYER_CHAR_SONIC,
    PLAYER_CHAR_TAILS,
    PLAYER_CHAR_SONIC_TAILS,
    PLAYER_CHAR_KNUX,
    PLAYER_CHAR_AMY,
    PLAYER_CHAR_SONIC_KNUX,
    PLAYER_CHAR_TAILS_KNUX,
    PLAYER_CHAR_SONIC_TAILS_KNUX,
} PlayerCharacterIDS;

typedef enum {
    SHIELD_NONE,
    SHIELD_BLUE,
    SHIELD_BUBBLE,
    SHIELD_FIRE,
    SHIELD_LIGHTNING,
} ShieldTypes;

typedef enum {
    PLAYER_DEATH_NONE,
    PLAYER_DEATH_DIE_USESFX,
    PLAYER_DEATH_DIE_NOSFX,
    PLAYER_DEATH_DROWN,
} DeathTypes;

typedef enum {
    PLAYER_HURT_NONE,
    PLAYER_HURT_HASSHIELD,
    PLAYER_HURT_RINGLOSS,
    PLAYER_HURT_DIE,
} HurtTypes;

typedef enum {
    SUPERSTATE_NONE,
    SUPERSTATE_FADEIN,
    SUPERSTATE_SUPER,
    SUPERSTATE_FADEOUT,
    SUPERSTATE_DONE,
} SuperStates;

// Object Class
#if MANIA_USE_PLUS
struct ObjectPlayer {
    RSDK_OBJECT
    TABLE(int32 sonicPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 tailsPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 knuxPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x60000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x30000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x70000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x40000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x60000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x30000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x70000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x40000, -0x20000 });
    TABLE(int32 mightyPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 rayPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 miraclePhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x14000, 0x600, 0x90000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0xC000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xE0000, 0x3C00, 0x8000, 0x1A00, 0x14000, 0x600, 0x90000, -0x40000, 0xB0000, 0x1400, 0x2400, 0x600, 0xC000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 miracleKnuxPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x60000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x30000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x14000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0xC000, 0x300, 0x40000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x60000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x30000, -0x20000,
            0xE0000, 0x3C00, 0x8000, 0x1A00, 0x14000, 0x600, 0x80000, -0x40000, 0xB0000, 0x1400, 0x2400, 0x600, 0xC000, 0x300, 0x40000, -0x20000 });
    TABLE(color superPalette_Sonic[18], { 0x000080, 0x0038C0, 0x0068F0, 0x1888F0, 0x30A0F0, 0x68D0F0, 0xF0C001, 0xF0D028, 0xF0E040, 0xF0E860,
                                          0xF0E898, 0xF0E8D0, 0xF0D898, 0xF0E0B0, 0xF0E8C0, 0xF0F0D8, 0xF0F0F0, 0xF0F0F8 });
    TABLE(color superPalette_Tails[18], { 0x800801, 0xB01801, 0xD05001, 0xE07808, 0xE89008, 0xF0A801, 0x800801, 0xB01801, 0xD05001, 0xE07808,
                                          0xE89008, 0xF0A801, 0xF03830, 0xF06848, 0xF09860, 0xF0B868, 0xF0C870, 0xF0D870 });
    TABLE(color superPalette_Knux[18], { 0x580818, 0x980130, 0xD00840, 0xE82858, 0xF06080, 0xF08088, 0xF33F90, 0xF26496, 0xF787A5, 0xF99FAF, 0xFBB7BF,
                                         0xFDCECE, 0xF33F90, 0xF26496, 0xF787A5, 0xF99FAF, 0xFBB7BF, 0xFDCECE });
    TABLE(color superPalette_Mighty[18], { 0x681818, 0x942424, 0xBB2525, 0xDF3434, 0xF2604A, 0xFB916A, 0xB81919, 0xE43A3A, 0xF75F5F, 0xFC8C7E,
                                           0xFBB8A2, 0xFED0B4, 0xB81919, 0xE43A3A, 0xF75F5F, 0xFC8C7E, 0xFBB8A2, 0xFED0B4 });
    TABLE(color superPalette_Ray[21], { 0x7C4616, 0xA06800, 0xB88810, 0xD0A810, 0xE0C020, 0xE8D038, 0xF0E078, 0x7C4616, 0xA06800, 0xB88810, 0xD0A810,
                                        0xE0C020, 0xE8D038, 0xF0E078, 0xBA7600, 0xE0A801, 0xF0C820, 0xF0E820, 0xF0F040, 0xF0F068, 0xF0F0B8 });
    TABLE(color superPalette_Amy[18], { 0x64036E, 0x980F8C, 0xC02AAA, 0xEA51B5, 0xF678D0, 0xFABBE3, 0xEC4F41, 0xF36F62, 0xF6887E, 0xF79F97, 0xFAB1AD,
                                        0xFDCDC9, 0xF67F74, 0xF8948B, 0xFAAFA8, 0xFCC4BF, 0xFEDEDC, 0xFEEEEB });
    TABLE(color miraclePalette_Sonic[18], { 0x000080, 0x0038C0, 0x0068F0, 0x1888F0, 0x30A0F0, 0x68D0F0, 0xBC34A3, 0xD94AB1, 0xF16AC2, 0xFF88CA,
                                            0xFEB6DE, 0xFFE0F1, 0xEE5DC1, 0xF278C7, 0xF990CF, 0xFFB2D8, 0xFFD6ED, 0xFFF0F8 });
    TABLE(color miraclePalette_Tails[18], { 0x800801, 0xB01801, 0xD05001, 0xE07808, 0xE89008, 0xF0A801, 0x7534BC, 0x9A4AD9, 0xC16AF1, 0xDC90F9,
                                            0xEDAAFD, 0xF6C3FE, 0xAF5DEE, 0xC67DF7, 0xE0A3FA, 0xEFBDFF, 0xF7D1FF, 0xFDEBFF });
    TABLE(color miraclePalette_Knux[18], { 0x580818, 0x980130, 0xD00840, 0xE82858, 0xF06080, 0xF08088, 0x3AB030, 0x3FD63D, 0x61EA69, 0x86F394,
                                           0xAAF9B7, 0xD3FDDE, 0x37CA2B, 0x5DEA60, 0x90F499, 0xB7FAC2, 0xD8FDE0, 0xEBFFF0 });
    TABLE(color miraclePalette_Mighty[18], { 0x681818, 0x942424, 0xBB2525, 0xDF3434, 0xF2604A, 0xFB916A, 0xBC6634, 0xD9884A, 0xF1AB6A, 0xFFCA8A,
                                             0xFEE2B4, 0xFFF6E0, 0xED9E54, 0xF2B378, 0xF9C890, 0xFFE1B2, 0xFFEFD6, 0xFFFBF0 });
    TABLE(color miraclePalette_Ray[21], { 0x7C4616, 0xA06800, 0xB88810, 0xD0A810, 0xE0C020, 0xE8D038, 0xF0E078, 0x8A001E, 0xBC3448, 0xD94A56, 0xF16A6C,
                                          0xFF8E8A, 0xFEB2AA, 0xFFE6E0, 0xCF0C36, 0xEE5D73, 0xF27883, 0xF99091, 0xFFB5B2, 0xFFD1CC, 0xFFEDEB });
    TABLE(color miraclePalette_Amy[18], { 0x64036E, 0x980F8C, 0xC02AAA, 0xEA51B5, 0xF678D0, 0xFABBE3, 0x519EDB, 0x5DB9E9, 0x75CEF0, 0x8EE0F5,
                                          0xA8F1FA, 0xCAFCFC, 0x5DB3EE, 0x78CCF2, 0x90DCF9, 0xB2EFFF, 0xD6FBFF, 0xF5FFFF });
    TABLE(color superPalette_Sonic_HCZ[18], { 0x200888, 0x3020C8, 0x3840F0, 0x4070F0, 0x4098F0, 0x40C0F0, 0x80C882, 0x6FDC8B, 0x7FE8A5, 0x87EEBA,
                                              0x8CF0D0, 0xA0F0D8, 0x5EE495, 0x4CEE9C, 0x5EF2B4, 0x75F2C6, 0x95F0D2, 0xA7F1DB });
    TABLE(color superPalette_Tails_HCZ[18], { 0x632F38, 0x7E5051, 0x8E6561, 0x9E776B, 0xAB877C, 0xBA9B90, 0x632F38, 0x7E5051, 0x8E6561, 0x9E776B,
                                              0xAB877C, 0xBA9B90, 0xBC6B78, 0xC98689, 0xCB9F97, 0xD4B0A6, 0xDFB9B1, 0xE4C2B9 });
    TABLE(color superPalette_Knux_HCZ[18], { 0x1C1359, 0x381588, 0x5F1FA8, 0x8828C0, 0xA048C0, 0xB868C8, 0x1C1359, 0x381588, 0x5F1FA8, 0x8828C0,
                                             0xA048C0, 0xB868C8, 0x664DC2, 0x7C60D2, 0x9768E0, 0xC070EF, 0xD086EB, 0xDE9CED });
    TABLE(color superPalette_Mighty_HCZ[18], { 0x301A76, 0x502098, 0x7028B0, 0x8048C8, 0x8362D8, 0x8D87DB, 0x301A76, 0x502098, 0x7028B0, 0x8048C8,
                                               0x8362D8, 0x8D87DB, 0x6429B5, 0x7250C8, 0x8666D8, 0x9890E0, 0xB4B9F1, 0xC6DFF0 });
    TABLE(color superPalette_Ray_HCZ[21], { 0x3D4285, 0x406090, 0x488890, 0x68A880, 0x70C080, 0x68D080, 0x50E888, 0x3D4285, 0x406090, 0x488890, 0x68A880,
                                            0x70C080, 0x68D080, 0x50E888, 0x5F8F75, 0x74B48F, 0x78D095, 0x70E58F, 0x78F0A3, 0x90F0C0, 0xA8F0E0 });
    TABLE(color superPalette_Amy_HCZ[18], { 0x3D1395, 0x6519B9, 0x8B38C1, 0xA958C9, 0xB278DC, 0xB598EA, 0x965DB7, 0xB171C4, 0xC287C6, 0xCC97C8,
                                            0xDAA7CE, 0xDBB8D2, 0xB77DC0, 0xCB90CC, 0xD2A4D0, 0xD8B7D2, 0xE3CEDD, 0xE7DCE3 });
    TABLE(color miraclePalette_Sonic_HCZ[18], { 0x200888, 0x3020C8, 0x3840F0, 0x4070F0, 0x4098F0, 0x40C0F0, 0x6858CF, 0x8064D2, 0x9F74D5, 0xB88FD3,
                                                0xCAB9DB, 0xD9D6DD, 0x916BD4, 0xA77ED3, 0xB996D4, 0xCAB8DA, 0xD6D2DC, 0xDCDBDE });
    TABLE(color miraclePalette_Tails_HCZ[18], { 0x632F38, 0x7E5051, 0x8E6561, 0x9E776B, 0xAB877C, 0xBA9B90, 0x5559B5, 0x6B6ACB, 0x907FDB, 0xB792E7,
                                                0xD2A3ED, 0xDBB5F2, 0x7B72CC, 0x9A86DE, 0xC79EEB, 0xD3B0F2, 0xE1C5F2, 0xE5D1E7 });
    TABLE(color miraclePalette_Knux_HCZ[18], { 0x1C1359, 0x381588, 0x5F1FA8, 0x8828C0, 0xA048C0, 0xB868C8, 0x3198BA, 0x39AFBD, 0x59C7C7, 0x76D2D8,
                                               0x96D9DF, 0xBADDDF, 0x39B5BD, 0x69C9CA, 0x82D5DB, 0x9EDADF, 0xB8E1E1, 0xC6E8E8 });
    TABLE(color miraclePalette_Mighty_HCZ[18], { 0x301A76, 0x502098, 0x7028B0, 0x8048C8, 0x8362D8, 0x8D87DB, 0x69828D, 0x88A09C, 0xA0B79D, 0xB8CEA5,
                                                 0xC2D9BA, 0xD1E3C9, 0x9BA994, 0xAAB9A1, 0xB6CAA8, 0xC3D9B9, 0xCFE2CE, 0xD2E8E8 });
    TABLE(color miraclePalette_Ray_HCZ[21], { 0x3D4285, 0x406090, 0x488890, 0x68A880, 0x70C080, 0x68D080, 0x50E888, 0x5B3B90, 0x7450A4, 0x9269B8, 0xB37EB4,
                                              0xC896BD, 0xD8B0C6, 0xE1CFD4, 0x7D50A4, 0x9666B5, 0xB37DBD, 0xC497BD, 0xCEACC4, 0xDDC6CF, 0xD8DDE1 });
    TABLE(color miraclePalette_Amy_HCZ[18], { 0x64036E, 0x980F8C, 0xC02AAA, 0xEA51B5, 0xF678D0, 0xFABBE3, 0x4A72D8, 0x5786E4, 0x679EE1, 0x83B8E5,
                                              0x9ACDE9, 0xBADEEB, 0x5F92E6, 0x72A6F0, 0x88B8E9, 0xA2CDED, 0xB6DCF0, 0xBFE5EC });
    TABLE(color superPalette_Sonic_CPZ[18], { 0x4000D8, 0x5800E0, 0x6810E0, 0x8020E0, 0xA020E0, 0xC040E0, 0xE04880, 0xE06890, 0xE078A8, 0xE078D8,
                                              0xE080E0, 0xE080E0, 0xE080B0, 0xE080B0, 0xE080C0, 0xE080C0, 0xE080E0, 0xE080E0 });
    TABLE(color superPalette_Tails_CPZ[18], { 0xC80180, 0xD1057A, 0xE00180, 0xE81088, 0xE83098, 0xE84898, 0xC80180, 0xD1057A, 0xE00180, 0xE81088,
                                              0xE83098, 0xE84898, 0xD8007C, 0xE61B84, 0xE14D97, 0xE961A4, 0xE871B7, 0xE77FD2 });
    TABLE(color superPalette_Knux_CPZ[18], { 0xA90087, 0xB00178, 0xC00190, 0xD001B0, 0xE001E0, 0xE820E8, 0xA90087, 0xB00178, 0xC00190, 0xD001B0,
                                             0xE001E0, 0xE820E8, 0xC60095, 0xDA00B4, 0xEC0CD4, 0xF449E6, 0xF45EE8, 0xE080E0 });
    TABLE(color superPalette_Mighty_CPZ[18], { 0xA90087, 0xCC048D, 0xD6049A, 0xDD03AE, 0xDC00CA, 0xE001E0, 0xA90087, 0xCC048D, 0xD6049A, 0xDD03AE,
                                               0xDC00CA, 0xE001E0, 0xB80180, 0xD1009D, 0xDC00C4, 0xE001E0, 0xE040E0, 0xE078E0 });
    TABLE(color superPalette_Ray_CPZ[21], { 0xD80180, 0xE00180, 0xE00190, 0xE02898, 0xE048A8, 0xE060B8, 0xE078E0, 0xD80180, 0xE00180, 0xE00190, 0xE02898,
                                            0xE048A8, 0xE060B8, 0xE078E0, 0xE00180, 0xE23286, 0xE05888, 0xE17793, 0xE080A8, 0xE080D8, 0xE080E0 });
    TABLE(color superPalette_Amy_CPZ[18], { 0xA00180, 0xD80188, 0xE001A0, 0xE001B0, 0xE000D5, 0xEF00EF, 0xC3007C, 0xD20186, 0xDB16AA, 0xE12DB5,
                                            0xDF4ABB, 0xD964C8, 0xD11BAA, 0xD443B6, 0xD758C2, 0xDB72D0, 0xE07FD8, 0xE080E0 });
    TABLE(color miraclePalette_Sonic_CPZ[18], { 0x4000D8, 0x5800E0, 0x6810E0, 0x8020E0, 0xA020E0, 0xC040E0, 0xB700B4, 0xC90DC0, 0xD50ECD, 0xDC32D3,
                                                0xDC54D9, 0xD874D7, 0xDC16D4, 0xE036D9, 0xE94BE0, 0xDF6ADC, 0xDF78DE, 0xE080E0 });
    TABLE(color miraclePalette_Tails_CPZ[18], { 0xC80180, 0xD1057A, 0xE00180, 0xE81088, 0xE83098, 0xE84898, 0x9000C7, 0xA800D8, 0xBF00E5, 0xCD00E9,
                                                0xD736E9, 0xDD5DEA, 0xB200E1, 0xC000E5, 0xD328E9, 0xD957EA, 0xE072EB, 0xE080E0 });
    TABLE(color miraclePalette_Knux_CPZ[18], { 0xA90087, 0xB00178, 0xC00190, 0xD001B0, 0xE001E0, 0xE820E8, 0x8C5E85, 0x9A6D8E, 0xAD7AA9, 0xBC80BE,
                                               0xCC85CD, 0xD388D9, 0x99718E, 0xAA7BA6, 0xC282C2, 0xCD84D4, 0xD785DE, 0xE080E0 });
    TABLE(color miraclePalette_Mighty_CPZ[18], { 0xA90087, 0xCC048D, 0xD6049A, 0xDD03AE, 0xDC00CA, 0xE001E0, 0xB12E78, 0xBD4D8A, 0xC55A99, 0xC771A4,
                                                 0xCD85B7, 0xD586CB, 0xC04787, 0xC35B9B, 0xCF6FAD, 0xD47DBA, 0xD58AC8, 0xE080E0 });
    TABLE(color miraclePalette_Ray_CPZ[21], { 0xD80180, 0xE00180, 0xE00190, 0xE02898, 0xE048A8, 0xE060B8, 0xE078E0, 0xD90076, 0xDE107F, 0xE3218A, 0xE23391,
                                              0xDE4B9B, 0xE365B2, 0xE17AD4, 0xD92E8B, 0xE13894, 0xE5459B, 0xE15DA5, 0xDD6BB1, 0xDF78CA, 0xE080E0 });
    TABLE(color miraclePalette_Amy_CPZ[18], { 0x64036E, 0x980F8C, 0xC02AAA, 0xEA51B5, 0xF678D0, 0xFABBE3, 0xA93DFF, 0xB24BFF, 0xC15EFF, 0xD069FF,
                                              0xD672FF, 0xDE79F0, 0xBA4EFF, 0xCD5AF7, 0xDC68FE, 0xE36DF5, 0xDD7AE1, 0xE080E0 });
    bool32 cantSwap;
    int32 playerCount;
    uint16 upState;
    uint16 downState;
    uint16 leftState;
    uint16 rightState;
    uint16 jumpPressState;
    uint16 jumpHoldState;
    int32 nextLeaderPosID;
    int32 lastLeaderPosID;
    Vector2 leaderPositionBuffer[16];
    Vector2 targetLeaderPosition;
    int32 autoJumpTimer;
    int32 respawnTimer;
    int32 aiInputSwapTimer;
    bool32 disableP2KeyCheck;
    int32 rings;
    STATIC(int32 ringExtraLife, 100);
    int32 powerups; // unused
    STATIC(int32 savedLives, 3);
    int32 savedScore;
    STATIC(int32 savedScore1UP, 50000);
    uint16 sonicFrames;
    uint16 superFrames;
    uint16 miracleFrames;
    uint16 tailsFrames;
    uint16 superTailsFrames;
    uint16 tailsTailsFrames;
    uint16 superTailsTailsFrames;
    uint16 miracleTailsFrames;
    uint16 miracleTailsTailsFrames;
    uint16 knuxFrames;
    uint16 superKnuxFrames;
    uint16 miracleKnuxFrames;
    uint16 mightyFrames;
    uint16 superMightyFrames;
    uint16 miracleMightyFrames;
    uint16 rayFrames;
    uint16 superRayFrames;
    uint16 miracleRayFrames;
    uint16 amyFrames;
    uint16 superAmyFrames;
    uint16 miracleAmyFrames;
    uint16 sfxJump;
    uint16 sfxRoll;
    uint16 sfxCharge;
    uint16 sfxRelease;
    uint16 sfxPeelCharge;
    uint16 sfxPeelRelease;
    uint16 sfxDropdash;
    uint16 sfxLoseRings;
    uint16 sfxHurt;
    uint16 sfxPimPom;
    uint16 sfxSkidding;
    uint16 sfxGrab;
    uint16 sfxFlying;
    bool32 playingFlySfx;
    uint16 sfxTired;
    bool32 playingTiredSfx;
    uint16 sfxLand;
    uint16 sfxSlide;
    uint16 sfxOuttahere;
    uint16 sfxTransform2;
    uint16 sfxSwap;
    uint16 sfxSwapFail;
    uint16 sfxMightyDeflect;
    uint16 sfxMightyDrill;
    uint16 sfxMightyLand;
    uint16 sfxMightyUnspin;
    int32 raySwoopTimer;
    int32 rayDiveTimer;
    bool32 gotHit[PLAYER_COUNT];
    StateMachine(configureGhostCB);
    bool32 (*canSuperCB)(bool32 isHUD);
    int32 superDashCooldown;
    uint16 sfxAmyHammer;
    uint16 sfxAmyHammerFly;
    uint16 sfx1up;
    bool32 hasReflectAchievement;
    TABLE(int32 miracleColors[32],
        { 0x4A2644, 0x2C0656, 0xFCA6DA, 0xFEC8EB, 0xFEE1F5, 0x623259, 0x8A407D, 0xC67595, 0xE5A9B4, 0xFDD6D7, 0xFFF0F0, 0x490198, 0x8A01D0, 0xC53AE9, 0xEC9FEF, 0x58CA9F,
          0x76DBB6, 0x91EDCE, 0xBEF4E2, 0x8D4311, 0xC15A15, 0xE27F22, 0xEAA939, 0xEED253, 0xEBE67A, 0x6A21B5, 0x8735ED, 0x9066F4, 0x9E93F0, 0xF990C6, 0xFDBAE4, 0x942981 });
    int32 colorStorage[32];
    TABLE(int32 miracleColors_HCZ[32],
        { 0x311095, 0x080D5F, 0xC893E7, 0xD9B9EE, 0xE8D3EE, 0x5329B0, 0x7139BE, 0x9C59D0, 0xC88ED9, 0xE2BBE8, 0xF4DDF1, 0x371C8E, 0x5B1FBE, 0x7A4DE9, 0xB388ED, 0x54A1C6,
          0x79C5D4, 0x93D9E4, 0xB9E2EE, 0x624384, 0x82589D, 0x9A779A, 0xB88F8F, 0xCAA38C, 0xD4C8A4, 0x422CA2, 0x613FD2, 0x7767E9, 0x858AEE, 0x9969CF, 0xD0A3EC, 0x5A49BF });
    int32 colorStorage_HCZ[32];
    TABLE(int32 miracleColors_CPZ[32],
        { 0x7F007F, 0x7200CA, 0xDC3DC9, 0xE35EDA, 0xE774E4, 0x990494, 0xBB0AA0, 0xD022A4, 0xE649BB, 0xEA60CA, 0xE176CC, 0x8600DB, 0x9C08E8, 0xC705F8, 0xE73FF8, 0x8F6BAE,
          0xA978B6, 0xC37BC6, 0xD77DC3, 0x980070, 0xB40085, 0xCB1B8B, 0xE2349A, 0xE455A2, 0xE470A9, 0x8800B5, 0x9700D6, 0xA507EF, 0xBD38E8, 0xD41BB3, 0xE052D3, 0x92008B });
    int32 colorStorage_CPZ[32];
    bool32 carryOverShieldApplied;
    bool32 restartShieldApplied;
};
#else
struct ObjectPlayer {
    RSDK_OBJECT
    int32 playerCount;
    TABLE(int32 sonicPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x80000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000 });
    TABLE(int32 tailsPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x80000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000 });
    TABLE(int32 knuxPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x60000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x30000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x60000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x30000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x60000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x30000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x60000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x8000, 0x300, 0x30000, -0x20000 });
    uint16 upState;
    uint16 downState;
    uint16 leftState;
    uint16 rightState;
    uint16 jumpPressState;
    uint16 jumpHoldState;
    int32 nextLeaderPosID;
    int32 lastLeaderPosID;
    Vector2 leaderPositionBuffer[16];
    Vector2 targetLeaderPosition;
    int32 autoJumpTimer;
    int32 respawnTimer;
    int32 aiInputSwapTimer;
#if GAME_VERSION != VER_100 // may not work with building static var files, but who's building 1.00 static var files anyways lol
    bool32 disableP2KeyCheck;
#endif
    int32 rings;
    STATIC(int32 ringExtraLife, 100);
    int32 powerups;
    STATIC(int32 savedLives, 3);
    int32 savedScore;
    STATIC(int32 savedScore1UP, 50000);
    uint16 sonicFrames;
    uint16 superFrames;
    uint16 tailsTailsFrames;
    uint16 tailsFrames;
    uint16 knuxFrames;
    TABLE(color superPalette_Sonic[18], { 0x000080, 0x0038C0, 0x0068F0, 0x1888F0, 0x30A0F0, 0x68D0F0, 0xF0C001, 0xF0D028, 0xF0E040, 0xF0E860,
                                          0xF0E898, 0xF0E8D0, 0xF0D898, 0xF0E0B0, 0xF0E8C0, 0xF0F0D8, 0xF0F0F0, 0xF0F0F8 });
    TABLE(color superPalette_Tails[18], { 0x800801, 0xB01801, 0xD05001, 0xE07808, 0xE89008, 0xF0A801, 0xF03830, 0xF06848, 0xF09860, 0xF0B868,
                                          0xF0C870, 0xF0D870, 0xF03830, 0xF06848, 0xF09860, 0xF0B868, 0xF0C870, 0xF0D870 });
    TABLE(color superPalette_Knux[18], { 0x580818, 0x980130, 0xD00840, 0xE82858, 0xF06080, 0xF08088, 0xF05878, 0xF06090, 0xF080A0, 0xF098B0, 0xF0B0C8,
                                         0xF0C0C8, 0xF05878, 0xF06090, 0xF080A0, 0xF098B0, 0xF0B0C8, 0xF0C0C8 });
    TABLE(color superPalette_Sonic_HCZ[18], { 0x200888, 0x3020C8, 0x3840F0, 0x4070F0, 0x4098F0, 0x40C0F0, 0x88C880, 0x68E090, 0x50F098, 0x68F0C0,
                                              0x78F0C8, 0xA0F0D8, 0x60E898, 0x48F0A0, 0x58F0B0, 0x68F0C0, 0x90F0D0, 0xA0F0D8 });
    TABLE(color superPalette_Tails_HCZ[18], { 0x880808, 0xA03810, 0xA05848, 0xB07058, 0xC08068, 0xC89078, 0xCC6161, 0xDC8462, 0xD5978A, 0xDEA893,
                                              0xE6B09D, 0xEABAA7, 0xCC6161, 0xDC8462, 0xD5978A, 0xDEA893, 0xE6B09D, 0xEABAA7 });
    TABLE(color superPalette_Knux_HCZ[18], { 0x181050, 0x301090, 0x5018A8, 0x8828C0, 0xA048C0, 0xB868C8, 0x746DA3, 0x7F65D0, 0x9768E0, 0xC070EF,
                                             0xD086EB, 0xDE9CED, 0x746DA3, 0x7F65D0, 0x9768E0, 0xC070EF, 0xD086EB, 0xDE9CED });
    TABLE(color superPalette_Sonic_CPZ[18], { 0x4000D8, 0x5800E0, 0x6810E0, 0x8020E0, 0xA020E0, 0xC040E0, 0xE04880, 0xE06890, 0xE078A8, 0xE078D8,
                                              0xE080E0, 0xE080E0, 0xE080B0, 0xE080B0, 0xE080C0, 0xE080C0, 0xE080E0, 0xE080E0 });
    TABLE(color superPalette_Tails_CPZ[18], { 0xC80180, 0xD00178, 0xE00180, 0xE81088, 0xE83098, 0xE84898, 0xF078F0, 0xF078F0, 0xF080F0, 0xF088F0,
                                              0xF098F0, 0xF0A0F0, 0xF078F0, 0xF078F0, 0xF080F0, 0xF088F0, 0xF098F0, 0xF0A0F0 });
    TABLE(color superPalette_Knux_CPZ[18], { 0xA00180, 0xB00178, 0xC00190, 0xD001B0, 0xE001E0, 0xE820E8, 0xF078D8, 0xF078E8, 0xF088F0, 0xF098F0,
                                             0xF0A8F0, 0xF0B0F0, 0xF078D8, 0xF078E8, 0xF088F0, 0xF098F0, 0xF0A8F0, 0xF0B0F0 });
    uint16 sfxJump;
    uint16 sfxRoll;
    uint16 sfxCharge;
    uint16 sfxRelease;
    uint16 sfxPeelCharge;
    uint16 sfxPeelRelease;
    uint16 sfxDropdash;
    uint16 sfxLoseRings;
    uint16 sfxHurt;
    uint16 unused; // this matches up perfectly with the position of "sfxPimPom" in plus, and it cant be padding so :eye:
    uint16 sfxSkidding;
    uint16 sfxGrab;
    uint16 sfxFlying;
    bool32 playingFlySfx;
    uint16 sfxTired;
    bool32 playingTiredSfx;
    uint16 sfxLand;
    uint16 sfxSlide;
    uint16 sfxOuttahere;
    uint16 sfxTransform2;
    bool32 gotHit[PLAYER_COUNT];
};
#endif

// Entity Class
struct EntityPlayer {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(nextAirState);
    StateMachine(nextGroundState);
    EntityCamera *camera;
    Animator animator;
    Animator tailAnimator;
    int32 minJogVelocity;
    int32 minRunVelocity;
    int32 minDashVelocity;
    int32 unused; // the only used variable in the player struct, I cant find a ref to it anywhere so...
    int32 tailRotation;
    int32 tailDirection;
    uint16 aniFrames;
    uint16 tailFrames;
    uint16 animationReserve; // what anim to return to after SpringTwirl/SpringDiagonal has finished and the player is falling downwards
    uint16 playerID;
    Hitbox *outerbox;
    Hitbox *innerbox;
    int32 characterID;
    int32 rings;
    int32 ringExtraLife;
    int32 shield;
    int32 lives;
    int32 score;
    int32 score1UP;
    bool32 hyperRing;
    int32 timer;
    int32 outtaHereTimer;
    int32 abilityTimer;
    int32 spindashCharge;
    int32 abilityValue;
    int32 drownTimer;
    int32 invincibleTimer;
    int32 superInvulnTimer;
    int32 speedShoesTimer;
    int32 blinkTimer;
    int32 scrollDelay;
    int32 skidding;
    int32 pushing;
    int32 underwater;     // 0 = not in water, 1 = in palette water, else water entityID
    bool32 groundedStore; // prev frame's onGround value
    bool32 invertGravity;
    bool32 isChibi;
#if GAME_VERSION != VER_100
    bool32 isTransforming;
#endif
    int32 superState;
    bool32 miracleState;
    int32 superRingLossTimer;
    int32 superBlendAmount;
    int32 superBlendState;
    bool32 sidekick;
    int32 scoreBonus;
    int32 jumpOffset;
    int32 collisionFlagH;
    int32 collisionFlagV;
    int32 topSpeed;
    int32 acceleration;
    int32 deceleration;
    int32 airAcceleration;
    int32 airDeceleration;
    int32 skidSpeed;
    int32 rollingFriction;
    int32 rollingDeceleration;
    int32 gravityStrength;
    int32 abilitySpeed;
    int32 jumpStrength;
    int32 jumpCap;
    int32 flailing;
    int32 sensorX[5];
    int32 sensorY;
    Vector2 moveLayerPosition;
#if MANIA_USE_PLUS
    StateMachine(stateInputReplay);
#endif
    StateMachine(stateInput);
    int32 controllerID;
    int32 controlLock;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    bool32 jumpHold;
    bool32 applyJumpCap;
    int32 jumpAbilityState;
    StateMachine(stateAbility);
    StateMachine(statePeelout);
    StateMachine(stateTallJump);
    int32 flyCarryTimer;
    Vector2 flyCarrySidekickPos;
    Vector2 flyCarryLeaderPos;
    uint8 deathType;
    bool32 forceRespawn;
#if MANIA_USE_PLUS
    bool32 isGhost;
#endif
    int32 abilityValues[8];
    void *abilityPtrs[8];
#if MANIA_USE_PLUS
    int32 uncurlTimer;
    bool32 hammeractivate;
#endif
};

// Object Struct
extern ObjectPlayer *Player;

// Standard Entity Events
void Player_Update(void);
void Player_LateUpdate(void);
void Player_StaticUpdate(void);
void Player_Draw(void);
void Player_Create(void *data);
void Player_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void Player_EditorDraw(void);
void Player_EditorLoad(void);
#endif
void Player_Serialize(void);

// Extra Entity Functions
void Player_LoadSprites(void);
void Player_LoadSpritesVS(void);
void Player_SaveValues(void);
void Player_GiveScore(EntityPlayer *player, int32 score);
void Player_GiveRings(EntityPlayer *player, int32 amount, bool32 playSfx);
void Player_GiveLife(EntityPlayer *entity);
void Player_ApplyShield(EntityPlayer *player);
void Player_ChangeCharacter(EntityPlayer *entity, int32 character);
bool32 Player_TryTransform(EntityPlayer *player, uint8 emeraldMasks, uint8 timeStoneMasks);
bool32 Player_TryTransform_ERZ(EntityPlayer *player, uint8 emeraldMasks, uint8 timeStoneMasks);
void Player_BlendSuperSonicColors(int32 bankID);
void Player_BlendSuperTailsColors(int32 bankID);
void Player_BlendSuperKnuxColors(int32 bankID);
#if MANIA_USE_PLUS
void Player_BlendSuperMightyColors(int32 bankID);
void Player_BlendSuperRayColors(int32 bankID);
void Player_BlendSuperAmyColors(int32 bankID);
#endif
void Player_HandleSuperForm(void);
bool32 Player_CheckP2KeyPress(void);
// returns the pointer to the nearest player to the current entity on the x axis only
EntityPlayer *Player_GetNearestPlayerX(void);
// returns the pointer to the nearest player to the current entity on both the x & y axis
EntityPlayer *Player_GetNearestPlayer(void);
#if MANIA_USE_PLUS
void Player_RemoveEncoreLeader(void);
#endif
void Player_ResetBoundaries(EntityPlayer *player);
void Player_HandleDeath(EntityPlayer *player);
void Player_HandleQuickRespawn(EntityPlayer *player);

// Collision
// returns a pointer to the currently active player hitbox (outer box)
Hitbox *Player_GetHitbox(EntityPlayer *player);
// returns a pointer to the alternate player hitbox (inner box)
Hitbox *Player_GetAltHitbox(EntityPlayer *player);
// performs a non-solid box collision with the player, this handles setting the appropriate collision-related player variabes automatically
bool32 Player_CheckCollisionTouch(EntityPlayer *player, void *entity, Hitbox *entityHitbox);
// performs an all-solid box collision with the player, this handles setting the appropriate collision-related player variabes automatically
bool32 Player_CheckCollisionBox(EntityPlayer *player, void *entity, Hitbox *entityHitbox);
// performs a top-solid box collision with the player, this handles setting the appropriate collision-related player variabes automatically
bool32 Player_CheckCollisionPlatform(EntityPlayer *player, void *entity, Hitbox *entityHitbox);

// Hits the player if not invulnerable, returns true if player was hit
bool32 Player_Hurt(EntityPlayer *player, void *entity);
// the same as above, though the knockback dir is gotten from the player dir rather the direction of the distance
bool32 Player_HurtFlip(EntityPlayer *player);
// Hits the player if not invulnerable and the player's shield doesn't match shield, returns true if player was hit
bool32 Player_ElementHurt(EntityPlayer *player, void *entity, int32 shield);
// returns true if the player is in an "attacking" state
bool32 Player_CheckAttacking(EntityPlayer *player, void *e);
// returns true if the player is in an "attacking" state (but omits invincibility timer as being an "attacking" state)
bool32 Player_CheckAttackingNoInvTimer(EntityPlayer *player, void *e);
// checks if the player collided with an entity, this collision differs from the touch one above since it uses hammerdrop & instashield if appropriate
bool32 Player_CheckBadnikTouch(EntityPlayer *player, void *entity, Hitbox *entityHitbox);
// checks if the player is attacking the badnik, returns true if the player attacked the badnik, otherwise the player is hit and returns false
bool32 Player_CheckBadnikBreak(EntityPlayer *player, void *entity, bool32 destroy);
// similar to checkBadnikTouch, this time for bosses, handles rebounds and stuff properly, does NOT check for hammerdrop/instashield hitboxes. returns
// true if player hit the boss, otherwise the player is hit and returns false
bool32 Player_CheckBossHit(EntityPlayer *player, void *entity);
// similar to checkHit, but for projectiles, handles the rebound effect when using shields or crouching as mighty, returns true if deflected,
// otherwise the player is hit and returns false
bool32 Player_ProjectileHurt(EntityPlayer *player, void *projectile);
#if MANIA_USE_PLUS
// similar to checkHit, but for objects that should bounce off mighty's shell, returns true if deflected, otherwise the player is hit and returns
// false
bool32 Player_CheckMightyShellHit(EntityPlayer *player, void *e, int32 velX, int32 velY);
#endif
// Similar to "Player_CheckBadnikBreak" but omits the score/explosion & animal stuff. Does not destroy 'entity'
bool32 Player_CheckItemBreak(EntityPlayer *player, void *entity, bool32 hitIfNotAttacking);

// State helpers
void Player_UpdatePhysicsState(EntityPlayer *entity);
void Player_HandleIdleAnimation(void);
void Player_HandleGroundAnimation(void);
void Player_HandleGroundMovement(void);
void Player_HandleGroundRotation(void);
void Player_HandleAirRotation(void);
void Player_HandleAirMovement(void);
void Player_HandleAirFriction(void);
void Player_Action_Jump(EntityPlayer *entity);
void Player_Action_Roll(void);
void Player_Action_Spindash(void);
void Player_Action_Spindash_CD(void);
void Player_Action_Peelout(void);
void Player_Action_TallJump(void);
#if MANIA_USE_PLUS
bool32 Player_SwapMainPlayer(bool32 forceSwap);
#endif
void Player_HandleRollDeceleration(void);
void Player_Hit(EntityPlayer *player);
bool32 Player_CheckValidState(EntityPlayer *player);
void Player_HandleFlyCarry(EntityPlayer *leader);
void Player_HandleSidekickRespawn(void);
void Player_State_StartSuper(void);

// States
void Player_State_Static(void);
void Player_State_Ground(void);
void Player_State_Air(void);
void Player_State_Roll(void);
void Player_State_TubeRoll(void);
void Player_State_TubeAirRoll(void);
void Player_State_LookUp(void);
void Player_State_Crouch(void);
void Player_State_Spindash(void);
void Player_State_Spindash_CD(void);
void Player_State_Peelout(void);
void Player_State_TallJump(void);
void Player_State_OuttaHere(void);
void Player_State_Transform(void);
void Player_State_Hurt(void);
void Player_State_Death(void);
void Player_State_Drown(void);
void Player_State_DropDash(void);
void Player_State_BubbleBounce(void);
void Player_State_TailsFlight(void);
void Player_State_FlyCarried(void);
void Player_State_FlightCancel(void);
void Player_State_KnuxGlideLeft(void);
void Player_State_KnuxGlideRight(void);
void Player_State_KnuxGlideDrop(void);
void Player_State_KnuxGlideSlide(void);
void Player_State_KnuxWallClimb(void);
void Player_State_KnuxLedgePullUp(void);
#if MANIA_USE_PLUS
void Player_State_MightyHammerDrop(void);
void Player_State_MightyUnspin(void);
void Player_SpawnMightyHammerdropDust(int32 speed, Hitbox *hitbox);
bool32 Player_CheckMightyUnspin(EntityPlayer *player, int32 bounceDistance, bool32 checkHammerDrop, int32 *uncurlTimer);
void Player_State_RayGlide(void);
void Player_State_AmyHeliHammer_Left(void);
void Player_State_AmyHeliHammer_Right(void);
#endif
void Player_State_FlyToPlayer(void);
void Player_State_ReturnToPlayer(void);
void Player_State_HoldRespawn(void);
void Player_FinishedReturnToPlayer(EntityPlayer *player, EntityPlayer *leader);
void Player_State_EncoreRespawn(void);
void Player_State_Victory(void);
void Player_State_Bubble(void);
void Player_State_WaterSlide(void);
void Player_State_TransportTube(void);

// Gravity States
void Player_Gravity_True(void);
void Player_Gravity_False(void);

// Jump Ability States
void Player_JumpAbility_Sonic(void);
void Player_JumpAbility_Tails(void);
void Player_JumpAbility_Knux(void);
#if MANIA_USE_PLUS
void Player_JumpAbility_Mighty(void);
void Player_JumpAbility_Ray(void);
void Player_JumpAbility_Amy(void);
void Player_State_AmyDoubleJump(void);

bool32 Player_SfxCheck_RayDive(void);
bool32 Player_SfxCheck_RaySwoop(void);
void Player_SfxUpdate_RayDive(int32 sfxID);
void Player_SfxUpdate_RaySwoop(int32 sfxID);
#endif

// Input States
void Player_Input_P1(void);
void Player_Input_P2_Delay(void);
void Player_Input_P2_AI(void);
void Player_Input_AI_SpindashPt1(void);
void Player_Input_AI_SpindashPt2(void);
void Player_Input_P2_Player(void);

void Player_State_DrawMiracle(void);

#endif //! OBJ_PLAYER_H
