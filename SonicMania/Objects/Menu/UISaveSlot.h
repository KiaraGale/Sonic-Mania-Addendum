#ifndef OBJ_UISAVESLOT_H
#define OBJ_UISAVESLOT_H

#include "Game.h"

typedef enum {
    UISAVESLOT_REGULAR,
    UISAVESLOT_NOSAVE,
} UISaveSlotTypes;

// Object Class
struct ObjectUISaveSlot {
    RSDK_OBJECT
    uint16 aniFrames;
    TABLE(int32 emeraldPalettes[180],
        { 0xA00000, 0xB01820, 0xC03040, 0xD04860, 0xE06080, 0x4040C8, 0x5858C8, 0xE060E0, 0x7070C8, 0x8888C8, 0xA0A0C8, 0xC048C8,
          0xA030B0, 0x801898, 0x600080, 0x88B8E0, 0x0081E0, 0x2890E0, 0x58A8E0, 0xB8D0E0, 0x208000, 0x409800, 0x60B000, 0x80C800,
          0xA0E000, 0xE0E0A0, 0xD0C878, 0xC0B050, 0xB09828, 0xA08000, 0x808080, 0x909090, 0xA0A0A0, 0xC0C0C0, 0xB0B0B0, 0xF0F0F0,
          0x004747, 0x007D7D, 0x00A2A2, 0x00DDDD, 0x89FAFA, 0x4F001E, 0x852465, 0xDAF970, 0xC040A0, 0xE060C0, 0xF195E1, 0xA0E000,
          0x60C000, 0x00A000, 0x006000, 0xA4A4A4, 0x404040, 0x656565, 0x898989, 0xCACACA, 0x1A1A75, 0x4040A0, 0x6060C0, 0x8080E0,
          0xAAA8FC, 0xEEF48E, 0xE0E000, 0xC0A000, 0x886600, 0x563000, 0x4E0000, 0x8A0000, 0xD60000, 0xF97F8D, 0xEB385C, 0xF0F0F0,
          0x5A0024, 0x7B0029, 0xB8001A, 0xDC0000, 0xFF4229, 0x6F4900, 0x926700, 0x7D7DFF, 0xB89800, 0xD6C004, 0xF1F141, 0x5C5CFF,
          0x3C3CEC, 0x2D2DB3, 0x251D8C, 0x840EF1, 0x300061, 0x420087, 0x6200C4, 0xAB49FF, 0x005B00, 0x2B8200, 0x48B400, 0x62D100,
          0x90FC00, 0xFF8C12, 0xFF5E0F, 0xE84200, 0xB41B0C, 0x840909, 0x004875, 0x006091, 0x008EA8, 0x40F2AD, 0x00BFB3, 0xF0F0F0, 
          0x6A6A6A, 0x808080, 0xA0A0A0, 0xC0C0C0, 0xE1E1E1, 0x890000, 0xAA0000, 0xFFC3FF, 0xD00000, 0xF2214D, 0xFF69A5, 0xFF80F2,
          0xF455EE, 0xDD38E0, 0xC026BB, 0x94E000, 0x207F00, 0x3E9A00, 0x5EBC00, 0xCDF386, 0x007AD5, 0x0099D9, 0x00BEE0, 0x3DDBEE,
          0x7FFFFA, 0xD768F3, 0xAE29EC, 0x8000C0, 0x6B008F, 0x550072, 0xA88700, 0xC7A600, 0xE0C000, 0xF3ECB0, 0xF2DA3B, 0xF0F0F0, 
          0x375A9C, 0x4E72BA, 0x6998C7, 0xB2D1F1, 0xD7E7F6, 0x85006A, 0xAA0088, 0x9D98FF, 0xD21AAA, 0xFF71DC, 0xFFB1E3, 0x7171FF,
          0x3E4AE8, 0x212CC0, 0x212187, 0xF6812C, 0x82000F, 0xA60000, 0xE71B1B, 0xF7AB59, 0x014501, 0x006C01, 0x00A700, 0x8AEF04,
          0xD3FF7D, 0xF7ED9C, 0xFFD513, 0xE0941A, 0xC5690D, 0xA64717, 0x665D7C, 0x807BA1, 0xACACD3, 0xECECF5, 0xD3D3F9, 0xF0F0F0 });
    TABLE(int32 erzColors[32],
        { 0x311808, 0x522010, 0x843018, 0xB55131, 0xD68A52, 0x4A0808, 0x731000, 0xAD2008, 0xD63808, 0xF7A221, 0x100829, 0x211052, 0x29106B, 0x391884, 0x6B209C, 0x84309C,
          0xB538AD, 0xCE59BD, 0xBDA2E7, 0x42006B, 0x73007B, 0x94008C, 0xBD008C, 0xF7009C, 0xF761B5, 0x180842, 0x520021, 0xB50800, 0xDE2000, 0xF76918, 0xF7EB8C, 0xFFFFFF });
    int32 colorStorage[96];
};

