/*
 * BaonBendState.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#include "BaonBendState.h"

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "../Engine/Game.h"
#include "../BendHUD.h"

#include <iostream>

// TODO: receber Baon no construtor
BaonBendState::BaonBendState(bool flipped) : BaonState(){
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
	id = "BEND";
	t = new Timer();
	t->Restart();
	for (int i = 0; i < 4; ++i){
		bendKey[i] = -1;
	}
	countBend = 0;
}

void BaonBendState::Update_(float dt) {
	t->Update(dt);
	baon->SetBendMode(true);
	baon->bendHUD->isHide = false;
	if(InputManager::GetInstance().KeyPress(H_KEY)){
		bendKey[countBend] = 0;
		countBend++;
	}
	if(InputManager::GetInstance().KeyPress(J_KEY)){
		bendKey[countBend] = 1;
		countBend++;
	}
	if(InputManager::GetInstance().KeyPress(K_KEY)){
		bendKey[countBend] = 2;
		countBend++;
	}
	if(InputManager::GetInstance().KeyPress(L_KEY)){
		bendKey[countBend] = 3;
		countBend++;
	}
	if(bendKey[0] == 1 && bendKey[1] == 2 && bendKey[2] == 3){
		executed = true;
		nextRequested = true;
		countBend = 0;
		next = "ATTACK1";
		nextFlipped = flipped;
		baon->bendHUD->isHide = true;
		for (int i = 0; i < 4; ++i){
			bendKey[i] = -1;
		}
	}
	if(InputManager::GetInstance().KeyRelease(F_KEY) || t->Get() > 3 ||countBend >= 3){
		executed = false;
		nextRequested = true;
		countBend = 0;
		next = "STAND";
		baon->bendHUD->isHide = true;
		for (int i = 0; i < 4; ++i){
			bendKey[i] = false;
		}
	}
}

void BaonBendState::NotifyTileCollision() {
}

bool BaonBendState::Is(std::string state) {
	return state.compare("BEND") == 0;
}
