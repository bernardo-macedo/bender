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
#include "BaonKickState.h"
#include "BaonPunchState.h"
#include "BaonWalkState.h"
#include <iostream>

BaonStandState::BaonStandState(bool flipped) {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	executed = false;
}

void BaonStandState::Update(float dt) {
	if(!executed){
		baon->Stand(flipped);
		executed = true;
	}

	if(InputManager::GetInstance().IsKeyDown(D_KEY)){
		nextRequested = true;
		next = new BaonWalkState(false);
		flipped = false;
		std::cout << "passou" << std::endl;
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

bool BaonStandState::Is(std::string name) {
	return name.compare("STAND") == 0;
}

void BaonStandState::NotifyTileCollision() {
	baon->GetBody()->SetVelY(0);
	baon->GetBody()->SetY(PLAYER_MAP_GROUND);
}
