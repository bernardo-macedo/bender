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
	if(!executed) {
		if (!Hud::GetInstance()->IsBuffering(Hud::TWO)) {
			Hud::GetInstance()->SetBuffering(Hud::TWO);
			float pedraX;
			if(!flipped){
				pedraX = baon->GetBox().GetX() + 80*baon->GetScale();

			}else{
				pedraX = baon->GetBox().GetX() - 80*baon->GetScale();
			}
			pedra = new SpikeStone(pedraX, baon->GetGroundTouchResolver()->GetGroundHeight(pedraX + 15) - 38*baon->GetScale(), baon->GetScale(), flipped);
			Game::GetInstance()->GetCurrentState()->AddObject(pedra);
			baon->SetLastGivenAttack(BaonAttack::SPIKESTONE);
		} else {
			bendErrorSound->Play(0);
		}
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
