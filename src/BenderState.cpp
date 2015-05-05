/*
 * BenderState.cpp
 *
 *  Created on: 30/04/2015
 *      Author: Pedro2
 */

#include "BenderState.h"
#include "Engine/InputManager.h"
#include "Engine/Game.h"
#include "Engine/Geometry/Point.h"
#include <math.h>

BenderState::~BenderState() {
	// TODO Auto-generated destructor stub
}

void BenderState::Setup() {
	tileSet = new TileSet(64, 64, "img/tileset.png");
	tileMap = new TileMap("map/tileMap.txt", tileSet);
	bg = new Sprite("img/ocean.jpg");
	m = new Minion(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
	AddObject(m);
	Camera::Follow(m);
}

void BenderState::Update() {
	int mouseX, mouseY;
	bool colPos[4]; //left up right down

	mouseX = InputManager::GetInstance().GetMouseX();
	mouseY = InputManager::GetInstance().GetMouseY();

	if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}

	Camera::Update(Game::GetInstance()->GetDeltaTime());
	m->Update(Game::GetInstance()->GetDeltaTime());
	Point col;
	int c = tileMap->collides(m, 0, &col);
	if(c == Rect::BOTTOM){
		m->GetBody()->SetVelY(0);
		m->GetBody()->SetY(col.getY() - m->GetBox().GetH()/2 - 1);
	}
	if(c == Rect::TOP){
		m->GetBody()->SetVelY(-m->GetBody()->GetVelY());
		m->GetBody()->SetY(col.getY() + m->GetBox().GetH()/2 + 1);
	}
	if(c == Rect::LEFT || c == Rect::RIGHT){
		m->GetBody()->SetVelX(-m->GetBody()->GetVelX());
		m->GetBody()->SetAngularVel(-m->GetBody()->GetAngularVel());
	}
}

void BenderState::Render() {
	bg->Render(0, 0, 0);
	tileMap->Render(0, 1, Camera::pos.getX(), Camera::pos.getY());
	for(int i = 0; i < objectArray.size(); i++) {
		if((objectArray[i])->IsDead()){
			objectArray.erase(objectArray.begin() + i);
		}
		else{
			objectArray[i]->Render();
		}
	}
	tileMap->Render(1, 1, Camera::pos.getX(), Camera::pos.getY());
}
