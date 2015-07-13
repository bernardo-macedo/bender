/*
 * BaonTransitionState.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: -Bernardo
 */

#include "BaonTransitionState.h"

BaonTransitionState::BaonTransitionState(bool flipped) {
	this->flipped = flipped;
	executed = false;

}

BaonTransitionState::~BaonTransitionState() {

}

void BaonTransitionState::Update_(float dt) {
	if (!executed) {
		baon->SetTransitionFrame(flipped);
		baon->GetBody()->SetVelX(0);
		executed = true;
	}
}

void BaonTransitionState::NotifyTileCollision() {
}

bool BaonTransitionState::Is(std::string state) {
	return state.compare("TRANSITION") == 0;
}
