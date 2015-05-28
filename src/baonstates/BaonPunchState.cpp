/*
 * BaonPunchState.cpp
 *
 *  Created on: 27/05/2015
 *      Author: Pedro2
 */

#include "BaonPunchState.h"

#include "../Baon.h"
#include "../Engine/Timer.h"
#include "BaonStateManager.h"

BaonPunchState::BaonPunchState(bool flipped) {
	this->flipped = flipped;
	count = 0;
	nextRequested = false;
	executed = false;
	t = new Timer();
}

void BaonPunchState::Update(Baon* baon, BaonStateManager* sm, float dt) {
	if(!executed){
		baon->Punch();
		executed = true;
	}
	if(t->Get() >= 5*0.1){
		nextRequested = true;
		sm->GetPreviousState()->Reset();
		next = sm->GetPreviousState();
	}
	else{
		t->Update(dt);
	}
}

bool BaonPunchState::Is(std::string state) {
	return state.compare("PUNCHING") == 0;
}
