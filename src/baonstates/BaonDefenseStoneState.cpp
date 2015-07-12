/*
 * BaonDefenseStoneState.cpp
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#include "BaonDefenseStoneState.h"

#include "../Baon.h"
#include "../ControleBend.h"
#include "../Engine/Game.h"
#include "../Engine/Sound.h"
#include "../Engine/State.h"
#include "../Engine/TileSet/GroundTouchResolver.h"

BaonDefenseStoneState::BaonDefenseStoneState(bool flipped) {
	executed = false;
	nextRequested = false;
	pedra= NULL;
	this->flipped = flipped;
}

void BaonDefenseStoneState::Update_(float dt) {
	if(!executed) {
		if(!Hud::GetInstance()->IsBuffering(Hud::ONE)) {
			Hud::GetInstance()->SetBuffering(Hud::ONE);
			float pedraX;
			if(flipped){
				pedraX = baon->GetBox().GetX() - 20*baon->GetScale();
			}
			else{
				pedraX = baon->GetBox().GetX() + 20*baon->GetScale();
			}
			pedra = new PedraDefesa(pedraX, baon->GetGroundTouchResolver()->GetGroundHeight(pedraX + 10) - 10*baon->GetScale());

			if (baon->GetGroundTouchResolver()->IsTouchingGround(pedra->GetBox(), baon->GetScale())) {
				Game::GetInstance()->GetCurrentState()->AddObject(pedra);
			}
		} else {
			bendErrorSound->Play(0);
		}
		executed = true;
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
