/*
 * BaonDefenseStoneState.cpp
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#include "BaonDefenseStoneState.h"

#include <string>

#include "../Baon.h"
#include "../Engine/Game.h"
#include "../Engine/State.h"
#include "../PedraDefesa.h"

BaonDefenseStoneState::BaonDefenseStoneState(bool flipped) {
	executed = false;
	nextRequested = false;
	pedra= NULL;
	this->flipped = flipped;
}

void BaonDefenseStoneState::Update_(float dt) {
	if(!executed){
		if(flipped){
			pedra = new PedraDefesa(baon->GetBox().GetX() - 20*baon->GetScale(),
					baon->GetBox().GetY() - 10*baon->GetScale());
		}
		else{
			pedra = new PedraDefesa(baon->GetBox().GetX() + 20*baon->GetScale(),
					baon->GetBox().GetY() - 10*baon->GetScale());
		}
		Game::GetInstance()->GetCurrentState()->AddObject(pedra);
	}

	next = "STAND";
	nextFlipped = flipped;
	nextRequested = true;
}

void BaonDefenseStoneState::NotifyTileCollision() {
}

bool BaonDefenseStoneState::Is(std::string state) {
	return state.compare("defense") == 0;
}
