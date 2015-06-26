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
#include "Engine/Game.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Timer.h"

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

	levelUpTimer = new Timer();
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

	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();

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
}

void StageTwo::Render() {
	for (int i = 0; i < tileMap->GetDepth(); i++) {
		tileMap->Render(i, 0, Camera::pos.getX(), Camera::pos.getY());
	}

	if(!baon->IsDead()){
		baon->Render();
	}

	RenderArray();

	if (levelUpText != NULL) {
		levelUpText->Render();
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
