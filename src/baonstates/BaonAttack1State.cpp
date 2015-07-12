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
BaonAttack1State::BaonAttack1State(bool flipped) : BaonState(){
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	id = "ATTACK1";
	justJumped = true;
	canExecute = false;
	bendJumpSound = new Sound("audio/sfx_bend_jump.wav");
}

BaonAttack1State::~BaonAttack1State() {
	delete bendJumpSound;
}

void BaonAttack1State::Update_(float dt) {
	if(!executed){
		if(canExecute) {
			if (!Hud::GetInstance()->IsBuffering(Hud::THREE)) {
				Hud::GetInstance()->SetBuffering(Hud::THREE);
				bendJumpSound->Play(0);
				pedra = new PedraBasico(baon->GetBox().GetX(),
						baon->GetBox().GetY() + baon->GetBox().GetH() - 10*baon->GetScale(),
						baon->GetScale());
				pedra->SetID(GameObject::PEDRA_BASICO_PULO_BAON);
				pedra->GetSprite()->SetFrameWidth(35);
				pedra->GetSprite()->SetFrameHeight(50);
				pedra->GetSprite()->SetFrameCount(3);
				pedra->GetSprite()->SetLine(0, 50);

				if (baon->GetGroundTouchResolver()->IsTouchingGround(pedra->GetBox(), pedra->GetScale())) {
					Game::GetInstance()->GetCurrentState()->AddObject(pedra);
				}
				baon->Jump(flipped);
				baon->SetJumpFrame();
				baon->GetBody()->SetVelY(-700);
				justJumped = true;
			} else {
				bendErrorSound->Play(0);
			}
			executed = true;
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
		if(pedra != NULL){
			if(!pedra->IsDead()){
				if(pedra->GetSprite()->GetCurrentFrame() < 3){
					pedra->GetSprite()->Update(dt);
				}
				else{
					pedra->SetDead(true);
					pedra = NULL;
					justJumped = false;
					canExecute = false;
				}
			}
		}
		if(baon->GetSprite()->GetCurrentFrame() < 2){
			baon->GetSprite()->Update(dt);
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
