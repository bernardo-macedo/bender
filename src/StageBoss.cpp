/*
 * StageBoss.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: -Bernardo
 */

#include "StageBoss.h"

StageBoss::StageBoss(int posX): AbstractStage(2, 4, posX) {

	Game::GetInstance()->SetCheckpoint(new Checkpoint(level, -1));

	music = new Music("audio/cutscenes.ogg");
	music->Play(Music::ALWAYS);

	tileMap = new TileMap("boss.tmx", 7, scale);

	baon = new Baon(scale, tileMap->GetMapMax(), initialPositionX);
	baon->SetGroundTouchResolver(tileMap);

	// Boss* boss = new Boss(scale, 1000);
	// bossAI = new BossAIManager(baon, boss);

	AddObject(baon);

	// AddObject(boss);

	AddObject(new Scroll(scale, 2));

	Camera::pos.setX(0);
	Camera::pos.setY(0);
	Camera::Follow(baon);
}

StageBoss::~StageBoss() {
	// TODO Auto-generated destructor stub
}

bool StageBoss::OnLevelWon(float dt) {

	levelUpTimer->Update(dt);
	if (!levelWon) {
		music->Stop();
		delete music;
		music = new Music("audio/sfx_levelWon.wav");
		music->Play(0);
		levelWon = true;
		SDL_Color color;
		color.r = color.g = color.b = 125;
		color.a = 255;
		levelUpText = new Text("font/Call me maybe.ttf", 40, Text::SOLID,
				"CONGRATULATIONS!", color, Game::SCREEN_WIDTH/2 - 150, Game::SCREEN_HEIGHT/2 - 40);
	}

	if (baon->IsFinished() && levelUpTimer->Get() > 6) {
		Game::GetInstance()->SetCheckpoint(NULL);
		popRequested = true;
		music->Stop();
		return true;
	}
	return false;
}
