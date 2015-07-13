/*
 * Stage.cpp
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#include "Stage.h"

#include <stddef.h>
#include <SDL_pixels.h>

#include "BendHUD.h"
#include "SwordEnemy.h"
#include "Engine/Camera.h"
#include "Engine/Collision.h"
#include "Engine/Geometry/Point.h"
#include "Engine/InputManager.h"
#include "Engine/Sprite.h"
#include "PedraBasico.h"

Stage::Stage(int posX) : AbstractStage(2, 1, posX) {
	int scale = 2;
	int level = 1;

	music = new Music("audio/floresta.ogg");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("floresta.tmx", 5, scale);

	baon = new Baon(scale, tileMap->GetMapMax(), initialPositionX);
	baon->SetGroundTouchResolver(tileMap);
	
	Enemy* e = new Enemy(scale, 700);
	SwordEnemy* swordEnemy = new SwordEnemy(scale, 600);
	BigEnemy* bigEnemy = new BigEnemy(scale, 50);
	enemyAI = new EnemyAIManager(baon, e);
	swordEnemyAI = new SwordEnemyAIManager(baon, swordEnemy);
	bigEnemyAI = new BigEnemyAIManager(baon, bigEnemy);

	AddObject(new Monumento(102, 8, scale, level));
	AddObject(new Monumento(262, 8, scale, level));

	AddObject(baon);

	AddObject(e);
	AddObject(swordEnemy);
	AddObject(bigEnemy);

	LoadLevelData("data/level1-data.txt");

	AddObject(new Scroll(scale, level));

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);
}

Stage::~Stage() {
}

bool Stage::OnLevelWon(float dt) {
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
		Game::GetInstance()->Push(new StageTwo());
		popRequested = true;
		//levelWonSound->Stop();
		music->Stop();
		return true;
	}
	return false;
}
