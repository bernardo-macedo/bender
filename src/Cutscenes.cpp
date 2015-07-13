/*
 * Cutscenes.cpp
 *
 *  Created on: 13/07/2015
 *      Author: Pedro2
 */

#include "Cutscenes.h"

#include "Engine/Game.h"
#include "Engine/InputManager.h"
#include "Engine/Sprite.h"
#include "TitleState.h"

Cutscenes::Cutscenes() {
	music = new Music("audio/cutscenes.ogg");
	music->Play(Music::ALWAYS);
	t = new Timer();
	c1 = new Sprite("img/cena1.png", 1, 1);
	c2 = new Sprite("img/cena2.png", 1, 1);
	c3 = new Sprite("img/cena3.png", 1, 1);
	c1->SetScaleX(2);
	c1->SetScaleY(2);
	c2->SetScaleX(2);
	c2->SetScaleY(2);
	c3->SetScaleX(2);
	c3->SetScaleY(2);
	number = 1;
}

Cutscenes::~Cutscenes() {
	delete music;
	delete c1;
	delete c2;
	delete c3;
	delete t;
}

void Cutscenes::ResolveDeadObject(GameObject* object) {
}

void Cutscenes::OnUpdate(float dt, GameObject* object) {
}

void Cutscenes::Update(float dt) {
	quitRequested = InputManager::GetInstance().QuitRequested();

	t->Update(dt);

	if (t->Get() > 10) {
		t->Restart();
		number++;
	}

	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
		number++;
		t->Restart();
	}
	if(InputManager::GetInstance().KeyPress(ENTER_KEY)){
		popRequested = true;
		Game::GetInstance()->Push(new TitleState());
	}

	if (number >= 4) {
		popRequested = true;
		Game::GetInstance()->Push(new TitleState());
	}
}

void Cutscenes::Render() {
	switch (number){
	case 1:
		c1->Render(0, 0, 0, false);
		break;
	case 2:
		c2->Render(0, 0, 0, false);
		break;
	case 3:
		c3->Render(0, 0, 0, false);
		break;
	default:
		break;
	}
}

void Cutscenes::Pause() {
}

void Cutscenes::Resume() {
}
