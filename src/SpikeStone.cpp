/*
 * SpikeStone.cpp
 *
 *  Created on: 07/07/2015
 *      Author: Pedro2
 */

#include "SpikeStone.h"

SpikeStone::SpikeStone(int x, int y, int scale) {
	SetID(GameObject::SPIKE_STONE_BAON);

	sp = new Sprite("img/spikestone.png", 4, 0.1);
	sp->SetFrameWidth(38);
	sp->SetFrameHeight(50);
	sp->SetLine(0, 50);
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	this->scale = scale;

	b = new Body("spike", x, y);
	b->SetVelX(300);
	box.SetX(x);
	box.SetY(y);
	box.SetW(sp->GetFrameWidth());
	box.SetW(sp->GetFrameHeight());

	dead = false;
}

void SpikeStone::Update(float dt) {
	Physic::GetInstance()->UpdatePhysic(GetBody(), dt);
	box.SetX(GetBody()->GetX());
	box.SetY(GetBody()->GetY());
	box.SetW(sp->GetFrameWidth());
	box.SetH(sp->GetFrameWidth());

	if(sp->GetCurrentFrame() < 4){
		sp->Update(dt);
	}
}

void SpikeStone::Render() {
	sp->Render(GetBox().GetX() + Camera::pos.getX(), GetBox().GetY() + Camera::pos.getY(), 0, false);
}

void SpikeStone::NotifyCollision(GameObject* other) {

}

void SpikeStone::NotifyTileCollision() {
}

bool SpikeStone::IsDead() {
	return dead;
}

bool SpikeStone::Is(std::string type) {
	return type.compare("spike") == 0;
}
