// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania Addendum
// Object Description: Mosqui Object (v4)
// Object Author: Christian Whitehead
// RSDKv5 Syntax Recreation: KiaraGale
// ---------------------------------------------------------------------

#include "Game.h"

ObjectMosqui *Mosqui;

void Mosqui_Update(void)
{
    RSDK_THIS(Mosqui);

    StateMachine_Run(self->state);
}

void Mosqui_LateUpdate(void) {}

void Mosqui_StaticUpdate(void) {}

void Mosqui_Draw(void)
{
    RSDK_THIS(Mosqui);

    RSDK.DrawSprite(&self->animator, NULL, false);
}

void Mosqui_Create(void* data)
{
    RSDK_THIS(Mosqui);
    self->visible = true;
    self->drawFX |= FX_FLIP;
    self->drawGroup     = Zone->objectDrawGroup[0];
    self->startPos      = self->position;
    self->startDir      = self->direction;
    self->active        = ACTIVE_BOUNDS;
    self->updateRange.x = 0x800000;
    self->updateRange.y = 0x800000;
    self->wasTurning    = true;

    if (data) {
        RSDK.SetSpriteAnimation(Mosqui->aniFrames, 3, &self->animator, false, 0);
        self->broken = true;
        self->state  = Mosqui_State_Init;
    }
    else {
        RSDK.SetSpriteAnimation(Mosqui->aniFrames, 0, &self->animator, false, 0);
        self->broken = false;
        self->state  = Mosqui_State_Init;
    }
}

void Mosqui_StageLoad(void) { Mosqui->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Mosqui.bin", SCOPE_STAGE); }

void Mosqui_State_Init(void) {}

void Mosqui_State_Move(void) {}

void Mosqui_State_Idle(void) {}

void Mosqui_State_Turn(void) {}

void Mosqui_State_PointDown(void) {}

void Mosqui_State_Attack(void) {}

void Mosqui_State_Stuck(void) {}

#if GAME_INCLUDE_EDITOR
void Mosqui_EditorDraw(void) {}

void Mosqui_EditorLoad(void) {}
#endif

void Mosqui_Serialize(void) { RSDK_EDITABLE_VAR(Mosqui, VAR_BOOL, broken); }
