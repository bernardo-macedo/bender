/*
 * ControleBend.cpp
 *
 *  Created on: 11/07/2015
 *      Author: Pedro2
 */

#include "ControleBend.h"

#include "Engine/Camera.h"
#include "Engine/Geometry/Point.h"

ControleBend::ControleBend(int x, int y, bool flipped) {
	SetID(GameObject::CONTROLE_BEND);

	sp = new Sprite("img/controle.png", 1, 0.01);
	t = new Timer();
	dead = false;
	this->flipped = flipped;

	sp->SetFrameWidth(80);
	sp->SetFrameHeight(80);
	sp->SetLine(0, 50);

	box.SetX(x);
	box.SetY(y);
	box.SetW(sp->GetFrameWidth());
	box.SetH(sp->GetFrameHeight());
}

ControleBend::~ControleBend(){
	delete t;
	delete sp;
}

void ControleBend::Update(float dt) {
	if(sp->GetFrameWidth() < 200){
		sp->SetFrameWidth(sp->GetFrameWidth() + 20);
		box.SetW(sp->GetFrameWidth());
		if (flipped){
			box.SetX(box.GetX() - 20);
		}
	}
	else{
		if(t->Get() < 0.4){
			t->Update(dt);
		}
		else{
			dead = true;
		}
	}
}

bool ControleBend::IsDead() {
	return dead;
}

void ControleBend::Render() {
	sp->Render(GetBox().GetX() + Camera::pos.getX(), GetBox().GetY() + Camera::pos.getY(), 0, false);
}

void ControleBend::NotifyCollision(GameObject* other) {
	std::cout << "colidiu com = " << other->GetID() << std::endl;
}

bool ControleBend::Is(std::string type) {
	return type.compare("Controle") == 0;
}
