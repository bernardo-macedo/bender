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

	tileMap = new TileMap("map/Tiles Floresta - Bender.tmx", 5, scale);

	baon = new Baon(scale, tileMap->GetMapMax());
	enemies.emplace_back(new Enemy(scale, 50));
	enemies.emplace_back(new Enemy(scale, 500));
	enemies.emplace_back(new Enemy(scale, 900));
	enemyAI = new EnemyAIManager(baon, enemies[0].get());
	enemyAI2 = new EnemyAIManager(baon, enemies[1].get());
	enemyAI3 = new EnemyAIManager(baon, enemies[2].get());
	monuments.emplace_back(new Monumento(1744, scale));
	monuments.emplace_back(new Monumento(5456, scale));

	sp = new Sprite("img/blackback.png");
	sp->SetScaleX(2);
	sp->SetScaleY(2);

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);

	music = new Music("audio/floresta.mp3");
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

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update(dt);

		if (!enemies[i]->IsDead()) {
			if (tileMap->CheckCollisions(enemies[i].get())) {
				tileMap->ResolveTileCollisions(enemies[i].get());
				enemies[i]->NotifyTileCollision();
			}
			if(baon != NULL){
				CollisionEnemies(i);
			}
		}
	}

	enemyAI->update(dt);
	enemyAI2->update(dt);
	enemyAI3->update(dt);

	if (baon == NULL) {
		Camera::Unfollow();
	} else {
		baon->Update(dt);
		if (tileMap->CheckCollisions(baon)) {
			tileMap->ResolveTileCollisions(baon);
			baon->NotifyTileCollision();
		}
		if(baon->IsDead()){
			baon = NULL;
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

	if(baon != NULL){
		baon->Render();
	}

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}
}

void Stage::Pause() {
}

void Stage::Resume() {
	music->Play(5);
}

Baon* Stage::GetPlayer(){
	return baon;
}

void Stage::CollisionEnemies(int i) {
	Rect a, b;
	a.SetH(baon->GetBox().GetH()*baon->GetScale());
	a.SetW(baon->GetBox().GetW()*baon->GetScale());
	a.SetX(baon->GetBox().GetX());
	a.SetY(baon->GetBox().GetY());

	b.SetH(enemies[i]->GetBox().GetH()*enemies[i]->GetScale());
	b.SetW(enemies[i]->GetBox().GetW()*enemies[i]->GetScale());
	b.SetX(enemies[i]->GetBox().GetX());
	b.SetY(enemies[i]->GetBox().GetY());
	if(Collision::IsColliding(a, b, 0, 0)){
		if(enemies[i]->isDamage){
			baon->TakeDamage(true);
		}
	}
}
