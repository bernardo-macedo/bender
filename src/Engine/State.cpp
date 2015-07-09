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
}

void State::UpdateArray(float dt) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
		/*
		if (objectArray[i]->Is("Being")) {
			Being* being = (Being*) objectArray[i].get();
			if (tileMap->CheckCollisions(being)) {
				tileMap->ResolveTileCollisions(being);
			}
		}
		*/
		if (objectArray[i]->IsDead()) {
			if(objectArray[i]->GetID() != GameObject::BAON){
				objectArray.erase(objectArray.begin() + i);
			}
		}
		else{
			if(objectArray[i]->GetID() == GameObject::ENEMY){
				Enemy* enemy = (Enemy*)objectArray[i].get();
				enemy->SetCloseToBaon(false);
				if (!enemy->IsRemovable()) {
					enemyAI->SetEnemy(enemy);
					enemyAI->update(dt);

					if (tileMap->CheckCollisions(enemy->GetBox(), enemy->GetScale())) {
						tileMap->ResolveTileCollisions(enemy);
					}
				}
				else{
					objectArray.erase(objectArray.begin() + i);
				}
			}
			for(unsigned int j = 0; j < objectArray.size(); j++){
				if(Collision::IsColliding(objectArray[i]->GetBox(), objectArray[j]->GetBox(), 0, 0)){
					objectArray[i]->NotifyCollision(objectArray[j].get());
					objectArray[j]->NotifyCollision(objectArray[i].get());
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
