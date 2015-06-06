/*
 * Stage.cpp
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#include "Stage.h"

#include "Engine/InputManager.h"
#include "Engine/Camera.h"
#include <iostream>

Stage::Stage() {
	int scale = 4;
	Camera::pos.setX(0);
	Camera::pos.setY(0);
	baon = new Baon(scale);
	enemies.emplace_back(new Enemy(scale));
	enemyAI = new EnemyAIManager(baon, enemies[0].get());
	monuments.emplace_back(new Monumento(1744, scale));
	monuments.emplace_back(new Monumento(5456, scale));
	sp = new Sprite("img/blackback.png");
	tileMap = new TileMap("map/Tiles Floresta - Bender.tmx", 5, scale);
	sp->SetScaleX(2);
	sp->SetScaleY(2);
	Camera::Follow(baon);
}

Stage::~Stage() {
	delete baon;
	delete enemyAI;
	delete sp;
	delete tileMap;
}

void Stage::Update(float dt) {
	Camera::Update(dt);
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)
			|| InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}

	baon->Update(dt);

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update(dt);

		if (!enemies[i]->IsDead()) {
			if (tileMap->CheckCollisions(enemies[i].get())) {
				tileMap->ResolveTileCollisions(enemies[i].get());
				enemies[i]->NotifyTileCollision();
			}
		}
	}

	enemyAI->update(dt);

	if (baon == NULL) {
		Camera::Unfollow();
	} else {

		if (tileMap->CheckCollisions(baon)) {
			tileMap->ResolveTileCollisions(baon);
			baon->NotifyTileCollision();
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

	baon->Render();

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}
}

void Stage::Pause() {
}

void Stage::Resume() {
}

Baon* Stage::GetPlayer(){
	return baon;
}
