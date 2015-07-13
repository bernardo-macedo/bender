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
	// TODO Auto-generated destructor stub
}

void Cutscenes::ResolveDeadObject(GameObject* object) {
}

void Cutscenes::OnUpdate(float dt, GameObject* object) {
}

void Cutscenes::Update(float dt) {
	if(InputManager::GetInstance().KeyPress(SPACE_KEY)){
		number++;
	}

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
	case 4:
		popRequested = true;
		Game::GetInstance()->Push(new TitleState());
		break;
	}
}

void Cutscenes::Render() {
}

void Cutscenes::Pause() {
}

void Cutscenes::Resume() {
}
