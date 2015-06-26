/*
 * Stage.cpp
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#include "Stage.h"

#include "Engine/Camera.h"
#include "Engine/Collision.h"
#include "Engine/Geometry/Point.h"
#include "Engine/InputManager.h"
#include "Engine/Sprite.h"
#include "PedraBasico.h"

Stage::Stage() {

	int scale = 2;

	music = new Music("audio/floresta.ogg");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("floresta.tmx", 5, scale);

	levelUpTimer = new Timer();

	baon = new Baon(scale, tileMap->GetMapMax());

	//enemies.emplace_back(new Enemy(scale, 100));
	enemies.emplace_back(new Enemy(scale, 500));
	enemies.emplace_back(new Enemy(scale, 900));
	enemyAI = new EnemyAIManager(baon, enemies[0].get());

	monuments.emplace_back(new Monumento(102, scale));
	monuments.emplace_back(new Monumento(262, scale));

	AddObject(new Scroll(scale, 1));
	AddObject(new Hud(scale, 1));

	sp = new Sprite("img/blackback.png");
	sp->SetScaleX(2);
	sp->SetScaleY(2);

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);
}

Stage::~Stage() {
	if (music != NULL) {
		music->Stop();
	}

	delete music;
	delete baon;
	delete enemyAI;
	delete sp;
	delete tileMap;
	delete levelUpTimer;
}

void Stage::Update(float dt) {
	baon->SetCloseToEnemy(false);
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

			if (tileMap->CheckCollisions(enemies[i].get())) {
				tileMap->ResolveTileCollisions(enemies[i].get());
			}
		}
		else{
			enemies.erase(enemies.begin() + i);
		}
	}

	UpdateArray(dt);

	for (unsigned int i = 0; i < monuments.size(); i++) {
		monuments[i]->Update(dt);
		if (monuments[i]->IsDead()) {
			monuments.erase(monuments.begin() + i);
		}
	}

	if (baon->IsDead()) {
		Camera::Unfollow();
		popRequested = true;
	} else {
		// Resolve levelUp
		if (baon->GetLevelWon()) {
			levelUpTimer->Update(dt);

			if (levelUpTimer->Get() > 5) {
				Game::GetInstance()->Push(new StageTwo());
				popRequested = true;
				return;
			}
		}

		baon->Update(dt);
		if (tileMap->CheckCollisions(baon)) {
			tileMap->ResolveTileCollisions(baon);
		}


	}

	if(!baon->bendHUD->IsDead()){
		baon->bendHUD->Update(dt);
	}

	for(unsigned i = 0; i < objectArray.size(); i++){
		if(objectArray[i]->Is("basico")){
			PedraBasico *pedra = (PedraBasico*)objectArray[i].get();
			if(pedra->Isthrown()){
				for(unsigned j = 0; j < enemies.size(); j++){
					if(Collision::IsColliding(objectArray[i]->GetBox(), enemies[j]->GetBox(), 0, 0)){
						enemies[j]->NotifyCollision(objectArray[i].get());
						objectArray.erase(objectArray.begin() + i);
						break;
					}
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

void Stage::Render() {
	sp->Render(0, 0, 0);
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

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}

	RenderArray();
}

void Stage::Pause() {
	if (music != NULL) {
		music->Stop();
	}
}

void Stage::Resume() {
	if (music != NULL) {
		music->Play(Music::ALWAYS);
	}
}

Baon* Stage::GetPlayer(){
	return baon;
}
