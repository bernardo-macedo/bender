/*
 * BaonFallingState.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonFallingState.h"

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "../Engine/Physics/Body.h"
#include "BaonRunState.h"
#include "BaonStandState.h"
#include "BaonStateManager.h"
#include "BaonWalkState.h"
#include <iostream>

// TODO: receber Baon no construtor
BaonFallingState::BaonFallingState(bool flipped) {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	id = "FALLING";
	executed = false;
}

void BaonFallingState::Update(float dt) {
	if (!executed && baon->IsFalling()) {
		baon->SetJumpFrame();
		baon->MidAir();
		baon->Fall();
	}
}

void BaonFallingState::NotifyTileCollision() {
	if (!baon->IsFalling() && !executed) {
		sm->GetPreviousState()->Reset();
		next = sm->GetPreviousState()->GetID();
		nextFlipped = flipped;
		nextRequested = true;
		baon->land->Play(0);
		baon->TakeDamage(false, false);
		executed = true;
	}

}

bool BaonFallingState::Is(std::string state) {
	return state.compare("FALLING") == 0;
}
