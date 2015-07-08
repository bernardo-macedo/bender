/*
 * AbstractStage.cpp
 *
 *  Created on: Jul 4, 2015
 *      Author: -Bernardo
 */

#include "AbstractStage.h"

AbstractStage::AbstractStage(int scale, int level, int posX) : State(posX) {
	this->scale = scale;
	this->level = level;

	std::cout << "chamou getInstance hud" << std::endl;
	Hud::GetInstance(scale, level);
}

AbstractStage::~AbstractStage() {
	if (music != NULL) {
		music->Stop();
	}

	delete baon;
	delete music;
	delete tileMap;
	delete levelUpText;
	delete levelUpTimer;
}

void AbstractStage::Update(float dt) {

	Hud::GetInstance()->Update(dt);

	baon->SetCloseToEnemy(false);

	baon->SetTouchingGround(tileMap->IsTouchingGround(baon->GetBox(), baon->GetScale()));

	if(baon->GetBendMode()){
		dt = dt/5;
	}
	Camera::Update(dt);

	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->SetCloseToBaon(false);
		if (!enemies[i]->IsRemovable()) {
			enemies[i]->Update(dt);
			enemyAI->SetEnemy(enemies[i].get());
			enemyAI->update(dt);

			if (tileMap->CheckCollisions(enemies[i]->GetBox(), enemies[i]->GetScale())) {
				tileMap->ResolveTileCollisions(enemies[i].get());
			}
		}
		else{
			enemies.erase(enemies.begin() + i);
		}
	}

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

		baon->Update(dt);
		if (tileMap->CheckCollisions(baon->GetBox(), baon->GetScale())) {
			tileMap->ResolveTileCollisions(baon);
		}
	}

	if(!baon->bendHUD->IsDead()){
		baon->bendHUD->Update(dt);
	}

	for(unsigned i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->GetID() == 100) {

					PedraBasico *pedra = (PedraBasico*)objectArray[i].get();
					if(pedra->Isthrown()){
						for(unsigned j = 0; j < enemies.size(); j++){
							if(Collision::IsColliding(objectArray[i]->GetBox(), enemies[j]->GetBox(), 0, 0)){
								enemies[j]->NotifyCollision(objectArray[i].get());
								objectArray.erase(objectArray.begin() + i);
								break;
							}
						}
					}
				} else {
					if(objectArray[i]->GetID() == 101){
						PedraBasico *pedra = (PedraBasico*)objectArray[i].get();
						if(pedra->Isthrown()){
							for(unsigned j = 0; j < enemies.size(); j++){
								if(Collision::IsColliding(objectArray[i]->GetBox(), baon->GetBox(), 0, 0)){
									baon->NotifyCollision(objectArray[i].get());
									objectArray.erase(objectArray.begin() + i);
									break;
								}
							}
						}
					}
				}
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

	Hud::GetInstance()->Render();

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
