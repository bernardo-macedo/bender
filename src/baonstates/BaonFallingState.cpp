/*
 * BaonFallingState.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#include "BaonFallingState.h"

#include "../Baon.h"
#include "../Engine/InputManager.h"
#include "../Engine/Physics/Body.h"
#include "BaonRunState.h"
#include "BaonStandState.h"
#include "BaonStateManager.h"
#include "BaonWalkState.h"

BaonFallingState::BaonFallingState(bool flipped) {
	this->flipped = flipped;
	popRequested = false;
	nextRequested = false;
}

void BaonFallingState::Update(Baon* baon, BaonStateManager* sm, float dt) {
	baon->MidAir();
	baon->Fall();
	if(baon->GetBox().GetY() >= MAP_GROUND){
		baon->fallUpdateCount = 2;
		baon->GetBody()->SetVelY(0);
		baon->GetBox().SetY(MAP_GROUND);
		baon->GetBody()->removeForce("gravity");
		if(InputManager::GetInstance().IsKeyDown(A_KEY)){
			if(sm->GetPreviousState()->Is("WALK") || sm->GetPreviousState()->Is("STAND")){
				next = new BaonWalkState(true);
				nextRequested = true;
			}
			else{
				next = new BaonRunState(true);
				nextRequested = true;
			}
		}
		else{
			if(InputManager::GetInstance().IsKeyDown(D_KEY)){
				if(sm->GetPreviousState()->Is("WALK") || sm->GetPreviousState()->Is("STAND")){
					next = new BaonWalkState(false);
					nextRequested = true;
				}
				else{
					next = new BaonRunState(false);
					nextRequested = true;
				}
			}
			else{
				next = new BaonStandState(flipped);
				nextRequested = true;
			}
		}
	}
}

bool BaonFallingState::Is(std::string state) {
	return state.compare("FALLING") == 0;
}
