#include "Game.h"

ObjectHPZIntro* HPZIntro;

int32 emeraldStopAngle[7] = { 0x80, 0x86, 0x7a, 0x8c, 0x74, 0x92, 0x6e };
Vector2 emeraldFlyVector[7] = {
	{ 0,    -1024 },
	{ -248, -992 },
	{ 248,  -992 },
	{ -480, -900 },
	{ 480,  -900 },
	{ -684, -756 },
	{ 684,  -756 }
};

void HPZIntro_Update(void) {
	RSDK_THIS(HPZIntro);

	++self->timer;
	StateMachine_Run(self->state);
	if (self->classID == TYPE_BLANK) return;
	foreach_active(Player, player) {
		player->state = Player_State_Static;
		player->direction = (self->drawFlags & HPZI_PLAYER_LEFT) ? FLIP_X : FLIP_NONE;
		if (self->drawFlags & HPZI_PLAYER_UP) {
			RSDK.SetSpriteAnimation(player->aniFrames, ANI_LOOK_UP, &player->animator, false, 1);
			if (player->animator.frameID == 5) player->animator.speed = 0;
		} else if (player->animator.animationID == ANI_LOOK_UP) {
			player->animator.speed = 64;
			if (player->animator.frameID == 0) RSDK.SetSpriteAnimation(player->aniFrames, ANI_IDLE, &player->animator, false, 1);
		}
	}
}

void HPZIntro_LateUpdate(void) {}

void HPZIntro_StaticUpdate(void) {}

void HPZIntro_Draw(void) {
	RSDK_THIS(HPZIntro);
	EntityPauseMenu *pauseMenu = RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);

	if (self->drawFlags & HPZI_EMERALDS) {
		const int32 sparsity = MIN(self->timer * 16, 6144); // 384 frames
		const int32 height = MIN(self->timer * 0x8000, 0x3F8000); // 127 frames

		for (int32 c = 0; c < 36; ++c) {
			HPZIntro->colorStorage[c] = RSDK.GetPaletteEntry(0, c + 128);
			RSDK.SetPaletteEntry(0, c + 128, HPZIntro->emeraldPalettes[c + (Addendum_GetOptionsRAM()->emeraldPalette * 36)]);
		}
		
		Vector2 pos;
		for (int32 i = 0; i < 7; ++i) {
			pos.x = self->position.x + RSDK.Sin256(self->emeraldAngle[i]) * sparsity + self->emeraldOffset[i].x;
			pos.y = self->position.y + RSDK.Cos256(self->emeraldAngle[i]) * sparsity - height + self->emeraldOffset[i].y;

			if (!self->alpha) {
				self->alpha = abs(RSDK.Sin256(self->timer * 1.25) / 3);
				self->alpha >>= 1;
				self->inkEffect = INK_NONE;
				RSDK.DrawSprite(&self->animatorEmeralds[i], &pos, false);
				self->alpha <<= 1;
				LogHelpers_Print("alpha is %d", self->alpha);
				self->inkEffect = INK_ADD;
				RSDK.DrawSprite(&self->animatorEmeraldGlow[i], &pos, false);
				self->alpha = 0;
			}
		}
		
		for (int32 c = 0; c < 36; ++c)
			RSDK.SetPaletteEntry(0, c + 128, HPZIntro->colorStorage[c]);
	}
}

void HPZIntro_Create(void *data) {
	RSDK_THIS(HPZIntro);

	if (!SceneInfo->inEditor) {
		if (SceneInfo->activeCategory == 9) {
			self->active    = ACTIVE_NORMAL;
			self->visible   = true;
			self->drawGroup = Zone->objectDrawGroup[0];
			EntityCamera* camera = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
			camera->state   = StateMachine_None;
			self->state     = HPZIntro_State_TeleportPlayer;
		}
		else
			destroyEntity(self);
	}
}

void HPZIntro_StageLoad(void) {
	HPZIntro->sfxTwinkle       = RSDK.GetSfx("Global/Twinkle.wav");
	HPZIntro->sfxEmeraldFlying = RSDK.GetSfx("LRZ/LittlePlanet.wav");
	HPZIntro->aniFramesEmerald = RSDK.LoadSpriteAnimation("Cutscene/Emeralds.bin", SCOPE_STAGE);
}

void HPZIntro_State_TeleportPlayer() {
	RSDK_THIS(HPZIntro);

	// putting this in the create event wasnt working so lol
	if (self->timer == 2) {
		foreach_active(Player, player) {
			player->visible = false;
			player->position = RSDK_GET_ENTITY(SLOT_PLAYER1, Player)->position;
		}
	}

	if (self->timer == 30) {
        EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
		EntityHPZBeam *telebeam = CREATE_ENTITY(HPZBeam, NULL, player->position.x, Zone->playerBoundsT[0] - 0x8000);
        self->teleBeam          = telebeam;
		self->teleBeam->target_y = player->position.y + TO_FIXED(16);
	}

	if (self->timer > 30 && self->teleBeam->hit_timer == 31) {
		foreach_active(Player, player) player->visible = true;
	}

	if (self->timer > 30 && self->teleBeam->classID == TYPE_BLANK) {
		if (!Addendum_GetSaveRAM()->emeraldsTransferred) {
			RSDK.PlaySfx(HPZIntro->sfxTwinkle, false, 0xFF);
			for (int32 i = 0; i != 7; ++i) {
				self->emeraldAngle[i] = i * 0x24;
				RSDK.SetSpriteAnimation(HPZIntro->aniFramesEmerald, 0, &self->animatorEmeralds[i], true, i);
				RSDK.SetSpriteAnimation(HPZIntro->aniFramesEmerald, 2, &self->animatorEmeraldGlow[i], true, i);
			}
			self->drawFlags |= HPZI_EMERALDS;
			self->timer = 0;
			self->state = HPZIntro_State_RaiseEmeralds;
		}
		else {
			foreach_active(Player, player) { player->state = Player_State_Ground; }
			EntityCamera* camera = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
			camera->state = Camera_State_FollowXY;
			destroyEntity(self);
		}
	}
}

