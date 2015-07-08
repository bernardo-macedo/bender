/*
 * PedraBasico.cpp
 *
 *  Created on: 14/06/2015
 *      Author: Pedro2
 */

#include "PedraBasico.h"

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

	box.SetX(x);
	box.SetW(21*scale);
	box.SetH(20*scale);
	box.SetY(y);

	b = new Body("basico", box.GetX(), box.GetY());

	thrown = false;
	dead = false;
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
	return collided || dead;
}

void PedraBasico::Render() {
	sp->Render(GetBox().GetX() + Camera::pos.getX(), GetBox().GetY() + Camera::pos.getY(), 0, false);
}

void PedraBasico::NotifyCollision(GameObject* other) {
}

void PedraBasico::NotifyTileCollision() {
	// TODO: devia chamar collided true, mas da uns bugs
	// o ideal seria corrigir antes da entrega..but..
	//collided = true;
}

bool PedraBasico::Is(std::string type) {
	return Being::Is(type) || type.compare("basico") == 0;
}

Sprite* PedraBasico::GetSprite() {
	return sp;
}

bool PedraBasico::IsFinnished() {
	return sp->GetCurrentFrame() >= 7;
}

bool PedraBasico::IsGoingLeft() {
	return goingLeft;
}

void PedraBasico::SetGoingLeft(bool left) {
	this->goingLeft = left;
}

void PedraBasico::SetLimitX(int limit) {
	limitX = limit;
}

bool PedraBasico::GetLimitX() {
	return limitX;
}

bool PedraBasico::Isthrown() {
	return thrown;
}

void PedraBasico::SetThrown(bool thrown) {
	this->thrown = thrown;
}

void PedraBasico::SetDead(bool dead) {
	this->dead = dead;
}
