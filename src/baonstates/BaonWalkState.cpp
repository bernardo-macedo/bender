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
#include "BaonKickState.h"
#include "BaonPunchState.h"
#include "BaonStandState.h"

BaonWalkState::BaonWalkState(bool fliped) {
	this->flipped = fliped;
	popRequested = false;
	nextRequested = false;
}

void BaonWalkState::Update(float dt){
	if(!executed){
		baon->Walk(flipped);
		executed = true;
	}

	if(!InputManager::GetInstance().IsKeyDown(A_KEY)){
		if(flipped){
			nextRequested = true;
			next = new BaonStandState(flipped);
		}
	}
	if(!InputManager::GetInstance().IsKeyDown(D_KEY)){
		if(!flipped){
			next = new BaonStandState(flipped);
			nextRequested = true;
		}
	}
	if(InputManager::GetInstance().KeyPress(W_KEY)){
		nextRequested = true;
		next = new BaonJumpState(flipped);
	}
	if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
		nextRequested = true;
		next = new BaonPunchState(flipped);
	}
	if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
		nextRequested = true;
		next = new BaonKickState(flipped);
	}
}

bool BaonWalkState::Is(std::string state) {
	return state.compare("WALK") == 0;
}

void BaonWalkState::NotifyTileCollision() {
	std::cout << "passou3" << std::endl;
	baon->GetBody()->SetVelY(0);
	baon->GetBody()->SetY(PLAYER_MAP_GROUND);
}