void HPZIntro_State_RaiseEmeralds() {
	RSDK_THIS(HPZIntro);

	if (self->timer >= 127) {
		self->drawFlags |= HPZI_PLAYER_UP;
	} else {
		self->drawFlags &= ~HPZI_PLAYER_UP;
	}

	bool32 all_stopped = true;
	for (int32 i = 0; i != 7; ++i) {
		if (self->timer >= 354 && emeraldStopAngle[i] - (self->emeraldAngle[i] % 0xff) < 4 && emeraldStopAngle[i] - ((self->emeraldAngle[i] - 4) % 0xff) >= 4) {
			self->emeraldAngle[i] = emeraldStopAngle[i];
		} else {
			self->emeraldAngle[i] += 4;
			all_stopped = false;
		}
	}
	if (all_stopped) {
		RSDK.PlaySfx(HPZIntro->sfxEmeraldFlying, false, 0xFF);
		for (int32 i = 0; i != 7; ++i) { self->velocity = emeraldFlyVector[i]; }
		self->state = HPZIntro_State_EmeraldsFlyOff;
	}
}

void HPZIntro_State_EmeraldsFlyOff() {
	RSDK_THIS(HPZIntro);

	for (int32 i = 0; i != 7; ++i) {
		self->emeraldOffset[i].x += emeraldFlyVector[i].x << 8;
		self->emeraldOffset[i].y += emeraldFlyVector[i].y << 8;
	}
	if (self->timer >= 513) {
		self->drawFlags &= ~HPZI_EMERALDS;
		Camera_SetupLerp(CAMERA_LERP_NORMAL, 0, HPZIntro->SortedSuperEmeralds[0]->position.x, HPZIntro->SortedSuperEmeralds[0]->position.y, 16);
		self->timer = 0;
		self->state = HPZIntro_State_ActivateSuperEmeralds;
	}
}

void HPZIntro_State_ActivateSuperEmeralds() {
	RSDK_THIS(HPZIntro);

	int32 target_beams = self->timer / 32;
	if (self->beams != target_beams) {
		self->beams = target_beams;
		if (self->beams < 9) {
			EntityCamera* camera = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
            int32 diff = self->beams <= 2 ? camera->position.x - HPZIntro->SortedSuperEmeralds[0]->position.x : camera->position.x - HPZIntro->SortedSuperEmeralds[self->beams - 2]->position.x;
			LogHelpers_Print("BEAM %d", self->beams);
			LogHelpers_Print("TARGETBEAM %d", target_beams);
			if (abs(diff) >= TO_FIXED(16)) {
				--self->timer;
				--self->beams;
				if (diff < 0) {
					camera->position.x += TO_FIXED(16);
				}
				else {
					camera->position.x -= TO_FIXED(16);
				}
			}
			else {
				if (self->beams != 8) {
					if (GET_BIT(HPZIntro->emeraldBeamed, self->beams - 1) == 0) { // prevents an issue where multiple beams would be created targetting the same emerald
						int32 spawn_y = Zone->playerBoundsT[0] - 0x8000;
						EntityHPZBeam* beam = CREATE_ENTITY(HPZBeam, NULL, HPZIntro->SortedSuperEmeralds[self->beams - 1]->position.x, spawn_y);
						beam->target_y = HPZIntro->SortedSuperEmeralds[self->beams - 1]->position.y;
						SET_BIT(HPZIntro->emeraldBeamed, 1, self->beams - 1);
					}
				}
			}
		}
	}

	if (self->beams != 9) {
		if (target_beams < 5) {
			self->drawFlags |= HPZI_PLAYER_LEFT;
		} else {
			self->drawFlags &= ~HPZI_PLAYER_LEFT;
		}
		if (target_beams & 1) {
			self->drawFlags |= HPZI_PLAYER_UP;
		} else {
			self->drawFlags &= ~HPZI_PLAYER_UP;
		}
	}
	else {
		foreach_active(Player, player) { player->state = Player_State_Ground; }
		EntityCamera* camera = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
		camera->state = Camera_State_FollowXY;
		Addendum_GetSaveRAM()->emeraldsTransferred = true;
		destroyEntity(self);
	}
}

#if GAME_INCLUDE_EDITOR
void HPZIntro_EditorDraw(void) {}
void HPZIntro_EditorLoad(void) {}
#endif

void HPZIntro_Serialize(void) {}
