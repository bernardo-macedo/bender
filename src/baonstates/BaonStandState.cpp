/*
 * BaonStandState.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonStandState.h"

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "BaonJumpState.h"
#include "BaonWalkState.h"

BaonStandState::BaonStandState(bool flipped) {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	executed = false;
}

void BaonStandState::Update(Baon* baon, BaonStateManager* sm) {
	if(!executed){
		baon->Stand(flipped);
		executed = true;
	}

	if(InputManager::GetInstance().IsKeyDown(D_KEY)){
		nextRequested = true;
		next = new BaonWalkState(false);
		flipped = false;
	}
	if(InputManager::GetInstance().IsKeyDown(A_KEY)){
		nextRequested = true;
		next = new BaonWalkState(true);
		flipped = true;
	}
	if(InputManager::GetInstance().KeyPress(W_KEY)){
		nextRequested = true;
		next = new BaonJumpState(flipped);
	}
}

bool BaonStandState::Is(std::string name) {
	return name.compare("STAND") == 0;
}
