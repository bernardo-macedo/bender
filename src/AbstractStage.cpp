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
	this->levelUpTimer = new Timer();
	this->levelUpText = NULL;

	baon = NULL;
	enemyAI = NULL;
	swordEnemyAI = NULL;
	bigEnemyAI = NULL;
	music = NULL;

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
	delete bigEnemyAI;
	delete levelWonSound;
}

void AbstractStage::OnUpdate(float dt, GameObject* object) {
	if(!popRequested){

		if(baon->GetBendMode()){
			SetSlowMotion(5);
		}
		else{
			SetSlowMotion(1);
		}

		Camera::Update(dt);

		popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
		quitRequested = InputManager::GetInstance().QuitRequested();

		if(object->GetID() == GameObject::ENEMY){
			UpdateBenderEnemy((Enemy*)object, dt);
		}

		if(object->GetID() == GameObject::SWORD_ENEMY) {
			UpdateSwordEnemy((SwordEnemy*)object, dt);
		}

		if (object->GetID() == GameObject::BIG_ENEMY) {
			UpdateBigEnemy((BigEnemy*)object, dt);
		}

		if(object->GetID() == GameObject::BAON){
			if (baon->GetLevelWon()) {
				OnLevelWon(dt);
			}
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

void AbstractStage::ResolveDeadObject(GameObject* object){
	if(object->GetID() == GameObject::BAON){
		Camera::Unfollow();
		popRequested = true;
		baon = NULL;
	}
}

void AbstractStage::Render() {
	for (int i = 0; i < tileMap->GetDepth(); i++) {
		tileMap->Render(i, 0, Camera::pos.getX(), Camera::pos.getY());
	}

	if(baon!= NULL && baon->bendHUD != NULL && !baon->bendHUD->IsDead()) {
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
	Hud::GetInstance()->Update(dt);
}

void AbstractStage::UpdateSwordEnemy(SwordEnemy* enemy, float dt) {
	swordEnemyAI->SetEnemy(enemy);
	swordEnemyAI->update(dt);

	if (tileMap->CheckCollisions(enemy->GetBox(), enemy->GetScale())) {
		tileMap->ResolveTileCollisions(enemy);
	}
}

void AbstractStage::UpdateBigEnemy(BigEnemy* enemy, float dt) {
	bigEnemyAI->SetEnemy(enemy);
	bigEnemyAI->update(dt);

	if (tileMap->CheckCollisions(enemy->GetBox(), enemy->GetScale())) {
		tileMap->ResolveTileCollisions(enemy);
	}
}

void AbstractStage::LoadLevelData(std::string file) {
	std::ifstream infile(file);
	std::string line;
	std::string enemyName;
	int position;
	while (std::getline(infile, line)) {
		std::istringstream iss(line);
		if (!(iss >> enemyName)) {
			break;
		} else if (enemyName == "bender") {
			while (iss >> position) {
				AddObject(new Enemy(scale, position));
				std::cout << "adicionou inimigo bender em " << position << std::endl;
			}
		} else if (enemyName == "sword") {
			while (iss >> position) {
				AddObject(new SwordEnemy(scale, position));
				std::cout << "adicionou inimigo sword em " << position << std::endl;
			}
		} else if (enemyName == "big") {
			while (iss >> position) {
				AddObject(new BigEnemy(scale, position));
				std::cout << "adicionou inimigo grande em " << position << std::endl;
			}
		} else {
			std::cout << "nada" << std::endl;
		}
	}
}
