/*
 * BaonStateManager.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonStateManager.h"

#include "../Engine/InputManager.h"
#include "../Engine/Timer.h"
#include "BaonRunState.h"
#include "BaonStandState.h"

BaonStateManager::BaonStateManager() {
	currentState = new BaonStandState(false);
	previousState = currentState;
	executed = false;
	t = new Timer();
	runTest = 0;
}

BaonStateManager::~BaonStateManager() {
	// TODO Auto-generated destructor stub
}

void BaonStateManager::Update(Baon* baon, float dt) {
	if(runTest == 1){
		t->Update(dt);
		if(InputManager::GetInstance().KeyPress(D_KEY)){
			if(currentState->Is("STAND") && t->Get() < 0.2){
				currentState = new BaonRunState(false);
			}
		}
		else{
			if(InputManager::GetInstance().KeyPress(A_KEY)){
				if(currentState->Is("STAND") && t->Get() < 0.2){
					currentState = new BaonRunState(true);
				}
			}
		}
	}

	if(InputManager::GetInstance().KeyPress(D_KEY)
			|| InputManager::GetInstance().KeyPress(A_KEY)){
		if(currentState->Is("STAND")){
			t->Restart();
			runTest = 1;
		}
	}

	currentState->Update(baon, this, dt);

	if(currentState->NextRequested()){
		if(!currentState->Is("JUMPING")){
			previousState = currentState;
		}
		currentState = currentState->Next();
		executed = false;
	}
}

BaonState* BaonStateManager::GetCurrentState(){
	return currentState;
}

BaonState* BaonStateManager::GetPreviousState(){
	return previousState;
}
