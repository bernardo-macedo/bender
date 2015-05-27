/*
 * BaonWalkState.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonWalkState.h"

#include <string>

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "BaonJumpState.h"
#include "BaonStandState.h"

BaonWalkState::BaonWalkState(bool fliped) {
	this->flipped = fliped;
	popRequested = false;
	nextRequested = false;
}

void BaonWalkState::Update(Baon* baon, BaonStateManager* sm){
	if(!executed){
		baon->Walk(flipped);
		executed = true;
	}

	if(InputManager::GetInstance().KeyRelease(A_KEY)){
		nextRequested = true;
		next = new BaonStandState(flipped);
	}
	if(InputManager::GetInstance().KeyRelease(D_KEY)){
		next = new BaonStandState(flipped);
		nextRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(W_KEY)){
		nextRequested = true;
		next = new BaonJumpState(flipped);
	}
}

bool BaonWalkState::Is(std::string state) {
	return state.compare("WALK") == 0;
}
