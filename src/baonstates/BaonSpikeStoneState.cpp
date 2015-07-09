/*
 * BaonSpikeStoneState.cpp
 *
 *  Created on: 07/07/2015
 *      Author: Pedro2
 */

#include "BaonSpikeStoneState.h"

#include "../Baon.h"
#include "../Engine/Game.h"
#include "../Engine/State.h"

BaonSpikeStoneState::BaonSpikeStoneState(bool flipped) : BaonState(){
	nextRequested = false;
	executed = false;
	t = new Timer();
	id = "SPIKESTONE";
}

void BaonSpikeStoneState::Update_(float dt) {
	pedra = new SpikeStone(baon->GetBox().GetX(), baon->GetBox().GetY(), baon->GetScale());
	Game::GetInstance()->GetCurrentState()->AddObject(pedra);
	nextRequested = true;
	next = "STAND";
	nextFlipped = flipped;
}

void BaonSpikeStoneState::NotifyTileCollision() {
}

bool BaonSpikeStoneState::Is(std::string state) {
	return state.compare("SPIKESTATE");
}
