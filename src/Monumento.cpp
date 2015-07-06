/*
 * Monumento.cpp
 *
 *  Created on: May 27, 2015
 *      Author: -Bernardo
 */

#include "Monumento.h"

Monumento::Monumento(int posX, int posY, int scale, int level) : level(level) {
	used = false;

	sp = new Sprite("img/monumento.png", 2);

	box.SetX(posX * 16 * scale);
	box.SetY(posY * 16 * scale);
	box.SetH(sp->GetHeight());
	box.SetW(sp->GetWidth());
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	sp->SetFrame(1);
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
	if (!used && other->Is("Baon")) {
		Game::GetInstance()->SetCheckpoint(new Checkpoint(level, box.GetCenter().getX()));
		sp->SetFrame(2);
		Baon* baon = (Baon*) other;
		baon->RestoreLife();
		used = true;
	}
}

bool Monumento::Is(std::string type) {
	return type.compare("Monument") == 0;
}
