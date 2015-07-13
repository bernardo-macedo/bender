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

State::State(int posX) : initialPositionX(posX) {
	quitRequested = false;
	popRequested = false;
	slowMotion = 1;
	tileMap = NULL;
}

void State::UpdateArray(float dt) {
	dt = dt/slowMotion;
	Update(dt);
	for (unsigned int i = 0; i < objectArray.size(); i++) {

		if (objectArray[i]->IsDead()) {
			ResolveDeadObject(objectArray[i].get());
			objectArray.erase(objectArray.begin() + i);
		}
		else{
			OnUpdate(dt, objectArray[i].get());
			objectArray[i]->Update(dt);
			for(unsigned int j = 0; j < objectArray.size(); j++){
				if(objectArray[i]->GetID() != objectArray[j]->GetID()
						&& Collision::IsColliding(objectArray[i]->GetBox(), objectArray[j]->GetBox(), 0, 0)){
					objectArray[i]->NotifyCollision(objectArray[j].get());
					objectArray[j]->NotifyCollision(objectArray[i].get());
				}
			}
		}
	}
}

void State::RenderArray() {
	Render();
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

void State::SetSlowMotion(int slow) {
	slowMotion = slow;
}
