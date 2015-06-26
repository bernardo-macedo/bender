/*
 * BaonAttack1State.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#include "BaonAttack1State.h"

#include "../Baon.h"
#include "../Engine/Game.h"
// TODO: receber Baon no construtor
BaonAttack1State::BaonAttack1State(bool flipped) {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	id = "ATTACK1";
	justJumped = true;
	canExecute = false;
}

void BaonAttack1State::Update(float dt) {
	if(!executed){
		if(canExecute){
			pedra = new PedraBasico(baon->GetBox().GetX(),
					baon->GetBox().GetY() + baon->GetBox().GetH(),
					2);
			pedra->GetSprite()->SetFrameWidth(35);
			pedra->GetSprite()->SetFrameHeight(50);
			pedra->GetSprite()->SetFrameCount(3);
			pedra->GetSprite()->SetLine(0, 50);
			Game::GetInstance()->GetCurrentState()->AddObject(pedra);
			baon->Jump(flipped);
			baon->GetBody()->SetVelY(-700);
			executed = true;
			justJumped = true;
		}
		else{
			nextRequested = true;
			next = "STAND";
			nextFlipped = flipped;
			justJumped = true;
			canExecute = false;
		}
	}
	else{
		if(pedra->GetSprite()->GetCurrentFrame() < 3){
			std::cout << pedra->GetSprite()->GetCurrentFrame() << std::endl;
			pedra->GetSprite()->Update(dt);
		}
		else{
			pedra->SetDead(true);
			justJumped = false;
			canExecute = false;
		}
		baon->MidAir();
	}
}

void BaonAttack1State::NotifyTileCollision() {
	if(executed){
		if(!justJumped){
			nextRequested = true;
			next = "STAND";
			nextFlipped = flipped;
			justJumped = true;
			canExecute = false;
		}
	}
	else{
		canExecute = true;
	}
}

bool BaonAttack1State::Is(std::string state) {
	return state.compare("ATTACK1") == 0;
}
