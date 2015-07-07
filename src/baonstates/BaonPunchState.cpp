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
}

void BaonPunchState::Update_(float dt) {
	if(!executed){
		if(!baon->IsCloseToEnemy()){
			soltouPedra = true;
			if(!flipped){
				pedra = new PedraBasico(baon->GetBox().GetX() + 30*baon->GetScale(),
							baon->GetBox().GetY() + 25*baon->GetScale(), baon->GetScale());
				pedra->SetID(100);
			}
			else{
				pedra = new PedraBasico(baon->GetBox().GetX() - 30*baon->GetScale(),
							baon->GetBox().GetY() + 25*baon->GetScale(), baon->GetScale());
				pedra->SetID(100);
			}
			pedra->GetSprite()->SetFrameHeight(25);
			pedra->GetSprite()->SetFrameWidth(35);
			pedra->GetSprite()->SetLine(2, 23);
			pedra->GetSprite()->SetFrameTime(0.02);
			Game::GetInstance()->GetCurrentState()->AddObject(pedra);
		}
		else{
			baon->GetSprite()->SetFrameTime(0.06);
		}
		baon->Punch();
		executed = true;
	}

	if(baon->GetSprite()->GetCurrentFrame() == 5){
		if(soltouPedra){
			if(pedra != NULL){
				if(!flipped){
					pedra->GetBody()->SetVelX(1000);
					pedra->GetBody()->SetVelY(0);
					pedra->SetGoingLeft(false);
				}
				else{
					pedra->GetBody()->SetVelX(-1000);
					pedra->GetBody()->SetVelY(0);
					pedra->SetGoingLeft(true);
				}
				pedra->SetThrown(true);
			}
		}
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
		if(soltouPedra){
			if(pedra != NULL && !pedra->IsFinnished()){
				pedra->GetSprite()->Update(dt);
			}
			else{
				pedra->GetBody()->SetVelY(-200);
			}
		}
		else{
			if(baon->GetSprite()->GetCurrentFrame() > 3){
				baon->isDamage = true;
			}
		}
	}
	if(baon->isTakingDamage()){
		if(soltouPedra && !pedra->Isthrown()){
			pedra->SetDead(true);
		}
		nextRequested = true;
		next = "TAKEHIT";
		nextFlipped = flipped;
	}
}

void BaonPunchState::NotifyTileCollision() {
}

bool BaonPunchState::Is(std::string state) {
	return state.compare("PUNCHING") == 0;
}
