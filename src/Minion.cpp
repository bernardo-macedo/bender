/*
 * Minion.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Pedro
 */

#include "Minion.h"
#include "Engine/Camera.h"
#include "Engine/InputManager.h"
#include "Engine/Physics/Physic.h"
#include <math.h>

#define PI 3.14
Minion::Minion(float x, float y) {
	sp = new Sprite("img/minion.png");
	b = new Body("teste", x, y);
	b->SetRotation(0);
	b->SetResistance(1.0);
	box.SetH(sp->GetHeight());
	box.SetW(sp->GetWidth());
	box.SetX(x);
	box.SetY(y);
	walkForceRight = 200;
	walkForceLeft = -200;
	b->ApplyForce(new Force("gravidade", 0, 400));
}

Minion::~Minion() {
}

void Minion::Update(float dt) {
	if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
		b->SetAngularAccel(-200);
		b->ApplyForce(new Force("direcao", walkForceLeft, 0));
	}
	if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
		b->SetAngularAccel(200);
		b->ApplyForce(new Force("direcao1", walkForceRight, 0));
	}
	if(InputManager::GetInstance().KeyRelease(LEFT_ARROW_KEY)){
		b->SetAngularAccel(0);
		b->removeForce("direcao");
	}
	if(InputManager::GetInstance().KeyRelease(RIGHT_ARROW_KEY)){
		b->SetAngularAccel(0);
		b->removeForce("direcao1");
	}

	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
		b->SetVelY(-300);
	}
	Physic::GetInstance()->UpdatePhysic(b, dt);
	box.SetX(b->GetX());
	box.SetY(b->GetY());
}

void Minion::Render() {
	sp->Render(box.GetX() - box.GetW()/2 - Camera::pos.getX(), box.GetY() - box.GetH()/2 - Camera::pos.getY(),b->GetRotation());
}

bool Minion::IsDead() {
	return false;
}

Body* Minion::GetBody() {
	return b;
}

void Minion::SetBody(Body* b) {
	this->b = b;
}

void Minion::Shoot() {
}
