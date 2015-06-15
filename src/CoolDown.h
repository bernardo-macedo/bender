/*
 * CoolDown.h
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#ifndef COOLDOWN_H_
#define COOLDOWN_H_

#include "Engine/Timer.h"
#include "Engine/Sprite.h"
#include "Engine/Geometry/Point.h"

class CoolDown {
public:
	CoolDown(float x, float y, int scale);
	virtual ~CoolDown();

	void Update(float dt);
	void Render();
private:
	Timer t;
	Sprite sp;
	Point pos;
	int currentFrame;
};

#endif /* COOLDOWN_H_ */
