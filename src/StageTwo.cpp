/*
 * StageTwo.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#include "StageTwo.h"

StageTwo::StageTwo(int posX) : AbstractStage(2, 2, posX) {

	Game::GetInstance()->SetCheckpoint(new Checkpoint(level, -1));

	music = new Music("audio/pantano.ogg");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("pantano.tmx", 0, scale);
	tileMap->SetExtraCollisionLayer(10);

	baon = new Baon(scale, tileMap->GetMapMax(), initialPositionX);
	baon->SetGroundTouchResolver(tileMap);

	AddObject(new Scroll(scale, 2));

	monuments.emplace_back(new Monumento(90, 8, scale, level));
	monuments.emplace_back(new Monumento(215, 8, scale, level));

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
}

bool StageTwo::OnLevelWon(float dt) {
	levelUpTimer->Update(dt);

	if (levelUpTimer->Get() > 1) {
		SDL_Color color;
		color.r = color.g = color.b = 225;
		color.a = 255;
		levelUpText = new Text("font/Call me maybe.ttf", 40, Text::SOLID,
				"YOU WIN! Press space", color, Game::SCREEN_WIDTH/2 - 150, Game::SCREEN_HEIGHT/2 - 40);
		if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
			Game::GetInstance()->Push(new StageThree());
			popRequested = true;
		}
		return true;
	}
	return false;
}
