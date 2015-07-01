/*
 * StageTwo.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#include "StageTwo.h"

#include <stddef.h>
#include <SDL_pixels.h>

#include "Baon.h"
#include "Engine/Collision.h"
#include "Engine/Game.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Timer.h"
#include "PedraBasico.h"

StageTwo::StageTwo(int posX) : State(posX) {
	int scale = 2;

	Game::GetInstance()->SetCheckpoint(new Checkpoint(2, -1));

	music = new Music("audio/pantano.ogg");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("pantano.tmx", 0, scale);
	tileMap->SetExtraCollisionLayer(10);

	baon = new Baon(scale, tileMap->GetMapMax(), initialPositionX);

	AddObject(new Scroll(scale, 2));
	AddObject(new Hud(scale, 2));

	monuments.emplace_back(new Monumento(90, scale, 2));
	monuments.emplace_back(new Monumento(215, scale, 2));

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);

	levelUpTimer = new Timer();

	enemies.emplace_back(new Enemy(scale, 900));
	enemies.emplace_back(new Enemy(scale, 4000));
	enemies.emplace_back(new Enemy(scale, 8000));
	enemies.emplace_back(new Enemy(scale, 8300));
	enemies.emplace_back(new Enemy(scale, 8600));

	enemyAI = new EnemyAIManager(baon, enemies[0].get());
	levelUpText = NULL;
}

StageTwo::~StageTwo() {
	if (music != NULL) {
		music->Stop();
	}

	delete baon;
	delete music;
	delete tileMap;
}

void StageTwo::Update(float dt) {
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
			levelUpTimer->Update(dt);

			if (levelUpTimer->Get() > 1) {
				SDL_Color color;
				color.r = color.g = color.b = 225;
				color.a = 255;
				levelUpText = new Text("font/Call me maybe.ttf", 40, Text::SOLID,
						"YOU WIN! Press space", color, Game::SCREEN_WIDTH/2 - 150, Game::SCREEN_HEIGHT/2 - 40);
				if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
					// TODO: Remover isso quando existir fase 3!
					Game::GetInstance()->SetCheckpoint(NULL);

					popRequested = true;
				}
				return;
			}
		}

		baon->Update(dt);
		if (tileMap->CheckCollisions(baon)) {
			tileMap->ResolveTileCollisions(baon);
			//baon->NotifyTileCollision();
		}
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

void StageTwo::Render() {
	for (int i = 0; i < tileMap->GetDepth(); i++) {
		tileMap->Render(i, 0, Camera::pos.getX(), Camera::pos.getY());
	}

	for (unsigned int i = 0; i < monuments.size(); i++) {
		monuments[i]->Render();
	}

	if(!baon->IsDead()){
		baon->Render();
	}

	RenderArray();

	if (levelUpText != NULL) {
		levelUpText->Render();
	}

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}
}

void StageTwo::Pause() {
	if (music != NULL) {
		music->Stop();
	}
}

void StageTwo::Resume() {
	if (music != NULL) {
		music->Play(Music::ALWAYS);
	}
}
