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
	this->levelWon = false;
	this->levelWonSound = new Sound("audio/sfx_levelWon.wav");

	Hud::GetInstance(scale, level);
}

AbstractStage::~AbstractStage() {
	if (music != NULL) {
		music->Stop();
	}

	objectArray.clear();
	delete music;
	delete tileMap;
	delete levelUpText;
	delete levelUpTimer;
	delete enemyAI;
	delete swordEnemyAI;
	delete levelWonSound;
}

void AbstractStage::OnUpdate(float dt, GameObject* object) {
	if(!popRequested){
		Hud::GetInstance()->Update(dt);

		if(baon->GetBendMode()){
			SetSlowMotion(5);
		}
		else{
			SetSlowMotion(1);
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

		if(object->GetID() == GameObject::ENEMY){
			UpdateBenderEnemy((Enemy*)object, dt);
		}

		if(object->GetID() == GameObject::SWORD_ENEMY){
			UpdateSwordEnemy((SwordEnemy*)object, dt);
		}

		if(object->GetID() == GameObject::BAON){
			if (baon->GetLevelWon()) {
				if (OnLevelWon(dt)) {
					return;
				}
			}
			else{
				baon->SetCloseToEnemy(false);
				baon->SetTouchingGround(tileMap->IsTouchingGround(baon->GetBox(), baon->GetScale()));

				if(!baon->bendHUD->IsDead()){
					baon->bendHUD->Update(dt);
				}

				if (tileMap->CheckCollisions(baon->GetBox(), baon->GetScale())) {
					tileMap->ResolveTileCollisions(baon);
				}
			}
		}
	}
}

void AbstractStage::ResolveDeadObject(GameObject* object){
	if(object->GetID() == GameObject::BAON){
		Camera::Unfollow();
		popRequested = true;
	}
}

void AbstractStage::Render() {
	for (int i = 0; i < tileMap->GetDepth(); i++) {
		tileMap->Render(i, 0, Camera::pos.getX(), Camera::pos.getY());
	}

	for (unsigned int i = 0; i < monuments.size(); i++) {
		monuments[i]->Render();
	}

	if(!baon->bendHUD->IsDead()){
		baon->bendHUD->Render();
	}

	Hud::GetInstance()->Render();

	if (levelUpText != NULL) {
		levelUpText->Render();
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

void AbstractStage::UpdateBenderEnemy(Enemy* enemy, float dt) {
	enemy->SetCloseToBaon(false);
	enemyAI->SetEnemy(enemy);
	enemyAI->update(dt);

	if (tileMap->CheckCollisions(enemy->GetBox(), enemy->GetScale())) {
		tileMap->ResolveTileCollisions(enemy);
	}
}

void AbstractStage::Update(float dt) {
}

void AbstractStage::UpdateSwordEnemy(SwordEnemy* enemy, float dt) {
	swordEnemyAI->SetEnemy(enemy);
	swordEnemyAI->update(dt);

	if (tileMap->CheckCollisions(enemy->GetBox(), enemy->GetScale())) {
		tileMap->ResolveTileCollisions(enemy);
	}
}
