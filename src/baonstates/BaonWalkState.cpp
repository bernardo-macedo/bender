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

BaonWalkState::BaonWalkState(bool fliped) : BaonState(){
	this->flipped = fliped;
	popRequested = false;
	nextRequested = false;
	id = "WALK";
	t = new Timer();
}

void BaonWalkState::Update_(float dt){
	t->Update(dt);
	if(!executed){
		baon->Walk(flipped);
		executed = true;
	}

	if(!InputManager::GetInstance().IsKeyDown(A_KEY)){
		if(flipped){
			nextRequested = true;
			next = "STAND";
			nextFlipped = flipped;
		}
	}
	if(!InputManager::GetInstance().IsKeyDown(D_KEY)){
		if(!flipped){
			next = "STAND";
			nextFlipped = flipped;
			nextRequested = true;
		}
	}
	if(InputManager::GetInstance().KeyPress(W_KEY)){
		nextRequested = true;
		next = "JUMP";
		nextFlipped = flipped;
	}
	if(!baon->GetBendMode() && InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
		nextRequested = true;
		next = "PUNCH";
		nextFlipped = flipped;
	}
	if(!baon->GetBendMode() && InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
		nextRequested = true;
		next = "KICK";
		nextFlipped = flipped;
	}
	if(t->Get() >= 0.3){
		baon->GetStepSound(1)->Play(0);
		t->Restart();
	}
	if(baon->isTakingDamage()){
		nextRequested = true;
		next = "TAKEHIT";
		nextFlipped = flipped;
	}

}

bool BaonWalkState::Is(std::string state) {
	return state.compare("WALK") == 0;
}

void BaonWalkState::NotifyTileCollision() {
}
