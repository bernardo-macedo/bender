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

	int scale = 2;

	music = new Music("audio/floresta.mp3");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("floresta.tmx", 5, scale);

	baon = new Baon(scale, tileMap->GetMapMax());

	enemies.emplace_back(new Enemy(scale, 100));
	enemies.emplace_back(new Enemy(scale, 500));
	enemies.emplace_back(new Enemy(scale, 900));
	enemyAI = new EnemyAIManager(baon, enemies[0].get());
	enemyAI2 = new EnemyAIManager(baon, enemies[1].get());
	enemyAI3 = new EnemyAIManager(baon, enemies[2].get());

	monuments.emplace_back(new Monumento(102, scale));
	monuments.emplace_back(new Monumento(262, scale));

	//AddObject(new Monumento(102, scale));
	//AddObject(new Monumento(262, scale));
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
	delete baon;
	delete enemyAI;
	delete enemyAI2;
	delete enemyAI3;
	delete sp;
	delete tileMap;
}

void Stage::Update(float dt) {

	if(baon->GetBendMode()){
		dt = dt/5;
	}
	Camera::Update(dt);
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)
			|| InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update(dt);

		if (!enemies[i]->IsDead()) {
			if (tileMap->CheckCollisions(enemies[i].get())) {
				tileMap->ResolveTileCollisions(enemies[i].get());
				//enemies[i]->NotifyTileCollision();
			}
		}
	}

	UpdateArray(dt);

	for (unsigned int i = 0; i < monuments.size(); i++) {
		monuments[i]->Update(dt);
		if (monuments[i]->IsDead()) {
			monuments.erase(monuments.begin() + i);
		}
	}

	enemyAI->update(dt);
	enemyAI2->update(dt);
	enemyAI3->update(dt);

	if (baon->IsDead()) {
		Camera::Unfollow();
	} else {
		baon->Update(dt);
		if (tileMap->CheckCollisions(baon)) {
			tileMap->ResolveTileCollisions(baon);
			//baon->NotifyTileCollision();
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

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}

	RenderArray();
}

void Stage::Pause() {
}

void Stage::Resume() {
	//music->Play(5);
}

Baon* Stage::GetPlayer(){
	return baon;
}
