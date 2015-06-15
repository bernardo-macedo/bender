/*
 * State.cpp
 *
 *  Created on: 19/05/2015
 *      Author: Pedro2
 */

#include "State.h"

State::State() {
	quitRequested = false;
	popRequested = false;
}

void State::UpdateArray(float dt) {
	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i].get()->Update(dt);
		if (objectArray[i].get()->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::RenderArray() {
	for (int i = 0; i < objectArray.size(); i++) {
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
