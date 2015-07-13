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

	Enemy* e = new Enemy(scale, 700);
	SwordEnemy* swordEnemy = new SwordEnemy(scale, 600);
	BigEnemy* bigEnemy = new BigEnemy(scale, 50);
	enemyAI = new EnemyAIManager(baon, e);
	swordEnemyAI = new SwordEnemyAIManager(baon, swordEnemy);
	bigEnemyAI = new BigEnemyAIManager(baon, bigEnemy);

	AddObject(new Monumento(90, 8, scale, level));
	AddObject(new Monumento(215, 8, scale, level));

	AddObject(baon);

	AddObject(e);
	AddObject(swordEnemy);
	AddObject(bigEnemy);

	LoadLevelData("data/level2-data.txt");

	AddObject(new Scroll(scale, 2));

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);
}

StageTwo::~StageTwo() {
}

bool StageTwo::OnLevelWon(float dt) {
	levelUpTimer->Update(dt);
	if (!levelWon) {
		music->Stop();
		delete music;
		music = new Music("audio/sfx_levelWon.wav");
		music->Play(0);
		//levelWonSound->Play(0);
		levelWon = true;
		SDL_Color color;
		color.r = color.g = color.b = 225;
		color.a = 255;
		levelUpText = new Text("font/Call me maybe.ttf", 40, Text::SOLID,
				"YOU WIN!", color, Game::SCREEN_WIDTH/2 - 70, Game::SCREEN_HEIGHT/2 - 40);
	}

	if (baon->IsFinished() && levelUpTimer->Get() > 6) {
		Game::GetInstance()->Push(new StageThree());
		popRequested = true;
		levelWonSound->Stop();
		music->Stop();
		return true;
	}
	return false;
}
