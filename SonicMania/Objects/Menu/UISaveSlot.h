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
    TABLE(int32 powerColors[96],
          { 0xA00000, 0xB01820, 0xC03040, 0xD04860, 0xE06080, 0x4040C8, 0x5858C8, 0xE060E0, 0x7070C8, 0x8888C8, 0xA0A0C8, 0xC048C8,
            0xA030B0, 0x801898, 0x600080, 0x88B8E0, 0x80E0,   0x2890E0, 0x58A8E0, 0xB8D0E0, 0x208000, 0x409800, 0x60B000, 0x80C800,
            0xA0E000, 0xE0E0A0, 0xD0C878, 0xC0B050, 0xB09828, 0xA08000, 0x808080, 0x909090, 0xA0A0A0, 0xC0C0C0, 0xB0B0B0, 0xE8E8E8,
            0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
            0x5A0024, 0x7B0029, 0xB8001A, 0xDC0000, 0xFF4229, 0x300061, 0x420087, 0x7D7DFF, 0x6200C4, 0x840EF1, 0xAB49FF, 0x5C5CFF,
            0x3C3CEC, 0x2D2DB3, 0x251D8C, 0x00BFB3, 0x004875, 0x006091, 0x008EA8, 0x40F2AD, 0x005B00, 0x2B8200, 0x48B400, 0x62D100,
            0x90FC00, 0xF1F141, 0xD6C004, 0xB89800, 0x926700, 0x6F4900, 0x840909, 0xB41B0C, 0xE84200, 0xFF8C12, 0xFF5E0F, 0xE8E8E8,
            0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000 });
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
    Animator livesAnimator;
#if MANIA_USE_PLUS
    Animator continuesAnimator;
#endif
    Animator emeraldsAnimator;
#if MANIA_USE_PLUS
    Animator stonesAnimator;
    Animator emeraldGlowAnimator;
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
