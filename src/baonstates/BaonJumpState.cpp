/*
 * BaonJumpState.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonJumpState.h"

#include "../Baon.h"
#include "../Engine/Physics/Body.h"
#include "BaonFallingState.h"

BaonJumpState::BaonJumpState(bool flipped) {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
}

void BaonJumpState::Update(float dt) {
	if(!executed){
		baon->Jump(flipped);
		executed = true;
	}
	else{
		baon->MidAir();
		if(baon->GetBody()->GetVelY() >= 0){
			executed = false;
			nextRequested = true;
			next = new BaonFallingState(flipped);
		}
	}
}

void BaonJumpState::NotifyTileCollision() {
}

bool BaonJumpState::Is(std::string state){
	return state.compare("JUMPING") == 0;
}
