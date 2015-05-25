/*
 * Stage.cpp
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#include "Stage.h"

#include "Engine/InputManager.h"
#include "Engine/Camera.h"

Stage::Stage() {
	Camera::pos.setX(0);
	baon = new Baon();
	sp = new Sprite("img/blackback.png");
	sp->SetScaleX(8);
	sp->SetScaleY(8);
}

void Stage::Update(float dt) {
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)
			|| InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}

	baon->Update(dt);
}

void Stage::Render() {
	sp->Render(0, 0, 0);
	baon->Render();
}

void Stage::Pause() {
}

void Stage::Resume() {
}
