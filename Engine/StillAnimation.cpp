/*
 * StillAnimation.cpp
 *
 *  Created on: 19/05/2015
 *      Author: Pedro2
 */

#include "StillAnimation.h"

#include <string>

#include "Camera.h"
#include "Geometry/Point.h"

StillAnimation::StillAnimation(float x, float y, float rotation, Sprite* sprite,
		float timeLimit, bool ends) {
	endTimer = new Timer();
	this->sp = sprite;
	box.SetX(x);
	box.SetY(y);
	box.SetH(sp->GetHeight());
	box.SetW(sp->GetWidth());
	oneTimeOnly = ends;
	this->timeLimit = timeLimit;
}

void StillAnimation::Update(float dt) {
	endTimer->Update(dt);
	sp->Update(dt);
}

bool StillAnimation::IsDead() {
	return oneTimeOnly && endTimer->Get() >= timeLimit;
}

void StillAnimation::NotifyCollision(GameObject* other) {
}

bool StillAnimation::Is(std::string string) {
	return string.compare("StillAnimation") == 0;
}

void StillAnimation::Render() {
	sp->Render(box.GetX() - sp->GetFrameWidth()/2 + Camera::pos.getX(), box.GetY() - sp->GetHeight()/2 + Camera::pos.getY(), 0);
}
