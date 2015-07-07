/*
 * BaonStateManager.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonStateManager.h"

#include "../Engine/SDL_Wrapper.h"

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "../Engine/Timer.h"
#include "BaonBendState.h"
#include "BaonDyingState.h"
#include "BaonFallingState.h"
#include "BaonJumpState.h"
#include "BaonKickState.h"
#include "BaonPunchState.h"
#include "BaonRunState.h"
#include "BaonStandState.h"
#include "BaonTakeHitState.h"
#include "BaonBendState.h"
#include "BaonAttack1State.h"
#include "BaonWalkState.h"
#include "BaonFastPunch.h"

#include <iostream>



BaonStateManager::BaonStateManager(Baon* baon) {
	estados.emplace("STAND", new BaonStandState(false));
	estados["STAND"]->SetBaon(baon);
	estados["STAND"]->SetStateManager(this);
	estados.emplace("WALK", new BaonWalkState(false));
	estados["WALK"]->SetBaon(baon);
	estados["WALK"]->SetStateManager(this);
	estados.emplace("KICK", new BaonKickState(false));
	estados["KICK"]->SetBaon(baon);
	estados["KICK"]->SetStateManager(this);
	estados.emplace("PUNCH", new BaonPunchState(false));
	estados["PUNCH"]->SetBaon(baon);
	estados["PUNCH"]->SetStateManager(this);
	estados.emplace("JUMP", new BaonJumpState(false));
	estados["JUMP"]->SetBaon(baon);
	estados["JUMP"]->SetStateManager(this);
	estados.emplace("RUN", new BaonRunState(false));
	estados["RUN"]->SetBaon(baon);
	estados["RUN"]->SetStateManager(this);
	estados.emplace("FALLING", new BaonFallingState(false));
	estados["FALLING"]->SetBaon(baon);
	estados["FALLING"]->SetStateManager(this);
	estados.emplace("TAKEHIT", new BaonTakeHitState(false));
	estados["TAKEHIT"]->SetBaon(baon);
	estados["TAKEHIT"]->SetStateManager(this);
	estados.emplace("BEND", new BaonBendState(false));
	estados["BEND"]->SetBaon(baon);
	estados["BEND"]->SetStateManager(this);
	estados.emplace("DYING", new BaonDyingState(false));
	estados["DYING"]->SetBaon(baon);
	estados["DYING"]->SetStateManager(this);
	estados.emplace("ATTACK1", new BaonAttack1State(false));
	estados["ATTACK1"]->SetBaon(baon);
	estados["ATTACK1"]->SetStateManager(this);
	estados.emplace("FASTPUNCH", new BaonFastPunch(false));
	estados["FASTPUNCH"]->SetBaon(baon);
	estados["FASTPUNCH"]->SetStateManager(this);



	currentState = estados["STAND"];
	this->baon = baon;

	previousState = currentState;

	executed = false;
	t = new Timer();
	runTest = 0;
}

BaonStateManager::~BaonStateManager() {
	// TODO Auto-generated destructor stub
}

void BaonStateManager::Update(float dt) {
	if(runTest == 1){
		t->Update(dt);

		if(InputManager::GetInstance().KeyPress(D_KEY)){
			if(currentState->Is("STAND") && t->Get() < 0.2){
				currentState = estados["RUN"];
				currentState->SetFlipped(false);
				currentState->Reset();
			}
		}
		else{
			if(InputManager::GetInstance().KeyPress(A_KEY)){
				if(currentState->Is("STAND") && t->Get() < 0.2){
					currentState = estados["RUN"];
					currentState->SetFlipped(true);
					currentState->Reset();
				}
			}
		}
		if (currentState != NULL) {
			currentState->SetBaon(baon);
			currentState->SetStateManager(this);
		}
	}

	if(InputManager::GetInstance().KeyPress(D_KEY)
			|| InputManager::GetInstance().KeyPress(A_KEY)){
		if(currentState->Is("STAND")){
			t->Restart();
			runTest = 1;
		}
	}

	if(InputManager::GetInstance().KeyPress(F_KEY) && baon->GetTouchingGround()){
		baon->SetBendMode(true);
	}

	currentState->Update(dt);

	if(currentState->NextRequested()){
		if(!currentState->Is("JUMPING")
			&& !currentState->Is("FALLING")){
			previousState = currentState;
		}
		estados[currentState->Next()]->SetFlipped(currentState->GetNextFlipped());
		currentState = estados[currentState->Next()];
		currentState->Reset();
		executed = false;
	}

	if(baon->IsDying()){
		if(!currentState->Is("DYING")){
			estados["DYING"]->SetFlipped(currentState->IsFlipped());
			currentState = estados["DYING"];
			currentState->Reset();
			executed = false;
		}
	} else if (baon->IsFalling() && !currentState->Is("FALLING")
			&& !currentState->Is("ATTACK1")
			&& !currentState->Is("TAKEHIT")) {
		previousState = currentState;
		estados["FALLING"]->SetFlipped(currentState->IsFlipped());
		currentState = estados["FALLING"];
		currentState->Reset();
		executed = false;
	}

}

BaonState* BaonStateManager::GetCurrentState(){
	return currentState;
}

BaonState* BaonStateManager::GetPreviousState(){
	return previousState;
}
