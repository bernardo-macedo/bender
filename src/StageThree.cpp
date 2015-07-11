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

	Enemy* e = new Enemy(scale, 450);
	SwordEnemy* swordEnemy = new SwordEnemy(scale, 600);
	enemyAI = new EnemyAIManager(baon, e);
	swordEnemyAI = new SwordEnemyAIManager(baon, swordEnemy);

	AddObject(new Monumento(90, 9, scale, level));
	AddObject(new Monumento(205, 8, scale, level));

	AddObject(baon);

	AddObject(e);
	AddObject(swordEnemy);

	LoadLevelData("data/level3-data.txt");

	AddObject(new Scroll(scale, level));

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);
}

StageThree::~StageThree() {}

bool StageThree::OnLevelWon(float dt) {

	levelUpTimer->Update(dt);
	if (!levelWon) {
		music->Stop();
		delete music;
		music = new Music("audio/sfx_levelWon.wav");
		music->Play(0);
		//levelWonSound->Play(0);
		levelWon = true;
		SDL_Color color;
		color.r = color.g = color.b = 125;
		color.a = 255;
		levelUpText = new Text("font/Call me maybe.ttf", 40, Text::SOLID,
				"CONGRATULATIONS!", color, Game::SCREEN_WIDTH/2 - 150, Game::SCREEN_HEIGHT/2 - 40);
	}

	if (InputManager::GetInstance().KeyPress(SPACE_KEY)
		|| InputManager::GetInstance().KeyPress(ENTER_KEY)
		|| InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)
		|| levelUpTimer->Get() > 6) {
		Game::GetInstance()->SetCheckpoint(NULL);
		popRequested = true;
		music->Stop();
		return true;
	}
	return false;
}
