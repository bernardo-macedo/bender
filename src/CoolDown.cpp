/*
 * CoolDown.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#include "CoolDown.h"

CoolDown::CoolDown(float x, float y, int scale) : currentFrame(1) {
	pos = Point(x,y);

	sp = Sprite("img/cooldown.png", 14);
	sp.SetScaleX(scale);
	sp.SetScaleY(scale);
}

CoolDown::~CoolDown() {
	// TODO Auto-generated destructor stub
}

void CoolDown::Update(float dt) {
	t.Update(dt);

	if (t.Get() > 0.5) {
		currentFrame = currentFrame >= 14 ? 1 : currentFrame + 1;
		sp.SetFrame(currentFrame);
		t.Restart();
	}
}

void CoolDown::Render() {
	sp.Render(pos.getX(), pos.getY(), 0);
}
