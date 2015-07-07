/*
 * BaonTakeHitState.cpp
 *
 *  Created on: 09/06/2015
 *      Author: Pedro2
 */

#include "BaonTakeHitState.h"

#include <string>

#include "../Baon.h"


BaonTakeHitState::BaonTakeHitState(bool flipped) : BaonState(){
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	executed = false;
	id = "TAKEHIT";
}

void BaonTakeHitState::Update_(float dt) {
	if(!executed){
		baon->TakeHit(flipped);
		executed = true;
	}

	if((!baon->IsCollisionFromRight() && baon->GetBody()->GetVelX() <= 0)
			|| (baon->IsCollisionFromRight() && baon->GetBody()->GetVelX() >= 0)){
		baon->GetBody()->SetVelX(0);
		baon->GetBody()->removeForce("resistance");
		nextRequested = true;
		next = "STAND";
		nextFlipped = flipped;
		baon->TakeDamage(false, false);
	}
}

void BaonTakeHitState::NotifyTileCollision() {
}

bool BaonTakeHitState::Is(std::string state) {
	return state.compare(id) == 0;
}
