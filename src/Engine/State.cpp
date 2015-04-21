/*
 * State.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include <cstdlib>
#include <ctime>

#include "State.h"
#include "InputManager.h"
#include "Game.h"
#include "Constants.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

State::State() {
	tileSet = new TileSet(64, 64, Constants::ImgPath + "tileset.png");
	tileMap = new TileMap(Constants::MapPath + "tileMap.txt", tileSet);
	quitRequested = false;
	bg = new Sprite(Constants::ImgPath + "ocean.jpg");
	srand(time(NULL));
	camera = new Camera();
}

State::~State(){
	objectArray.clear();
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Update() {
	int mouseX, mouseY;
	bool achouFace = false;

	mouseX = InputManager::GetInstance().GetMouseX();
	mouseY = InputManager::GetInstance().GetMouseY();

	if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}

	if(InputManager::GetInstance().MousePress(1)){
		for(int i = objectArray.size() - 1; i >= 0; --i) {
			Face* face = (Face*) objectArray[i].get();

			if(face->GetBox().IsInside((float)(mouseX - camera->pos.getX()), (float)(mouseY - camera->pos.getY()))) {
				achouFace = true;
				face->Damage((rand() % 10 + 10));
				break;
			}
		}
		if(!achouFace){
			AddObject(mouseX - camera->pos.getX(), mouseY - camera->pos.getY());
		}
	}

	if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
		camera->pos.setX(camera->pos.getX() - 200*Game::GetInstance()->GetDeltaTime());
	}

	if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
		camera->pos.setX(camera->pos.getX() + 200*Game::GetInstance()->GetDeltaTime());
	}

	if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
		camera->pos.setY(camera->pos.getY() + 200*Game::GetInstance()->GetDeltaTime());
	}

	if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
		camera->pos.setY(camera->pos.getY() - 200*Game::GetInstance()->GetDeltaTime());
	}
}

void State::Render() {
	bg->Render(0, 0);
	tileMap->Render(0, 1, camera->pos.getX(), camera->pos.getY());
	for(int i = 0; i < objectArray.size(); i++) {
		if((objectArray[i])->IsDead()){
			objectArray.erase(objectArray.begin() + i);
		}
		else{
			objectArray[i]->Render(camera->pos.getX(), camera->pos.getY());
		}
	}
	tileMap->Render(1, 1, camera->pos.getX(), camera->pos.getY());
}

void State::AddObject(float mouseX, float mouseY){
	objectArray.emplace_back(new Face(mouseX, mouseY));
}
