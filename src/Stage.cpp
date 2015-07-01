/*
 * Stage.cpp
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#include "Stage.h"

#include <stddef.h>
#include <SDL_pixels.h>

#include "BendHUD.h"
#include "enemystates/SwordEnemy.h"
#include "Engine/Camera.h"
#include "Engine/Collision.h"
#include "Engine/Geometry/Point.h"
#include "Engine/InputManager.h"
#include "Engine/Sprite.h"
#include "PedraBasico.h"

Stage::Stage(int posX) : State(posX) {

	int scale = 2;

	music = new Music("audio/floresta.ogg");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("floresta.tmx", 5, scale);

	levelUpTimer = new Timer();

	baon = new Baon(scale, tileMap->GetMapMax(), initialPositionX);

	//enemies.emplace_back(new Enemy(scale, 100));
	enemies.emplace_back(new Enemy(scale, 900));
	enemies.emplace_back(new Enemy(scale, 4000));
	enemies.emplace_back(new Enemy(scale, 8000));
	enemies.emplace_back(new Enemy(scale, 8300));
	enemies.emplace_back(new Enemy(scale, 8600));

	//enemies.emplace_back(new SwordEnemy(scale, 50));
	enemyAI = new EnemyAIManager(baon, enemies[0].get());

	monuments.emplace_back(new Monumento(102, scale, 1));
	monuments.emplace_back(new Monumento(262, scale, 1));

	AddObject(new Scroll(scale, 1));
	AddObject(new Hud(scale, 1));

	sp = new Sprite("img/blackback.png");
	sp->SetScaleX(2);
	sp->SetScaleY(2);

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);

	levelUpText = NULL;
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
	delete levelUpText;
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
		} else if (Collision::IsColliding(monuments[i]->GetBox(), baon->GetBox(), 0 , 0)) {
			monuments[i]->NotifyCollision(baon);
		}
	}

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
			    	Game::GetInstance()->Push(new StageTwo());
			    	popRequested = true;
			    }
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
		if(objectArray[i]->GetID() == 100){
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
		}
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

	if (levelUpText != NULL) {
		levelUpText->Render();
	}
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
