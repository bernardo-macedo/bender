/*
 * BaonDyingState.cpp
 *
 *  Created on: 25/06/2015
 *      Author: Pedro2
 */

#include "BaonDyingState.h"

#include "../Engine/Timer.h"
#include "../Baon.h"

float BaonDyingState::STATE_TIME = 1;

BaonDyingState::BaonDyingState(bool flipped) {
	t = new Timer();
	executed = false;
	nextRequested = false;
	this->flipped = flipped;
}

BaonDyingState::~BaonDyingState() {
	// TODO Auto-generated destructor stub
}

void BaonDyingState::Update(float dt) {
	if(!executed){
		baon->GetSprite()->SetFrameWidth(32);
		baon->GetSprite()->SetFrameHeight(50);
		baon->GetSprite()->SetFrameTime(0);
		baon->GetSprite()->SetLine(13, 50);
		baon->GetSprite()->Update(dt);
		baon->GetBody()->SetVelX(0);
		baon->GetBody()->SetAccelX(0);
		baon->GetBody()->clearForces();
		executed = true;
	}
	else{
		t->Update(dt);
		if(t->Get() >= STATE_TIME){
			baon->SetDead(true);
		}
	}
}

void BaonDyingState::NotifyTileCollision() {
}

bool BaonDyingState::Is(std::string state) {
	return state.compare("DYING") == 0;
}
