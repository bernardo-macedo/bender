/*
 * BigRock.cpp
 *
 *  Created on: 13/07/2015
 *      Author: Pedro2
 */

#include "BigRock.h"

#include "Engine/Camera.h"
#include "Engine/Collision.h"
#include "Engine/Game.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Physics/Body.h"
#include "Engine/Physics/Physic.h"

BigRock::BigRock(int x, int y) {
	SetID(GameObject::BIG_ROCK);

	sp = new Sprite("img/bigrock.png", 5, 0.2);
	sp->SetFrameHeight(80);
	sp->SetFrameWidth(80);
	t = new Timer();
	dead = false;
	b = new Body("bigrock", x, y);
	finnishedLifting = false;
}

BigRock::~BigRock() {
	// TODO Auto-generated destructor stub
}

void BigRock::Update(float dt) {
	Physic::GetInstance()->UpdatePhysic(b, dt);
	box.SetX(b->GetX());
	box.SetY(b->GetY());
	if(sp->GetCurrentFrame() < 5){
		sp->Update(dt);
	}
	else{
		finnishedLifting = true;
		if(t->Get() < 0.2){
			t->Update(dt);
		}
		else{
			b->SetVelX(300);
			if(GetBody()->GetX() > Game::SCREEN_WIDTH - Camera::pos.getX()
					|| GetBody()->GetX() < 0  - Camera::pos.getX()){
				dead = true;
			}
		}
	}
}

bool BigRock::IsDead() {
	return dead;
}

void BigRock::Render() {
	sp->Render(GetBox().GetX() + Camera::pos.getX(), GetBox().GetY() + Camera::pos.getY(), 0, false);
}

void BigRock::NotifyCollision(GameObject* other) {
	if(other->GetID() == GameObject::ENEMY
			|| other->GetID() == GameObject::SWORD_ENEMY
			|| other->GetID() == GameObject::BIG_ENEMY){
	}
}

void BigRock::NotifyTileCollision(Collision::CollisionAxis collisionAxis) {
}

bool BigRock::Is(std::string type) {
	return false;
}

bool BigRock::finnished() {
	return finnishedLifting;
}
