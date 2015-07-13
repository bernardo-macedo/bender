/*
 * BaonPunchState.cpp
 *
 *  Created on: 27/05/2015
 *      Author: Pedro2
 */

#include "BaonPunchState.h"

#include "../Baon.h"
#include "../Engine/Timer.h"
#include "BaonStateManager.h"
#include "../Engine/Game.h"

BaonPunchState::BaonPunchState(bool flipped) : BaonState(){
	this->flipped = flipped;
	nextRequested = false;
	executed = false;
	t = new Timer();
	id = "PUNCH";
	soltouPedra = false;
	pedra = NULL;
	throwRockSound = new Sound("audio/sfx_throwRock.wav");
	punchSound = new Sound("audio/sfx_char_punch_swing1.wav");
	previousFrame = 1;
}

void BaonPunchState::Update_(float dt) {
	if(!executed){
		if(!baon->IsCloseToEnemy()) {
			float pedraX;
			if(!flipped){
				pedraX = baon->GetBox().GetX() + 30*baon->GetScale();
			}
			else{
				pedraX = baon->GetBox().GetX() - 30*baon->GetScale();
			}
			pedra = new PedraBasico(pedraX, baon->GetGroundTouchResolver()->GetGroundHeight(pedraX + 10) - 25*baon->GetScale(), baon->GetScale(), this);
			pedra->SetID(GameObject::PEDRA_BASICO_BAON);
			pedra->SetRockSprite(0.02);
			pedra->SetGoingLeft(flipped);

			if (baon->GetGroundTouchResolver()->IsTouchingGround(pedra->GetBox(), pedra->GetScale())) {
				throwRockSound->Play(0);
				float y = baon->GetGroundTouchResolver()->GetGroundHeight(pedra->GetBody()->GetX()) - pedra->GetBox().GetH() - 45;
				pedra->SetLimitY(y);
				Game::GetInstance()->GetCurrentState()->AddObject(pedra);
				baon->SetLastGivenAttack(BaonAttack::ROCK);
				soltouPedra = true;
			}
		} else {
			punchSound->Play(0);
			baon->GetSprite()->SetFrameTime(0.06);
			baon->SetLastGivenAttack(BaonAttack::PUNCH);
			if (pedra != NULL) {
				pedra->SetDead(true);
				pedra = NULL;
			}
		}
		baon->Punch();
		executed = true;
	}

	if(baon->GetSprite()->GetCurrentFrame() >= 5) {
		nextRequested = true;
		sm->GetPreviousState()->Reset();
		next = sm->GetPreviousState()->GetID();
		baon->isDamage = false;
		nextFlipped = flipped;

		soltouPedra = false;
		baon->GetSprite()->SetFrameTime(0.1);
	}
	else{
		t->Update(dt);
		if(!soltouPedra && baon->GetSprite()->GetCurrentFrame() > 3){
			baon->isDamage = true;
		}
	}
	if(baon->isTakingDamage()){
		if(soltouPedra && pedra != NULL && !pedra->Isthrown()){
			pedra->SetDead(true);
		}
		nextRequested = true;
		next = "TAKEHIT";
		nextFlipped = flipped;
	}

	previousFrame = baon->GetSprite()->GetCurrentFrame();
}

void BaonPunchState::NotifyTileCollision() {
}

BaonPunchState::~BaonPunchState() {
	delete throwRockSound;
	delete punchSound;
}

bool BaonPunchState::Is(std::string state) {
	return state.compare("PUNCHING") == 0;
}

void BaonPunchState::ResolveDeadReferences(int id) {
	/*
	if (id == GameObject::PEDRA_BASICO_BAON) {
		pedra = NULL;
	}
	*/
}

void BaonPunchState::OnRockDead() {
	pedra = NULL;
}
