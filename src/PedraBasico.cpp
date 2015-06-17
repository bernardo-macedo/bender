/*
 * PedraBasico.cpp
 *
 *  Created on: 14/06/2015
 *      Author: Pedro2
 */

#include "PedraBasico.h"

#include <iostream>

#include "Engine/Camera.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Physics/Body.h"
#include "Engine/Physics/Physic.h"

PedraBasico::PedraBasico(int x, int y, int scale) {
	sp = new Sprite("img/basico.png", 7, 0.1);
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	collided = false;
	this->scale = scale;

	b = new Body("basico", x, y);
	box.SetX(x);
	box.SetY(y);
	box.SetW(21*scale);
	box.SetH(20*scale);
}

PedraBasico::~PedraBasico() {
	delete sp;
}

void PedraBasico::Update(float dt) {
	Physic::GetInstance()->UpdatePhysic(GetBody(), dt);
	box.SetX(GetBody()->GetX());
	box.SetY(GetBody()->GetY());
	box.SetW(21*scale);
	box.SetH(20*scale);
}

bool PedraBasico::IsDead() {
	return collided;
}

void PedraBasico::Render() {
	sp->Render(GetBox().GetX() + Camera::pos.getX(), GetBox().GetY() + Camera::pos.getY(), 0, false);
}

void PedraBasico::NotifyCollision(GameObject* other) {
}

void PedraBasico::NotifyTileCollision() {
}

bool PedraBasico::Is(std::string type) {
	return type.compare("basico") == 0;
}

Sprite* PedraBasico::GetSprite() {
	return sp;
}
