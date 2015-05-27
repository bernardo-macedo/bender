/*
 * StillAnimation.h
 *
 *  Created on: 19/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_STILLANIMATION_H_
#define ENGINE_STILLANIMATION_H_

#include "Timer.h"
#include "Sprite.h"
#include "GameObject.h"

class StillAnimation : public GameObject{
private:
	Timer *endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite* sp;
public:
	StillAnimation(float x, float y, float rotation, Sprite* sprite, float imeLimit, bool ends);
	void Update(float dt);
	bool IsDead();

	void NotifyCollision(GameObject* other);
	bool Is(std::string string);
	void Render();
};

#endif /* ENGINE_STILLANIMATION_H_ */
