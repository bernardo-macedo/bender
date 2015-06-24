/*
 * State.cpp
 *
 *  Created on: 19/05/2015
 *      Author: Pedro2
 */

#include "State.h"

#include <stddef.h>

#include "../PedraBasico.h"
#include "Camera.h"
#include "Game.h"
#include "Geometry/Point.h"
#include "Physics/Body.h"

State::State() {
	quitRequested = false;
	popRequested = false;
}

void State::UpdateArray(float dt) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
		if (objectArray[i].get()->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
		else{
			if(objectArray[i]->GetID() == 100 || objectArray[i]->GetID() == 101){
				PedraBasico *pedra = (PedraBasico*)objectArray[i].get();
				if(pedra->GetBody()->GetX() > Game::SCREEN_WIDTH - Camera::pos.getX()
						|| pedra->GetBody()->GetX() < 0  - Camera::pos.getX()){
					objectArray.erase(objectArray.begin() + i);
				}
			}
		}
	}
}

void State::RenderArray() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i].get()->Render();
	}
}

State::~State() {
	// TODO Auto-generated destructor stub
}

void State::AddObject(GameObject* object) {
	objectArray.emplace_back(object);
}

bool State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}

GameObject* State::FindByID(int id) {
	for(unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->GetID() == id){
			return objectArray[i].get();
		}
	}
	return NULL;
}
