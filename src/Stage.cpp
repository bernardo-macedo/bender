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
	Camera::pos.setX(0);
	Camera::pos.setY(0);
	baon = new Baon();
	sp = new Sprite("img/blackback.png");
	tileMap = new TileMap("map/Tiles Floresta - Bender.tmx");
	sp->SetScaleX(2);
	sp->SetScaleY(2);
	Camera::Follow(baon);
}

void Stage::Update(float dt) {
	Camera::Update(dt);
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)
			|| InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}
	baon->Update(dt);

	if (baon == NULL) {
		Camera::Unfollow();
	}

	//std::cout << "Baon.x = " << baon->GetBox().GetX() << " Baon.y = " << baon->GetBox().GetY() << std::endl;
	//std::cout << "Camera.x = " << Camera::pos.getX() << " Camera.y = " << Camera::pos.getY() << std::endl;
}

void Stage::Render() {
	sp->Render(0, 0, 0);
	for (int i = 0; i < tileMap->GetDepth(); i++) {
		tileMap->Render(i, 0, Camera::pos.getX(), Camera::pos.getY());
	}
	baon->Render();
}

void Stage::Pause() {
}

void Stage::Resume() {
}
