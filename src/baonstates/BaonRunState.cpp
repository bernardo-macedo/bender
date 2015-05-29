/*
 * BaonRunState.cpp
 *
 *  Created on: 27/05/2015
 *      Author: Pedro2
 */

#include "BaonRunState.h"

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "BaonJumpState.h"
#include "BaonStandState.h"

BaonRunState::BaonRunState(bool flipped){
	executed = false;
	this->flipped = flipped;
	nextRequested = false;
}
void BaonRunState::Update(float dt) {
	if(!executed){
		baon->Run(flipped);
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

bool BaonRunState::Is(std::string state) {
	return state.compare("RUN") == 0;
}

void BaonRunState::NotifyTileCollision(Body* previousBody, float dt) {
	baon->GetBody()->SetVelY(0);
	baon->GetBody()->SetY(PLAYER_MAP_GROUND);
}
