/*
 * Hud.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#include "Hud.h"

Hud::Hud(int scale, int phase) {
	hud.Open("img/hud.png");

	hud.SetScaleX(scale);
	hud.SetScaleY(scale);

	box.SetX(Game::SCREEN_WIDTH/2 - hud.GetWidth()/2);
	box.SetY(8 * scale);

	switch(phase) {
	case 3:
		hudItems.push_back(CoolDown(box.GetX() + (33 * scale), box.GetY(), scale));
	case 2:
		hudItems.push_back(CoolDown(box.GetX() + (14 * scale), box.GetY() + (25 * scale), scale));
		hudItems.push_back(CoolDown(box.GetX() + (33 * scale), box.GetY() + (25 * scale), scale));
	case 1:
		hudItems.push_back(CoolDown(box.GetX(), box.GetY() + (12 * scale), scale));
		hudItems.push_back(CoolDown(box.GetX() + (47 * scale), box.GetY() + (12 * scale), scale));
		hudItems.push_back(CoolDown(box.GetX() + (14 * scale), box.GetY() + 0, scale));
		break;
	default:
		break;
	}

}

Hud::~Hud() {
	// TODO Auto-generated destructor stub
}

void Hud::Update(float dt) {
	// Para testes apenas! Substituir o codigo deste metodo!

	for (unsigned int i = 0; i < hudItems.size(); i++) {
		hudItems[i].Update(dt);
	}

}

bool Hud::IsDead() {
	return false;
}

void Hud::Render() {
	hud.Render(box.GetX(), box.GetY(), 0);

	for (unsigned int i = 0; i < hudItems.size(); i++) {
		hudItems[i].Render();
	}
}

void Hud::NotifyCollision(GameObject* other) {
}

bool Hud::Is(std::string type) {
	return type.compare("Hud") == 0;
}