// Entity Class
struct EntityUISaveSlot {
    MANIA_UI_ITEM_BASE
    bool32 isNewSave;
#if MANIA_USE_PLUS
    StateMachine(stateInput);
#endif
    int32 listID;
    int32 frameID;
    int32 altFrameID;
    int32 buddyFrameID1;
    int32 buddyFrameID2;
    int32 saveZoneID;
#if MANIA_USE_PLUS
    int32 saveActID;
    int32 actTotal;
#endif
    int32 saveLives;
#if MANIA_USE_PLUS
    int32 saveContinues;
#endif
    int32 saveEmeralds;
#if MANIA_USE_PLUS
    int32 saveSuperEmeralds;
    bool32 emeraldsTransferred;
    int32 saveTimeStones;
    uint8 saveEncorePlayer;
    uint8 saveEncoreBuddy;
    uint8 saveEncoreFriends[4];
#endif
    UISaveSlotTypes type;
    int32 slotID;
#if MANIA_USE_PLUS
    bool32 encoreMode;
#endif
    bool32 currentlySelected;
    int32 zoneIconSprX;
    int32 textBounceOffset;
    int32 buttonBounceOffset;
    int32 textBouncePos;
    int32 buttonBouncePos;
    int32 fxRadius;
#if MANIA_USE_PLUS
    EntityFXRuby *fxRuby;
    bool32 debugEncoreDraw;
    uint8 dCharPoint;
    uint8 dCharPartner;
    uint8 dCharStock1;
    uint8 dCharStock2;
    uint8 dCharStock3;
    uint8 dCharStock4;
#endif
    Animator uiAnimator;
    Animator playersAnimator;
    Animator shadowsAnimator;
    Animator sidekickAnimator;
    Animator sidekickShadowAnimator;
    Animator buddy1Animator;
    Animator buddy2Animator;
    Animator livesAnimator;
#if MANIA_USE_PLUS
    Animator continuesAnimator;
#endif
    Animator emeraldsAnimator;
#if MANIA_USE_PLUS
    Animator superEmeraldsAnimator;
    Animator stonesAnimator;
    Animator emeraldGlowAnimator;
    Animator superEmeraldGlowAnimator;
    Animator stoneGlowAnimator;
#endif
    Animator zoneIconAnimator;
    Animator zoneNameAnimator;
    Animator fuzzAnimator;
    Animator iconBGAnimator;
    Animator saveStatusAnimator;
    Animator numbersAnimator;
    Animator actNameAnimator;
    uint16 textFrames;
    int32 glowTimer;
    void (*processYPressCB)(void);
    bool32 p2Active;
    bool32 p3Active;
    bool32 p4Active;
};

// Object Struct
extern ObjectUISaveSlot *UISaveSlot;

// Standard Entity Events
void UISaveSlot_Update(void);
void UISaveSlot_LateUpdate(void);
void UISaveSlot_StaticUpdate(void);
void UISaveSlot_Draw(void);
void UISaveSlot_Create(void *data);
void UISaveSlot_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void UISaveSlot_EditorDraw(void);
void UISaveSlot_EditorLoad(void);
#endif
void UISaveSlot_Serialize(void);

// Extra Entity Functions
#if MANIA_USE_PLUS
uint8 UISaveSlot_GetPlayerIDFromID(uint8 id);
uint8 UISaveSlot_GetIDFromPlayerID(uint8 playerID);
void UISaveSlot_DrawPlayerIcon_Encore(uint8 playerID, bool32 isSilhouette, uint8 buddyID, uint8 *friendIDs, uint8 friendCount, int32 drawX,
                                      int32 drawY);
#endif
void UISaveSlot_DrawPlayerIcons(int32 drawX, int32 drawY);
void UISaveSlot_DrawPlayerInfo(int32 drawX, int32 drawY);
void UISaveSlot_SetupButtonElements(void);
void UISaveSlot_SetupAnimators(void);
void UISaveSlot_LoadSaveInfo(void);
void UISaveSlot_HandleSaveIcons(void);

void UISaveSlot_DeleteDLG_CB(void);
#if MANIA_USE_PLUS
void UISaveSlot_DeleteSaveCB(bool32 success);
#else
void UISaveSlot_DeleteSaveCB(void);
#endif
void UISaveSlot_ProcessButtonCB(void);
void UISaveSlot_SelectedCB(void);

void UISaveSlot_NextCharacter(void);
void UISaveSlot_PrevCharacter(void);
void UISaveSlot_NextCharacter_ExtraPlayers(int32 playerID);
void UISaveSlot_NextZone(void);
void UISaveSlot_PrevZone(void);

bool32 UISaveSlot_CheckButtonEnterCB(void);
bool32 UISaveSlot_CheckSelectedCB(void);
void UISaveSlot_ButtonEnterCB(void);
void UISaveSlot_ButtonLeaveCB(void);
void UISaveSlot_HandleSaveIconChange(void);

void UISaveSlot_State_NotSelected(void);
void UISaveSlot_State_OtherWasSelected(void);
void UISaveSlot_State_NewSave(void);
void UISaveSlot_State_ActiveSave(void);
#if MANIA_USE_PLUS
void UISaveSlot_StateInput_NewSave(void);
#endif
void UISaveSlot_State_CompletedSave(void);
void UISaveSlot_State_Selected(void);

#endif //! OBJ_UISAVESLOT_H
