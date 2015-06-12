/*
 * Monumento.cpp
 *
 *  Created on: May 27, 2015
 *      Author: -Bernardo
 */

#include "Monumento.h"

Monumento::Monumento(int posX, int scale) {
	sp = new Sprite("img/monumento.png");

	box.SetX(posX * 16 * scale);
	box.SetY(MONUMENT_MAP_GROUND * 16 * scale);
	box.SetH(sp->GetHeight());
	box.SetW(sp->GetWidth());
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
}

Monumento::~Monumento() {
	delete sp;
}

void Monumento::Update(float dt) {
	// TODO ?
}

bool Monumento::IsDead() {
	return false;
}

void Monumento::Render() {
	sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0);
}

void Monumento::NotifyCollision(GameObject* other) {
	// TOOD
}

bool Monumento::Is(std::string type) {
	return type.compare("Monument") == 0;
}
