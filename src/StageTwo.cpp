/*
 * StageTwo.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#include "StageTwo.h"

StageTwo::StageTwo() {
	int scale = 2;

	music = new Music("audio/pantano.ogg");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("pantano.tmx", 0, scale);
	tileMap->SetExtraCollisionLayer(10);

	baon = new Baon(scale, tileMap->GetMapMax());

	AddObject(new Scroll(scale, 2));
	AddObject(new Hud(scale, 2));

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);
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
	Camera::Update(dt);
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)
			|| InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}

	UpdateArray(dt);

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

void StageTwo::Render() {
	for (int i = 0; i < tileMap->GetDepth(); i++) {
		tileMap->Render(i, 0, Camera::pos.getX(), Camera::pos.getY());
	}

	if(!baon->IsDead()){
		baon->Render();
	}

	RenderArray();
}

void StageTwo::Pause() {
}

void StageTwo::Resume() {
}
