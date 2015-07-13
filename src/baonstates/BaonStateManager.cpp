/*
 * BaonStateManager.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonStateManager.h"

#include <stddef.h>

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "../Engine/Timer.h"
#include "BaonAttack1State.h"
#include "BaonBigRockState.h"
#include "BaonControleState.h"
#include "BaonDefenseStoneState.h"
#include "BaonDyingState.h"
#include "BaonFallingState.h"
#include "BaonFastPunch.h"
#include "BaonJumpState.h"
#include "BaonKickState.h"
#include "BaonPunchState.h"
#include "BaonRunState.h"
#include "BaonSpikeStoneState.h"
#include "BaonStandState.h"
#include "BaonTakeHitState.h"
#include "BaonWalkState.h"
#include "BaonTransitionState.h"



BaonStateManager::BaonStateManager(Baon* baon) {
	flipped = false;
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
	estados.emplace("DYING", new BaonDyingState(false));
	estados["DYING"]->SetBaon(baon);
	estados["DYING"]->SetStateManager(this);
	estados.emplace("ATTACK1", new BaonAttack1State(false));
	estados["ATTACK1"]->SetBaon(baon);
	estados["ATTACK1"]->SetStateManager(this);
	estados.emplace("FASTPUNCH", new BaonFastPunch(false));
	estados["FASTPUNCH"]->SetBaon(baon);
	estados["FASTPUNCH"]->SetStateManager(this);
	estados.emplace("SPIKESTONE", new BaonSpikeStoneState(false));
	estados["SPIKESTONE"]->SetBaon(baon);
	estados["SPIKESTONE"]->SetStateManager(this);
	estados.emplace("BENDDEFESA", new BaonDefenseStoneState(false));
	estados["BENDDEFESA"]->SetBaon(baon);
	estados["BENDDEFESA"]->SetStateManager(this);
	estados.emplace("BENDCONTROLE", new BaonControleState(false));
	estados["BENDCONTROLE"]->SetBaon(baon);
	estados["BENDCONTROLE"]->SetStateManager(this);
	estados.emplace("BIGROCK", new BaonBigRockState(false));
	estados["BIGROCK"]->SetBaon(baon);
	estados["BIGROCK"]->SetStateManager(this);
	estados.emplace("TRANSITION", new BaonTransitionState(false));
	estados["TRANSITION"]->SetBaon(baon);
	estados["TRANSITION"]->SetStateManager(this);

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

	if(InputManager::GetInstance().KeyPress(SPACE_KEY) && baon->GetTouchingGround()
		&& !baon->IsState("TAKEHIT")
		&& !baon->IsState("FASTPUNCH")){
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
		if (previousState->Is("JUMP")) {
			previousState = estados["STAND"];
		} else {
			previousState = currentState;
		}
		estados["FALLING"]->SetFlipped(currentState->IsFlipped());
		currentState = estados["FALLING"];
		currentState->Reset();
		executed = false;
	} else if (baon->GetLevelWon() && currentState->Is("STAND")) {
		estados["TRANSITION"]->SetFlipped(currentState->IsFlipped());
		currentState = estados["TRANSITION"];
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

