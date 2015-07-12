/*
 * BaonControleState.cpp
 *
 *  Created on: 11/07/2015
 *      Author: Pedro2
 */

#include "BaonControleState.h"

#include "../Baon.h"
#include "../Engine/Game.h"
#include "../Engine/Sound.h"
#include "../Engine/State.h"
#include "../Engine/TileSet/GroundTouchResolver.h"
#include "../Hud.h"

BaonControleState::BaonControleState(bool flipped) {
	executed = false;
	nextRequested = false;
	pedra = NULL;
}

BaonControleState::~BaonControleState() {
	// TODO Auto-generated destructor stub
}

void BaonControleState::Update_(float dt) {
	if(Hud::GetInstance()->GetLevel() >= 2){
		if(!executed) {
			if(!Hud::GetInstance()->IsBuffering(Hud::FOUR)) {
				Hud::GetInstance()->SetBuffering(Hud::FOUR);
				float pedraX;
				if(flipped){
					pedraX = baon->GetBox().GetX() - 30*baon->GetScale();
				}
				else{
					pedraX = baon->GetBox().GetX() + 30*baon->GetScale();
				}
				pedra = new ControleBend(pedraX, baon->GetGroundTouchResolver()->GetGroundHeight(pedraX + 10) - 28*baon->GetScale(), flipped);

				if (baon->GetGroundTouchResolver()->IsTouchingGround(pedra->GetBox(), baon->GetScale())) {
					Game::GetInstance()->GetCurrentState()->AddObject(pedra);
				}
			} else {
				bendErrorSound->Play(0);
			}
			executed = true;
		}
	}

	next = "STAND";
	nextFlipped = flipped;
	nextRequested = true;
}

void BaonControleState::NotifyTileCollision() {
}

bool BaonControleState::Is(std::string state) {
}
