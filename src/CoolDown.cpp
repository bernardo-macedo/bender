/*
 * CoolDown.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#include "CoolDown.h"

CoolDown::CoolDown(float x, float y, int scale, bool enabled) : currentFrame(1) {
	pos = Point(x,y);

	sp = Sprite("img/cooldown.png", 14);
	sp.SetScaleX(scale);
	sp.SetScaleY(scale);

	SetEnabled(enabled);
}

CoolDown::~CoolDown() {
	// TODO Auto-generated destructor stub
}

void CoolDown::Update(float dt) {
	if (enabled) {
		t.Update(dt);

		if (t.Get() > 0.5) {
			currentFrame++;
			sp.SetFrame(currentFrame);
			t.Restart();
			if (currentFrame >= 14) {
				completed = true;
				currentFrame = 1;
			}
		}
	}
}

void CoolDown::Render() {
	sp.Render(pos.getX(), pos.getY(), 0);
}

void CoolDown::SetEnabled(bool enabled) {
	this->enabled = enabled;
	if (enabled) {
		sp.SetFrame(14);
	} else {
		sp.SetFrame(1);
	}
}

bool CoolDown::HasCompleted() {
	return completed;
}

void CoolDown::Restart() {
	completed = false;
}
