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
	this->flipped = flipped;
	t = new Timer();
	id = "SPIKESTONE";
	pedra = NULL;
}

void BaonSpikeStoneState::Update_(float dt) {
	if(!executed){
		if(!flipped){
			pedra = new SpikeStone(baon->GetBox().GetX() + 30*baon->GetScale(), baon->GetBox().GetY() + 12*baon->GetScale(), baon->GetScale(), false);
		}else{
			pedra = new SpikeStone(baon->GetBox().GetX() - 30*baon->GetScale(), baon->GetBox().GetY() + 12*baon->GetScale(), baon->GetScale(), true);
		}
		Game::GetInstance()->GetCurrentState()->AddObject(pedra);
		executed = true;
	}
	nextRequested = true;
	next = "STAND";
	nextFlipped = flipped;
}

void BaonSpikeStoneState::NotifyTileCollision() {
}

bool BaonSpikeStoneState::Is(std::string state) {
	return state.compare("SPIKESTATE");
}
