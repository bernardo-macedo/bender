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
	soundPlayed = false;
	pedra = NULL;
	bendJumpSound = new Sound("audio/sfx_bend_jump.wav");
}

BaonAttack1State::~BaonAttack1State() {
	delete bendJumpSound;
}

void BaonAttack1State::Update_(float dt) {
	if(!executed){
		if (!Hud::GetInstance()->IsBuffering(Hud::THREE)) {
			Hud::GetInstance()->SetBuffering(Hud::THREE);
			bendJumpSound->Play(0);
			pedra = new PedraBasico(baon->GetBox().GetX(),
					baon->GetBox().GetY() + baon->GetBox().GetH() - 10*baon->GetScale(),
					baon->GetScale(), this);
			pedra->SetID(GameObject::PEDRA_BASICO_PULO_BAON);
			pedra->SetJumpRockSprite();

			if (baon->GetGroundTouchResolver()->IsTouchingGround(pedra->GetBox(), pedra->GetScale())) {
				Game::GetInstance()->GetCurrentState()->AddObject(pedra);
			}
			baon->Jump(flipped);
			baon->SetJumpFrame();
			baon->GetBody()->SetVelY(-700);
			justJumped = true;
			executed = true;
		} else {
			if (!soundPlayed) {
				soundPlayed = true;
				bendErrorSound->Play(0);
			}
			nextRequested = true;
			next = "STAND";
			nextFlipped = flipped;
			justJumped = true;
			canExecute = false;
		}
	}
	else{
		soundPlayed = false;
		if(pedra != NULL){
			if(!pedra->IsDead()){
				if(pedra->GetCurrentFrame() >= 3){
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
}

bool BaonAttack1State::Is(std::string state) {
	return state.compare("ATTACK1") == 0;
}

void BaonAttack1State::ResolveDeadReferences(int id) {
	if (id == GameObject::PEDRA_BASICO_PULO_BAON) {
		pedra = NULL;
	}
}

void BaonAttack1State::OnRockDead() {
	pedra = NULL;
}
