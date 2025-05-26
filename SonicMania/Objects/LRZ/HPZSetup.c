#include "Game.h"

ObjectHPZSetup* HPZSetup;

void HPZSetup_Update(void) {}

void HPZSetup_LateUpdate(void) {}

void HPZSetup_StaticUpdate(void) {
	if (SceneInfo->activeCategory == 9)
		SceneInfo->timeEnabled = false;
}

void HPZSetup_Draw(void) {}

void HPZSetup_Create(void *data) {}

void HPZSetup_StageLoad(void) {
	if (SceneInfo->activeCategory == 9) {
		Zone_StartFadeIn(30, 0xF0F0F0);
		Zone->cameraBoundsL[0] = 0;
		Zone->cameraBoundsR[0] = 1152;

		if (!addendumVar->doHPZResults) {
			Entity* player = RSDK_GET_ENTITY_GEN(0);
			CREATE_ENTITY(HPZIntro, NULL, player->position.x, player->position.y);
		}

#if MANIA_USE_PLUS
		if (globals->gameMode == MODE_ENCORE) {
			RSDK.LoadPalette(0, "EncoreLRZ3.act", 0b0000000011111111);
			RSDK.CopyPalette(0, 240, 1, 240, 16);
		}
#endif
	}
}

#if GAME_INCLUDE_EDITOR
void HPZSetup_EditorDraw(void) {}

void HPZSetup_EditorLoad(void) {}
#endif

void HPZSetup_Serialize(void) {}
