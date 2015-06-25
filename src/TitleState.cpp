/*
 * TitleState.cpp
 *
 *  Created on: May 19, 2015
 *      Author: -Bernardo
 */

#include "TitleState.h"

TitleState::TitleState() {
	bg.SetScaleX(2);
	bg.SetScaleY(2);

	bg.Open("img/title.png");
	menu = new MenuPrincipal(2);

}

TitleState::~TitleState() {
	delete menu;
}

void TitleState::Update(float dt) {

	menu->Update(dt);

	if (InputManager::GetInstance().KeyPress(ENTER_KEY)) {
		switch (menu->GetSelectedButton()) {
		case 0:
			Game::GetInstance()->Push(new Stage());
			break;
		case 3:
			this->quitRequested = true;
			break;
		default:
			break;
		}

	}
}

void TitleState::Render() {
	bg.Render(0,0);
	menu->Render();
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}
