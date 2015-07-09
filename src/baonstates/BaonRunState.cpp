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

BaonRunState::BaonRunState(bool flipped) : BaonState(){
	executed = false;
	this->flipped = flipped;
	nextRequested = false;
	t = new Timer();
	id = "RUN";
}
void BaonRunState::Update_(float dt) {
	t->Update(dt);
	if(!executed) {
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
	if(!baon->GetBendMode() && InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
		nextRequested = true;
		next = "FASTPUNCH";
		nextFlipped = flipped;
	}
	if(t->Get() >= 0.4){
		baon->step2->Play(0);
		t->Restart();
	}
	if(baon->isTakingDamage()){
		nextRequested = true;
		next = "TAKEHIT";
		nextFlipped = flipped;
	}
}

bool BaonRunState::Is(std::string state) {
	return state.compare("RUN") == 0;
}

void BaonRunState::NotifyTileCollision() {
}
