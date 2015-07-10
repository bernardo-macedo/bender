/*
 * SpikeStone.cpp
 *
 *  Created on: 07/07/2015
 *      Author: Pedro2
 */

#include "SpikeStone.h"

#include "Engine/Collision.h"
#include "Engine/Game.h"
#include "Engine/State.h"

SpikeStone::SpikeStone(int x, int y, int scale, bool flipped) {
	SetID(GameObject::SPIKE_STONE_BAON);
	this->flipped = flipped;

	sp = new Sprite("img/spikestone.png", 4, 0.001);
	sp->SetFrameWidth(38);
	sp->SetFrameHeight(50);
	sp->SetLine(0, 50);
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	this->scale = scale;

	if(flipped){
		transp = new TransparentGameObject(x - sp->GetFrameWidth()*10, y, sp->GetFrameWidth()*10, sp->GetFrameHeight(), false);
	}
	else{
		transp = new TransparentGameObject(x, y, sp->GetFrameWidth()*10, sp->GetFrameHeight(), true);
	}
	t = new Timer();

	b = new Body("spike", x, y);
	box.SetX(x);
	box.SetY(y);
	box.SetW(sp->GetFrameWidth());
	box.SetW(sp->GetFrameHeight());
	flipped = false;
	transpSet = false;

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
	else{
		if(!transpSet){
			Game::GetInstance()->GetCurrentState()->AddObject(transp);
			transpSet = true;
		}
		else{
			if(t->Get() < 0.5){
				t->Update(dt);
			}
			else{
				this->dead = true;
				transp->SetDead(true);
			}
		}
	}
}

void SpikeStone::Render() {
	sp->Render(GetBox().GetX() + Camera::pos.getX(), GetBox().GetY() + Camera::pos.getY(), 0, flipped);
}

void SpikeStone::NotifyCollision(GameObject* other) {

}

void SpikeStone::NotifyTileCollision(Collision::CollisionAxis collisionAxis) {
}

bool SpikeStone::IsDead() {
	return dead;
}

void SpikeStone::SetFlipped(bool flipped) {
	this->flipped = flipped;
}

bool SpikeStone::Is(std::string type) {
	return type.compare("spike") == 0;
}

bool SpikeStone::IsRight() {
	return right;
}
