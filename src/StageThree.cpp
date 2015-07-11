/*
 * StateThree.cpp
 *
 *  Created on: Jul 4, 2015
 *      Author: -Bernardo
 */

#include "StageThree.h"

StageThree::StageThree(int posX) : AbstractStage(2, 3, posX) {

	Game::GetInstance()->SetCheckpoint(new Checkpoint(level, -1));

	music = new Music("audio/deserto.ogg");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("deserto.tmx", 6, scale);

	baon = new Baon(scale, tileMap->GetMapMax(), initialPositionX);
	baon->SetGroundTouchResolver(tileMap);

	Enemy* enemy = new Enemy(scale, 450);
	enemyAI = new EnemyAIManager(baon, enemy);

	AddObject(new Monumento(90, 9, scale, level));
	AddObject(new Monumento(205, 8, scale, level));

	AddObject(baon);

	AddObject(enemy);
	AddObject(new Enemy(scale, 3800));
	AddObject(new Enemy(scale, 8000));
	AddObject(new Enemy(scale, 8600));
	AddObject(new Enemy(scale, 9500));

	AddObject(new Scroll(scale, level));

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);
}

StageThree::~StageThree() {}

bool StageThree::OnLevelWon(float dt) {
	levelUpTimer->Update(dt);

	if (levelUpTimer->Get() > 1) {
		if (!levelWon) {
			music->Stop();
			levelWonSound->Play(0);
			levelWon = true;
		}
		SDL_Color color;
		color.r = color.g = color.b = 125;
		color.a = 255;
		levelUpText = new Text("font/Call me maybe.ttf", 40, Text::SOLID,
				"YOU WIN! Press space", color, Game::SCREEN_WIDTH/2 - 150, Game::SCREEN_HEIGHT/2 - 40);
		if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
			Game::GetInstance()->SetCheckpoint(NULL);
			popRequested = true;
		}
		return true;
	}
	return false;
}
