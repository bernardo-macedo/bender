/*
 * BaonBigRockState.cpp
 *
 *  Created on: 13/07/2015
 *      Author: Pedro2
 */

#include "BaonBigRockState.h"

#include "../Baon.h"
#include "../BaonAttack.h"
#include "../Hud.h"

BaonBigRockState::BaonBigRockState(bool flipped) {
	executed = false;
	nextRequested = false;
	t = new Timer();
	pedra = NULL;
	this->flipped = flipped;
}

BaonBigRockState::~BaonBigRockState() {
	// TODO Auto-generated destructor stub
}

void BaonBigRockState::Update_(float dt) {
	if(Hud::GetInstance()->GetLevel() >= 3){
		if(!executed){
			if(!Hud::GetInstance()->IsBuffering(Hud::SIX)) {
				Hud::GetInstance()->SetBuffering(Hud::SIX);
				baon->SetLastGivenAttack(BaonAttack::CONTROL);
				if(flipped){
					pedra = new BigRock(baon->GetBox().GetX() - 20, baon->GetBox().GetY() );
				}
				else{
					pedra = new BigRock(baon->GetBox().GetX() + 80, baon->GetBox().GetY() );
				}
				Game::GetInstance()->GetCurrentState()->AddObject(pedra);
				executed = true;
			}
			else{
				nextRequested = true;
				next = "STAND";
				nextFlipped = flipped;
			}
		}
		else{
			if(pedra->finnished()){
				nextRequested = true;
				next = "STAND";
				nextFlipped = flipped;
			}
		}
	}
	else{
		nextRequested = true;
		next = "STAND";
		nextFlipped = flipped;
	}
}

void BaonBigRockState::NotifyTileCollision() {
}

bool BaonBigRockState::Is(std::string state) {
	return state.compare("BIGROCK") == 0;
}
