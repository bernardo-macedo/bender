/*
 * State.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include "StageState.h"

#include <cstdlib>
#include <ctime>

#include "Collision.h"
#include "Game.h"
#include "GameObject.h"
#include "Geometry/Point.h"
#include "../EndState.h"

StageState::StageState() {
	alienCount = 0;
	initialAlienCount = alienCount;
	tileMap = new TileMap("map/Tiles Floresta - Bender.tmx");
	quitRequested = false;
	bg = new Sprite("img/ocean.jpg");
	srand(time(NULL));

	camera = new Camera();

	p = new Penguins(100, 100);

	for(int i = 0; i < alienCount; i++){
		AddObject(new Alien(rand()%tileSet->GetTileWidth()*25,
							rand()%tileSet->GetTileHeight()*25,
							rand()%8 + 1, i + 10));
	}

	camera->Follow(p);
	AddObject(p);

	music = new Music("audio/stageState.ogg");
}

StageState::~StageState(){
	objectArray.clear();
}

void StageState::Update(float dt) {
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	if(InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}

	camera->Update(dt);

	Penguins *pl = (Penguins*)FindByID(0);
	for(int i = objectArray.size() - 1; i >= 0; --i) {
		objectArray[i]->Update(dt);
		for(int j = 0; j < initialAlienCount; j++){
			Alien *a = (Alien*)FindByID(j + 10);
			if(a != NULL){
				std::cout << a->GetID() << std::endl;
				if(Collision::IsColliding(a->GetBox(), objectArray[i]->GetBox(), a->GetAngle(), objectArray[i]->GetAngle())){
					a->NotifyCollision(objectArray[i].get());
					break;
				}
			}
		}
		if(pl != NULL){
			if(Collision::IsColliding(pl->GetBox(), objectArray[i]->GetBox(), pl->GetAngle(), objectArray[i]->GetAngle())){
				pl->NotifyCollision(objectArray[i].get());
			}
		}
	}
}

void StageState::Render() {
	bg->Render(0, 0);
	for (int i = 0; i < tileMap->GetDepth() - 1; i++) {
		tileMap->Render(i, 0, camera->pos.getX(), camera->pos.getY());
	}

	for(int i = 0; i < objectArray.size(); i++) {
		if((objectArray[i])->IsDead()){
			if(objectArray[i]->Is("Alien")){
				alienCount --;
				if(alienCount <= 0){
					popRequested = true;
					StateData *s = new StateData();
					s->playerVictory = true;
					Game::GetInstance()->Push(new EndState(s));
				}
			}
			if(objectArray[i]->Is("Penguins")){
				popRequested = true;
				StateData *s = new StateData();
				s->playerVictory = false;
				Game::GetInstance()->Push(new EndState(s));
			}
			objectArray.erase(objectArray.begin() + i);
		}
		else{
			objectArray[i]->Render();
		}
	}

	tileMap->Render(tileMap->GetDepth() - 1, 0, camera->pos.getX(), camera->pos.getY());
}

void StageState::Resume(){
	music->Play(Music::ALWAYS);
}

void StageState::Pause(){
	music->Stop();
}
