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
	enemies.push_back(new Enemy());
	enemyAI = new EnemyAIManager(baon, enemies[0]);
	monuments.push_back(new Monumento(1744));
	monuments.push_back(new Monumento(5456));
	sp = new Sprite("img/blackback.png");
	tileMap = new TileMap("map/Tiles Floresta - Bender.tmx", 5, 3);
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

	for(auto enemy : enemies){
		enemy->Update(dt);
	}

	enemyAI->update(dt);

	if (baon == NULL) {
		Camera::Unfollow();
	} else {

		if (tileMap->CheckCollisions(baon->GetBox())) {
			std::cout << "baon pos antes = (" << baon->GetBox().GetX() << ", " << baon->GetBox().GetY() << std::endl;
			tileMap->ResolveTileCollisions(baon);
			std::cout << "baon pos depois = (" << baon->GetBox().GetX() << ", " << baon->GetBox().GetY() << std::endl;
			baon->NotifyTileCollision(NULL, dt);
		}
	}

}

void Stage::Render() {
	sp->Render(0, 0, 0);
	for (int i = 0; i < tileMap->GetDepth(); i++) {
		tileMap->Render(i, 0, Camera::pos.getX(), Camera::pos.getY());
	}

	for(auto enemy : enemies){
		enemy->Render();
	}

	for(auto monument : monuments) {
		monument->Render();
	}

	baon->Render();
}

void Stage::Pause() {
}

void Stage::Resume() {
}

Baon* Stage::GetPlayer(){
	return baon;
}
