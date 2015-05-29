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

	Body previousBody = baon->GetBodyValue();
	std::cout << "PreviousBody antes de Update: x = " << previousBody.GetX() << " y = " << previousBody.GetY() << std::endl;
	//previousBody.SetX(baon->GetBox().GetX());
	//previousBody.SetY(baon->GetBox().GetY());
	//std::cout << "PreviousBody antes de Update 2: x = " << previousBody.GetX() << " y = " << previousBody.GetY() << std::endl;
	baon->Update(dt);

	if (baon->GetBody()->GetForce("gravity") != NULL) {
		std::cout << "existe gravidade atuando" << std::endl;
	}

	for(auto enemy : enemies){
		enemy->Update(dt);
	}

	if (baon == NULL) {
		Camera::Unfollow();
	} else {
		Collision::CollisionSide collisionSide = tileMap->CheckCollisions(baon->GetBox());
		if (collisionSide.HasCollidedVertically()) {
			ResolveCollision(previousBody, dt, true);
			baon->NotifyTileCollision(&previousBody, dt);
		}
		if (collisionSide.HasCollidedHorizontally()) {
			ResolveCollision(previousBody, dt, false);
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

void Stage::ResolveCollision(Body previousBody, float dt, bool vertical) {
	float step;

	if (vertical) {
		// ignora colisao vertical se estiver indo pra cima
		if (baon->GetBody()->GetVelY() < 0) {
			return;
		}
		baon->SetBodyY(previousBody);
	} else {
		baon->SetBodyX(previousBody);
	}
	dt = dt/2;
	for (int i = 2; i < 3; i++) {
		baon->Update(dt);
		step = (1 << i);	// 2^i
		Collision::CollisionSide collisionSide = tileMap->CheckCollisions(baon->GetBox());
		if (collisionSide.HasCollided()) {
			if (collisionSide.HasCollidedHorizontally() && !vertical) {
				baon->SetBodyX(previousBody);
				baon->SetPosX(previousBody.GetX());
			}
			if (collisionSide.HasCollidedVertically() && vertical) {
				baon->SetBodyY(previousBody);
				baon->SetPosY(previousBody.GetY());
			}

			dt -= dt/step;
		} else {
			/*
			if (vertical) {
				baon->GetBody()->SetAccelY(0);
				baon->GetBody()->SetVelY(0);
			} else {
				baon->GetBody()->SetAccelX(0);
				std::cout << "Chamou SetVelX em ResolveCollision" << std::endl;
				baon->GetBody()->SetVelX(0);
			}
			*/
			previousBody = baon->GetBodyValue();
			dt += dt/step;
		}
	}

}
