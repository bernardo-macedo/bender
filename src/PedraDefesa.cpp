/*
 * PedraDefesa.cpp
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#include "PedraDefesa.h"

#include "Engine/Camera.h"
#include "Engine/Geometry/Point.h"

PedraDefesa::PedraDefesa(int x, int y) {
	SetID(GameObject::PEDRA_DEFESA);
	t = new Timer();

	sp = new Sprite("img/defesa.png", 4, 0.1);
	sp->SetFrameHeight(100);
	sp->SetFrameWidth(60);
	sp->SetLine(0, 100);
	sp->SetScaleX(2);
	sp->SetScaleY(2);

	box.SetX(x);
	box.SetY(y);
	box.SetW(sp->GetFrameWidth());
	box.SetH(sp->GetFrameHeight());

	dead = false;
}

PedraDefesa::~PedraDefesa() {
	// TODO Auto-generated destructor stub
}

void PedraDefesa::Update(float dt) {
	if(sp->GetCurrentFrame() < 4){
		sp->Update(dt);
	}
	else{
		if(t->Get() < 3){
			t->Update(dt);
		}
		else{
			dead = true;
		}
	}
}

bool PedraDefesa::IsDead() {
	return dead;
}

void PedraDefesa::Render() {
	sp->Render(GetBox().GetX() + Camera::pos.getX(),
			GetBox().GetY() + Camera::pos.getY(), 0, false);
}

void PedraDefesa::NotifyCollision(GameObject* other) {
}

bool PedraDefesa::Is(std::string type) {
	return false;
}
