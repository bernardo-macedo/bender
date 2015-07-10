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

BaonFallingState::BaonFallingState(bool flipped) : BaonState() {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	id = "FALLING";
	executed = false;
	locallyExecuted = false;
}

void BaonFallingState::Update_(float dt) {
	if (!executed && !locallyExecuted && baon->IsFalling()) {
		baon->SetJumpFrame();
		baon->MidAir();
		baon->Fall();
		locallyExecuted = true;
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
