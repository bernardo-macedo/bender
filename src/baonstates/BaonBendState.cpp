/*
 * BaonBendState.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonBendState.h"

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "../Engine/Physics/Body.h"
#include "BaonRunState.h"
#include "BaonStandState.h"
#include "BaonStateManager.h"
#include "BaonWalkState.h"

#include <iostream>

// TODO: receber Baon no construtor
BaonBendState::BaonBendState(bool flipped) {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	id = "BEND";
}

void BaonBendState::Update(float dt) {
	baon->SetBendMode(true);
	if(InputManager::GetInstance().KeyRelease(F_KEY)){
		executed = false;
		nextRequested = true;
		next = "STAND";
		nextFlipped = flipped;
	}
}

void BaonBendState::NotifyTileCollision() {
}

bool BaonBendState::Is(std::string state) {
	return state.compare("BEND") == 0;
}
