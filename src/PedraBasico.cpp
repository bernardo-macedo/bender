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

PedraBasico::PedraBasico(int x, int y, int scale, RockDeathListener* listener) {
	this->listener = listener;
	sp = new Sprite("img/basico.png", 7, 0.1);
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	this->scale = scale;
	limitX = 0;
	limitY = -999;

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
	if (!IsFinnished()) {
		sp->Update(dt);
	}
	Physic::GetInstance()->UpdatePhysic(GetBody(), dt);

	if (limitY == -999) {
		// O limite em Y so eh setado para o Baon. O inimigo nao seta esse limite.
		// Se nao estiver setado o valor sera padrao (-999)
		box.SetX(GetBody()->GetX());
		box.SetY(GetBody()->GetY());
	} else {
		// O Y cresce pra baixo
		if (GetBody()->GetY() < limitY) {
			thrown = true;
			box.SetY(limitY);
			GetBody()->SetVelY(0);

			if (goingLeft) {
				GetBody()->SetVelX(-1000);
			} else {
				GetBody()->SetVelX(1000);
			}
		} else {
			box.SetY(GetBody()->GetY());
			GetBody()->SetVelY(-8 * (GetBody()->GetY() - limitY + 5));
			GetBody()->SetVelX(0);
		}
		box.SetX(GetBody()->GetX());
	}


	if(Isthrown()){
		if(GetBody()->GetX() > Game::SCREEN_WIDTH - Camera::pos.getX()
				|| GetBody()->GetX() < 0  - Camera::pos.getX()){
			dead = true;
			listener->OnRockDead();
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
			&& (other->GetID() == GameObject::ENEMY
					|| other->GetID() == GameObject::SWORD_ENEMY
					|| other->GetID() == GameObject::BIG_ENEMY)){
		dead = true;
		listener->OnRockDead();
	}
	if(this->GetID() == GameObject::PEDRA_BASICO_ENEMY
			&& (other->GetID() == GameObject::BAON
					|| other->GetID() == GameObject::PEDRA_DEFESA)){
		dead = true;
		listener->OnRockDead();
	}

	if(other->GetID() == GameObject::PEDRA_DEFESA) {
		dead = true;
		listener->OnRockDead();
	}

	if(other->GetID() == GameObject::BIG_ROCK){
		dead = true;
		listener->OnRockDead();
	}
}

void PedraBasico::NotifyTileCollision(Collision::CollisionAxis collisionAxis) {
	//collided = true;
}

bool PedraBasico::Is(std::string type) {
	return Being::Is(type) || type.compare("basico") == 0;
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

void PedraBasico::SetRockSprite(float speed) {
	sp->SetFrameHeight(25);
	sp->SetFrameWidth(35);
	sp->SetLine(2, 23);
	sp->SetFrameTime(speed);
}

void PedraBasico::SetJumpRockSprite() {
	sp->SetFrameWidth(35);
	sp->SetFrameHeight(50);
	sp->SetFrameCount(3);
	sp->SetLine(0, 50);
}

void PedraBasico::SetLimitY(float y) {
	limitY = y;
}

int PedraBasico::GetCurrentFrame() {
	return sp->GetCurrentFrame();
}
