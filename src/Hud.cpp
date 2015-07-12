/*
 * Hud.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#include "Hud.h"

Hud* Hud::instance = NULL;

Hud::Hud(int scale, int level) {
	hud.Open("img/hud.png");

	hud.SetScaleX(scale);
	hud.SetScaleY(scale);

	box.SetX(Game::SCREEN_WIDTH/2 - hud.GetWidth()/2);
	box.SetY(8 * scale);

	this->scale = scale;
	this->level = level;

	// Level 1
	hudItems.push_back(CoolDown(box.GetX(), box.GetY() + (12 * scale), scale, true));
	hudItems.push_back(CoolDown(box.GetX() + (47 * scale), box.GetY() + (12 * scale), scale, true));
	hudItems.push_back(CoolDown(box.GetX() + (14 * scale), box.GetY() + 0, scale, true));

	// Level 2
	hudItems.push_back(CoolDown(box.GetX() + (14 * scale), box.GetY() + (25 * scale), scale, level > 1));
	hudItems.push_back(CoolDown(box.GetX() + (33 * scale), box.GetY() + (25 * scale), scale, level > 1));

	// Level 3
	hudItems.push_back(CoolDown(box.GetX() + (33 * scale), box.GetY(), scale, level == 3));

	for (int i = 0; i < 6; i++) {
		bufferingAttacks[i] = false;
	}

}

Hud::~Hud() {}

void Hud::Update(float dt) {

	for (unsigned int i = 0; i < 6; i++) {
		if (bufferingAttacks[i]) {
			if (!hudItems[i].HasCompleted()) {
				hudItems[i].Update(dt);
			} else {
				bufferingAttacks[i] = false;
				hudItems[i].Restart();
			}
		}
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

void Hud::SetBuffering(HudAttack hudAttackNumber) {
	if (IsValidAttack(hudAttackNumber)) {
		bufferingAttacks[hudAttackNumber] = true;
	}
}

bool Hud::IsBuffering(HudAttack hudAttackNumber) {
	return bufferingAttacks[hudAttackNumber];
}

void Hud::SetLevel(int level) {
	this->level = level;

	if (level == 3) {
		hudItems[5].SetEnabled(true);
	}
	if (level > 1) {
		hudItems[3].SetEnabled(true);
		hudItems[4].SetEnabled(true);
	}
}

Hud* Hud::GetInstance(int scale, int level) {
	if (instance == NULL) {
		instance = new Hud(scale, level);
	} else {
		instance->SetLevel(level);
	}
	return instance;
}

Hud* Hud::GetInstance() {
	if (instance == NULL) {
		instance = new Hud(2, 1);
	}
	return instance;
}

bool Hud::IsValidAttack(HudAttack hudAttackNumber) {
	bool valid = false;

	switch (level) {
	case 3:
		valid = hudAttackNumber == HudAttack::SIX;
	case 2:
		valid = valid || hudAttackNumber == HudAttack::FOUR || HudAttack::FIVE;
	case 1:
		valid = valid || hudAttackNumber == HudAttack::ONE || hudAttackNumber == HudAttack::TWO || hudAttackNumber == HudAttack::THREE;
		break;
	default:
		break;
	}
	return valid;

}

int Hud::GetLevel() {
	return level;
}
