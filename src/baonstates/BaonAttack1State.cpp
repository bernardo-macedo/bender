/*
 * BaonAttack1State.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#include "BaonAttack1State.h"

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "../Engine/Physics/Body.h"
#include "BaonRunState.h"
#include "BaonStandState.h"
#include "BaonStateManager.h"
#include "BaonWalkState.h"

#include <iostream>

// TODO: receber Baon no construtor
BaonAttack1State::BaonAttack1State(bool flipped) {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	id = "ATTACK1";
}

void BaonAttack1State::Update(float dt) {
	std::cout << "atack1" << std::endl;
	executed = true;
	nextRequested = true;
	next = "STAND";
	nextFlipped = flipped;
}

void BaonAttack1State::NotifyTileCollision() {
}

bool BaonAttack1State::Is(std::string state) {
	return state.compare("ATTACK1") == 0;
}
