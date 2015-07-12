/*
 * ControleBend.h
 *
 *  Created on: 11/07/2015
 *      Author: Pedro2
 */

#ifndef CONTROLEBEND_H_
#define CONTROLEBEND_H_

#include <string>

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Timer.h"

class ControleBend : public GameObject{
public:
	ControleBend(int x, int y, bool flipped);
	virtual ~ControleBend();

	void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
private:
	Timer *t;
	Sprite *sp;
	bool dead, flipped;
};

#endif /* CONTROLEBEND_H_ */
