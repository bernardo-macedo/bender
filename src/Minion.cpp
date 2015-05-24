/*
 * Minion.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Pedro
 */

#include "Minion.h"
#include "Engine/Camera.h"
#include <math.h>
#include "Engine/Game.h"
#include <stdlib.h>
#include <time.h>

#define PI 3.14
Minion::Minion(GameObject* minionCenter, float arcOffset) {
	sp = new Sprite("img/minion.png");
	this->center = minionCenter;
	arc = arcOffset;
	box.SetH(sp->GetHeight());
	box.SetW(sp->GetWidth());
	box.SetX(center->GetBox().GetX() + cos(arc)*150);
	box.SetY(center->GetBox().GetY() + sin(arc)*150);
	float dec = rand() % 51;
	sp->SetScaleX(1 + dec/100.0);
	sp->SetScaleY(1 + dec/100.0);
}

Minion::~Minion() {
}

void Minion::Update(float dt) {
	arc += (PI/3)*dt;
	rotation = arc*180/M_PI;
	box.SetX(center->GetBox().GetX() + cos(arc)*150);
	box.SetY(center->GetBox().GetY() + sin(arc)*150);
}

void Minion::Render() {
	sp->Render(box.GetX() - box.GetW()/2 + Camera::pos.getX(), box.GetY() - box.GetH()/2 + Camera::pos.getY(), rotation);
}

bool Minion::IsDead() {
	return false;
}

void Minion::Shoot(Point pos) {
	float dist = sqrt(pow(pos.getX() - box.GetX(),2) + pow(pos.getY() - box.GetY(),2));
	float ang = atan2(pos.getY() - box.GetY(), pos.getX() - box.GetX());
	Bullet *b = new Bullet(box.GetX(), box.GetY(), ang, 300, dist, "img/minionBullet2.png", true);
	Game::GetInstance()->GetCurrentState()->AddObject(b);
}

bool Minion::Is(std::string type) {
	return (type.compare("Minion") == 0);
}

void Minion::NotifyCollision(GameObject* other) {
}
