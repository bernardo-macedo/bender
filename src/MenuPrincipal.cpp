/*
 * MenuPrincipal.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: -Bernardo
 */

#include "MenuPrincipal.h"
#include <iostream>

MenuPrincipal::MenuPrincipal(int scale) {
	this->scale = scale;
	LoadSpriteData();
	sp = new Sprite("img/menuLabels.png", 2);
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	selectedButton = 0;
}

MenuPrincipal::~MenuPrincipal() {
	delete sp;
}

void MenuPrincipal::Update(float dt) {

	if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)) {
		selectedButton = selectedButton < numButtons - 1 ? selectedButton + 1 : 0;
	}
	if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY)) {
		selectedButton = selectedButton == 0 ? numButtons - 1 : selectedButton - 1;
	}
}

void MenuPrincipal::Render() {
	for (int i = 0; i < numButtons; i++) {
		sp->SetFrameHeight(spriteData[i * 2]);
		sp->SetFrameWidth(spriteData[i * 2 + 1]);
		sp->SetLine(i, spriteData[i * 2]);
		if (i == selectedButton) {
			sp->SetFrame(2);
		} else {
			sp->SetFrame(1);
		}
		sp->Render(20 * scale, (20 + (i * sp->GetFrameHeight())) * scale, 0);
	}
}

int MenuPrincipal::GetSelectedButton() {
	return selectedButton;
}

void MenuPrincipal::LoadSpriteData() {
	FILE *fp = fopen("data/menu-data.txt", "r");
	fscanf(fp, "%d", &numButtons);
	int val;
	while(!feof(fp)){
		fscanf(fp, "%d", &val);
		spriteData.push_back(val);
	}
}
