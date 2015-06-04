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
	id = "RUN";
}
void BaonRunState::Update(float dt) {
	if(!executed){
		baon->Run(flipped);
		executed = true;
	}

	if(!InputManager::GetInstance().IsKeyDown(A_KEY)){
		if(flipped){
			nextRequested = true;
			next = "STAND";
			nextFlipped = true;
		}
	}
	if(!InputManager::GetInstance().IsKeyDown(D_KEY)){
		if(!flipped){
			next = "STAND";
			nextFlipped = false;
			nextRequested = true;
		}
	}
	if(InputManager::GetInstance().KeyPress(W_KEY)){
		nextRequested = true;
		next = "JUMP";
		nextFlipped = flipped;
	}
}

bool BaonRunState::Is(std::string state) {
	return state.compare("RUN") == 0;
}

void BaonRunState::NotifyTileCollision(Body* previousBody, float dt) {
}
