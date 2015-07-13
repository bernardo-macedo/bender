/*
 * TitleState.cpp
 *
 *  Created on: May 19, 2015
 *      Author: -Bernardo
 */

#include "TitleState.h"

TitleState::TitleState() {
	bg = new Sprite("img/title.png", 24, 0.1);
	bg->SetScaleX(2);
	bg->SetScaleY(2);

	menu = new MenuPrincipal(2);
	music = new Music("audio/title.ogg");
	music->Play(Music::ALWAYS);

	selectButtonSound = new Sound("audio/sfx_menuSelect.wav");

}

TitleState::~TitleState() {
	if (music != NULL) {
		music->Stop();
	}
	delete bg;
	delete menu;
	delete music;
	delete selectButtonSound;
}

void TitleState::Update(float dt) {
	bg->Update(dt);
	menu->Update(dt);
	quitRequested = InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().KeyPress(ENTER_KEY)) {
		selectButtonSound->Play(0);
		switch (menu->GetSelectedButton()) {
		case 0:
			Game::GetInstance()->SetCheckpoint(NULL);
			Game::GetInstance()->Push(new StageTwo());
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
					Game::GetInstance()->Push(new StageThree(lastCheckpoint->GetPositionX()));
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
	bg->Render(0,0);
	menu->Render();
}

void TitleState::Pause() {

}

void TitleState::Resume() {
	if (music != NULL) {
		music->Play(Music::ALWAYS);
	}
}

void TitleState::OnUpdate(float dt, GameObject*) {
}

void TitleState::ResolveDeadObject(GameObject* object) {
}
