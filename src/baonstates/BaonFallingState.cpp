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
}

void BaonFallingState::Update(float dt) {
	if (baon->IsFalling()) {
		baon->MidAir();
		baon->Fall();
	} else {
		sm->GetPreviousState()->Reset();
		next = sm->GetPreviousState()->GetID();
		nextFlipped = flipped;
		nextRequested = true;
		baon->land->Play(0);
		baon->TakeDamage(false, false);
	}
}

void BaonFallingState::NotifyTileCollision() {
	if (!baon->IsFalling()) {
		sm->GetPreviousState()->Reset();
		next = sm->GetPreviousState()->GetID();
		nextFlipped = flipped;
		nextRequested = true;
		baon->land->Play(0);
		baon->TakeDamage(false, false);
	}
}

bool BaonFallingState::Is(std::string state) {
	return state.compare("FALLING") == 0;
}
