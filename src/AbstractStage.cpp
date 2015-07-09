/*
 * AbstractStage.cpp
 *
 *  Created on: Jul 4, 2015
 *      Author: -Bernardo
 */

#include "AbstractStage.h"

AbstractStage::AbstractStage(int posX) : State(posX) {}

AbstractStage::~AbstractStage() {
	if (music != NULL) {
		music->Stop();
	}

	objectArray.clear();
	delete music;
	delete tileMap;
	delete levelUpText;
	delete levelUpTimer;
}

void AbstractStage::Update(float dt) {
	baon->SetCloseToEnemy(false);

	baon->SetTouchingGround(tileMap->IsTouchingGround(baon->GetBox(), baon->GetScale()));

	if(baon->GetBendMode()){
		dt = dt/5;
	}
	Camera::Update(dt);

	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();

	for (unsigned int i = 0; i < monuments.size(); i++) {
		monuments[i]->Update(dt);
		if (monuments[i]->IsDead()) {
			monuments.erase(monuments.begin() + i);
		} else if (Collision::IsColliding(monuments[i]->GetBox(), baon->GetBox(), 0 , 0)) {
			monuments[i]->NotifyCollision(baon);
		}
	}

	UpdateArray(dt);

	if (baon->IsDead()) {
		Camera::Unfollow();
		popRequested = true;
	} else {

		// Resolve levelUp
		if (baon->GetLevelWon()) {
			if (OnLevelWon(dt)) {
				return;
			}
		}

		if (tileMap->CheckCollisions(baon->GetBox(), baon->GetScale())) {
			tileMap->ResolveTileCollisions(baon);
		}
	}

	if(!baon->bendHUD->IsDead()){
		baon->bendHUD->Update(dt);
	}
}

void AbstractStage::Render() {
	for (int i = 0; i < tileMap->GetDepth(); i++) {
		tileMap->Render(i, 0, Camera::pos.getX(), Camera::pos.getY());
	}

	for (unsigned int i = 0; i < monuments.size(); i++) {
		monuments[i]->Render();
	}

	if(!baon->IsDead()){
		baon->Render();
	}

	if(!baon->bendHUD->IsDead()){
		baon->bendHUD->Render();
	}

	RenderArray();

	if (levelUpText != NULL) {
		levelUpText->Render();
	}

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}
}

void AbstractStage::Pause() {
	if (music != NULL) {
		music->Stop();
	}
}

void AbstractStage::Resume() {
	if (music != NULL) {
		music->Play(Music::ALWAYS);
	}
}
