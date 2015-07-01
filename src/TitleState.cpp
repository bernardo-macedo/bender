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
	music = new Music("audio/title.ogg");
	music->Play(Music::ALWAYS);

}

TitleState::~TitleState() {
	if (music != NULL) {
		music->Stop();
	}

	delete menu;
	delete music;
}

void TitleState::Update(float dt) {

	menu->Update(dt);

	quitRequested = InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().KeyPress(ENTER_KEY)) {
		switch (menu->GetSelectedButton()) {
		case 0:
			Game::GetInstance()->SetCheckpoint(NULL);
			Game::GetInstance()->Push(new Stage());
			break;
		case 1:
		{
			Checkpoint *lastCheckpoint = Game::GetInstance()->GetCheckpoint();
			if (lastCheckpoint != NULL) {
				if (lastCheckpoint->GetLevel() == 1) {
					Game::GetInstance()->Push(new Stage(lastCheckpoint->GetPositionX()));
				} else if (lastCheckpoint->GetLevel() == 2) {
					Game::GetInstance()->Push(new StageTwo(lastCheckpoint->GetPositionX()));
				} else if (lastCheckpoint->GetLevel() == 3) {
					// StageThree()..
				}
			}
		}
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
	if (music != NULL) {
		music->Play(Music::ALWAYS);
	}
}
