/*
 * Scroll.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: -Bernardo
 */

#include "Scroll.h"
#include <iostream>

Scroll::Scroll(int scale, int phase) :
	phase(phase), isOpen(false) {
	sp = new Sprite("img/scrolls.png", 4);

	sp->SetScaleX(scale);
	sp->SetScaleY(scale);

	sp->SetFrame(1);

	box.SetX(250 * scale);
	box.SetY(96 * scale);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());

}

Scroll::~Scroll() {
	delete sp;
}

void Scroll::Update(float dt) {

	if (InputManager::GetInstance().KeyPress(H_KEY)) {
		if (isOpen) {
			sp->SetFrame(1);
			isOpen = false;
		} else {
			if (phase >= 0 && phase < 4) {
				sp->SetFrame(phase + 1);
				isOpen = true;
			}
		}
	}
}

bool Scroll::IsDead() {
	return false;
}

void Scroll::Render() {
	sp->Render(box.GetX(), box.GetY(), 0);
}

void Scroll::NotifyCollision(GameObject* other) {
}

bool Scroll::Is(std::string type) {
	return type.compare("Scroll") == 0;
}
