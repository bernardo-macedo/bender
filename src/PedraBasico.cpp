/*
 * PedraBasico.cpp
 *
 *  Created on: 14/06/2015
 *      Author: Pedro2
 */

#include "PedraBasico.h"

#include "Engine/Camera.h"
#include "Engine/Game.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Physics/Body.h"
#include "Engine/Physics/Physic.h"

PedraBasico::PedraBasico(int x, int y, int scale) {
	sp = new Sprite("img/basico.png", 7, 0.1);
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	this->scale = scale;
	limitX = 0;

	box.SetX(x);
	box.SetW(21*scale);
	box.SetH(20*scale);
	box.SetY(y);

	b = new Body("basico", box.GetX(), box.GetY());

	thrown = false;
	dead = false;
	goingLeft = false;
	collided = false;
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

	if(Isthrown()){
		if(GetBody()->GetX() > Game::SCREEN_WIDTH - Camera::pos.getX()
				|| GetBody()->GetX() < 0  - Camera::pos.getX()){
			dead = true;
		}
	}
}

bool PedraBasico::IsDead() {
	return collided || dead;
}

void PedraBasico::Render() {
	sp->Render(GetBox().GetX() + Camera::pos.getX(), GetBox().GetY() + Camera::pos.getY(), 0, false);
}

void PedraBasico::NotifyCollision(GameObject* other) {
	if(this->GetID() == GameObject::PEDRA_BASICO_BAON
			&& (other->GetID() == GameObject::ENEMY || other->GetID() == GameObject::SWORD_ENEMY)){
		dead = true;
	}
	if(this->GetID() == GameObject::PEDRA_BASICO_ENEMY
			&& other->GetID() == GameObject::BAON){
		dead = true;
	}
	if(other->GetID() == GameObject::PEDRA_DEFESA){
		dead = true;
	}
}

void PedraBasico::NotifyTileCollision(Collision::CollisionAxis collisionAxis) {
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
